using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class PlayerMovement : MonoBehaviour {
		private Animator animator;
		private CharacterController controller;
		private PlayerStateManager stateManager;

		private float horizon;
		private float vertical;
		private float inputMagnitude;
		private Vector3 moveDirection;
		private Vector3 desiredMoveDirection;

		public float desiredRotationSpeed;
		public float allowPlayerRotation;
		public float moveSpeed;

		private void Start() {
			animator = GetComponent<Animator>();
			controller = GetComponent<CharacterController>();
			stateManager = GetComponent<PlayerStateManager>();

			moveDirection = Vector3.zero;
			desiredMoveDirection = Vector3.zero;
		}

		private void Update() {
			ProcessInput();
		}

		private void ProcessInput() {
			horizon = stateManager.horizon;
			vertical = stateManager.vertical;
						
			inputMagnitude = new Vector2(horizon, vertical).sqrMagnitude;
			inputMagnitude = Mathf.Clamp01(inputMagnitude);
			animator.SetFloat("Magnitude", inputMagnitude);

			if (inputMagnitude > allowPlayerRotation) Rotation();
			else desiredMoveDirection = Vector3.zero;

			Move();
		}

		private void Rotation() {
			Camera camera = Camera.main;
			Vector3 forward = camera.transform.forward;
			Vector3 right = camera.transform.right;

			forward.y = 0.0f;
			right.y = 0.0f;

			forward.Normalize();
			right.Normalize();

			desiredMoveDirection = forward * vertical + right * horizon;

			transform.rotation = Quaternion.Slerp(transform.rotation,
			Quaternion.LookRotation(desiredMoveDirection), desiredRotationSpeed);
		}

		private void Move() {
			if (controller.isGrounded) {
				moveDirection = transform.forward * inputMagnitude * moveSpeed;
			}

			moveDirection.y -= 45.0f * Time.deltaTime;
			controller.Move(moveDirection * Time.deltaTime);
		}
	}
}