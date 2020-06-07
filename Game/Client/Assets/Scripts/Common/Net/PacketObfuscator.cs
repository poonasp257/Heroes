using System;

namespace Heroes {
    public static class PacketObfuscator {
        private static Obfuscation obfuscation = new XorObfuscation();    

        public static void encodeHeader(ref Byte[] src) {
            obfuscation.encode(ref src, 0, sizeof(Int32));
        }

        public static void encodeData(ref Byte[] src, int len) {
            obfuscation.encode(ref src, sizeof(Int32), len);
        }

        public static void decodeHeader(ref Byte[] src) {
            obfuscation.decode(ref src, 0, sizeof(Int32));
        }

        public static void decodeData(ref Byte[] src, int len) {
            obfuscation.decode(ref src, sizeof(Int32), len);
        }
    }
}