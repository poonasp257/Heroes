using System;
using System.IO;
using System.Collections;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Threading;
using UnityEngine;

namespace Heroes {
	public class NetworkManager : MonoBehaviour {
		private enum NetState {
			Stopped,
			Connected,
			Disconnected
		}

		private readonly object lockObject = new object();

		public delegate void Notifier(PacketType type, Packet rowPacket);
		private Dictionary<PacketType, Notifier> notifierMap;

		private Queue<Packet> receviePacketQueue;

		private Coroutine retryConnectCoroutine;
		private const float retryInterval = 5.0f;

		private Thread receiveWorker;
		private NetworkStream stream;
		private TcpClient client;
		private NetState state;

		private MessageBoxHandler messageBoxHandler;

		[SerializeField] private string ip = "127.0.0.1";
		[SerializeField] private int port = 0;

		private bool IsConnected { get { return state == NetState.Connected; } }

		private void Awake() {
			notifierMap = new Dictionary<PacketType, Notifier>();
			receviePacketQueue = new Queue<Packet>();

			retryConnectCoroutine = null;

			receiveWorker = null;
			stream = null;
			client = null;
			state = NetState.Stopped;
		}

		private void Start() {
			this.connect(ip, port);

			var handlerObject = GameObject.Find("MessageBox Handler");
			if (handlerObject) messageBoxHandler = handlerObject.GetComponent<MessageBoxHandler>();

			DontDestroyOnLoad(this.gameObject);
		}

		private void OnDestroy() {
			if(IsConnected) this.disconnect();

			receiveWorker.Join();
		}

		private void Update() {
			if(!IsConnected && retryConnectCoroutine == null) {
				retryConnectCoroutine = StartCoroutine(RetryConnect());
			}

			if(receviePacketQueue.Count != 0) {
				ProcessPacket();
			}
		}
		
		private void connect(string ip, int port) {
			if (string.IsNullOrWhiteSpace(ip)) {
				throw new Exception("IP address is null or empty");
			}

			try {
				client = new TcpClient();
				client.Connect(ip, port);
			}
			catch (Exception err) {
				Debug.Log(err);
				return;
			}

			receiveWorker = new Thread(new ThreadStart(this.receivePacket));
			receiveWorker.Start();
			stream = client.GetStream();

			state = NetState.Connected;
		}

		private void disconnect() {
			this.close();

			ExitRequestPacket packet = new ExitRequestPacket();
			this.sendPacket(packet);
		}

		private void close() {
			client.Close();
			stream.Close();
			stream.Flush();

			state = NetState.Stopped;
		}

		private void ProcessPacket() {
			Packet packet = null;
			lock(lockObject) {
				packet = receviePacketQueue.Dequeue();
			}

			if (notifierMap.ContainsKey(packet.type())) {
				notifierMap[packet.type()](packet.type(), packet);
			}
		}
	
		private IEnumerator RetryConnect() {
			messageBoxHandler.notice("재접속 시도중입니다.");

			while (!IsConnected) {
				this.connect(ip, port);

				yield return new WaitForSeconds(retryInterval);
			}

			messageBoxHandler.close();
			retryConnectCoroutine = null;
		}

		public void sendPacket(Packet packet) {
			if (!IsConnected) return;

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
		}

		// receive thread
		public void receivePacket() {
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
					receviePacketQueue.Enqueue(packet);
				}
			}

			this.close();
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