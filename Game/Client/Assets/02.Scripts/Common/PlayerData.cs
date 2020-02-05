using System;

namespace Heroes {
	public class PlayerData {
		private static PlayerData instance = null;

		public static PlayerData Instance {
			get {
				if(instance == null) {
					instance = new PlayerData();
				}

				return instance;
			}
		}

		public ChannelInfo Channel { get; set; }
		public UInt64 AccountId { get; set; }
		public UInt64 CharacterId { get; set; }

		public PlayerData() {
			AccountId = 0;
			CharacterId = 0;
		}
	}
}