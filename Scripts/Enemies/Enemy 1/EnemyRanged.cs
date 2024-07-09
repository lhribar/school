using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyRanged : MonoBehaviour
{
    private bool alreadyAttacked = false;
    public GameObject projectile;
    public float reloadSpeed;
    private EnemyMovement enemyMovement;
    private Animator animator;

    private void Start() {
        animator = GetComponent<Animator>();
        enemyMovement = GetComponent<EnemyMovement>();
    }
    private void Update() {

        if (enemyMovement.playerInAttackRange && enemyMovement.playerInSightRange){
            AttackPlayer();
            animator.SetFloat("Speed", 0, 0.1f, Time.deltaTime);
        }

    }

    private void AttackPlayer(){
        enemyMovement.agent.SetDestination (enemyMovement.transform.position);
        Vector3 direction = (enemyMovement.player.position - enemyMovement.transform.position).normalized;
        Quaternion lookRotation = Quaternion.LookRotation(new Vector3(direction.x, 0, direction.z));
        enemyMovement.transform.rotation = Quaternion.Slerp(enemyMovement.transform.rotation, lookRotation, Time.deltaTime * enemyMovement.rotationSpeed);

        if (!alreadyAttacked){
            animator.SetTrigger("Attack");
            Invoke("InstantiateProjectile", 0.5f);
        
            alreadyAttacked = true;
            Invoke(nameof(ResetAttack), reloadSpeed);
        }
    }

    public void InstantiateProjectile(){
        GameObject bullet = Instantiate(projectile, new Vector3(transform.position.x, transform.position.y, transform.position.z), Quaternion.identity);
        bullet.GetComponent<Rigidbody>().AddForce(transform.forward * 10f, ForceMode.Impulse);
        Destroy(bullet, 3f);
    }

    private void ResetAttack(){
        alreadyAttacked = false;
    }
}
