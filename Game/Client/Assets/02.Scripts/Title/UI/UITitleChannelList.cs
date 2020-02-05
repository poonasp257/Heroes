using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace Heroes {
    public class UITitleChannelList : MonoBehaviour {
        private ChannelManager channelManager;
        private MessageBoxHandler messageBoxHandler;

        [SerializeField] GameObject channelPrefab;

        private void Start() {
            var msgBoxHandlerObj = GameObject.Find("MessageBox Handler");
            messageBoxHandler = msgBoxHandlerObj?.GetComponent<MessageBoxHandler>();

            var channelManagerObj = GameObject.Find("Channel Manager");
            channelManager = channelManagerObj?.GetComponent<ChannelManager>();
            channelManager.channelListRequest(createChannelBoxes);

            messageBoxHandler.notice("채널 목록을 불러오고 있습니다.");
        }

        private void createChannelBoxes(List<ChannelInfo> channelList) {
            messageBoxHandler.close();

            foreach (ChannelInfo channel in channelList) {
				var channelBox = Instantiate(channelPrefab, this.transform);
                channelBox.name = channel.name;

				UIChannelBox channelInfo = channelBox.GetComponent<UIChannelBox>();
                channelInfo.onClickEvent = () => {
                    channelManager.connectToChannel(channel.ip, channel.port);
                    SceneManager.LoadScene("Select");                    
                };
			}    
        }
    }
}