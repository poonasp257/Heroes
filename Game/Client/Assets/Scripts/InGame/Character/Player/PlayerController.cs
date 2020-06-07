using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;

namespace Heroes {
	public class PlayerController : BaseController {
		private PlayerManager playerManager = null;
		private PlayerStateManager stateManager = null;
		private Coroutine moveCoroutine = null;

		private float delayTimer = 0f;
		protected Vector3 previousMoveDir = Vector3.zero;
		protected Vector3 currentMoveDir = Vector3.zero;

		public List<Vector3> Route { get; set; }

		public bool IsAutoMoving { get { return moveCoroutine != null; } }

		protected override void Start() {
			base.Start();

			stateManager = GetComponent<PlayerStateManager>();
			if (stateManager == null) {
				stateManager = gameObject.AddComponent<PlayerStateManager>();
			}
			
			var playerManagerObj = GameObject.Find("Player Manager");
			playerManager = playerManagerObj?.GetComponent<PlayerManager>();
			if (playerManager == null) throw new Exception("Player Manager not found");
		}

		protected override void Update() {
			if (stateManager.IsDead) {
				playerManager.activeRequestReviveWindow();
			}

			if (isBlockedInput ||
				stateManager.IsInAction ||
				PlayerCamera.EnabledCursor) return;
				
			inputAction();
			inputInteraction();
		}

		protected override void FixedUpdate() {
			if (stateManager.IsDead) return;

			base.FixedUpdate();

			if (!stateManager.IsGrounded ||
				stateManager.IsInAction) return;

			if (!isBlockedInput) processMovement();
		}

		private void processMovement() {
			float horizon = Input.GetAxis("Horizontal");
			float vertical = Input.GetAxis("Vertical"); 
			Vector3 h = horizon * Camera.main.transform.right;
			Vector3 v = vertical * Camera.main.transform.forward;
			previousMoveDir = currentMoveDir;
			currentMoveDir = (h + v).normalized;

			if (horizon == 0f && vertical == 0f) {
				if(previousMoveDir != Vector3.zero) {
					PlayerCamera.EnabledInput = true;
				}

				return;
			}

			if (moveCoroutine != null) this.stopAutoMove();

			PlayerCamera.EnabledInput = false;
			PlayerCamera.HideCursor();
			movement.moveAmount = Mathf.Clamp01(new Vector2(horizon, vertical).sqrMagnitude);
			movement.direction = currentMoveDir * movement.moveAmount * Time.deltaTime;
			this.updateMovement(movement);
			notifyCharacterMovement();
		}

		private void notifyCharacterMovement() {
            delayTimer += Time.deltaTime;
			if (delayTimer >= 0.03f) {
				movement.position = transform.position;
				playerManager.notifyMovement(movement);
				delayTimer = 0f;
			}

			return;
        }

        private void inputAction() {
			if (Input.GetButtonDown("Roll")) {
				this.stopMovement();
				stateManager.executeAction(ActionType.Roll);
				movement.position = transform.position;
				playerManager.notifyAction(ActionType.Roll, movement);
			}
			else if (Input.GetButtonDown("Attack")) {
				this.stopMovement();
				stateManager.executeAction(ActionType.Attack);
				movement.position = transform.position;
				playerManager.notifyAction(ActionType.Attack, movement);
			}
		}

		private void inputInteraction() {
			if (Input.GetButtonDown("Auto Move")) {
				if (moveCoroutine == null) followRoute();
				else stopAutoMove();
			}
		}

		private void stopAutoMove() {
			StopCoroutine(moveCoroutine);
			moveCoroutine = null;
			this.stopMovement();
		}

		private void followRoute() {
			if (Route == null) return;

			moveCoroutine = StartCoroutine(MoveOneWayPath());
			// moveCoroutine = StartCoroutine(MoveRoundTripPath());
		}

		private IEnumerator MoveOneWayPath() {
			while (Route.Count > 0) {
				Vector3 to = Route.First();
				to.y = this.transform.position.y;
				while (true) {
					yield return null;

					float distance = Vector3.Distance(this.transform.position, to);
					if (distance <= 1f) break;

					this.moveTo(to);
					this.updateMovement(movement);
					notifyCharacterMovement();
				}
			}

			if (moveCoroutine != null) stopAutoMove();
		}

		private IEnumerator MoveRoundTripPath() {
			yield break;
		}
	}
}