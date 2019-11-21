using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace Heroes {
	public class LobbyManager : MonoBehaviour {
		private NetworkManager networkManager;
		private MessageBox msgBox;

		private GameObject chanelInfoPrefab;
		private GameObject characterInfoPrefab;

		//private UInt64 accountId;
		public UInt64 AccountId { get; set; }

		//private string selectedChanel;
		public string SelectedChanel { get; set; }

		private void Awake() {
			chanelInfoPrefab = Resources.Load<GameObject>("UI/Prefab/Chanel/Chanel Info");
			characterInfoPrefab = Resources.Load<GameObject>("UI/Prefab/Character List/Character Info");
		}

		private void Start() {
			networkManager = GameObject.Find("Network Manager").GetComponent<NetworkManager>();
			msgBox = GameObject.Find("Message Handler").GetComponent<MessageBox>();
			
			this.chanelStatusRequest();

			networkManager.RegisterNotification(PacketType.ChanelStatusResponse, chanelStatusResponse);
			networkManager.RegisterNotification(PacketType.AccountInfoResponse, accountInfoResponse);
		}

		private void chanelStatusRequest() {
			ChanelStatusRequestPacket packet = new ChanelStatusRequestPacket();
			networkManager.send(packet);

			msgBox.notice("채널 정보를 불러오고 있습니다.");
		}

		public void accountInfoRequest() {
			AccountInfoRequestPacket packet = new AccountInfoRequestPacket();
			packet.accountId = this.AccountId;
					   
			networkManager.send(packet);
			msgBox.notice("캐릭터 정보를 불러오고 있습니다.");
		}

		public void chanelStatusResponse(PacketType type, Packet rowPacket) {
			msgBox.close();

			ChanelStatusResponsePacket packet = rowPacket as ChanelStatusResponsePacket;	
			if(packet == null) {
				Debug.Log("invalid packet");
				return;
			}

			GameObject contents = GameObject.Find("Contents");			
			foreach(ChanelInfo info in packet.chanelList) {
				GameObject chanel = Instantiate(chanelInfoPrefab, contents.transform);
				UIChanelInfo chanelInfo = chanel.GetComponent<UIChanelInfo>();
				chanelInfo.ID = info.id;
				chanelInfo.Traffic = info.traffic;
			}
		}

		public void accountInfoResponse(PacketType type, Packet rowPacket) {
			msgBox.close();

			AccountInfoResponsePacket packet = rowPacket as AccountInfoResponsePacket;
			if(packet == null) {
				Debug.Log("invalid packet");
				return;
			}

			StartCoroutine(LoadSelectSceneProcess(packet.creatableCharacters, packet.familyName, packet.characterList));
		}

		public IEnumerator LoadSelectSceneProcess(Int32 creatableCharacters, string familyName, List<CharacterInfo> characterList) {
			yield return StartCoroutine(LoadSelectScene()); yield return null;

			UICharacterCounter characterCounterUI = GameObject.Find("Character Counter").GetComponent<UICharacterCounter>();
			characterCounterUI.CreatedCount = characterList.Count;
			characterCounterUI.CreatableCount = creatableCharacters;
			
			UISelectedCharacter selectedCharacterUI = GameObject.Find("Selected Character").GetComponent<UISelectedCharacter>();
			selectedCharacterUI.FamilyName = familyName;

			GameObject contents = GameObject.Find("Contents");			
			foreach(CharacterInfo info in characterList) {
				GameObject character = Instantiate(characterInfoPrefab, contents.transform);
				UICharacterInfo characterInfo = character.GetComponent<UICharacterInfo>();
				characterInfo.Class = info.characterClass;
				characterInfo.Level = info.level;
				characterInfo.CharacterName = info.characterName;
				characterInfo.Location = info.location;
			}
		}

		public IEnumerator LoadSelectScene() {
			AsyncOperation op = SceneManager.LoadSceneAsync("Select");
			op.allowSceneActivation = false;

			while (!op.isDone){
				yield return null;

				if (op.progress >= 0.9f) {
					op.allowSceneActivation = true;
					yield break;
				}
			}
		}
	}
}
