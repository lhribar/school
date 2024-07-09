using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyMelee : MonoBehaviour
{
    Animator animator;
    EnemyMovement enemyMovement;
    public Transform player;
    public Transform enemyTransform;
    private bool canAttack = false;
    public float aiDamage;

    
    private void Awake(){
        animator = GetComponentInParent<Animator>();
        enemyMovement = GetComponentInParent<EnemyMovement>();
        player = GameObject.Find("Player").transform;
    }

    private void Update(){
        if (enemyMovement.playerInAttackRange && enemyMovement.playerInSightRange){
            AttackPlayer();
        }
        if (!animator.GetCurrentAnimatorStateInfo(1).IsName("attack") && !animator.GetCurrentAnimatorStateInfo(1).IsName("attackNoDamage")  && enemyMovement.playerInAttackRange && (Vector3.Angle(enemyTransform.transform.forward, player.transform.position - enemyTransform.transform.position) < 20)){
            Attack();
        }
        if (animator.GetCurrentAnimatorStateInfo(1).IsName("attackNoDamage")){
            canAttack = false;
        }
    }

    private void AttackPlayer(){
        
        enemyMovement.agent.SetDestination (enemyMovement.transform.position);
        Vector3 direction = (player.position - enemyMovement.transform.position).normalized;
        Quaternion lookRotation = Quaternion.LookRotation(new Vector3(direction.x, 0, direction.z));
        if (!animator.GetCurrentAnimatorStateInfo(1).IsName("attack") && !animator.GetCurrentAnimatorStateInfo(1).IsName("attackNoDamage")){
            enemyMovement.transform.rotation = Quaternion.Slerp(enemyMovement.transform.rotation, lookRotation, Time.deltaTime * enemyMovement.rotationSpeed);
        }
    }

    private void OnTriggerEnter(Collider other){
        if (canAttack){
            if (other.tag == "Player"){
                GameObject enemyObj = other.gameObject;
                canAttack = false;
                enemyObj.GetComponent<PlayerHealth>().UpdateHealth(-aiDamage);
            }
        }
    }

    private void Attack(){
        animator.SetFloat("Speed", 0, 0.1f, Time.deltaTime);
        animator.SetTrigger("Attack");
        canAttack = true;
    }

    private void SetCanAttackToFalse(){
        canAttack = false;
    }
}
