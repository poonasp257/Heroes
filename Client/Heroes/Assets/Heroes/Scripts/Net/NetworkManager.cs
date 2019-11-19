using System;
using System.IO;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Threading;
using UnityEngine;

namespace Heroes {
	public class NetworkManager : MonoBehaviour {
		private enum NetState {
			Started,
			Connected,
			Disconnected,
			Stopped
		}

		private readonly object lockObject = new object();

		public delegate void Notifier(PacketType type, Packet rowPacket);
		private Dictionary<PacketType, Notifier> notifierMap;

		private Queue<Packet> packetQueue;

		private Thread receiveWorker;
		private NetworkStream stream;
		private TcpClient client;
		private NetState state;

		private void Awake() {
			notifierMap = new Dictionary<PacketType, Notifier>();
			packetQueue = new Queue<Packet>();

			receiveWorker = null;
			stream = null;
			client = null;

			state = NetState.Started;

			DontDestroyOnLoad(this.gameObject);
		}

		private void Start() {
			this.connect("127.0.0.1", 9000); // Connect Relay Server
		}

		private void Update() {
			if (!isConnected()) return;
	
			PacketProcess();
		}

		private void OnDestroy() {
			this.disConnect();
		}

		private void PacketProcess() {
			if (packetQueue.Count == 0) return;

			Packet packet = null;
			lock(lockObject) {
				packet = packetQueue.Dequeue();
			}
			notifierMap[packet.type()](packet.type(), packet);
		}

		private void close() {
			notifierMap.Clear();
			packetQueue.Clear();

			client.Close();
			stream.Close();
			stream.Flush();
			receiveWorker.Abort();

			client = null;
			stream = null;
			receiveWorker = null;

			notifierMap = null;

			state = NetState.Stopped;
		}

		private bool isConnected() {
			return state == NetState.Connected;
		}

		public bool connect(string ip, uint port) {
			if (string.IsNullOrWhiteSpace(ip)) {
				Debug.Log("IP address is null or empty");
				return false;
			}

			if (isConnected()) this.close();

			try { 
				client = new TcpClient();
				client.Connect(ip, Convert.ToInt32(port));
			}
			catch (Exception err) {
				Debug.Log(err);
				return false;
			}

			receiveWorker = new Thread(new ThreadStart(recieve));
			receiveWorker.Start();

			stream = client.GetStream();

			state = NetState.Connected;

			return true;
		}

		public void disConnect() {
			if (!isConnected()) return;

			state = NetState.Disconnected;

			ExitRequestPacket packet = new ExitRequestPacket();
			this.send(packet);
		}

		public void send(Packet packet) {
			if (!isConnected()) return;

			packet.serialize();

			MemoryStream packetStream = new MemoryStream(); 
			Int32 packetLen = sizeof(Int32) + (Int32)(packet.getStream().Length);

			Byte[] packetHeader = BitConverter.GetBytes(packetLen);
			packetStream.Write(packetHeader, 0, packetHeader.Length);

			Byte[] packetData = packet.getStream().ToArray();
			packetStream.Write(packetData, 0, packetData.Length);

			Byte[] buffer = packetStream.ToArray();
			stream.Write(buffer, 0, buffer.Length);
			stream.Flush();

			Debug.Log("buffer length: " + buffer.Length);
		}

		// receive thread
		public void recieve() {
			while (isConnected()) {
				Byte[] buffer = new Byte[client.ReceiveBufferSize];

				int offset = 0;
				int readLen = stream.Read(buffer, offset, buffer.Length);

				Int32 packetLen = PacketUtil.GetHeader(buffer, ref offset); 				
				while (readLen < packetLen) {
					readLen += stream.Read(buffer, offset, buffer.Length - readLen);
				}

				Byte[] packetData = new Byte[packetLen];
				Buffer.BlockCopy(buffer, offset, packetData, 0, packetLen);

				Packet packet = PacketUtil.AnalyzerPacket(packetData);
				if (packet == null && isConnected()) {
					Debug.Log("unidentified packet received...");
					continue;
				}

				lock (lockObject) {
					packetQueue.Enqueue(packet);
				}
			}

			this.close();
		}

		public void RegisterNotification(PacketType type, Notifier notifier) {
			this.notifierMap.Add(type, notifier);
		}

		public void UnregisterNotification(PacketType type) {
			if(notifierMap.ContainsKey(type)) {
				notifierMap.Remove(type);
			}
		}

		public void ClearNotification() {
			notifierMap.Clear();
		}
	}
}