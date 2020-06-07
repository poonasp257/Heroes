using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class ObjectManager {
		private static ObjectManager instance = null;
		private List<GameObject> gameObjects = null;

		public static ObjectManager Instance {
			get {
				if (instance == null) {
					instance = new ObjectManager();
					instance.gameObjects = new List<GameObject>();
				}

				return instance;
			}
		}

		public void DontDestroyOnLoad(GameObject target) {
			Object.DontDestroyOnLoad(target);
			gameObjects.Add(target);
		}

		public void Destroy(string objectName) {
			for(int i = 0; i < gameObjects.Count; ++i) {
				if(gameObjects[i].name != objectName) continue;
					 
				GameObject.Destroy(gameObjects[i]);
				gameObjects.RemoveAt(i);
			}
		}

		public void DestroyAllObjects() {
			foreach (var gameObject in gameObjects) {
				GameObject.Destroy(gameObject);
			}

			gameObjects.Clear();
		}

		public void DestroyAllObjects(string excludeObjectName) {
			for(int i = 0; i < gameObjects.Count; ) {
				if(gameObjects[i].name == excludeObjectName) { 
					++i;
					continue;
				}

				GameObject.Destroy(gameObjects[i]);
				gameObjects.RemoveAt(i);
			}
		}
		
		public void DestroyAllObjects(List<string> excludeObjectNames) {
			for(int i = 0; i < gameObjects.Count; ) {
				if(excludeObjectNames.Contains(gameObjects[i].name)) { 
					++i;
					continue;
				}

				GameObject.Destroy(gameObjects[i]);
				gameObjects.RemoveAt(i);
			}
		}
	}
}