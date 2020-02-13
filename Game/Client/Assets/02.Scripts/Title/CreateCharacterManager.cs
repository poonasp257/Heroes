using System;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

namespace Heroes {
	public class CreateCharacterManager : MonoBehaviour {
		private NetworkManager networkManager;
		private MessageBoxHandler messageBoxHandler;

		[SerializeField] private CharacterClass selectedCharacterClass;
		[SerializeField] private Text selectedClassName;
		[SerializeField] private Text selectedClassDescription;

		[SerializeField] private GameObject createDialog;

		private void Start() {
			var connectedChannel = GameObject.Find("Channel Manager/Connected Channel");
			networkManager = connectedChannel?.GetComponent<NetworkManager>();
			if (networkManager == null) throw new Exception("Connected channel not found");
			
			var messageBoxHandlerObj = GameObject.Find("MessageBox Handler");
			messageBoxHandler = messageBoxHandlerObj?.GetComponent<MessageBoxHandler>();
			if(messageBoxHandler == null) throw new Exception("MessageBoxHandler not found");
			
			networkManager.RegisterNotification(PacketType.CreateCharacterResponse, createCharacterResponse);
		}

		private void OnDestroy() {
			networkManager.UnregisterNotification(PacketType.CreateCharacterResponse);
		}

		private string getClassName(CharacterClass characterClass) {
			switch(characterClass) {
				case CharacterClass.Warrior: return "워리어";
				case CharacterClass.Crusader: return "크루세이더"; 
				case CharacterClass.Archer: return "아쳐"; 
				case CharacterClass.Assassin: return "어쌔신";
				case CharacterClass.Wizard: return "위자드";
				case CharacterClass.Elementalist: return "정령술사";
				default: return "";
			}
		}

		private string getClassDescription(CharacterClass characterClass) {
			string description = "";
			return description;
		}
		
		public void selectClass(CharacterClass characterClass) {
			this.selectedCharacterClass = characterClass;
			selectedClassName.text = this.getClassName(characterClass);
			selectedClassDescription.text = this.getClassDescription(characterClass);
		}

		public void deselectClass() {
			this.selectedCharacterClass = CharacterClass.None;
			selectedClassName.text = "";
			selectedClassDescription.text = "";
		}

		public void backToSelectScene() {
			SceneManager.LoadScene("Select");
		}

		public void openCreateDialog() {
			if (this.selectedCharacterClass == CharacterClass.None) {
				messageBoxHandler.alert("클래스를 선택해야 합니다.");
				return;
			}

			createDialog.SetActive(true);
		}

		public void createCharacterRequest(GameObject characterNameField) {
			Text characterNameText = characterNameField.GetComponent<Text>();
			string characterName = characterNameText.text;
			if (string.IsNullOrWhiteSpace(characterName)) {
				messageBoxHandler.alert("이름을 입력해주세요.");
				return;
			}
			else if (characterName.Length < 1 || characterName.Length > 10) {
				messageBoxHandler.alert("올바르지 않은 이름입니다.");
				return;
			}

			string warningStr = string.Format("[{0}]로 캐릭터 이름을 정하시겠습니까?", characterName);
			messageBoxHandler.confirm(warningStr, () => {
				CreateCharacterRequestPacket packet = new CreateCharacterRequestPacket();
				packet.accountId = PlayerData.Instance.AccountId;
				packet.characterClass = this.selectedCharacterClass;
				packet.characterName = characterName;

				networkManager.sendPacket(packet);
				messageBoxHandler.notice("캐릭터를 생성하고 있습니다.");
			});
		}

		private void createCharacterResponse(PacketType type, Packet rowPacket) {
			messageBoxHandler.close();

			CreateCharacterResponsePacket packet = rowPacket as CreateCharacterResponsePacket;	
			var errorCode = (ErrorCode)packet.errorCode;

			switch(errorCode) {
				case ErrorCode.Success:
					SceneManager.LoadScene("Select");
					break;
				case ErrorCode.BadRequest:
					messageBoxHandler.alert("올바르지 않은 이름입니다.");
					break;
				case ErrorCode.Conflict:
					messageBoxHandler.alert("이미 존재하는 이름입니다.");
					break;
				default:
					messageBoxHandler.alert("알 수 없는 에러 발생");
					break;
			}
		}
	}
}
