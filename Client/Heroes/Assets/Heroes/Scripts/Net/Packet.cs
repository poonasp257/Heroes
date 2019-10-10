using System.Runtime.InteropServices;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public abstract class Packet {
		protected PacketType type;
		public PacketType Type { get { return type; } }
		public abstract byte[] Serialize();
		public abstract void DeSerialize(byte[] bytes);
	}

	[StructLayout(LayoutKind.Sequential)]
	public class LoginAuthRequest : Packet {
		public string id;
		public string password;

		public LoginAuthRequest() {
			type = PacketType.PK_LOGIN_AUTH_REQ;
		}

		public override byte[] Serialize() {
			return new byte[1];
		}

		public override void DeSerialize(byte[] bytes) {

		}
	}

	[StructLayout(LayoutKind.Sequential)]
	public class LoginAuthAnswer : Packet {
		public bool result;

		public LoginAuthAnswer() {
			type = PacketType.PK_LOGIN_AUTH_ANS;
		}

		public override byte[] Serialize() {
			return new byte[1];
		}

		public override void DeSerialize(byte[] bytes) {

		}
	}
}