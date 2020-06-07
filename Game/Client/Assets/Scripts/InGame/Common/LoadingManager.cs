using System;
using System.Collections;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace Heroes {
	public class LoadingManager : MonoBehaviour {
        private NetworkManager networkManager = null;
		[SerializeField] private PlayerManager playerManager = null;
		[SerializeField] private MonsterManager monsterManager = null;
		[SerializeField] private GridManager gridManager = null;
		[SerializeField] private ProgressControl progress = null;

		private void Start() {
			var connectedChannel = GameObject.Find("Channel Manager/Connected Channel");
			networkManager = connectedChannel?.GetComponent<NetworkManager>();
			if (networkManager == null) throw new Exception("Connected channel not found");

			networkManager.registerNotification(PacketType.ConnectChannelResponse, connectChannelResponse);
			this.connectChannelRequest();
		}

		private void OnDestroy() {
			networkManager.unregisterNotification(PacketType.ConnectChannelResponse);
		}

		private void connectChannelRequest() {
			var packet = new ConnectChannelRequestPacket();
			packet.accessKey = AccountData.Instance.accessKey;
			packet.familyName = AccountData.Instance.FamilyName;
			packet.characterInfo = AccountData.Instance.CurrentCharacter;
			networkManager.sendPacket(packet);
		}

		private void connectChannelResponse(Packet rowPacket) {
			var packet = rowPacket as ConnectChannelResponsePacket;
			playerManager.generatePlayerCharacter(packet.playerId);
			AccountData.Instance.PlayerId = packet.playerId;
			progress.fillProgress(0.2f);
			
			StartCoroutine(LoadingScene());
		}

		private IEnumerator LoadingScene() {
			var loadWorldTask = gridManager.loadWorldMap();
			while(!loadWorldTask.IsCompleted) {
				yield return null;
			}
			progress.fillProgress(0.8f);

			AsyncOperation op = SceneManager.LoadSceneAsync("Main");
			op.allowSceneActivation = false;
			while (!op.isDone) {
				yield return null;

				if (op.progress >= 0.9f) {
					progress.fillProgress(1.0f);

					if (progress.IsFilled) {
						playerManager.gameObject.SetActive(true);
						monsterManager.gameObject.SetActive(true);
						op.allowSceneActivation = true;
						yield break;
					}
				}
			}
		}
	}
}