using System;
using System.Text;
using UnityEngine;

namespace Heroes {
	interface Obfuscation {
		void encode(ref Byte[] src, int offset, int count);
		void decode(ref Byte[] src, int offset, int count);
	}

	public class XorObfuscation : Obfuscation {
		private readonly string originalKey;
		private readonly int originalKeyLen;

		public XorObfuscation() {
			originalKey = "heroes";
			originalKeyLen = originalKey.Length;
		}
				
		public void encode(ref Byte[] src, int offset, int count) {
			Byte[] nextKey = Encoding.ASCII.GetBytes(originalKey);
			int startIdx = offset;
			int endIdx = offset + count;
			int keyIdx = 0;

			for (int i = startIdx; i < endIdx; ++i) {
				src[i] ^= nextKey[keyIdx];
				nextKey[keyIdx++] = src[i];
				if (keyIdx == originalKeyLen) keyIdx = 0;
			}
		}

		public void decode(ref Byte[] src, int offset, int count) {
			Byte[] nextKey = Encoding.ASCII.GetBytes(originalKey);
			int startIdx = offset;
			int endIdx = offset + count;
			int keyIdx = 0;

			for (int i = startIdx; i < endIdx; ++i) {
				Util.swap<Byte>(ref src[i], ref nextKey[keyIdx]);
				src[i] ^= nextKey[keyIdx++];
				if (keyIdx == originalKeyLen) keyIdx = 0;
			}
		}
	}
}