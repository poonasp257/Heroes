using System;
using System.Collections;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace Heroes {
	public class SceneLoader : MonoBehaviour {
		private static string nextScene;

		private NetworkManager networkManager;
		private PlayerManager playerManager = null;
		private GridManager gridManager = null;

		private Transform progressBar = null;
		private Transform startPoint = null;
		private Transform endPoint = null;
		private Vector3 movePoint;

		private void Start() {
			progressBar = GameObject.Find("Progress/Progress Bar")?.transform;
			if(progressBar == null) throw new Exception("Progress bar not found");

			startPoint = GameObject.Find("Progress/Start Point")?.transform;
			if (startPoint == null) throw new Exception("Start point not found");

			endPoint = GameObject.Find("Progress/End Point")?.transform;
			if (endPoint == null) throw new Exception("End point not found");

			var connectedChannel = GameObject.Find("Channel Manager/Connected Channel");
			networkManager = connectedChannel?.GetComponent<NetworkManager>();
			if (networkManager == null) throw new Exception("Connected channel not found");

			var playerManagerObj = GameObject.Find("Player Manager");
			playerManager = playerManagerObj?.GetComponent<PlayerManager>();
			if (playerManager == null) throw new Exception("Player Manager not found");

			var gridManagerObj = GameObject.Find("Grid Manager");
			gridManager = gridManagerObj?.GetComponent<GridManager>();
			if (gridManager == null) throw new Exception("Grid Manager not found");

			networkManager.RegisterNotification(PacketType.ConnectChannelResponse, connectChannelResponse);

			this.connectChannelRequest();
		}

		private void OnDestroy() {
			networkManager.UnregisterNotification(PacketType.ConnectChannelResponse);
		}

		private void Update() {
			Vector3 velo = Vector3.zero;
			progressBar.position = Vector3.SmoothDamp(progressBar.position, 
				movePoint, ref velo, 0.1f);
		}

		private void connectChannelRequest() {
			ConnectChannelRequestPacket packet = new ConnectChannelRequestPacket();
			packet.accessKey = AccountData.Instance.accessKey;
			packet.playerInfo.familyName = AccountData.Instance.FamilyName;
			packet.playerInfo.characterInfo = AccountData.Instance.CurrentCharacter;
			networkManager.sendPacket(packet);
		}

		private void connectChannelResponse(PacketType type, Packet rowPacket) {
			ConnectChannelResponsePacket packet = rowPacket as ConnectChannelResponsePacket;
			playerManager.initialize(packet.playerList);
			fillProgressBar(0.2f);
			StartCoroutine(LoadingScene());
		}

		private void fillProgressBar(float amount) {
			float distance = (startPoint.position - endPoint.position).magnitude;
			float unit = distance * Mathf.Clamp(amount, 0.0f, 1.0f);
			movePoint = startPoint.position + new Vector3(unit, 0, 0); 
		}

		private IEnumerator LoadingScene() {
			var loadWorldTask = gridManager.loadWorldMap();
			while(!loadWorldTask.IsCompleted) {
				yield return null;
			}
			fillProgressBar(0.8f);

			AsyncOperation op = SceneManager.LoadSceneAsync(nextScene);
			op.allowSceneActivation = false;
			while (!op.isDone) {
				yield return null;

				if (op.progress >= 0.9f) {
					playerManager.activeAllPlayer();
					//soundManager.PlayBGM(BGMState.Main);
					fillProgressBar(1.0f);
					op.allowSceneActivation = true;
					yield break;
				}
			}
		}

		public static void LoadScene(string sceneName) {
			nextScene = sceneName;
			SceneManager.LoadScene("Loading");
		}
	}
}