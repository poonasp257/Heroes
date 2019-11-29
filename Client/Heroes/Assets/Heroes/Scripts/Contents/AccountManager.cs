using System;
using UnityEngine;

namespace Heroes {
	public class AccountManager : MonoBehaviour {
		private NetworkManager networkManager;
		private MessageBox msgBox;
		
		[SerializeField] private GameObject characterInfoItem;
		[SerializeField] private GameObject creatableItem;
		[SerializeField] private GameObject lockedItem;
		
		private void Awake() {
			networkManager = GameObject.Find("Network Manager").GetComponent<NetworkManager>();
			msgBox = GameObject.Find("Message Handler").GetComponent<MessageBox>();

			networkManager.RegisterNotification(PacketType.AccountInfoResponse, accountInfoResponse);
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
			if(packet == null) {
				Debug.Log("invalid packet");
				return;
			}

			UICharacterCounter characterCounterUI = GameObject.Find("Character Counter").GetComponent<UICharacterCounter>();
			characterCounterUI.CreatedCount = packet.characterTable.Count;
			characterCounterUI.CreatableCount = packet.creatableCharacters;

			GameObject characterListContainer = GameObject.Find("List");
			if (packet.characterTable.Count != 0) {
				foreach (var characterInfo in packet.characterTable) {
					GameObject character = Instantiate(characterInfoItem, characterListContainer.transform);
					UICharacterInfo characterInfoUI = character.GetComponent<UICharacterInfo>();

					characterInfoUI.CharacterID = characterInfo.Key;
					characterInfoUI.Info = characterInfo.Value;
				}
			}

			if (packet.creatableCharacters == packet.characterTable.Count) return;

			Instantiate(creatableItem, characterListContainer.transform);
			--packet.creatableCharacters;

			int lockedItemCount = packet.creatableCharacters - packet.characterTable.Count;
			for (int i = 0; i < lockedItemCount; ++i) {
				Instantiate(lockedItem, characterListContainer.transform);
			}
		}
	}
}
