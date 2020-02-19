using System;
using System.Collections;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace Heroes {
	public class SceneLoader : MonoBehaviour {
		private static string nextScene;

		private NetworkManager networkManager;

		[SerializeField] private Transform progressBar = null;
		[SerializeField] private PlayerManager playerManager = null;
		[SerializeField] private GridManager gridManager = null;

		private void Start() {
			var connectedChannel = GameObject.Find("Channel Manager/Connected Channel");
			networkManager = connectedChannel?.GetComponent<NetworkManager>();
			if (networkManager == null) throw new Exception("Connected channel not found");

			StartCoroutine(LoadingScene());

			networkManager.RegisterNotification(PacketType.ConnectChannelResponse, connectChannelResponse);
			this.connectChannelRequest();
		}

		private void OnDestroy() {
			networkManager.UnregisterNotification(PacketType.ConnectChannelResponse);
		}
						
		//public void connectChannelResponse(PacketType type, Packet rowPacket) {
		//	ConnectChannelResponsePacket packet = rowPacket as ConnectChannelResponsePacket;
			
		//	foreach(var info in packet.playerTable) {
		//		var playerInfo = info.Value;
				
		//		GameObject player = createCharacter(info.Key, playerInfo);
		//		player.SetActive(false);

		//		if (info.Key == PlayerData.Instance.AccountId) { 
		//			player.tag = "Player";
		//			player.AddComponent<PlayerController>();
		//		}
		//	}
		//}

		private void connectChannelRequest() {
			ConnectChannelRequestPacket packet = new ConnectChannelRequestPacket();
			packet.playerInfo.accountId = PlayerData.Instance.AccountId;
			packet.playerInfo.familyName = PlayerData.Instance.FamilyName;
			packet.playerInfo.characterInfo = PlayerData.Instance.CurrentCharacter;
			networkManager.sendPacket(packet);
		}

		private void connectChannelResponse(PacketType type, Packet rowPacket) {
			ConnectChannelResponsePacket packet = rowPacket as ConnectChannelResponsePacket;
			//playerManager.setPlayerTable(packet.playerTable);
			StartCoroutine("Build or Load World Map");
		}

		private IEnumerator LoadingScene() {
			AsyncOperation op = SceneManager.LoadSceneAsync(nextScene);
			op.allowSceneActivation = false;

			while (!op.isDone) {
				yield return null;

				Vector3 currentPosition = Camera.main.WorldToScreenPoint(progressBar.position);
				Vector3 targetPosition = currentPosition;
				targetPosition.x = Camera.main.pixelWidth;
				
				Vector3 movedPosition = Vector3.MoveTowards(currentPosition, targetPosition, 10.0f);
				progressBar.position = Camera.main.ScreenToWorldPoint(movedPosition);

				if (op.progress >= 0.9f) {
					if (targetPosition.x <= currentPosition.x) {
						op.allowSceneActivation = true;
						//playerManager.activeAllPlayer();
						//soundManager.PlayBGM(BGMState.Main);
						yield break;
					}
				}
			}
		}		

		public static void LoadScene(string sceneName) {
			nextScene = sceneName;
			SceneManager.LoadScene("Loading");
		}
	}
}