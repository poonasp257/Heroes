using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class AuthenticationManager : MonoBehaviour {
		private void Start() {

		}

		private void Update() {

		}
			   
		public void RequestLogin() {
			Debug.Log("Login request");

			LoadingSceneManager.LoadScene("Town");
		}

		public void RequestRegister() {
			Debug.Log("Register request");
		}
	}
}