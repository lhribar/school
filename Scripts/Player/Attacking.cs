
using System.Collections;
using System.Collections.Generic;
using UnityEngine.EventSystems;
using UnityEngine;
using System;

public class Attacking : MonoBehaviour
{
    //VARIABLES
    [SerializeField] private int enemyDamageAmount;

    private bool canAttack = false;
    //public GameObject enemyObj;
    //EnemyAi enemyAi;
    Animator animator;
    PlayerManager playerManager;


    private void Awake() {
        //enemyAi = GetComponent<EnemyAi>();
        animator = GetComponentInParent<Animator>();
        playerManager = GetComponentInParent<PlayerManager>();
    }

    private void Update(){
        if (EventSystem.current.IsPointerOverGameObject()){
            return;
        }
        
        if (!animator.GetCurrentAnimatorStateInfo(1).IsName("attack") && Input.GetKey(KeyCode.Mouse0) && playerManager.playerMovement.characterController.isGrounded){
            Attack();
            Invoke("SetCanAttackToFalse", animator.GetCurrentAnimatorStateInfo(1).length);
        }
    }


    private void OnTriggerEnter(Collider other){
        if (canAttack){
            if (other.tag == "Enemy"){
                Debug.Log("enemy hit");
                GameObject enemyObj = other.gameObject;
                canAttack = false;
                enemyObj.GetComponent<EnemyMovement>().TakeDamage(enemyDamageAmount * (1+playerManager.damage / 100));
            }
            else if (other.tag == "Boss"){

                other.GetComponent<Boss>().TakeDamage(enemyDamageAmount * (1+playerManager.damage / 100));
                canAttack = false;
            }

            else if (other.tag == "Orb"){
                other.GetComponent<OtherHealth>().TakeDamage(enemyDamageAmount * (1+playerManager.damage / 100));
                canAttack = false;
            }
        }
    }



    private void Attack(){
        animator.SetTrigger("Attack");
        canAttack = true;
    }

    private void SetCanAttackToFalse(){
        canAttack = false;
    }
    
}