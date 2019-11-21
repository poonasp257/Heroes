using System;
using UnityEngine;

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
		public UInt64 characterId;
		public UInt16 characterClass;
		public UInt32 level;
		public string characterName;
		public string location;
		// 착용 중인 장비
	}

	public struct CharacterStatus {
		public Int64 hp;
		public Int64 mp;
		public Int64 exp;
		public Vector3 position;
		public Vector3 rotation;
	}
}