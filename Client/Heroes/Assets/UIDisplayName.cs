using System.Collections;
using UnityEngine;

public class UIDisplayName : MonoBehaviour {
	private MeshRenderer[] meshRenderers;
	private Vector3 startScale;

	private bool isFadeIn;
	private const float fadeSpeed = 4.0f; 

	private const float minDistance = 6.0f;
	private const float maxDistance = 35.0f;

	private void Start() {
		meshRenderers = GetComponentsInChildren<MeshRenderer>();
		startScale = transform.localScale;
		isFadeIn = false;
	}

	private void  Update() {
		float dist = Vector3.Distance(Camera.main.transform.position, transform.position);
		if (!isFadeIn && dist < maxDistance) StartCoroutine("FadeIn");
		else if(isFadeIn && maxDistance <= dist ) StartCoroutine("FadeOut");
		
		if (!isFadeIn) return;

		if (dist < minDistance) dist = minDistance;

		transform.transform.rotation = Camera.main.transform.rotation;
		transform.localScale = startScale * (dist / minDistance);		
	}

	IEnumerator FadeIn() {
		isFadeIn = true;

		Color fadeColor = new Color(1.0f, 1.0f, 1.0f, 0.0f);
		while(fadeColor.a < 1.0f) {
			yield return null;

			fadeColor.a += Time.deltaTime * fadeSpeed;
			for(int i = 0; i < meshRenderers.Length; ++i) {
				meshRenderers[i].material.color = fadeColor;
			}
		}
	}

	IEnumerator FadeOut() {
		isFadeIn = false;

		Color fadeColor = new Color(1.0f, 1.0f, 1.0f, 1.0f);
		while(fadeColor.a > 0.0f) {
			yield return null;	

			fadeColor.a -= Time.deltaTime * fadeSpeed;
			for(int i = 0; i < meshRenderers.Length; ++i) {
				meshRenderers[i].material.color = fadeColor;
			}
		}
	}
}
