using System.Collections;
using UnityEngine;

public class UIDisplayName : MonoBehaviour {
	private MeshRenderer[] meshRenderers;
	private Vector3 startScale;

	private bool isFadeIn;
	private const float FadeSpeed = 4.0f; 

	private const float MinDistance = 6.0f;
	private const float MaxDistance = 35.0f;

	private void Start() {
		meshRenderers = GetComponentsInChildren<MeshRenderer>();
		startScale = transform.localScale;
		isFadeIn = false;
	}

	private void  Update() {
		float dist = Vector3.Distance(Camera.main.transform.position, transform.position);
		if (!isFadeIn && dist < MaxDistance) StartCoroutine("FadeIn");
		else if(isFadeIn && MaxDistance <= dist ) StartCoroutine("FadeOut");
		
		if (!isFadeIn) return;

		if (dist < MinDistance) dist = MinDistance;

		transform.transform.rotation = Camera.main.transform.rotation;
		transform.localScale = startScale * (dist / MinDistance);		
	}

	IEnumerator FadeIn() {
		isFadeIn = true;

		Color fadeColor = new Color(1.0f, 1.0f, 1.0f, 0.0f);
		while(fadeColor.a < 1.0f) {
			yield return null;

			fadeColor.a += Time.deltaTime * FadeSpeed;
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

			fadeColor.a -= Time.deltaTime * FadeSpeed;
			for(int i = 0; i < meshRenderers.Length; ++i) {
				meshRenderers[i].material.color = fadeColor;
			}
		}
	}
}
