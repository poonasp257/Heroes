using System;
using System.IO;
using System.Collections;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Threading;
using UnityEngine;

namespace Heroes {
	public class NetworkManager : MonoBehaviour {
		private readonly object lockObject = new object();

		public delegate void Notifier(PacketType type, Packet rowPacket);
		private Dictionary<PacketType, Notifier> notifierMap;

		private Queue<Packet> sendPacketQueue;
		private Queue<Packet> receivePacketQueue;

		private Coroutine retryConnectCoroutine;
		private const float retryInterval = 3.0f;

		private Thread receiveWorker;
		private NetworkStream stream;
		private TcpClient client;

		[SerializeField] private string ip = "127.0.0.1";
		[SerializeField] private int port = 0;

		private bool IsConnected { 
			get {
				if (client == null) return false;

				return client.Connected; 
			} 
		}

		private void Awake() {
			notifierMap = new Dictionary<PacketType, Notifier>();
			sendPacketQueue = new Queue<Packet>();
			receivePacketQueue = new Queue<Packet>();

			retryConnectCoroutine = null;

			receiveWorker = null;
			stream = null;
			client = null;
		}

		private void Start() {
			StartCoroutine(ProcessSendPacketQueue());
			StartCoroutine(ProcessReceivePacketQueue());
		}

		private void OnDestroy() {
			if(IsConnected) this.disconnect();

			receiveWorker.Join();
		}

		private void Update() {
			if(!IsConnected && retryConnectCoroutine == null) {
				retryConnectCoroutine = StartCoroutine(TryConnect());
			}
		}
		
		private void close() {
			client.Close();
			stream.Close();
			stream.Flush();
		}

		private IEnumerator ProcessSendPacketQueue() {
			while(true) {
				yield return null;

				if (sendPacketQueue.Count == 0 || !IsConnected) continue;

				Packet packet = sendPacketQueue.Dequeue();

				MemoryStream packetStream = new MemoryStream();
				Int32 packetLen = sizeof(Int32) + (Int32)(packet.getStream().Length);

				Byte[] packetHeader = BitConverter.GetBytes(packetLen);
				packetStream.Write(packetHeader, 0, packetHeader.Length);

				Byte[] packetData = packet.getStream().ToArray();
				packetStream.Write(packetData, 0, packetData.Length);

				Byte[] buffer = packetStream.ToArray();
				stream.Write(buffer, 0, buffer.Length);
				stream.Flush();
			}
		}

		private IEnumerator ProcessReceivePacketQueue() {
			while(true) {
				yield return null;

				if (receivePacketQueue.Count == 0 || !IsConnected) continue;

				Packet packet = null;
				lock(lockObject) {
					packet = receivePacketQueue.Dequeue();
				}

				if (notifierMap.ContainsKey(packet.type())) {
					notifierMap[packet.type()](packet.type(), packet);
				}
			}
		}
	
		private IEnumerator TryConnect() {
			while (!IsConnected) {
				this.connect(ip, port);

				yield return new WaitForSeconds(retryInterval);
			}

			retryConnectCoroutine = null;
		}

		// receive thread
		private void processReceivePacket() {
			Byte[] buffer = new Byte[client.ReceiveBufferSize];

			while (IsConnected) {
				int offset = 0;
				int readLen = 0;

				try { 
					readLen = stream.Read(buffer, offset, buffer.Length);
				}
				catch(Exception err) {
					Debug.Log(err);
					break;
				}

				Int32 packetLen = PacketUtil.GetHeader(buffer, ref offset); 	
				Byte[] packetData = new Byte[packetLen];
				Buffer.BlockCopy(buffer, offset, packetData, 0, packetLen);

				Packet packet = PacketUtil.AnalyzerPacket(packetData);
				if (packet == null) {
					Debug.Log("unidentified packet received...");
					continue;
				}

				lock (lockObject) {
					receivePacketQueue.Enqueue(packet);
				}
			}
		}

		public void connect(string ip, int port) {
			if (string.IsNullOrWhiteSpace(ip)) {
				throw new Exception("IP address is null or empty");
			}

			this.ip = ip;
			this.port = port;
			
			try {
				client = new TcpClient();
				client.Connect(ip, port);
			}
			catch (Exception err) {
				Debug.Log(err);
				return;
			}

			receiveWorker = new Thread(new ThreadStart(this.processReceivePacket));
			receiveWorker.Start();
			stream = client.GetStream();
		}

		public void disconnect() {
			this.close();

			ExitRequestPacket packet = new ExitRequestPacket();
			this.sendPacket(packet);
		}

		public void sendPacket(Packet packet) {
			packet.serialize();
			sendPacketQueue.Enqueue(packet);
		}
		
		public void RegisterNotification(PacketType type, Notifier notifier) {
			if (notifierMap.ContainsKey(type)) return;

			this.notifierMap.Add(type, notifier);
		}

		public void UnregisterNotification(PacketType type) {
			if(notifierMap.ContainsKey(type)) {
				notifierMap.Remove(type);
			}
		}
	}
}