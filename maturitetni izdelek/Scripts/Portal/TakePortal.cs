using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TakePortal : MonoBehaviour
{
    public GameObject locationToPortal;
    private void OnTriggerEnter(Collider other) {
        if (other.tag == "Player"){
            other.GetComponent<CharacterController>().enabled = false;
            other.transform.position = locationToPortal.transform.position;
            other.GetComponent<CharacterController>().enabled = true;
        }
    }
}
