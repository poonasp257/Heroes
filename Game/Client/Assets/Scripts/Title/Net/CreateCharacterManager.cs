using System;
using System.IO;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using Newtonsoft.Json.Linq;

namespace Heroes {
	public class CreateCharacterManager : MonoBehaviour {
		private NetworkManager networkManager;
		private MessageBoxHandler messageBoxHandler;

		private JObject parsedCharactersInfo = null;
		private GameObject previewCharacter = null;
		[SerializeField] private CharacterClassType selectedType = CharacterClassType.None;
		[SerializeField] private Text selectedClassName = null;
		[SerializeField] private Text selectedClassDescription = null;
		[SerializeField] private Transform previewNode = null;
		[SerializeField] private GameObject createDialog = null;

		private void Awake() {
			this.loadCharacterInfo();
		}

		private void Start() {
			var connectedChannel = GameObject.Find("Channel Manager/Connected Channel");
			networkManager = connectedChannel?.GetComponent<NetworkManager>();
			if (networkManager == null) throw new Exception("Connected channel not found");
			
			var messageBoxHandlerObj = GameObject.Find("MessageBox Handler");
			messageBoxHandler = messageBoxHandlerObj?.GetComponent<MessageBoxHandler>();
			if(messageBoxHandler == null) throw new Exception("MessageBoxHandler not found");
			
			networkManager.registerNotification(PacketType.CreateCharacterResponse, createCharacterResponse);
		}

		private void OnDestroy() {
			networkManager.unregisterNotification(PacketType.CreateCharacterResponse);
		}

		private void loadCharacterInfo() {
			var jsonData = Util.LoadJsonFile("/Data", "/character_description");
			parsedCharactersInfo = JObject.Parse(jsonData);
		}

		private void updateSelectedCharacter(CharacterClassType type) {
			JToken info = parsedCharactersInfo[type.ToString()];
			selectedType = type;
			selectedClassName.text = info["language"]["kr"].ToObject<string>();
			selectedClassDescription.text = info["description"].ToObject<string>();
		}

		public string getName(CharacterClassType type) {
			JToken info = parsedCharactersInfo[type.ToString()];
			return info["language"]["kr"].ToObject<string>();
		}

		public void selectClass(CharacterClassType type) {
			this.updateSelectedCharacter(type);
			if(previewCharacter) previewCharacter.SetActive(false);
			previewCharacter = previewNode.Find(type.ToString())?.gameObject;
			previewCharacter.SetActive(true);
		}

		public void deselectClass() {
			this.selectedType = CharacterClassType.None;
			selectedClassName.text = "";
			selectedClassDescription.text = "";
		}

		public void openCreateDialog() {
			if (this.selectedType == CharacterClassType.None) {
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
				var packet = new CreateCharacterRequestPacket();
				packet.accessKey = AccountData.Instance.accessKey;
				packet.classType = this.selectedType;
				packet.characterName = characterName;
				networkManager.sendPacket(packet);
				messageBoxHandler.notice("캐릭터를 생성하고 있습니다.");
			});
		}

		private void createCharacterResponse(Packet rowPacket) {
			messageBoxHandler.close();

			var packet = rowPacket as CreateCharacterResponsePacket;	
			var errorCode = (StatusCode)packet.errorCode;
			switch(errorCode) {
				case StatusCode.Success:
					SceneManager.LoadScene("Select");
					break;
				case StatusCode.BadRequest:
					messageBoxHandler.alert("올바르지 않은 이름입니다.");
					break;
				case StatusCode.Conflict:
					messageBoxHandler.alert("이미 존재하는 이름입니다.");
					break;
				default:
					messageBoxHandler.alert("알 수 없는 에러 발생");
					break;
			}
		}
	}
}
