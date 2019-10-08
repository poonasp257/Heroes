using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public abstract class Packet {
		protected PacketType type;
		public abstract void Serialize();
		public abstract void DeSerialize();
	}

	public class LoginAuthRequest : Packet {
		public LoginAuthRequest() {
			type = PacketType.PK_LOGIN_AUTH_REQ;
		}

		public override void Serialize() {

		}

		public override void DeSerialize() {

		}
	}

	public class LoginAuthAnswer : Packet {
		public LoginAuthAnswer()
		{
			type = PacketType.PK_LOGIN_AUTH_ANS;
		}

		public override void Serialize()
		{

		}

		public override void DeSerialize()
		{

		}
	}
}