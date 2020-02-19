using System;
using UnityEngine;

namespace Heroes {
	public enum CharacterClass : UInt16 {
		None,
		Warrior,
		Crusader,
		Archer,
		Assassin,
		Wizard,
		Elementalist
	}

	public enum ActionType : UInt16 {
		WeakAttack, SmashAttack, Roll
	}

	public enum ErrorCode : Byte {
		Success,
		Fail,
		BadRequest,
		Unauthorized,
		Conflict
	}
	
	public enum MessageType {
		Alert,
		Confirm,
		Notice
	}

	public struct ChannelInfo {
		public string name;
		public string ip;
		public UInt16 port;
	}

	public struct CharacterInfo {
		public UInt64 characterId;
		public string characterName;
		public CharacterClass characterClass;
		public UInt32 level;
		public float exp;
		public Int64 currentHp;
		public Int64 currentMp;
		public Int64 maxHp;
		public Int64 maxMp;
		public Vector3 position;
		public Vector3 rotation;
		public string location;
		// 착용 중인 장비
	}

	public struct PlayerInfo {
		public UInt64 accountId;
		public string familyName;
		public CharacterInfo characterInfo;
	}

	public struct CharacterMovement {
		public float moveAmount;
		public Vector3 position;
		public Vector3 rotation;

		public CharacterMovement(float moveAmount, Vector3 position, Vector3 rotation) {
			this.moveAmount = moveAmount;
			this.position = position;
			this.rotation = rotation;
		}
	}
}