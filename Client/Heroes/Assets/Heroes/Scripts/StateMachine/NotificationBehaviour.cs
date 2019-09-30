using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NotificationBehaviour : StateMachineBehaviour {
	public string conditionName = "";
	public bool status = true;
	public bool resetOnExit = true;

	public override void OnStateUpdate(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)
	{
		animator.SetBool(conditionName, status);
	}

	override public void OnStateExit(Animator animator, AnimatorStateInfo stateInfo, int layerIndex) {
		animator.SetBool(conditionName, !status);
	}
}
