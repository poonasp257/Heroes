using System;
using System.IO;
using System.Text;
using System.Collections.Generic;

namespace Heroes {
	public static class Serializer {		
		public static void serialize(MemoryStream stream, PacketType type) {
			serialize(stream, (UInt32)type);
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
			serialize(stream, str.Length);
			stream.Write(Encoding.UTF8.GetBytes(str), 0, str.Length);
		}

		public static void serialize(MemoryStream stream, ChanelStatus value) {
			serialize(stream, value.id);
			serialize(stream, value.traffic);
		}

		public static void serialize(MemoryStream stream, List<ChanelStatus> list) {
			serialize(stream, list.Count);
			foreach(ChanelStatus value in list) {
				serialize(stream, value);
			}
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
			value = Encoding.ASCII.GetString(data, offset, strLen);
			offset += strLen;
		}

		public static void deserialize(byte[] data, ref Int32 offset, out ChanelStatus value) {
			deserialize(data, ref offset, out value.id);
			deserialize(data, ref offset, out value.traffic);
		}

		public static void deserialize(byte[] data, ref Int32 offset, ref List<ChanelStatus> list) {
			Int32 size;
			deserialize(data, ref offset, out size);

			ChanelStatus value;
			for(int i = 0; i < size; ++i) {
				deserialize(data, ref offset, out value);
				list.Add(value);
			}
		} 
	}
}