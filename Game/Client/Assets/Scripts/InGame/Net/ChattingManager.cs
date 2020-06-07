using System;
using UnityEngine;
using UnityEngine.UI;

namespace Heroes {
    public class ChattingManager : MonoBehaviour {
        private NetworkManager networkManager = null;
        private PlayerController playerController = null;

        private InputField inputField = null;
        [SerializeField] private UIChattingWindow chatWindow = null;
        [SerializeField] private GameObject chatInputBox = null;

        private void Start() {
            var player = GameObject.FindWithTag("Player");
            playerController = player?.GetComponent<PlayerController>();
            if (playerController == null) throw new Exception("Player Controller doesn't exist");

            inputField = chatInputBox.GetComponentInChildren<InputField>();

            var connectedChannel = GameObject.Find("Channel Manager/Connected Channel");
            networkManager = connectedChannel?.GetComponent<NetworkManager>();
            if (networkManager == null) throw new Exception("Connected channel not found");

            networkManager.registerNotification(PacketType.NotifyChat, notifyChat);
        }

        private void OnDestroy() {
            networkManager.unregisterNotification(PacketType.NotifyChat);
        }

        private void Update() {
            if (Input.GetKeyDown(KeyCode.Return)) {
                if (!chatInputBox.activeSelf) {
                    this.enableInputBox();
                    return;
                }

                if (string.IsNullOrWhiteSpace(inputField.text)) {
                    this.disableInputBox();
                    return;
                }
                
                this.chatUserRequest();
            }

        }

        private void enableInputBox() {
            PlayerCamera.ShowCursor();
            PlayerCamera.EnabledInput = false;
            UIModalManager.EnabledInput = false;
            if (!playerController.IsAutoMoving) {
                playerController.blockInput();
                playerController.stopMovement();
            }

            chatInputBox.SetActive(true);
            inputField.ActivateInputField();
        }

        private void disableInputBox() {
            PlayerCamera.HideCursor();
            PlayerCamera.EnabledInput = true;
            UIModalManager.EnabledInput = true;
            if(!playerController.IsAutoMoving) {
                playerController.unblockInput();
                playerController.stopMovement();
            }

            inputField.text = "";
            chatInputBox.SetActive(false);
        }

        private void chatUserRequest() {
            NotifyChatPacket packet = new NotifyChatPacket();
            packet.playerId = AccountData.Instance.PlayerId;
            packet.name = AccountData.Instance.CurrentCharacter.name;
            packet.message = inputField.text;
            networkManager.sendPacket(packet);

            this.disableInputBox();
        }

        private void notifyChat(Packet rowPacket) {
            NotifyChatPacket packet = rowPacket as NotifyChatPacket;
            chatWindow?.createUserChatBox(packet.name, packet.message);
        }
    }
}