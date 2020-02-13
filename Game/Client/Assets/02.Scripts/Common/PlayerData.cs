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

		public UInt64 AccountId { get; set; }
		public ChannelInfo CurrentChannel { get; set; }
		public CharacterInfo CurrentCharacter { get; set; }
		public string FamilyName { get; set; }
	}
}