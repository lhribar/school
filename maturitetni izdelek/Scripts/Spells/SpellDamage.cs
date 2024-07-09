using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpellDamage : MonoBehaviour
{
    [SerializeField] private GameObject spell;

    private void OnTriggerEnter(Collider other) {
        if (other.gameObject.CompareTag("Enemy")){
            other.gameObject.GetComponent<EnemyMovement>().TakeDamage(50);
            Destroy(this.gameObject);
        }
        if (other.gameObject.CompareTag("Boss")){
            other.gameObject.GetComponent<Boss>().TakeDamage(25);
            Destroy(this.gameObject);
        }
    }
}
