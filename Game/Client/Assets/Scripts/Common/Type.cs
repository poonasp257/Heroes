using System;
using UnityEngine;
using Newtonsoft.Json;

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

	public enum StatusCode : Byte {
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

	public enum CellType {
		Ground, NotGround
	}

	public class Cell {
		public Vector3 position;
		public CellType type;

		public Cell() {
			this.position = Vector3.zero;
			this.type = CellType.NotGround;
		}

		public Cell(Vector3 position, CellType type) {
			this.position = position;
			this.type = type;
		}
	}

	public struct WorldMapData {
		public Vector3 center;
		public int height;
		public int width;
		public int row;
		public int column;
		public float cellSize;
		public Cell[] map;
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