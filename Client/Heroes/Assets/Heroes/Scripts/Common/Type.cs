﻿using System;
using UnityEngine;

namespace Heroes {
	public enum CharacterClass : UInt16 {
		Warrior,
		Archer,
		Assassin,
		Mage
	}

	public enum ActionType : UInt16 {
		WeakAttack, SmashAttack, Roll
	}

	public enum MessageType {
		Alert,
		Confirm,
		Notice
	}

	public struct ChanelInfo {
		public UInt16 id;
		public Int32 traffic;
		public string name;
	}

	public struct CharacterInfo {
		public UInt64 characterId;
		public UInt32 level;
		public Int64 hp;
		public Int64 mp;
		public Int64 exp;
		public Vector3 position;
		public Vector3 rotation;
		public CharacterClass characterClass;
		public string familyName;
		public string characterName;
		public string location;
		// 착용 중인 장비
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

	public struct CharacterAction {
		public ActionType type;
	}
}