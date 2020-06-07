using System;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public enum CharacterClassType : UInt16 {
		None,
		Warrior,
		Crusader,
		Archer,
		Assassin,
		Wizard,
		Elementalist
	}

	public enum ActionType : UInt16 {
		Roll,
		Attack,
		Hit,
		Die,
		Revive
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

	[Serializable]
	public struct Cell {
		public Vector3 position;
		public CellType type;

		public Cell(Vector3 position, CellType type) {
			this.position = position;
			this.type = type;
		}
	}

	[Serializable]
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
		public UInt64 id;
		public string name;
		public CharacterClassType type;
		public UInt32 level;
		public float exp;
		public Int64 currentHp;
		public Int64 currentMp;
		public Int64 maxHp;
		public Int64 maxMp;
		public Int64 defense;
		public UInt64 damage;
		public Vector3 position;
		public Vector3 rotation;
		public string location;
	}

	public struct PlayerInfo {
		public UInt64 id;
		public string familyName;
		public CharacterInfo characterInfo;
	}

	public struct CharacterMovement {
		public float moveAmount;
		public Vector3 direction;
		public Vector3 position;

		public CharacterMovement(float moveAmount, Vector3 direction, Vector3 position) {
			this.moveAmount = moveAmount;
			this.direction = direction;
			this.position = position;
		}
	}

	public struct MonsterInfo {
		public UInt64 id;
		public UInt64 typeId;
		public string name;
		public UInt32 level;
		public Int64 currentHp;
		public Int64 maxHp;
		public UInt32 damage;
		public UInt32 defense;
		public Vector3 position;
		public Vector3 rotation;
		public Vector3 originPosition;
		public Vector3 originRotation;
	};

	public struct MonsterZoneInfo {
		public UInt64 id;
		public Vector3 position;
		public List<MonsterInfo> monsterList;
	};
}