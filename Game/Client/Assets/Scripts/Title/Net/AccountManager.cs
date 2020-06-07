using System;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

namespace Heroes {
	public class AccountManager : MonoBehaviour {
		private NetworkManager networkManager;
		private MessageBoxHandler messageBoxHandler;
		
		[Header("Family Name Setting Dialog")]
		[SerializeField] private GameObject familyNameDialog = null;
		[SerializeField] private InputField familyNameInputField = null;

		[SerializeField] private UICharacterList characterListUI = null;
		[SerializeField] private UISelectedCharacter selectedCharacterUI = null;

		private void Start() {
			var connectedChannel = GameObject.Find("Channel Manager/Connected Channel");
			networkManager = connectedChannel?.GetComponent<NetworkManager>();
			if (networkManager == null) throw new Exception("Connected Channel not found");

			var msgBoxHandlerObj = GameObject.Find("MessageBox Handler");
			messageBoxHandler = msgBoxHandlerObj?.GetComponent<MessageBoxHandler>();
			if (messageBoxHandler == null) throw new Exception("MessageBox Handler not found");

			networkManager.registerNotification(PacketType.SearchAccountResponse, searchAccountResponse);
			networkManager.registerNotification(PacketType.CreateAccountResponse, createAccountResponse);
			networkManager.registerNotification(PacketType.GetCharacterListResponse, getCharacterListResponse);
			networkManager.registerNotification(PacketType.ChangeCharacterOrderResponse, changeCharacterOrderResponse);
			networkManager.registerNotification(PacketType.DeleteCharacterResponse, deleteCharacterResponse);

			this.searchAccountRequest();
		}

		private void OnDestroy() {
			networkManager.unregisterNotification(PacketType.SearchAccountResponse);
			networkManager.unregisterNotification(PacketType.CreateAccountResponse);
			networkManager.unregisterNotification(PacketType.GetCharacterListResponse);
			networkManager.unregisterNotification(PacketType.ChangeCharacterOrderResponse);
			networkManager.unregisterNotification(PacketType.DeleteCharacterResponse);
		}

		private void Update() {
			if (messageBoxHandler.IsOpened) return; 

			if(Input.GetButtonDown("Submit")
				&& familyNameDialog.activeSelf) {
				this.createAccountRequest();
			}
		}

		private void searchAccountRequest() {
			var packet = new SearchAccountRequestPacket();
			packet.accessKey = AccountData.Instance.accessKey;
			networkManager.sendPacket(packet);
			messageBoxHandler.notice("계정 정보를 불러오고 있습니다.");
		}

		private void searchAccountResponse(Packet rowPacket) {
			messageBoxHandler.close();

			var packet = rowPacket as SearchAccountResponsePacket;
			var errorCode = (StatusCode)packet.errorCode;

			switch(errorCode) {
				case StatusCode.Success:
					AccountData.Instance.FamilyName = packet.familyName;
					characterListUI.CreatableCharactersCount = packet.creatableCharactersCount;
					this.getCharacterListRequest();
					break;
				case StatusCode.Fail:
					familyNameDialog.SetActive(true);
					break;
				default:
					messageBoxHandler.alert("알 수 없는 에러 발생");
					this.searchAccountRequest();
					break;
			}
		}

		public void createAccountRequest() {
			var familyName = familyNameInputField.text;
			if(string.IsNullOrWhiteSpace(familyName)) {
				messageBoxHandler.alert("이름을 입력해주세요.");
				return;
			}
			else if(familyName.Length < 1 || familyName.Length > 10) {			
				messageBoxHandler.alert("올바르지 않은 이름입니다.");
				return;
			}

			var packet = new CreateAccountRequestPacket();
			packet.accessKey = AccountData.Instance.accessKey;
			packet.familyName = familyNameInputField.text;
			networkManager.sendPacket(packet);
			messageBoxHandler.notice("처리 중입니다.");
		}

		private void createAccountResponse(Packet rowPacket) {
			messageBoxHandler.close();

			var packet = rowPacket as CreateAccountResponsePacket;
			var errorCode = (StatusCode)packet.errorCode;

			switch(errorCode) {
				case StatusCode.Success: 
					familyNameDialog.SetActive(false);
					this.searchAccountRequest();
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

		private void getCharacterListRequest() {
			var packet = new GetCharacterListRequestPacket();
			packet.accessKey = AccountData.Instance.accessKey;
			networkManager.sendPacket(packet);
			messageBoxHandler.notice("캐릭터 목록을 불러오고 있습니다.");
		}

		private void getCharacterListResponse(Packet rowPacket) {
			messageBoxHandler.close();

			var packet = rowPacket as GetCharacterListResponsePacket;
			characterListUI.initialize(packet.characterList);
		}

		public void changeCharacterOrderRequest(int fromIndex, int toIndex) {
            var packet = new ChangeCharacterOrderRequestPacket();
            packet.accessKey = AccountData.Instance.accessKey;
            packet.fromIndex = (UInt16)fromIndex;
            packet.toIndex = (UInt16)toIndex;
			networkManager.sendPacket(packet);
			messageBoxHandler.notice("처리 중입니다.");
        }

		private void changeCharacterOrderResponse(Packet rowPacket) {
			messageBoxHandler.close();

			var packet = rowPacket as ChangeCharacterOrderResponsePacket;
			characterListUI.changeCharacterOrder(packet.fromIndex, packet.toIndex);
		}

		public void deleteCharacterRequest() {
			if (!selectedCharacterUI.IsSelected) return;

			var packet = new DeleteCharacterRequestPacket();
			packet.accessKey = AccountData.Instance.accessKey;
			packet.characterId = selectedCharacterUI.CharacterId;

			messageBoxHandler.confirm("삭제 하시겠습니까?", () => {
				networkManager.sendPacket(packet);
				messageBoxHandler.notice("처리 중입니다.");
			});
		}

		public void deleteCharacterResponse(Packet rowPacket) {
			messageBoxHandler.close();
			SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);
		}
	}
}
