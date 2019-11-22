﻿using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace Heroes {
	public class LobbyManager : MonoBehaviour {
		private NetworkManager networkManager;
		private MessageBox msgBox;

		private GameObject chanelInfoItem;
		private GameObject characterInfoItem;
		private GameObject creatableItem;
		private GameObject lockedItem;

		//private UInt64 accountId;
		public UInt64 AccountId { get; set; }

		//private string selectedChanel;
		public string SelectedChanel { get; set; }

		//private string selectedCharacter;
		public UInt64 SelectedCharacter { get; set; }

		private void Awake() {
			chanelInfoItem = Resources.Load<GameObject>("UI/Prefab/Chanel/ChanelInfo Item");
			characterInfoItem = Resources.Load<GameObject>("UI/Prefab/Character List/CharacterInfo Item");
			creatableItem = Resources.Load<GameObject>("UI/Prefab/Character List/Creatable Item");
			lockedItem = Resources.Load<GameObject>("UI/Prefab/Character List/Locked Item");

			networkManager = GameObject.Find("Network Manager").GetComponent<NetworkManager>();
			msgBox = GameObject.Find("Message Handler").GetComponent<MessageBox>();

			networkManager.RegisterNotification(PacketType.ChanelStatusResponse, chanelStatusResponse);
			networkManager.RegisterNotification(PacketType.AccountInfoResponse, accountInfoResponse);
			networkManager.RegisterNotification(PacketType.ConnectChanelResponse, connectChanelResponse);
		}

		private void Start() {
			this.chanelStatusRequest();
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

		
		public void connectChanelRequest() {
			ConnectChanelRequestPacket packet = new ConnectChanelRequestPacket();
			packet.chanelId = SelectedChanel;
			packet.characterId = SelectedCharacter;

			networkManager.send(packet);
		}

		public void chanelStatusResponse(PacketType type, Packet rowPacket) {
			msgBox.close();

			ChanelStatusResponsePacket packet = rowPacket as ChanelStatusResponsePacket;	
			if(packet == null) {
				Debug.Log("invalid packet");
				return;
			}

			GameObject list = GameObject.Find("List");			
			foreach(ChanelInfo info in packet.chanelList) {
				GameObject chanel = Instantiate(chanelInfoItem, list.transform);
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
		
		public void connectChanelResponse(PacketType type, Packet rowPacket) {
			ConnectChanelResponsePacket packet = rowPacket as ConnectChanelResponsePacket;

			Debug.Log(packet.status.hp);
		}
		
		public IEnumerator LoadSelectSceneProcess(Int32 creatableCharacters, string familyName, List<CharacterInfo> characterList) {
			yield return StartCoroutine(LoadSelectScene()); yield return null; yield return null;

			UICharacterCounter characterCounterUI = GameObject.Find("Character Counter").GetComponent<UICharacterCounter>();
			characterCounterUI.CreatedCount = characterList.Count;
			characterCounterUI.CreatableCount = creatableCharacters;

			GameObject list = GameObject.Find("List");

			if (characterList.Count != 0) {
				UISelectedCharacter selectedCharacterUI = GameObject.Find("Selected Character").GetComponent<UISelectedCharacter>();
				selectedCharacterUI.FamilyName = familyName;
				selectedCharacterUI.CharacterName = characterList[0].characterName;

				foreach (CharacterInfo info in characterList) {
					GameObject character = Instantiate(characterInfoItem, list.transform);
					UICharacterInfo characterInfo = character.GetComponent<UICharacterInfo>();

					characterInfo.ID = info.characterId;
					characterInfo.Class = info.characterClass;
					characterInfo.Level = info.level;
					characterInfo.CharacterName = info.characterName;
					characterInfo.Location = info.location;
				}
			}

			if (creatableCharacters == characterList.Count) yield break;

			Instantiate(creatableItem, list.transform);
			--creatableCharacters;

			int lockedItemCount = creatableCharacters - characterList.Count;
			for (int i = 0; i < lockedItemCount; ++i) {
				Instantiate(lockedItem, list.transform);
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
