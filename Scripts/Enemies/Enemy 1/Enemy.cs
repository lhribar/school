using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class Enemy : MonoBehaviour
{
    public int ID;
    public NavMeshAgent agent;
    public Transform player;
    public LayerMask whatIsGround, whatIsPlayer;
    public LayerMask whatIsWalkable;
    public int enemyHealth = 100;

    public int maxEnemyHealth = 100;
    public int aiDamage = 0;
    private Healthbar healthbar;
    public bool bossSpawn;


    //ASOIUDAOS
    public bool isDead = false;

    //PATROLING
    public Vector3 walkPoint;
    bool walkPointSet;
    public float walkPointRange;

    //ATTACKING
    public float timeBetweenAttacks;
    public bool alreadyAttacked = false;

    //STATES
    public float sightRange, attackRange;
    public bool playerInSightRange, playerInAttackRange;

    //animator
    Animator animator;
    public float rotationSpeed;

    //QUEST
    private PlayerManager playerManager;
    

    private void Awake() {
        animator = GetComponent<Animator>();
        agent = GetComponent<NavMeshAgent>();
        player = GameObject.Find("ToonRTS_demo_Knight").transform;
        healthbar = GetComponentInChildren<Healthbar>();
        playerManager = GameObject.Find("Player").GetComponent<PlayerManager>();
    }

    private void Update(){
        //check for sight and attack range
        playerInSightRange = Physics.CheckSphere(transform.position, sightRange, whatIsPlayer);
        playerInAttackRange = Physics.CheckSphere(transform.position, attackRange, whatIsPlayer);

        if (!playerInSightRange && !playerInAttackRange){

            Patroling();
            animator.SetFloat("Speed", 1, 0.1f, Time.deltaTime);
        }
        if(playerInSightRange && !playerInAttackRange){

            chasePlayer();
        }
    }

    private void Patroling(){
        if (!walkPointSet){
            SearchWalkPoint();
        }
        if (walkPointSet){
            agent.SetDestination(walkPoint);
        }
 
        Vector3 distanceToWalkPoint = transform.position - walkPoint;

        //walkpoint reached
        if (distanceToWalkPoint.magnitude <2f){
            walkPointSet = false;
        }
    }

    private void SearchWalkPoint(){
        float randomZ = Random.Range(-walkPointRange, walkPointRange);
        float randomX = Random.Range(-walkPointRange, walkPointRange);

        walkPoint = new Vector3(transform.position.x + randomX, transform.position.y, transform.position.z + randomZ);

        //walkpoint ni izven mape
        if (!bossSpawn){
                            
            if (Physics.Raycast(walkPoint, -transform.up, 2f, whatIsGround) && !Physics.Raycast(walkPoint, -transform.up, 2f, whatIsWalkable)){
                walkPointSet = true;
            } 
        }
        else{
            if(Physics.Raycast(walkPoint, -transform.up, 2f, whatIsWalkable)){

                walkPointSet = true;
            }
        }
    }

    private void chasePlayer(){
        agent.SetDestination(player.position);
    }

    private void AttackPlayer(){
        agent.SetDestination (transform.position);
        Vector3 direction = (player.position - transform.position).normalized;
        Quaternion lookRotation = Quaternion.LookRotation(new Vector3(direction.x, 0, direction.z));
        if (!animator.GetCurrentAnimatorStateInfo(1).IsName("attack") && !animator.GetCurrentAnimatorStateInfo(1).IsName("attackNoDamage")){
            Debug.Log("attacking player");
            transform.rotation = Quaternion.Slerp(transform.rotation, lookRotation, Time.deltaTime * rotationSpeed);
        }
    }

    public void TakeDamage(int damage){
        enemyHealth -= damage;

        healthbar.UpdateHealthBar(enemyHealth, maxEnemyHealth);
        
        if (enemyHealth <= 0){
            Debug.Log("ddfiugzoiudfs");
            isDead = true;
            Destroy(gameObject, 0.0f);
            if (playerManager.quest.isActive){
                playerManager.quest.EnemyKilled(ID);
            }
            
        }
    }

     private void OnDrawGizmosSelected(){
        Gizmos.color = Color.red;
        Gizmos.DrawWireSphere(transform.position, attackRange);
        Gizmos.color = Color.yellow;
        Gizmos.DrawWireSphere(transform.position, sightRange);
     }

}

