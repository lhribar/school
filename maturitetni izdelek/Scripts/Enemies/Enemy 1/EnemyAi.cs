using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class EnemyAi : MonoBehaviour
{

    //VARIABLES
    public NavMeshAgent agent;
    public Transform player;
    public LayerMask whatIsGround, whatIsPlayer;
    public GameObject projectile;
    public int enemyHealth = 100;

    public int maxEnemyHealth = 100;
    public int aiDamage = 10;

    [SerializeField] private Healthbar healthbar;

    //ASOIUDAOS
    public bool isDead = false;

    //PATROLING
    public Vector3 walkPoint;
    bool walkPointSet;
    public float walkPointRange;

    //ATTACKING
    public float timeBetweenAttacks;
    bool alreadyAttacked;

    //STATES
    public float sightRange, attackRange;
    public bool playerInSightRange, playerInAttackRange;

    //animator
    Animator animator;

    private void Awake() {
        animator = GetComponent<Animator>();
        agent = GetComponent<NavMeshAgent>();
        player = GameObject.Find("ToonRTS_demo_Knight").transform;
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
        if (playerInAttackRange && playerInSightRange){
            AttackPlayer();
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
        if (distanceToWalkPoint.magnitude <1f){
            walkPointSet = false;
        }
    }

    private void SearchWalkPoint(){
        float randomZ = Random.Range(-walkPointRange, walkPointRange);
        float randomX = Random.Range(-walkPointRange, walkPointRange);

        walkPoint = new Vector3(transform.position.x + randomX, transform.position.y, transform.position.z + randomZ);

        //walkpoint ni izven mape
        if (Physics.Raycast(walkPoint, -transform.up, 2f, whatIsGround)){
            walkPointSet = true;
        } 
    }

    private void chasePlayer(){
        agent.SetDestination(player.position);
    }

    private void AttackPlayer(){
        //ai doesnt move
        agent.SetDestination (transform.position);
        
        /*Vector3 lookAt = new Vector3(player.position.x, agent.transform.position.y, player.position.z);
        transform.LookAt(lookAt);
        */
        //transform.LookAt(player);

        Vector3 direction = (player.position - transform.position).normalized;
        Quaternion lookRotation = Quaternion.LookRotation(new Vector3(direction.x, 0, direction.z));
        transform.rotation = Quaternion.Slerp(transform.rotation, lookRotation, Time.deltaTime * 5f);
        
        if (!alreadyAttacked){
            Rigidbody rigidbody = Instantiate(projectile, transform.position, Quaternion.identity).GetComponent<Rigidbody>();
            rigidbody.AddForce(transform.forward * 32f, ForceMode.Impulse);
            rigidbody.AddForce(transform.up * 8f, ForceMode.Impulse);
        
            alreadyAttacked = true;
            Invoke(nameof(ResetAttack), timeBetweenAttacks);
        }
    }

    private void ResetAttack(){
        alreadyAttacked = false;
    }

    public void TakeDamage(int damage){
        enemyHealth -= damage;
        Debug.Log("AAAAAAAAAAAAAAAAAAAAAAA");
        
        healthbar.UpdateHealthBar(maxEnemyHealth, enemyHealth);

        if (enemyHealth <= 0){
            Debug.Log("ddfiugzoiudfs");
            isDead = true;
            Destroy(gameObject, 0.5f);
        }
    }

     private void OnDrawGizmosSelected(){
        Gizmos.color = Color.red;
        Gizmos.DrawWireSphere(transform.position, attackRange);
        Gizmos.color = Color.yellow;
        Gizmos.DrawWireSphere(transform.position, sightRange);
     }

}
