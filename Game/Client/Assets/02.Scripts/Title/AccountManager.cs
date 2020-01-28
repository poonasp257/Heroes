using UnityEngine;
using UnityEngine.SceneManagement;

namespace Heroes {
	public class AccountManager : MonoBehaviour {
		private NetworkManager networkManager;
		private MessageBoxHandler msgBox;
		
		[SerializeField] private GameObject characterInfoItem;
		[SerializeField] private GameObject creatableItem;
		[SerializeField] private GameObject lockedItem;
		
		private void Awake() {
			networkManager = GameObject.Find("Network Manager").GetComponent<NetworkManager>();
			msgBox = GameObject.Find("MessageBox Handler").GetComponent<MessageBoxHandler>();

			networkManager.RegisterNotification(PacketType.AccountInfoResponse, accountInfoResponse);
			networkManager.RegisterNotification(PacketType.DeleteCharacterResponse, deleteCharacterResponse);
		}

		private void Start() {
			this.accountInfoRequest();
		}

		public void accountInfoRequest() {
			AccountInfoRequestPacket packet = new AccountInfoRequestPacket();
			packet.accountId = PlayerData.Instance.AccountId;

			networkManager.send(packet);
			msgBox.notice("캐릭터 정보를 불러오고 있습니다.");
		}

		public void accountInfoResponse(PacketType type, Packet rowPacket) {
			msgBox.close();

			AccountInfoResponsePacket packet = rowPacket as AccountInfoResponsePacket;
			if (packet == null) {
				Debug.Log("invalid packet");
				return;
			}

			UICharacterCounter characterCounterUI = GameObject.Find("Character Counter").GetComponent<UICharacterCounter>();
			characterCounterUI.CreatedCount = packet.characterList.Count;
			characterCounterUI.CreatableCount = packet.maxCreatableCharacters;

			GameObject characterListContainer = GameObject.Find("List");
			foreach (var characterInfo in packet.characterList) {
				GameObject character = Instantiate(characterInfoItem, characterListContainer.transform);
				UICharacterInfo characterInfoUI = character.GetComponent<UICharacterInfo>();

				characterInfoUI.Info = characterInfo;
			}

			if (packet.maxCreatableCharacters == packet.characterList.Count) return;

			Instantiate(creatableItem, characterListContainer.transform);
			--packet.maxCreatableCharacters;

			int lockedItemCount = packet.maxCreatableCharacters - packet.characterList.Count;
			for (int i = 0; i < lockedItemCount; ++i) {
				Instantiate(lockedItem, characterListContainer.transform);
			}
		}

		public void deleteCharacterRequest() {
			UISelectedCharacter selectedCharacterUI = GameObject.Find("Selected Character").GetComponent<UISelectedCharacter>();
			if (!selectedCharacterUI.isSelected()) return;

			DeleteCharacterRequestPacket packet = new DeleteCharacterRequestPacket();
			packet.characterId = selectedCharacterUI.Info.characterId;

			msgBox.confirm("삭제 하시겠습니까?", () => {
					networkManager.send(packet);
					msgBox.notice("삭제 요청 중 입니다.");
			});
		}

		public void deleteCharacterResponse(PacketType type, Packet rowPacket) {
			msgBox.close();			
			SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);
		}
	}
}
