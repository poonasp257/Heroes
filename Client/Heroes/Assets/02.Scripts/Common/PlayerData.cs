using System;

namespace Heroes {
	public class PlayerData {
		private static PlayerData instance = null;

		private UInt16 channelId;
		private UInt64 accountId;
		private UInt64 characterId;
		private CharacterInfo characterInfo;

		public static PlayerData Instance {
			get {
				if(instance == null) {
					instance = new PlayerData();
				}

				return instance;
			}
		}

		public UInt16 ChannelId {
			get {
				return channelId;
			}
			set {
				channelId = value;
			}
		}

		public UInt64 AccountId {
			get {
				return accountId;
			}
			set {
				accountId = value;
			}
		}

		public UInt64 CharacterId {
			get {
				return characterId;
			}
			set {
				characterId = value;
			}
		}

		public PlayerData() {
			accountId = 0;
			channelId = 0;
			characterId = 0;
		}
	}
}