using UnityEngine;

namespace Heroes {
	public class MinimapIcon : MonoBehaviour {
		private SpriteRenderer iconRenderer;

		[SerializeField] private GameObject fieldOfViewPrefab;
		
		[SerializeField] private Sprite playerIcon;
		[SerializeField] private Sprite otherPlayerIcon;

		private void Start() {
			iconRenderer = GetComponent<SpriteRenderer>();

			if (this.transform.parent.tag == "Player") {
				iconRenderer.sprite = playerIcon;
				Instantiate(fieldOfViewPrefab, this.transform);
			}
			else if(this.transform.parent.tag == "Other Player") {
				iconRenderer.sprite = otherPlayerIcon;
			}
		}
	}
}