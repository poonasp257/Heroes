using System.Collections;
using UnityEngine;

namespace Heroes {
    public class BaseController : MonoBehaviour {
        protected Animator animator = null;
        protected CharacterController characterController = null;
        protected CharacterMovement movement;

        protected bool isBlockedInput = false;
        private Coroutine slowdownCoroutine = null;
        [SerializeField] private float slowDownSpeed = 2.0f;
        [SerializeField] private float rotationSpeed = 20.0f;

        protected virtual void Awake() {
            movement.moveAmount = 0f;
            movement.direction = Vector3.zero;
            movement.position = this.transform.position;
        }

        protected virtual void Start() {
            animator = GetComponentInChildren<Animator>();
            characterController = GetComponent<CharacterController>();
        }

        private void gravity() {
            this.updateMovement(Vector3.down * 20.0f);
        }

        private IEnumerator SlowDownMovement() {
            while (true) {
                movement.moveAmount -= Time.deltaTime * slowDownSpeed;
                if (movement.moveAmount < 0) movement.moveAmount = 0f;

                Vector3 target = new Vector3(0f, movement.direction.y, 0f);
                movement.direction = Vector3.MoveTowards(movement.direction, target, Time.deltaTime * slowDownSpeed);
                this.updateMovement(movement);
                if (movement.moveAmount == 0f &&
                    movement.direction.x == 0f &&
                    movement.direction.z == 0f) {
                    slowdownCoroutine = null;
                    yield break;
                }

                yield return null;
            }
        }

        public void stopMovement() {
            if (slowdownCoroutine != null) return;

            slowdownCoroutine = StartCoroutine(SlowDownMovement());
        }

        public virtual void resetMovement() {
            movement.moveAmount = 0f;
            movement.direction = Vector3.zero;
        }       

        public virtual void updateMovement(Vector3 direction) {
            characterController.Move(direction * Time.deltaTime);
        }

        public virtual void updateMovement(CharacterMovement movement) {
            animator.SetFloat("moveAmount", movement.moveAmount);
            Vector3 desiredMoveDirection = movement.direction;
            desiredMoveDirection.y = 0f;
            if (desiredMoveDirection == Vector3.zero) {
                desiredMoveDirection = transform.forward;
            }

            Quaternion lookAngle = Quaternion.LookRotation(desiredMoveDirection);
            transform.rotation = Quaternion.RotateTowards(transform.rotation, lookAngle, rotationSpeed);
            this.movement = movement;
        }

        protected virtual void Update() {

        }

        protected virtual void FixedUpdate() {
            gravity();
        }

        public void moveTo(CharacterMovement movement) {
            Vector3 to = movement.position;
            Vector3 moveDir = (to - this.transform.position).normalized;
            this.movement.moveAmount = movement.moveAmount;
            this.movement.direction = moveDir * movement.moveAmount * Time.deltaTime;
        }

        public void moveTo(Vector3 to) {
            if (movement.moveAmount <= 1f) {
                movement.moveAmount += Time.deltaTime;
            }

            Vector3 moveDir = (to - this.transform.position).normalized; 
            movement.direction = moveDir * movement.moveAmount * Time.deltaTime;
        }

        public void blockInput() {
            Input.ResetInputAxes();
            isBlockedInput = true;
        }

        public void unblockInput() {
            isBlockedInput = false;
        }
    }
}