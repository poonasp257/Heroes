using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using UnityEngine.UI;

namespace Heroes {
	public class WorldMapController : MonoBehaviour {
		private bool isRotationg = false;

		private float zoom = 1.0f;
		private const float MinHeight = 15.0f;
		private const float MaxHeight = 200.0f;

		private RenderTexture targetTexture = null;
		[SerializeField] private RawImage worldMapImage = null;

		private Quaternion rotation = Quaternion.identity;
		private Transform worldMapView = null;
		private Camera viewCamera = null;
		private CameraFX viewCameraFX = null;

		private bool isFoundDestination = false;
		private Vector3 destination;
		private GameObject lightPillar = null;
		private LineRenderer routeRenderer = null;
		private Coroutine findRouteCoroutine = null;
		[SerializeField] private GameObject lightPillarPrefab;

		private PlayerController playerController = null;
		private PlayerStateManager playerStateManager = null;
		private GridManager gridManager = null;

		private InformHandler informHandler = null;

		private bool IsOpened { get { return worldMapImage.color.a > 0f; } }

		private void Start() {
			worldMapView = transform.Find("View");
			viewCamera = worldMapView.GetComponent<Camera>();
			viewCameraFX = viewCamera.GetComponent<CameraFX>();

			var route = transform.Find("Route");
			routeRenderer = route?.GetComponent<LineRenderer>();
			lightPillar = Instantiate(lightPillarPrefab);
			lightPillar.SetActive(false);

			var player = GameObject.FindWithTag("Player");
			playerController = player?.GetComponent<PlayerController>();
			playerStateManager = player?.GetComponent<PlayerStateManager>();

			gridManager = GameObject.Find("Grid Manager").GetComponent<GridManager>();

			informHandler = GameObject.Find("Canvas/Inform Handler").GetComponent<InformHandler>();
		}

		private void OnDestroy() {
			if(targetTexture) targetTexture.Release();
		}

		private void Update() {
			if (Input.GetButtonDown("Map")) {
				if (IsOpened) closeMap();
				else openMap();
			}
			else if (Input.GetButtonDown("Cancel")) {
				closeMap();
			}

			if (!IsOpened) return;

			if (Input.GetMouseButton(0)) moveAround();
			else if (Input.GetMouseButton(1)) rotateView();
			else if (Input.GetMouseButtonUp(1)) {
				if(isRotationg) {
					isRotationg = false;
					return;
				}

				if (isFoundDestination) {
					hideRoute();
					return;
				}

				isFoundDestination = findDestination();
				if (!isFoundDestination) {
					informHandler.displayMessage("갈 수 없는 곳입니다");
					return;
				}

				viewCameraFX.shake();
				findRouteCoroutine = StartCoroutine(FindRealtimeRoute());
			}

			zoomInOut();
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

		private void openMap() {
			UIModalManager.EnabledInput = false;
			PlayerCamera.EnabledInput = false;
			PlayerCamera.ShowCursor();

			playerController.stopMovement();
			playerController.blockInput();
			playerStateManager.disableRootMotion();

			createViewTexture();
			StartCoroutine(FadeInMap());
		}

		private void closeMap() {
			UIModalManager.EnabledInput = true;
			PlayerCamera.EnabledInput = true;
			PlayerCamera.HideCursor();

			playerController.unblockInput();
			playerStateManager.enableRootMotion();
			StartCoroutine(FadeOutMap());
		}

		private IEnumerator FadeInMap() {
			worldMapImage.gameObject.SetActive(true);
			Color color = worldMapImage.color;
			while (color.a < 1.0f) {
				yield return null;
				color.a += Time.deltaTime * 5.0f;
				worldMapImage.color = color;
			}
		}

		private IEnumerator FadeOutMap() {
			Color color = worldMapImage.color;
			while (color.a > 0) {
				yield return null;
				color.a -= Time.deltaTime * 5.0f;
				worldMapImage.color = color;
			}
			worldMapImage.gameObject.SetActive(false);
		}

		private void zoomInOut() {
			zoom -= Input.GetAxis("Mouse ScrollWheel");
			zoom = Mathf.Clamp(zoom, 1.0f, 2.0f);

			Vector3 pos = worldMapView.localPosition;
			pos.y = MinHeight + (MaxHeight - MinHeight) * (zoom - 1.0f);
			worldMapView.localPosition = pos;
		}

		private void moveAround() {
			Vector3 h = Input.GetAxis("Mouse X") * worldMapView.right;
			Vector3 v = Input.GetAxis("Mouse Y") * worldMapView.up;
			Vector3 moveDir = h + v;
			moveDir.y = 0f;
			transform.position -= moveDir * 2.0f * zoom;
		}

		private void rotateView() {
			float mouseX = Input.GetAxis("Mouse X");
			float mouseY = -Input.GetAxis("Mouse Y");
			if (mouseX == 0f && mouseY == 0f) return;

			rotation.y += mouseX * 2.0f;
			rotation.x += mouseY * 2.0f;
			rotation.x = Mathf.Clamp(rotation.x, -60, 0);
			Quaternion localRotation = Quaternion.Euler(rotation.x, rotation.y, 0.0f);
			transform.rotation = localRotation;
			isRotationg = true;
		}

		private bool findDestination() {
			int layMask = (1 << LayerMask.NameToLayer("Ground"))
				| (1 << LayerMask.NameToLayer("Enviroment"))
				| (1 << LayerMask.NameToLayer("Water"));
			Ray ray = viewCamera.ScreenPointToRay(Input.mousePosition);
			RaycastHit hit;
			if (Physics.Raycast(ray.origin, ray.direction, out hit, viewCamera.farClipPlane, layMask)) {
				if (hit.transform.gameObject.layer != LayerMask.NameToLayer("Ground")) {
					return false;
				}
			}

			destination = hit.point;
			return true;
		}

		private List<Vector3> findRoute() {
			var playerPosition = playerController.transform.position;
			return gridManager.findPath(playerPosition, destination);
		}

		private void drawLightPillar(Vector3 drawPoint) {
			lightPillar.transform.position = drawPoint;
			lightPillar.SetActive(true);
		}

		private void drawPath(List<Vector3> path) {
			routeRenderer.positionCount = path.Count;
			for (int i = 0; i < path.Count; ++i) {
				var node = path[i];
				node.y += 1f;
				routeRenderer.SetPosition(i, node);
			}
		}
		
		private void showRoute(List<Vector3> path) {
			drawLightPillar(path.Last());
			drawPath(path);
		}

		private void hideRoute() {
			isFoundDestination = false;
			lightPillar.SetActive(false);
			routeRenderer.positionCount = 0;
			if (findRouteCoroutine != null) StopCoroutine(findRouteCoroutine);
		}

		private IEnumerator FindRealtimeRoute() {
			while (isFoundDestination) {
				yield return new WaitForSeconds(0.1f);

				var path = findRoute();
				if (path == null) {
					informHandler.displayMessage("갈 수 없는 곳입니다");
					break;
				}

				path.RemoveAt(0);
				playerController.Route = path;

				if (path.Count == 0) break;

				showRoute(path);
			}

			hideRoute();
		}		
	}
}