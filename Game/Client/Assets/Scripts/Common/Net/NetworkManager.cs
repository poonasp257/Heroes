using System;
using System.IO;
using System.Collections;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Threading;
using UnityEngine;
using System.Threading.Tasks;

namespace Heroes {
	public class NetworkManager : MonoBehaviour {
		private readonly object lockObject = new object();

		public delegate void Notifier(Packet rowPacket);
		private Dictionary<PacketType, Notifier> notifierMap;

		private Queue<Packet> sendPacketQueue;
		private Queue<Packet> receivePacketQueue;

		private Thread receiveWorker;
		private NetworkStream stream;
		private TcpClient client;

		private MessageBoxHandler messageBoxHandler = null;

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

			receiveWorker = null;
			stream = null;
			client = null;
		}

		private void Start() {
			var messageBoxHandlerObj = GameObject.Find("MessageBox Handler");
			messageBoxHandler = messageBoxHandlerObj?.GetComponent<MessageBoxHandler>();
			if (messageBoxHandler == null) throw new Exception("Message Box Handler not found");
		}

		private void Update() {
			if (IsConnected) return;
			
			if (!messageBoxHandler.IsOpened) {
				messageBoxHandler.alert("서버와 연결이 끊겼습니다.", () => SceneLoader.LoadLoginScene());
			}
		}

		private void OnDestroy() {
			if (IsConnected) this.disconnect();

			receiveWorker?.Join();
		}
				
		private void closeConnection() {
			client.Close();
			stream.Flush();
			stream.Close();
		}

		private IEnumerator ProcessSendPacketQueue() {
			MemoryStream packetStream = new MemoryStream();
			while (IsConnected) {
				yield return null;

				if (sendPacketQueue.Count == 0) continue;

				Packet packet = sendPacketQueue.Dequeue();
				Int32 packetLen = sizeof(Int32) + (Int32)(packet.getStream().Length);
				Byte[] packetHeader = BitConverter.GetBytes(packetLen);
				Byte[] packetData = packet.getStream().ToArray();
				packetStream.Write(packetHeader, 0, packetHeader.Length);
				packetStream.Write(packetData, 0, packetData.Length);

				Byte[] buffer = packetStream.ToArray();
				PacketObfuscator.encodeHeader(ref buffer);
				PacketObfuscator.encodeData(ref buffer, packetLen - sizeof(Int32));

				try {
					stream.Write(buffer, 0, buffer.Length);
					stream.Flush();
					packetStream.SetLength(0);
				} catch(Exception e) {
					Debug.Log(e.Message);
				}

				//Debug.Log("send "+packet.type());
			}
		}

		private IEnumerator ProcessReceivePacketQueue() {
			Packet packet = null;
			while (IsConnected) {
				yield return null;

				lock (lockObject) {
					if (receivePacketQueue.Count == 0) continue;

					packet = receivePacketQueue.Dequeue();
				}

				if (notifierMap.ContainsKey(packet.type())) {
					notifierMap[packet.type()](packet);
				}
			}
		}
	
		private void processReceivePacket() {
			Byte[] packetBytes = new Byte[client.ReceiveBufferSize];
			Byte[] remainPacket = new Byte[client.ReceiveBufferSize];
			while (IsConnected) {
				int offset = 0;
				int readLen = 0;
				try {
					readLen = stream.Read(packetBytes, offset, packetBytes.Length);
					if(readLen == 0) {
						this.closeConnection();
						break;
					}
				}
				catch(Exception err) {
					Debug.Log(err.Message);
					break;
				}

				PacketObfuscator.decodeHeader(ref packetBytes);
				Int32 packetLen = PacketAnalyzer.GetHeader(packetBytes, ref offset);

				while (readLen < packetLen) {
					Int32 remainLen = 0;
					remainLen = stream.Read(remainPacket, 0, remainPacket.Length);
					Buffer.BlockCopy(remainPacket, 0, packetBytes, readLen, remainLen);
					readLen += remainLen;
				}

				Int32 packetDataSize = packetLen - offset;
				Byte[] packetData = new byte[packetLen - offset];
				PacketObfuscator.decodeData(ref packetBytes, packetDataSize);
				Buffer.BlockCopy(packetBytes, offset, packetData, 0, packetDataSize);
				
				//Byte[] packetData = new byte[packetDataSize];
				//PacketObfuscator.decodeData(ref buffer, packetDataSize);
				//Buffer.BlockCopy(buffer, offset, packetData, 0, packetDataSize);

				Packet packet = PacketAnalyzer.AnalyzerPacket(packetData);
				if (packet == null) {
					Debug.Log("unidentified packet received...");
					continue;
				}
				
				lock (lockObject) {
					receivePacketQueue.Enqueue(packet);
				}

				//Debug.Log("recv "+packet.type());
			}
		}

		public void connectServer() {
			this.connect(ip, port);
		}

		public void connect(string ip, int port) {
			if (string.IsNullOrWhiteSpace(ip)) {
				throw new Exception("IP address is null or empty");
			}

			this.ip = ip;
			this.port = port;
			client = new TcpClient();

			try {
				Task result = client.ConnectAsync(ip, port);
				if(!result.Wait(TimeSpan.FromSeconds(10))) {
					messageBoxHandler?.alert("네트워크 상태가 원활하지 않습니다.");
					return;
				}
			} catch(Exception error) {
				Debug.Log(error.Message);
				messageBoxHandler?.alert("서버와 연결할 수 없었습니다.", () => SceneLoader.LoadLoginScene());
				return;
			}

			stream = client.GetStream();
			receiveWorker = new Thread(new ThreadStart(this.processReceivePacket));
			receiveWorker.Start();

			StartCoroutine(ProcessSendPacketQueue());
			StartCoroutine(ProcessReceivePacketQueue());
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
		
		public void registerNotification(PacketType type, Notifier notifier) {
			if (notifierMap == null ||
				notifierMap.ContainsKey(type)) return;

			this.notifierMap.Add(type, notifier);
		}

		public void unregisterNotification(PacketType type) {
			if (notifierMap == null ||
				!notifierMap.ContainsKey(type)) return;

			this.notifierMap.Remove(type);
		}
	}
}