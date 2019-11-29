using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class PlayerController : MonoBehaviour {
		private Animator animator;
		private CharacterController controller;
		private PlayerManager playerManager;

		private bool isAttacking;
		private bool isRolling;

		private float horizon;
		private float vertical;
		private float moveAmount;
		private Vector3 moveDirection;
		private Vector3 desiredMoveDirection;

		private const float MaxComboDelay = 0.4f;
		private const float MaxRunSpeed = 1.0f;
		private const float MaxSprintSpeed = 1.4f;

		[Header("Movement")]
		[SerializeField] private float rotationSpeed = 0.5f;
		[SerializeField] private float moveSpeed = 1.0f;

		[Header("Attack")]
		[SerializeField] private int attackStep;
		[SerializeField] private float lastAttackTime;

		private void Start() {
			Initialize();
		}

		private void Update() {
			InputAction();
			DetectAction();
		}

		private void FixedUpdate() {
			if (controller.isGrounded) {
				InputMovement();
				ProcessMovement();
			}

			UpdateAnimatorState();
		}

		private void Initialize() {
			playerManager = GameObject.Find("Player Manager").GetComponent<PlayerManager>();

			animator = GetComponent<Animator>();
			controller = GetComponent<CharacterController>();

			lastAttackTime = 0.0f;
			attackStep = 0;
		}

		private void InputAction() {
			if (Input.GetButtonDown("Roll")) Roll();
			else if (Input.GetButtonDown("Weak Attack")) WeakAttack();
			else if (Input.GetButtonDown("Smash Attack")) SmashAttack();
		}

		private void DetectAction() {
			isAttacking = animator.GetBool("isAttacking");
			isRolling = animator.GetBool("isRolling");

			if (isAttacking) {
				lastAttackTime = Time.time;
				return;
			}

			if (Time.time - lastAttackTime > MaxComboDelay) {
				attackStep = 0;
				animator.SetInteger("attackStep", attackStep);
				animator.SetBool("LButton", false);
				animator.SetBool("RButton", false);
				return;
			}
		}

		private void InputMovement() {
			horizon = Input.GetAxis("Horizontal");
			vertical = Input.GetAxis("Vertical");

			Camera camera = Camera.main;
			Vector3 h = horizon * camera.transform.right;
			Vector3 v = vertical * camera.transform.forward;

			moveDirection = (h + v).normalized;
			moveAmount = new Vector2(horizon, vertical).sqrMagnitude;
			moveAmount = Mathf.Clamp01(moveAmount);

			if (Input.GetButtonDown("Sprint")) moveSpeed = MaxSprintSpeed;
			else if (Input.GetButtonUp("Sprint")) moveSpeed = MaxRunSpeed;
		}

		private void UpdateAnimatorState() {
			animator.SetFloat("moveAmount", moveAmount);
			animator.SetFloat("moveSpeed", moveSpeed);
		}

		private void ProcessMovement() {
			if (controller.isGrounded == false) {
				Gravity();
				return;
			}

			if (moveAmount == 0.0f || isAttacking) return;

			LookMoveDirection();
			Move();

			playerManager.inputMovement(new CharacterMovement(
				moveAmount, transform.position, transform.eulerAngles));
		}

		private void Gravity() {
			if (controller.isGrounded) return;

			Vector3 gravity = Vector3.down * 9.8f;
			controller.Move(gravity * Time.deltaTime);
		}

		private void LookMoveDirection() {
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
			controller.Move(motion * Time.deltaTime);
		}

		private void Roll() {
			if (isRolling) return;

			animator.SetTrigger("Roll");
		}

		private void WeakAttack() {
			if (attackStep >= 4 || isAttacking) return;

			animator.SetInteger("attackStep", attackStep);
			animator.SetTrigger("Combat");
			lastAttackTime = Time.time;
			++attackStep;
		}

		private void SmashAttack() {
			if (attackStep == 0) return;

			animator.SetBool("RButton", true);
			attackStep = 0;
		}
	}
}