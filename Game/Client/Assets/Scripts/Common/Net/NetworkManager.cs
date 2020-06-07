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
			if (IsConnected) this.disconnect();

			receiveWorker.Join();
		}

		private void Update() {
			if(!IsConnected && retryConnectCoroutine == null) {
				retryConnectCoroutine = StartCoroutine(TryConnect());
			}
		}
		
		private void closeConnection() {
			client.Close();
			stream.Flush();
			stream.Close();
		}

		private IEnumerator ProcessSendPacketQueue() {
			MemoryStream packetStream = new MemoryStream();
			
			while (true) {
				yield return null;

				if (sendPacketQueue.Count == 0 || !IsConnected) {
					continue;
				}

				Packet packet = sendPacketQueue.Dequeue();
				Int32 packetLen = sizeof(Int32) + (Int32)(packet.getStream().Length);
				Byte[] packetHeader = BitConverter.GetBytes(packetLen);
				Byte[] packetData = packet.getStream().ToArray();
				packetStream.Write(packetHeader, 0, packetHeader.Length);
				packetStream.Write(packetData, 0, packetData.Length);

				Byte[] buffer = packetStream.ToArray();
				PacketObfuscator.encodeHeader(ref buffer);
				PacketObfuscator.encodeData(ref buffer, packetLen - sizeof(Int32));

				stream.Write(buffer, 0, buffer.Length);
				stream.Flush();
				packetStream.SetLength(0);

				Debug.Log("send packet: " + packet.type());
			}
		}

		private IEnumerator ProcessReceivePacketQueue() {
			while(true) {
				yield return null;
				if (receivePacketQueue.Count == 0 || !IsConnected) { 
					continue;
				}
				
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
					if(readLen == 0) {
						Debug.Log("Connected server is stopped...");
						this.closeConnection();
						break;
					}
				}
				catch(Exception err) {
					Debug.Log(err);
					break;
				}

				PacketObfuscator.decodeHeader(ref buffer);
				Int32 packetLen = PacketAnalyzer.GetHeader(buffer, ref offset);

				Int32 packetDataSize = packetLen - offset;
				Byte[] packetData = new Byte[packetDataSize];
				PacketObfuscator.decodeData(ref buffer, packetDataSize);
				Buffer.BlockCopy(buffer, offset, packetData, 0, packetDataSize);

				Packet packet = PacketAnalyzer.AnalyzerPacket(packetData);
				if (packet == null) {
					Debug.Log("unidentified packet received...");
					continue;
				}
				
				lock (lockObject) {
					receivePacketQueue.Enqueue(packet);
				}

				Debug.Log("received packet: " + packet.type());
			}
		}

		public void connect(string ip, int port) {
			if (string.IsNullOrWhiteSpace(ip)) {
				throw new Exception("IP address is null or empty");
			}
			
			try {
				this.ip = ip;
				this.port = port;

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
			this.closeConnection();

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