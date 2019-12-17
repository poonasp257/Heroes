using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class MonsterController : MonoBehaviour {
		[SerializeField] private float hp = 100;

		private Animator animator;

		private GameObject target;
		Vector3 moveDir;

		private float coolTime = 2.0f;

		private void Start() {
			animator = GetComponent<Animator>();
		}

		private void Update() {
			if (!target || hp <= 0 ) return;
			moveDir = Vector3.zero;
			ChasingTarget();

			animator.SetFloat("moveAmount",moveDir.magnitude);
		}

		private void OnTriggerEnter(Collider collider) {
			DamageCollider damageCollider = collider.GetComponent<DamageCollider>();
			if (damageCollider) TakeDamage(damageCollider.Damage);
		}

		private void TakeDamage(float damage) {
			hp -= damage;
			animator.Play("Take Damage");

			if(hp <= 0 ) {
				animator.Play("Die");
			}
		}

		private void Attack() {
			animator.Play("Attack");
			var state = target.GetComponentInParent<CharacterStateManager>();
			var info = state.Info;
			info.currentHp -= 10;
			state.Info = info;
		}

		private void ChasingTarget() {
			Vector3 targetPos = target.transform.position;
			Vector3 myPos = transform.position;

			float dist = Vector3.Distance(targetPos, myPos);
			if (dist < 3.0f)
			{
				coolTime += Time.deltaTime;
				if (coolTime >= 2.0f)
				{
					Attack();
					coolTime = 0.0f;
				}
				return;
			}

			moveDir = (targetPos - myPos).normalized;
			
			transform.position += moveDir * Time.deltaTime * 2.0f;
			transform.LookAt(target.transform, transform.up);
		}

		public void setTarget(GameObject target) {
			this.target = target;
		}
	}
}