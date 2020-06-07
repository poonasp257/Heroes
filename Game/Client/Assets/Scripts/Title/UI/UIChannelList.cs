using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace Heroes {
    public class UIChannelList : MonoBehaviour {
        private ChannelManager channelManager;

        [SerializeField] private GameObject channelPrefab = null;
        [SerializeField] private UISelectedChannel selectedChannelUI = null;

        private void Start() {
            var channelManagerObj = GameObject.Find("Channel Manager");
            channelManager = channelManagerObj?.GetComponent<ChannelManager>();
        }

        public void createChannelBoxes(List<ChannelInfo> channelList) {
            foreach (ChannelInfo channel in channelList) {
				var channelBoxObj = Instantiate(channelPrefab, this.transform);
                channelBoxObj.name = channel.name;

				UIChannelBox channelBox = channelBoxObj.GetComponent<UIChannelBox>();
                channelBox.onClickAction = () => selectedChannelUI.selectChannel(channel.name);
                channelBox.onConnectAction = () => {
                    channelManager.connectToChannel(channel.ip, channel.port);
                    AccountData.Instance.CurrentChannel = channel;
                    SceneManager.LoadScene("Select");                    
                };
			}    
        }
    }
}