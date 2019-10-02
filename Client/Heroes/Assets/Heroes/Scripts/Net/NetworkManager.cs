using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class NetworkManager : MonoBehaviour {
		private int port;
		private IPAddress ipAddress;
		private IPEndPoint remoteEP;
		protected Socket socket;

		private void Start() {
			Initialize();
		}

		private void Update() {

		}

		private void Initialize() {
			ipAddress = IPAddress.Parse("127.0.0.1");

			remoteEP = new IPEndPoint(ipAddress, 9000);
			socket = new Socket(AddressFamily.InterNetwork,
				SocketType.Stream, ProtocolType.Tcp);
		}

		public void Connect() {
			socket.Connect(remoteEP);
		}

		public void DisConnect() {
			socket.Shutdown(SocketShutdown.Both);
			socket.Close();
		}

		public void Send(byte[] data) {
			socket.Send(data);
		}

		public byte[] Recieve() {
			byte[] buffer = new byte[1024];
			socket.Receive(buffer);

			return buffer;
		}
	}
}