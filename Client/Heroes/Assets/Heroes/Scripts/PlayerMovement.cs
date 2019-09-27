using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class PlayerMovement : MonoBehaviour {
		private Animator animator;
		private CharacterController controller;
		private PlayerStateManager stateManager;

		private float lastRollTime;
		private float horizon;
		private float vertical;
		private float moveAmount;
		private Vector3 moveDirection;
		private Vector3 desiredMoveDirection;

		[SerializeField] private float rotationSpeed = 0.5f;
		[SerializeField] private float allowPlayerRotation = 0.0f;
		[SerializeField] private float moveSpeed = 7.0f;
		[SerializeField] private float rollCoolTime = 1.0f;

		private void Start() {
			Initialize();
		}

		private void Update() {
			InputAction();
		}

		private void FixedUpdate() {
			ProcessInput();
			FixedTick();
		}

		private void Initialize() {
			animator = GetComponent<Animator>();
			controller = GetComponent<CharacterController>();
			stateManager = GetComponent<PlayerStateManager>();

			lastRollTime = 0.0f;
		}

		private void InputAction() {
			if (Input.GetButtonDown("Roll")) Roll();
		}

		private void ProcessInput() {
			if (stateManager.InAction) return;

			horizon = Input.GetAxis("Horizontal");
			vertical = Input.GetAxis("Vertical");

			Camera camera = Camera.main;
			Vector3 h = horizon * camera.transform.right;
			Vector3 v = vertical * camera.transform.forward;

			moveDirection = (h + v).normalized;
			moveAmount = new Vector2(horizon, vertical).sqrMagnitude;
			moveAmount = Mathf.Clamp01(moveAmount);
			animator.SetFloat("moveAmount", moveAmount);
		}

		private void FixedTick() {
			Rotate();
			Move();
		}

		private void Rotate() {
			if (moveAmount < allowPlayerRotation) return;

			desiredMoveDirection = moveDirection;
			desiredMoveDirection.y = 0.0f;
			if (desiredMoveDirection == Vector3.zero) {
				desiredMoveDirection = transform.forward;
			}

			Quaternion lookAngle = Quaternion.LookRotation(desiredMoveDirection);
			transform.rotation = Quaternion.Slerp(transform.rotation,
				lookAngle, rotationSpeed);
		}

		private void Move() {
			Vector3 motion = moveDirection * moveAmount * moveSpeed;

			if(controller.isGrounded == false) {
				motion.y -= 9.8f;
			}

			controller.Move(motion * Time.deltaTime);
		}

		private void Roll() {
			if (Time.time - lastRollTime < rollCoolTime) return;

			animator.CrossFade("Roll", 0.2f);
			stateManager.InAction = true;
			lastRollTime = Time.time;
		}
	}
}