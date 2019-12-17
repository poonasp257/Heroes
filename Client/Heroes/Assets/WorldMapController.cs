using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

namespace Heroes {
	public class WorldMapController : MonoBehaviour {
		private bool isOpened = false;
		private bool isRotationg = false;

		private float mouseX;
		private float mouseY;

		private float zoom = 1.0f;
		private const float MinHeight = 150.0f;
		private const float MaxHeight = 300.0f;
		private const float offset = 20.0f;
		private const float sensitivity = 1.0f;

		private RenderTexture targetTexture = null;

		private RawImage worldMapImage = null;
		[SerializeField] private GameObject worldMap = null;

		private Quaternion rotation = Quaternion.identity;
		private Transform worldMapView = null;
		private Camera viewCamera = null;
		private CameraFX viewCameraFX = null;

		private GameObject lightPillar;
		[SerializeField] private GameObject lightPillarPrefab;

		private GameObject player = null;
		private PlayerController playerController = null;
		private GridManager gridManager = null;
		private Coroutine pathFindCorutine = null;
		private List<Vector3> path = new List<Vector3>();

		private void OnDestroy() {
			targetTexture.Release();
		}
		
		private void Start() {
			if(worldMap) {
				worldMapImage = worldMap.GetComponent<RawImage>();
			}

			worldMapView = transform.Find("View");
			viewCamera = worldMapView.GetComponent<Camera>();
			viewCameraFX = viewCamera.GetComponent<CameraFX>();
			
			lightPillar = Instantiate(lightPillarPrefab);
			lightPillar.SetActive(false);

			player = GameObject.FindWithTag("Player");
			playerController = player.GetComponent<PlayerController>();
			gridManager = GameObject.Find("Grid Manager").GetComponent<GridManager>();

			createViewTexture();
			closeMap();
		}

		private void Update() {
			if(Input.GetKeyDown(KeyCode.M)) {
				if (isOpened) closeMap();
				else openMap();
			}

			if (!isOpened) return;

			zoomInOut();

			if (Input.GetMouseButton(0)) moveAround();
			else if (Input.GetMouseButton(1)) { 
				rotateView();
				if(mouseX != 0.0f && mouseY != 0.0f) isRotationg = true;
			}
			else if(Input.GetMouseButtonUp(1)) {
				if(!isRotationg) showRoute();

				isRotationg = false;
			}

			mouseX = Input.GetAxis("Mouse X");
			mouseY = Input.GetAxis("Mouse Y");
		}

		private void createViewTexture() {
			if(targetTexture) {
				if (Screen.width == targetTexture.width
					&& Screen.height == targetTexture.height) return;

				targetTexture.Release();
			}
			
			targetTexture = new RenderTexture(Screen.width, Screen.height, 0);
			targetTexture.Create();

			worldMapImage.texture = targetTexture;
			viewCamera.targetTexture = targetTexture;
		}

		private void zoomInOut() {
			zoom -= Input.GetAxis("Mouse ScrollWheel");
			zoom = Mathf.Clamp(zoom, 1.0f, 2.0f);

			Vector3 pos = worldMapView.localPosition;
			pos.y = MinHeight + (MaxHeight - MinHeight) * (zoom - 1.0f);

			worldMapView.localPosition = pos;
		}

		private void moveAround() {			
			Vector3 h = mouseX * worldMapView.right;
			Vector3 v = -mouseY * worldMapView.up;

			Vector3 moveDir = h + v;
			moveDir.y = 0;

			transform.position -= moveDir * 2.0f * zoom;
		}

		private void rotateView() {
			rotation.y += mouseX * 2.0f;
			rotation.x += mouseY * 2.0f;

			rotation.x = Mathf.Clamp(rotation.x, -60, 0);

			Quaternion localRotation = Quaternion.Euler(rotation.x, rotation.y, 0.0f);
			transform.rotation = localRotation;
		}
		
		private void showRoute() {
			if(lightPillar.activeSelf) {
				if (pathFindCorutine != null) StopCoroutine(pathFindCorutine);
				lightPillar.SetActive(false);
				return;
			}

			int layMask = (1 << LayerMask.NameToLayer("Ground"))
				| (1 << LayerMask.NameToLayer("Enviroment"))
				| (1 << LayerMask.NameToLayer("Water"));

			Ray ray = viewCamera.ScreenPointToRay(Input.mousePosition);
			RaycastHit hit;

			if (Physics.Raycast(ray.origin, ray.direction, out hit, viewCamera.farClipPlane, layMask)) {
				if (hit.transform.gameObject.layer != LayerMask.NameToLayer("Ground")) {
					print("갈 수 없는 곳입니다.");
					return;
				}

				path = gridManager.findPath(player.transform.position, hit.point);

				Vector3 hitOnCell = gridManager.posToCenter(hit.point);
				hitOnCell.y = hit.point.y;

				drawLightPillar(hitOnCell);
				drawPath(path);
			}
		}

		private void drawLightPillar(Vector3 drawPoint) {
			lightPillar.transform.position = drawPoint;
			lightPillar.SetActive(true);

			viewCameraFX.Shake();
		}

		private void drawPath(List<Vector3> path) {
			for (int i = 0; i < path.Count - 1; ++i) {
				Debug.DrawLine(path[i], path[i + 1], Color.blue, 1000.0f);
			}
		}

		public void openMap() {
			createViewTexture();	

			Cursor.lockState = CursorLockMode.None;
			Cursor.visible = true;
			StartCoroutine("FadeInMap");
		}

		public void closeMap() {
			Cursor.lockState = CursorLockMode.Locked;
			Cursor.visible = false;
			StartCoroutine("FadeOutMap");
		}

		public IEnumerator MoveOneWayPath() {
			if (path == null || player == null) yield break;

			foreach(var node in path) {
				Vector3 to = node;
				to.y = player.transform.position.y;

				float distance = Mathf.Infinity;
				while (distance > 3.0f) {
					playerController.MoveTo(to);
					distance = Vector3.Distance(player.transform.position, to);
					yield return null;
				}
			}

			playerController.StopMovement();
			lightPillar.SetActive(false);
		}

		//public IEnumerator MoveRoundTripPath(GameObject player) {
			
		//}

		IEnumerator FadeInMap() {
			Color color = worldMapImage.color;
			while (true) {
				color.a += Time.deltaTime * 8.0f;
				worldMapImage.color = color;

				if (color.a >= 1.0f) {
					isOpened = true;
					yield break;
				}

				yield return null;
			}
		}

		IEnumerator FadeOutMap() {
			Color color = worldMapImage.color;
			while (true) {
				color.a -= Time.deltaTime * 8.0f;
				worldMapImage.color = color;

				if (color.a <= 0) {
					isOpened = false;
					yield break;
				}

				yield return null;
			}
		}		
	}
}