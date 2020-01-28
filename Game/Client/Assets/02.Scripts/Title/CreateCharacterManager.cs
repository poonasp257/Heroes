using System;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

namespace Heroes {
	public class CreateCharacterManager : MonoBehaviour {
		private NetworkManager networkManager;
		private MessageBoxHandler msgBox;

		private Text selectedClass;
		
		private void Start() {
			networkManager = GameObject.Find("Network Manager").GetComponent<NetworkManager>();
			msgBox = GameObject.Find("MessageBox Handler").GetComponent<MessageBoxHandler>();
			selectedClass = GameObject.Find("Selected Class").GetComponent<Text>();

			networkManager.RegisterNotification(PacketType.CreateCharacterResponse, createCharacterResponse);
		}

		public void backToSelectScene() {
			SceneManager.LoadScene("Select");
		}

		public void createCharacterRequest(GameObject characterNameField) {
			Text characterName = characterNameField.GetComponent<Text>();
			if (string.IsNullOrWhiteSpace(characterName.text)
				|| characterName.text.Length < 4) {
				msgBox.alert("생성할 수 없는 이름입니다.");
				return;
			}

			CreateCharacterRequestPacket packet = new CreateCharacterRequestPacket();
			packet.accountId = PlayerData.Instance.AccountId;
			packet.characterClass = (CharacterClass)Enum.Parse(typeof(CharacterClass), selectedClass.text);
			packet.characterName = characterName.text;
			
			networkManager.send(packet);
			msgBox.notice("캐릭터를 생성하고 있습니다.");
		}

		public void createCharacterResponse(PacketType type, Packet rowPacket) {
			msgBox.close();

			CreateCharacterResponsePacket packet = rowPacket as CreateCharacterResponsePacket;	
			if(packet == null) {
				Debug.Log("invalid packet");
				return;
			}
			
			if(packet.errorCode >= 0) {
				msgBox.alert("이미 존재하는 이름입니다.");
				return;
			}

			msgBox.alert("캐릭터 생성 성공!", () => {
				SceneManager.LoadScene("Select");
			});
		}
	}
}
