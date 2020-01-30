using System.Collections;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace Heroes {
	public class LoadingSceneManager : MonoBehaviour {
		private static string nextScene;

		private PlayerManager playerManager;
		private SoundManager soundManager;
	
		private GameObject objects;

		private void Start() {
			playerManager = GameObject.Find("Player Manager").GetComponent<PlayerManager>();
			soundManager = GameObject.Find("Sound Manager").GetComponent<SoundManager>();

			objects = GameObject.Find("Objects");

			StartCoroutine(Loading());
		}

		public static void LoadScene(string sceneName) {
			nextScene = sceneName;
			SceneManager.LoadScene("Loading");
		}

		public IEnumerator Loading() {
			AsyncOperation op = SceneManager.LoadSceneAsync(nextScene);
			op.allowSceneActivation = false;

			while (!op.isDone) {
				yield return null;

				Vector3 screenPos = Camera.main.WorldToScreenPoint(objects.transform.position);
				Vector3 targetPos = screenPos;
				targetPos.x = Camera.main.pixelWidth;

				Vector3 movePos = Vector3.MoveTowards(screenPos, targetPos, 10.0f);
				objects.transform.position = Camera.main.ScreenToWorldPoint(movePos);

				if (op.progress >= 0.9f) {
					if (targetPos.x < screenPos.x + 300.0f) {
						op.allowSceneActivation = true;
						playerManager.activeAllPlayer();
						soundManager.PlayBGM(BGMState.Main);
						yield break;
					}
				}
			}
		}
	}
}