using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;



public class PlayerMovement : MonoBehaviour
{
    
    Rigidbody playerRigidbody;
    Vector3 moveDirection;
    [SerializeField] private float movementSpeed = 5f;
    private float moveX;
    private float moveZ;

    [Header("Falling")]
    public float inAirTimer;
    public float leapingVelocity;
    public float fallingVelocity;
    Transform cameraObject;
    PlayerManager playerManager;

    [Header("Jump Speeds")]
    private Vector3 playerVelocity;
    [SerializeField] private float jumpHeight;
    [SerializeField] private float gravityIntensity;

    Animator animator;
    public CharacterController characterController;



    private void Awake() {
        animator = GetComponentInChildren<Animator>();
        playerManager = GetComponent<PlayerManager>();
        playerRigidbody = GetComponent<Rigidbody>();
        characterController = GetComponent<CharacterController>();
        cameraObject = Camera.main.transform;
    }

    private void HandleRotation(){
        Vector3 targetDirection = Vector3.zero;
        targetDirection = cameraObject.forward * moveZ;
        targetDirection = targetDirection + cameraObject.right * moveX;

        if (targetDirection == Vector3.zero){
            targetDirection = transform.forward;
        }

        Quaternion targetRotation = Quaternion.LookRotation(targetDirection);
        Quaternion playerRotation = Quaternion.Slerp(transform.rotation, targetRotation, 15 * Time.deltaTime);

        transform.rotation = playerRotation;
    }

    private void Update(){
        Falling();
        HandleMovement();
        HandleRotation();
    }
    private void HandleMovement(){
        if (!animator.GetCurrentAnimatorStateInfo(1).IsName("attack")){
            moveX = Input.GetAxis("Horizontal");
            moveZ = Input.GetAxis("Vertical");
            moveDirection = cameraObject.forward * moveZ;
            moveDirection = moveDirection + cameraObject.right * moveX;

            moveDirection.Normalize();
            moveDirection.y = 0f;

            if (characterController.isGrounded){
                if (moveDirection != Vector3.zero)
                    Walk();
                else if (moveDirection == Vector3.zero)
                    Idle();

                if (Input.GetKeyDown(KeyCode.Space))
                    Jump();
            }
            moveDirection = moveDirection * movementSpeed;
            characterController.Move(moveDirection * Time.deltaTime);
            playerVelocity.y += gravityIntensity * Time.deltaTime;
            characterController.Move(playerVelocity * Time.deltaTime);
        }
        else{
            characterController.Move(new Vector3(0, 0, 0) * Time.deltaTime);
        }
 
    }
    private void Falling(){
        if (!characterController.isGrounded){
            inAirTimer = inAirTimer + Time.deltaTime;
            playerRigidbody.AddForce(transform.forward * leapingVelocity);
            playerRigidbody.AddForce(-Vector3.up * fallingVelocity * inAirTimer);
        }

        if (characterController.isGrounded){
            inAirTimer = 0;
        }
    }

    public void Jump(){
        float jumpingVelocity = Mathf.Sqrt(-2 * gravityIntensity * 1.5f);
        playerVelocity.y = jumpingVelocity;
    }
    private void Walk(){
        animator.SetFloat("Speed", 1, 0.1f, Time.deltaTime);
    }
    private void Idle(){
        animator.SetFloat("Speed", 0, 0.1f, Time.deltaTime);
    }
}

