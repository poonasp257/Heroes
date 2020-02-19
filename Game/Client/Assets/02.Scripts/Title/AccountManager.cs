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

			networkManager.RegisterNotification(PacketType.SearchAccountResponse, searchAccountResponse);
			networkManager.RegisterNotification(PacketType.CreateAccountResponse, createAccountResponse);
			networkManager.RegisterNotification(PacketType.GetCharacterListResponse, getCharacterListResponse);
			networkManager.RegisterNotification(PacketType.ChangeCharacterOrderResponse, changeCharacterOrderResponse);
			networkManager.RegisterNotification(PacketType.DeleteCharacterResponse, deleteCharacterResponse);

			this.searchAccountRequest();
		}

		private void OnDestroy() {
			networkManager.UnregisterNotification(PacketType.SearchAccountResponse);
			networkManager.UnregisterNotification(PacketType.CreateAccountResponse);
			networkManager.UnregisterNotification(PacketType.GetCharacterListResponse);
			networkManager.UnregisterNotification(PacketType.ChangeCharacterOrderResponse);
			networkManager.UnregisterNotification(PacketType.DeleteCharacterResponse);
		}

		private void Update() {
			if (messageBoxHandler.IsOpened) return; 

			if(Input.GetButtonDown("Submit")
				&& familyNameDialog.activeSelf) {
				this.createAccountRequest();
			}
		}

		private void searchAccountRequest() {
			SearchAccountRequestPacket packet = new SearchAccountRequestPacket();
			packet.accountId = PlayerData.Instance.AccountId;
			networkManager.sendPacket(packet);
			messageBoxHandler.notice("계정 정보를 불러오고 있습니다.");
		}

		private void searchAccountResponse(PacketType type, Packet rowPacket) {
			messageBoxHandler.close();

			SearchAccountResponsePacket packet = rowPacket as SearchAccountResponsePacket;
			var errorCode = (ErrorCode)packet.errorCode;

			switch(errorCode) {
				case ErrorCode.Success:
					PlayerData.Instance.FamilyName = packet.familyName;
					characterListUI.CreatableCharactersCount = packet.creatableCharactersCount;
					this.getCharacterListRequest();
					break;
				case ErrorCode.Fail:
					familyNameDialog.SetActive(true);
					break;
				default:
					messageBoxHandler.alert("알 수 없는 에러 발생");
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

			CreateAccountRequestPacket packet = new CreateAccountRequestPacket();
			packet.accountId = PlayerData.Instance.AccountId;
			packet.familyName = familyNameInputField.text;
			networkManager.sendPacket(packet);
			messageBoxHandler.notice("처리 중입니다.");
		}

		private void createAccountResponse(PacketType type, Packet rowPacket) {
			messageBoxHandler.close();

			CreateAccountResponsePacket packet = rowPacket as CreateAccountResponsePacket;
			var errorCode = (ErrorCode)packet.errorCode;

			switch(errorCode) {
				case ErrorCode.Success: 
					familyNameDialog.SetActive(false);
					this.searchAccountRequest();
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

		private void getCharacterListRequest() {
			GetCharacterListRequestPacket packet = new GetCharacterListRequestPacket();
			packet.accountId = PlayerData.Instance.AccountId;
			networkManager.sendPacket(packet);
			messageBoxHandler.notice("캐릭터 목록을 불러오고 있습니다.");
		}

		private void getCharacterListResponse(PacketType type, Packet rowPacket) {
			messageBoxHandler.close();

			GetCharacterListResponsePacket packet = rowPacket as GetCharacterListResponsePacket;
			characterListUI.initialize(packet.characterList);
		}

		public void changeCharacterOrderRequest(int fromIndex, int toIndex) {
            ChangeCharacterOrderRequestPacket packet = new ChangeCharacterOrderRequestPacket();
            packet.accountId = PlayerData.Instance.AccountId;
            packet.fromIndex = (UInt16)fromIndex;
            packet.toIndex = (UInt16)toIndex;
			networkManager.sendPacket(packet);
			messageBoxHandler.notice("처리 중입니다.");
        }

		private void changeCharacterOrderResponse(PacketType type, Packet rowPacket) {
			messageBoxHandler.close();

			ChangeCharacterOrderResponsePacket packet = rowPacket as ChangeCharacterOrderResponsePacket;
			characterListUI.changeCharacterOrder(packet.fromIndex, packet.toIndex);
		}

		public void deleteCharacterRequest() {
			if (!selectedCharacterUI.IsSelected) return;

			DeleteCharacterRequestPacket packet = new DeleteCharacterRequestPacket();
			packet.accountId = PlayerData.Instance.AccountId;
			packet.characterId = selectedCharacterUI.CharacterId;

			messageBoxHandler.confirm("삭제 하시겠습니까?", () => {
				networkManager.sendPacket(packet);
				messageBoxHandler.notice("처리 중입니다.");
			});
		}

		public void deleteCharacterResponse(PacketType type, Packet rowPacket) {
			messageBoxHandler.close();
			SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);
		}

		public void backToChannelSelectionScene() {
			var channelManager = GameObject.Find("Channel Manager");
			if (channelManager != null) Destroy(channelManager);

			SceneManager.LoadScene("Channel");
		}

		public void disconnectGame() {
			messageBoxHandler.confirm("게임을 종료하시겠습니까?", () => {
				Application.Quit();
			});
		}
	}
}
