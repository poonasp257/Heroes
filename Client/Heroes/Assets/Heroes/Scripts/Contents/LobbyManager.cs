using System;
using UnityEngine;

namespace Heroes {
	public class LobbyManager : MonoBehaviour {
		//private UInt64 accountId;
		//private string accountId;

		public string AccountId { get; set; }

		private void Awake() {
			Debug.Log("Chanel Awake");
		}

		private void Start() {
			Debug.Log("Chanel Start");
		}
		
		private void Update() {
			
		}
	}
}
