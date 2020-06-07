using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace Heroes {
	public class SceneLoader : MonoBehaviour {
		private MessageBoxHandler messageBoxHandler = null;

		private void Start() {
			var msgHandlerObject = GameObject.Find("MessageBox Handler");
			messageBoxHandler = msgHandlerObject?.GetComponent<MessageBoxHandler>();
			if (messageBoxHandler == null) throw new Exception("MessageBox Handler not found");
		}

		public void LoadMainScene() {
			SceneManager.LoadScene("Loading");
		}

		public void LoadCharacterSelectionScene() {
			messageBoxHandler.confirm("캐릭터 선택 화면으로 돌아가시겠습니까?", () => {
				var scene = SceneManager.GetActiveScene();
				if(scene.name == "Main") {
					var connectedChannelObj = GameObject.Find("Channel Manager/Connected Channel");
					var connectedChannel = connectedChannelObj.GetComponent<NetworkManager>();					
					var packet = new DisconnectChannelRequestPacket();
					packet.accessKey = AccountData.Instance.accessKey;
					packet.playerId = AccountData.Instance.PlayerId;
					connectedChannel.sendPacket(packet);

					List<string> excludeObjNames = new List<string>();
					excludeObjNames.Add("Channel Manager");
					excludeObjNames.Add("MessageBox Handler");
					ObjectManager.Instance.DestroyAllObjects(excludeObjNames);
				}

				SceneManager.LoadScene("Select");
			});
		}

		public void LoadChannelSelectionScene() {
			messageBoxHandler.confirm("채널 선택 화면으로 돌아가시겠습니까?", () => {
				var scene = SceneManager.GetActiveScene();
				if(scene.name == "Main") {
					var connectedChannelObj = GameObject.Find("Channel Manager/Connected Channel");
					var connectedChannel = connectedChannelObj.GetComponent<NetworkManager>();					
					var packet = new DisconnectChannelRequestPacket();
					packet.accessKey = AccountData.Instance.accessKey;
					packet.playerId = AccountData.Instance.PlayerId;
					connectedChannel.sendPacket(packet);
				}

				ObjectManager.Instance.DestroyAllObjects("MessageBox Handler");
				SceneManager.LoadScene("Channel");
			});
		}

		public void Quit() {
			messageBoxHandler.confirm("게임을 종료하시겠습니까?", () => {
				Application.Quit();
			});
		}
		
		public static void LoadLoginScene() {
			ObjectManager.Instance.DestroyAllObjects();
			SceneManager.LoadScene("Login");
		}
	}
}