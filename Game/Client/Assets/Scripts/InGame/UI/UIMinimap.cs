using System;
using UnityEngine;
using UnityEngine.UI;

namespace Heroes {
	public class UIMinimap : MonoBehaviour {
		private PlayerStateManager stateManager;
		[SerializeField] private Text location;

		private void Start() {
			var player = GameObject.FindWithTag("Player");
			if (player == null) throw new Exception("player not found");

			stateManager = player.GetComponent<PlayerStateManager>();
		}

		private void Update() {
			location.text = stateManager.info.location;
		}
	}
}