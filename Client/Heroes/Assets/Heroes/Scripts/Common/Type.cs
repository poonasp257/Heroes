using System;

namespace Heroes {
	public enum CharacterClass : UInt16 {
		Warrior,
		Archer,
		Assassin,
		Mage
	}

	public enum ActionType {
		WeakAttack, SmashAttack, Roll
	}

	public enum MessageType {
		Alert,
		Confirm,
		Notice
	}

	public struct ChanelInfo {
		public Int32 traffic;
		public string id;
	}

	public struct CharacterInfo {
		public UInt16 characterClass;
		public UInt32 level;
		public string characterName;
		public string location;
	}
}