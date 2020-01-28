using System;
using UnityEngine;
using UnityEngine.UI;

namespace Heroes {
public class UICharacterCounter : MonoBehaviour {
		private Text count;

		public Int32 CreatedCount { get; set; }
		public Int32 CreatableCount { get; set; }

		private void Awake() {
			count = GetComponent<Text>();
		}

		private void Update() {
			count.text = String.Format("({0}/{1})", CreatedCount, CreatableCount);
		}
	}
}