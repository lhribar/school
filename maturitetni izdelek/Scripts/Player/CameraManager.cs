using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraManager : MonoBehaviour
{
    //REFERENCES
    private Transform targetTransform;
    public Transform cameraTransform;

    public Vector3 cameraFollowVelocity = Vector3.zero;
    public Vector3 cameraVectorPosition = Vector3.zero;

    //VARIABLES

    [SerializeField] private float mouseSensitivity = 1.5f;
    public float lookAngleY; //Camera looking up and down
    public float lookAngleX; //Camera looking left and right

    private void Awake(){
        targetTransform = FindObjectOfType<PlayerManager>().transform;
        cameraTransform = Camera.main.transform;
    }

    public void HandleAllCameraMovement(){
        if (!PauseMenu.isPaused){
            FollowTarget();
            RotateCamera();
        }

    }
    private void FollowTarget(){
        Vector3 targetPosition = Vector3.SmoothDamp(transform.position, targetTransform.position, ref cameraFollowVelocity, 0.2f);
        transform.position = targetPosition;
    }

    private void RotateCamera(){
        lookAngleY = lookAngleY + (Input.GetAxis("Mouse X") * mouseSensitivity);
        Vector3 rotation;
        Quaternion targetRotation;

        rotation = Vector3.zero;
        rotation.y = lookAngleY;
        targetRotation = Quaternion.Euler(rotation);
        transform.rotation = targetRotation;
        
        //float mouseX = Input.GetAxis("Mouse X") * mouseSensitivity * Time.deltaTime;
        //float mouseY = Mathf.Clamp(Input.GetAxis("Mouse Y") * mouseSensitivity / 2, 35, 35);
        
        //lookAngleX = Mathf.Clamp(lookAngleX - (Input.GetAxis("Mouse Y") * 5f), -35, 35);



        //rotation = Vector3.zero;
        //rotation.x = lookAngleX;

        //targetRotation = Quaternion.Euler(rotation);
        //transform.rotation = targetRotation;
    }

}
