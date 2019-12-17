using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public enum BGMState {
		Title, Main		
	}

	public class SoundManager : MonoBehaviour {
		private AudioSource bgm;

		[Header("Background Music")]
		[SerializeField] private AudioClip titleBGM;
		[SerializeField] private AudioClip mainBGM;

		[Header("Sound FX")]
		[SerializeField] private AudioClip attackSound; 

		private void Start() {
			bgm = GetComponent<AudioSource>();

			if (!titleBGM) return;

			bgm.clip = titleBGM;
			bgm.loop = true;
			bgm.Play();

			DontDestroyOnLoad(this.gameObject);
		}

		private void Update() {
			if (Input.GetKeyDown(KeyCode.F1)) {
				bgm.enabled = false;
			}
		}

		public void PlayBGM(BGMState state) {
			switch(state) {
				case BGMState.Title: bgm.clip = titleBGM; break;
				case BGMState.Main: bgm.clip = mainBGM; break;
			}

			bgm.Play();
		}

		public void StopBGM() {
			bgm.Stop();
		}
	}
}