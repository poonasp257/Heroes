using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

namespace Heroes {
	public class UICreatableItem : MonoBehaviour {
		private MessageBoxHandler msgbox;	

		private void Start() {
			msgbox = GameObject.Find("MessageBox Handler").GetComponent<MessageBoxHandler>();

			Button button = GetComponent<Button>();
			button.onClick.AddListener(() => {
				msgbox.confirm("캐릭터를 생성하시겠습니까?", () => SceneManager.LoadScene("Create"));	
			});
		}
	}
}