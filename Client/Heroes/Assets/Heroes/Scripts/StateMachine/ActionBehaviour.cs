using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ActionBehaviour : StateMachineBehaviour {
	public bool status = true;
	public bool resetOnExit = true;

	override public void OnStateUpdate(Animator animator, AnimatorStateInfo stateInfo, int layerIndex) {
		animator.SetBool("canMove", status);
	}

	override public void OnStateExit(Animator animator, AnimatorStateInfo stateInfo, int layerIndex) {
		if(resetOnExit) animator.SetBool("canMove", !status);
	}
}
