using System;
using System.IO;
using System.Text;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public static class Serializer {
		public static void serialize(MemoryStream stream, PacketType type) {
			serialize(stream, (UInt32)type);
		}

		public static void serialize(MemoryStream stream, CharacterClass type) {
			serialize(stream, (UInt16)type);
		}

		public static void serialize(MemoryStream stream, ActionType type) {
			serialize(stream, (UInt16)type);
		}

		public static void serialize(MemoryStream stream, bool value) {
			stream.Write(BitConverter.GetBytes(value), 0, sizeof(bool));
		}

		public static void serialize(MemoryStream stream, Byte value) {
			stream.Write(BitConverter.GetBytes(value), 0, sizeof(Byte));
		}

		public static void serialize(MemoryStream stream, Char value) {
			stream.Write(BitConverter.GetBytes(value), 0, sizeof(Char));
		}

		public static void serialize(MemoryStream stream, Int16 value) {
			stream.Write(BitConverter.GetBytes(value), 0, sizeof(Int16));
		}

		public static void serialize(MemoryStream stream, UInt16 value) {
			stream.Write(BitConverter.GetBytes(value), 0, sizeof(UInt16));
		}

		public static void serialize(MemoryStream stream, float value) {
			stream.Write(BitConverter.GetBytes(value), 0, sizeof(float));
		}

		public static void serialize(MemoryStream stream, Int32 value) {
			stream.Write(BitConverter.GetBytes(value), 0, sizeof(Int32));
		}

		public static void serialize(MemoryStream stream, UInt32 value) {
			stream.Write(BitConverter.GetBytes(value), 0, sizeof(UInt32));
		}

		public static void serialize(MemoryStream stream, Int64 value) {
			stream.Write(BitConverter.GetBytes(value), 0, sizeof(Int64));
		}

		public static void serialize(MemoryStream stream, UInt64 value) {
			stream.Write(BitConverter.GetBytes(value), 0, sizeof(UInt64));
		}

		public static void serialize(MemoryStream stream, string str) {
			byte[] bytes = Encoding.Unicode.GetBytes(str);

			serialize(stream, str.Length);
			stream.Write(bytes, 0, bytes.Length);
		}

		public static void serialize(MemoryStream stream, Vector3 value) {
			serialize(stream, value.x);
			serialize(stream, value.y);
			serialize(stream, value.z);
		}

		public static void serialize(MemoryStream stream, ChannelInfo value) {
			serialize(stream, value.name);
			serialize(stream, value.ip);
			serialize(stream, value.port);
		}

		public static void serialize(MemoryStream stream, CharacterInfo value) {
			serialize(stream, value.characterId);
			serialize(stream, value.characterName);
			serialize(stream, value.characterClass);
			serialize(stream, value.level);
			serialize(stream, value.exp);
			serialize(stream, value.currentHp);
			serialize(stream, value.currentMp);
			serialize(stream, value.maxHp);
			serialize(stream, value.maxMp);
			serialize(stream, value.position);
			serialize(stream, value.rotation);
			serialize(stream, value.location);
		}

		public static void serialize(MemoryStream stream, CharacterMovement value) {
			serialize(stream, value.moveAmount);
			serialize(stream, value.position);
			serialize(stream, value.rotation);
		}

		public static void serialize(MemoryStream stream, PlayerInfo value) {
			serialize(stream, value.accountId);
			serialize(stream, value.familyName);
			serialize(stream, value.characterInfo);
		}

		public static void serialize(MemoryStream stream, List<ChannelInfo> list) {
			serialize(stream, list.Count);
			foreach(ChannelInfo value in list) {
				serialize(stream, value);
			}
		}

		public static void serialize(MemoryStream stream, List<CharacterInfo> list) {
			serialize(stream, list.Count);
			foreach(CharacterInfo value in list) {
				serialize(stream, value);
			}
		}

		public static void serialize(MemoryStream stream, Dictionary<UInt64, CharacterInfo> table) {
			serialize(stream, table.Count);
			foreach(var pair in table) {
				serialize(stream, pair.Key);
				serialize(stream, pair.Value);
			}
		}
			   
		public static void deserialize(byte[] data, ref Int32 offset, out CharacterClass type) {
			UInt16 value = BitConverter.ToUInt16(data, offset);
			type = (CharacterClass)value;
			offset += sizeof(UInt16);
		}

		public static void deserialize(byte[] data, ref Int32 offset, out ActionType type) {
			UInt16 value = BitConverter.ToUInt16(data, offset);
			type = (ActionType)value;
			offset += sizeof(UInt16);
		}
		
		public static void deserialize(byte[] data, ref Int32 offset, out bool value) {
			value = BitConverter.ToBoolean(data, offset); 
			offset += sizeof(bool);
		}

		public static void deserialize(byte[] data, ref Int32 offset, out Byte value) {
			value = data[offset];
			offset += sizeof(Byte);
		}

		public static void deserialize(byte[] data, ref Int32 offset, out Char value) {
			value = BitConverter.ToChar(data, offset);
			offset += sizeof(Char);
		}

		public static void deserialize(byte[] data, ref Int32 offset, out Int16 value) {
			value = BitConverter.ToInt16(data, offset);
			offset += sizeof(Int16);
		}

		public static void deserialize(byte[] data, ref Int32 offset, out UInt16 value) {
			value = BitConverter.ToUInt16(data, offset);
			offset += sizeof(UInt16);
		}

		public static void  deserialize(byte[] data, ref Int32 offset, out float value) {
			value = BitConverter.ToSingle(data, offset);
			offset += sizeof(float);
		}

		public static void deserialize(byte[] data, ref Int32 offset, out Int32 value) {
			value = BitConverter.ToInt32(data, offset);
			offset += sizeof(Int32);
		}

		public static void deserialize(byte[] data, ref Int32 offset, out UInt32 value) {
			value = BitConverter.ToUInt32(data, offset);
			offset += sizeof(UInt32);
		}

		public static void deserialize(byte[] data, ref Int32 offset, out Int64 value) {
			value = BitConverter.ToInt64(data, offset);
			offset += sizeof(Int64);
		}

		public static void deserialize(byte[] data, ref Int32 offset, out UInt64 value) {
			value = BitConverter.ToUInt64(data, offset);
			offset += sizeof(UInt64);
		}

		public static void deserialize(byte[] data, ref Int32 offset, out string value) {
			Int32 strLen;
			deserialize(data, ref offset, out strLen);

			Int32 size = strLen * sizeof(char);
			value = Encoding.Unicode.GetString(data, offset, size);
			offset += size;
		}

		public static void deserialize(byte[] data, ref Int32 offset, out Vector3 value) {
			deserialize(data, ref offset, out value.x);
			deserialize(data, ref offset, out value.y);
			deserialize(data, ref offset, out value.z);
		}

		public static void deserialize(byte[] data, ref Int32 offset, out ChannelInfo value) {
			deserialize(data, ref offset, out value.name);
			deserialize(data, ref offset, out value.ip);
			deserialize(data, ref offset, out value.port);
		}

		public static void deserialize(byte[] data, ref Int32 offset, out CharacterInfo value) {
			deserialize(data, ref offset, out value.characterId);
			deserialize(data, ref offset, out value.characterName);
			deserialize(data, ref offset, out value.characterClass);
			deserialize(data, ref offset, out value.level);
			deserialize(data, ref offset, out value.exp);
			deserialize(data, ref offset, out value.currentHp);
			deserialize(data, ref offset, out value.currentMp);
			deserialize(data, ref offset, out value.maxHp);
			deserialize(data, ref offset, out value.maxMp);
			deserialize(data, ref offset, out value.position);
			deserialize(data, ref offset, out value.rotation);
			deserialize(data, ref offset, out value.location);
		}
				
		public static void deserialize(byte[] data, ref Int32 offset, out PlayerInfo value) {
			deserialize(data, ref offset, out value.accountId);
			deserialize(data, ref offset, out value.familyName);
			deserialize(data, ref offset, out value.characterInfo);
		}

		public static void deserialize(byte[] data, ref Int32 offset, out CharacterMovement value) {
			deserialize(data, ref offset, out value.moveAmount);
			deserialize(data, ref offset, out value.position);
			deserialize(data, ref offset, out value.rotation);
		}
		
		public static void deserialize(byte[] data, ref Int32 offset, ref List<ChannelInfo> list) {
			Int32 size;
			deserialize(data, ref offset, out size);

			ChannelInfo value;
			for(int i = 0; i < size; ++i) {
				deserialize(data, ref offset, out value);
				list.Add(value);
			}
		} 

		public static void deserialize(byte[] data, ref Int32 offset, ref List<CharacterInfo> list) {
			Int32 size;
			deserialize(data, ref offset, out size);

			CharacterInfo value;
			for(int i = 0; i < size; ++i) {
				deserialize(data, ref offset, out value);
				list.Add(value);
			}
		} 

		public static void deserialize(byte[] data, ref Int32 offset, ref Dictionary<UInt64, CharacterInfo> table) {
			Int32 size;
			deserialize(data, ref offset, out size);
			
			UInt64 key;
			CharacterInfo value;
			for(int i = 0; i < size; ++i) {
				deserialize(data, ref offset, out key);
				deserialize(data, ref offset, out value);
				table.Add(key, value);
			}
		} 
	}
}