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
    void Start() {
        animator = GetComponent<Animator>();
        controller = GetComponent<CharacterController>();
    }

    // Update is called once per frame
    void Update() {
        inputX = Input.GetAxis("Horizontal");
        inputZ = Input.GetAxis("Vertical");

        ProcessInput();
    }

    void ProcessInput() {
        animator.SetFloat("InputX", inputX, 0.0f, Time.deltaTime * 2.0f);
        animator.SetFloat("InputZ", inputZ, 0.0f, Time.deltaTime * 2.0f);

        float inputMagnitude = new Vector2(inputX, inputZ).sqrMagnitude;

        if (inputMagnitude > allowPlayerRotation) Rotation();
        else desiredMoveDirection = Vector3.zero;

        Move();
    }

    void Rotation() {
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

    void Move() {
        gravity -= 9.8f * Time.deltaTime;

        Vector3 moveDirection = desiredMoveDirection * moveSpeed * Time.deltaTime;
        moveDirection = new Vector3(moveDirection.x, gravity, moveDirection.z);
        controller.Move(moveDirection);

        if(controller.isGrounded) gravity = 0;
    }
}
