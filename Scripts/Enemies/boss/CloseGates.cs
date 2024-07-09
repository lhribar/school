using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CloseGates : MonoBehaviour
{
    public GameObject gates;
    public GameObject bossStart;
    private void OnTriggerEnter(Collider other) {
        if (other.tag == "Player"){
            gates.SetActive(true);
            bossStart.GetComponent<Boss>().enabled = true;
            //Destroy(gameObject);
            gameObject.SetActive(false);
        }
    }
}
