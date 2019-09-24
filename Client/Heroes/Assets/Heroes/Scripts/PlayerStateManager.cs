using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class PlayerStateManager : MonoBehaviour {
		public enum ActionState {
			Idle, Move, Attack, Roll, Dash, Hit, Dead
		};

		private const float MaxComboDelay = 0.3f;

		private bool inAction;
		private float lastAttackTime;
		private CharacterStatus status;

		public float horizon; //{ get; private set; }
		public float vertical; //{ get; private set; }

		public bool isPressedLB; //{ get; private set; }
		public bool isPressedRB; //{ get; private set; }
		public int countOfLeftAttack; //{ get; private set; }

		public ActionState state; //{ get; private set; }


		void Start() {
			Initialize();
			status = new CharacterStatus();
		}

		void Update() {
			InputHandler();
			Tick();
		}

		void Initialize() { 
			inAction = false;
			state = ActionState.Idle;
		}

		private void InputHandler() {
			horizon = Input.GetAxis("Horizontal");
			vertical = Input.GetAxis("Vertical");

			if (Input.GetMouseButtonDown(0)) { 
				isPressedLB = true;
				++countOfLeftAttack;
				lastAttackTime = Time.time;
			}
			else if (Input.GetMouseButtonDown(1)) { 
				isPressedRB = true;
				lastAttackTime = Time.time;
			}

			if (Input.GetMouseButtonUp(0)) isPressedLB = false; 
			else if (Input.GetMouseButtonUp(1)) isPressedRB = false;
		}

		private void Tick() {
			if(Time.time - lastAttackTime > MaxComboDelay) {
				countOfLeftAttack = 0;
			}

			UpdateActionState();
		}
		 
		private void UpdateActionState() {
			if (horizon != 0 || vertical != 0) state = ActionState.Move;
			else state = ActionState.Idle;
		}
	}
}