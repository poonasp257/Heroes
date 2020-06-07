using System;
using UnityEngine;

namespace Heroes {
	public class MonsterController : BaseController {
		private bool isHit = false;
		private float displayTimer = 0.0f;
		private const float displayDurationTime = 30.0f;
		private UIFloatingInformation informationUI = null;
		public MonsterStateManager stateManager = null;

		public MonsterSpawnZone SpawnZone { get; set; }
		public bool NeedReturnOriginPosition { get; set;}

		public float moveAmount;
		public Vector3 position;
		public Vector3 direction;
 
		protected void OnDisable() {
			this.disableInformation();
		}

		protected override void Awake() {
			base.Awake();

			stateManager = GetComponent<MonsterStateManager>();
			informationUI = GetComponentInChildren<UIFloatingInformation>();
			informationUI.gameObject.SetActive(false);
		}
			 
		protected override void Start() {
			base.Start();
		}

		protected override void Update() {
			base.Update();

			if(isHit) {
				displayTimer += Time.deltaTime;
				if (displayTimer < displayDurationTime) return;

				this.disableInformation();
			}
		}

        protected override void FixedUpdate() {
			moveAmount = movement.moveAmount;
			position = movement.position;
			direction = movement.direction;

            base.FixedUpdate();

			if(NeedReturnOriginPosition) {
				if (Vector3.Distance(transform.position, stateManager.info.originPosition) > 1f) {
					transform.position = Vector3.MoveTowards(transform.position,
						stateManager.info.originPosition, Time.deltaTime * 4.0f);
					stateManager.info.currentHp += 10;
					if(stateManager.info.currentHp > stateManager.info.maxHp) {
						stateManager.info.currentHp = stateManager.info.maxHp;
					}

					return;
				}

				NeedReturnOriginPosition = false;
				this.resetMovement();
				this.updateMovement(movement);
				transform.position = stateManager.info.originPosition;
				transform.rotation = Quaternion.Euler(stateManager.info.originRotation);
				stateManager.info.currentHp = stateManager.info.maxHp;
			}

			if (Vector3.Distance(transform.position, movement.position) > 2.0f) {
				transform.position = Vector3.MoveTowards(transform.position, 
					movement.position, Time.deltaTime * 4.0f);
				this.updateMovement(movement);
				return;
			}
			else { 
				base.resetMovement();
				this.updateMovement(movement);
				return;
			}
		}

		private void OnTriggerEnter(Collider other) {
			if(other.tag == "Weapon") {
				this.enableInformation();

				UInt64 monsterId = (stateManager as MonsterStateManager).info.id;
				SpawnZone.takeDamage(monsterId);
			}
		}

		private void enableInformation() {
			isHit = true;
			displayTimer = 0f;
			informationUI.gameObject.SetActive(true);
		}

		private void disableInformation() {
			isHit = false;
			displayTimer = 0f;
			informationUI.gameObject.SetActive(false);
		}

		public override void resetMovement() {
			base.resetMovement();
			movement.position = stateManager.info.originPosition;
		}

        public override void updateMovement(CharacterMovement movement) {
			animator.SetFloat("moveAmount", movement.moveAmount);
			Vector3 desiredMoveDirection = (movement.position - transform.position).normalized;
			desiredMoveDirection.y = 0f;
			if (desiredMoveDirection == Vector3.zero) {
				desiredMoveDirection = transform.forward;
			}

			transform.rotation = Quaternion.LookRotation(desiredMoveDirection);
			this.movement = movement;
		}

		public void loseAggression() {
			NeedReturnOriginPosition = true;
			movement.moveAmount = 1.0f;
			movement.position = stateManager.info.originPosition;
			movement.direction = (stateManager.info.originPosition - transform.position).normalized;
			this.updateMovement(movement);
		}
	}
}