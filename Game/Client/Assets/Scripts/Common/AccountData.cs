using System;
using UnityEngine;

namespace Heroes {
	public class AccountData {
		private static AccountData instance = null;

		public static AccountData Instance {
			get {
				if(instance == null) {
					instance = new AccountData();
				}

				return instance;
			}
		}

		public string accessKey { get; set; }
		public ChannelInfo CurrentChannel { get; set; }
		public UInt64 PlayerId { get; set; }
		public CharacterInfo CurrentCharacter { get; set; }
		public string FamilyName { get; set; }
	}
}