using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
    private Animator animator;
    private CharacterController controller;

    private float inputX;
    private float inputZ;
    private float gravity;
    private Vector3 desiredMoveDirection;
    
    public float desiredRotationSpeed;
    public float allowPlayerRotation;
    public float moveSpeed;

    // Start is called before the first frame update
    private void Start() {
        animator = GetComponent<Animator>();
        controller = GetComponent<CharacterController>();
    }

    // Update is called once per frame
    private void Update() {
        inputX = Input.GetAxis("Horizontal");
        inputZ = Input.GetAxis("Vertical");

        ProcessInput();
    }

    private void ProcessInput() {
        animator.SetFloat("InputX", inputX, 0.0f, Time.deltaTime * 2.0f);
        animator.SetFloat("InputZ", inputZ, 0.0f, Time.deltaTime * 2.0f);

        float inputMagnitude = new Vector2(inputX, inputZ).sqrMagnitude;
		inputMagnitude = Mathf.Clamp(inputMagnitude, 0, 1);
		animator.SetFloat("InputMagnitude", inputMagnitude, 0.0f, Time.deltaTime * 2.0f);

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

        desiredMoveDirection = forward * inputZ + right * inputX;

        transform.rotation = Quaternion.Slerp(transform.rotation,
        Quaternion.LookRotation(desiredMoveDirection), desiredRotationSpeed);
    }

    private void Move() {
        gravity -= 9.8f * Time.deltaTime;

        Vector3 moveDirection = desiredMoveDirection * moveSpeed * Time.deltaTime;
        moveDirection = new Vector3(moveDirection.x, gravity, moveDirection.z);

		controller.Move(moveDirection);

        if(controller.isGrounded) gravity = 0;
    }
}