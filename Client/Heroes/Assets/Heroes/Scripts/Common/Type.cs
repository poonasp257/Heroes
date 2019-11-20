using System;

namespace Heroes {
	public enum CharacterClass {
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

	public struct ChanelStatus {
		public Int32 traffic;
		public string id;
	}

	public struct CharacterStatus {
		
	}
}