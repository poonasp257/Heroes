using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace Heroes {
	public class LoadingSceneManager : MonoBehaviour {
		private static string nextScene;
		private GameObject player;
		private GameObject monster;

		private void Start() {
			StartCoroutine(LoadScene());

			player = GameObject.Find("Player");
			monster = GameObject.Find("Monster");
		}

		public static void LoadScene(string sceneName) {
			nextScene = sceneName;
			SceneManager.LoadScene("Loading");
		}

		IEnumerator LoadScene() {
			yield return null;

			AsyncOperation op = SceneManager.LoadSceneAsync(nextScene);
			op.allowSceneActivation = false;

			float timer = 0.0f;
			while (!op.isDone) {
				yield return null;

				timer += Time.deltaTime;
				if (op.progress >= 0.9f) {
					op.allowSceneActivation = true;
				}
				else {
					
				}
			}
		}
	}
}