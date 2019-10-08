using System;
using System.Runtime.InteropServices;
using System.Net.Sockets;
using System.Net;

namespace Heroes {
	public class NetworkManager {
		private readonly IPAddress ipAddress;
		private readonly IPEndPoint remoteEP;
		private Socket socket;

		public NetworkManager(int port, string ip) {
			ipAddress = IPAddress.Parse(ip);
			remoteEP = new IPEndPoint(ipAddress, port);
		}

		public void CreateTCPSocket()
		{
			socket = new Socket(AddressFamily.InterNetwork,
				SocketType.Stream, ProtocolType.Tcp);
		}

		public void CreateUDPSocket() {
			socket = new Socket(AddressFamily.InterNetwork,
				SocketType.Dgram, ProtocolType.Udp);
		}

		public void Connect() {
			socket.Connect(remoteEP);
		}

		public void DisConnect() {
			socket.Shutdown(SocketShutdown.Both);
			socket.Close();
		}

		public void Send(byte[] outBuffer) {
			socket.Send(outBuffer);
		}

		public void Recieve(byte[] inBuffer) {
			socket.Receive(inBuffer);
		}
	}
}