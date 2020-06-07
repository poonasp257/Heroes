using System.Linq;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIFloatingInformation : MonoBehaviour {
	private List<Image> images;
	private List<Text> names;

	private Vector3 startScale;
	private bool isFadeIn = false;
	[SerializeField] private float fadeSpeed = 4.0f; 
	[SerializeField] private float minDistance = 6.0f;
	[SerializeField] private float maxDistance = 35.0f;

	private void Start() {
		images = GetComponentsInChildren<Image>().ToList();
		names = GetComponentsInChildren<Text>().ToList();
		startScale = transform.localScale;
	}

	private void  Update() {
		float dist = Vector3.Distance(Camera.main.transform.position, transform.position);
		if(!isFadeIn) {
			if (dist < maxDistance) {
				StartCoroutine("FadeIn");
			}

			return;
		}

		if(maxDistance <= dist ) StartCoroutine("FadeOut");		
		transform.transform.rotation = Camera.main.transform.rotation;
	}

	private void fadeAllInformation(float alpha) {
		foreach (var name in names) {
			var fadeColor = name.color;
			fadeColor.a = alpha;
			name.color = fadeColor;
		}

		foreach (var image in images) {
			var fadeColor = image.color;
			fadeColor.a = alpha;
			image.color = fadeColor;
		}
	}

	private IEnumerator FadeIn() {
		isFadeIn = true;
		
		float alpha = 0f;
		while(alpha < 1.0f) {
			alpha += Time.deltaTime * fadeSpeed;
			this.fadeAllInformation(alpha);

			yield return null;
		}
	}

	private IEnumerator FadeOut() {
		isFadeIn = false;

		float alpha = 1.0f;
		while (alpha > 0.0f) {
			alpha -= Time.deltaTime * fadeSpeed;
			this.fadeAllInformation(alpha);

			yield return null;
		}
	}
}
