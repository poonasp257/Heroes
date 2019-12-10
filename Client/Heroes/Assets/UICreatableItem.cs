using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

namespace Heroes {
	public class UICreatableItem : MonoBehaviour {
		private MessageBox msgbox;	

		private void Start() {
			msgbox = GameObject.Find("Message Handler").GetComponent<MessageBox>();

			Button button = GetComponent<Button>();
			button.onClick.AddListener(() => {
				msgbox.confirm("캐릭터를 생성하시겠습니까?", () => SceneManager.LoadScene("Create"));	
			});
		}
	}
}