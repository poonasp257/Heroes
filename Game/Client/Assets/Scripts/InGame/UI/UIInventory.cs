using System;
using UnityEngine;
using UnityEngine.UI;

namespace Heroes {
    public class UIInventory : MonoBehaviour {
        private PlayerStateManager playerStateManager = null;

        [Header("Status")]
        [SerializeField] private Text damage = null;
        [SerializeField] private Text defense = null;

        private void Start() {
            var player = GameObject.FindWithTag("Player");
            playerStateManager = player?.GetComponent<PlayerStateManager>();
            if (playerStateManager == null) throw new Exception("Player not found...");
        }

        private void Update() {
            damage.text = playerStateManager.info.damage.ToString();
            defense.text = playerStateManager.info.defense.ToString();
        }
    }
}