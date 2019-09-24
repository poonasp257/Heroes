using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerCombat : MonoBehaviour
{
	private Animator animator;
	private int numOfClicks;

	public bool isPlaying;

    private void Start() {
		animator = GetComponent<Animator>();
    }

    private void Update() {
		if (isPlaying)
		{
			isPlaying = false;
			animator.CrossFade("2Hand-Sword-Attack1", 0.2f);
		}
    }
}
