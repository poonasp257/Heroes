using System;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

namespace Heroes {
	public class UICreatableBox : MonoBehaviour {
		private MessageBoxHandler messageBoxHandler;	

		private void Start() {
			var messageBoxHandlerObj = GameObject.Find("MessageBox Handler");
			messageBoxHandler = messageBoxHandlerObj.GetComponent<MessageBoxHandler>();
			if (messageBoxHandler == null) throw new Exception("MessageBox Handler not found"); 

			var button = GetComponent<Button>();
			button.onClick.AddListener(() => messageBoxHandler.confirm("캐릭터를 생성하시겠습니까?", 
				() => SceneManager.LoadScene("Create")));
		}
	}
}