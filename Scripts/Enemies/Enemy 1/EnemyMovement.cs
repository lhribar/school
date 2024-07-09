using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;


public class EnemyMovement : MonoBehaviour
{
    public int ID;
    public int enemySaveID;
    public NavMeshAgent agent;
    public float range;
    public Transform centrePoint;
    public Transform player;

    public Healthbar healthbar;
    [SerializeField] public float currentAIHealth;
    public float maxAIHealth;
    public PlayerManager playerManager;

    //PLAYER
    public LayerMask playerMask;
    public float rotationSpeed;
    public float sightRange, attackRange;
    public bool playerInSightRange, playerInAttackRange;
    private Animator animator;
    public EnemySpawner enemySpawner;
    


    private void Awake() {
        //SaveManager.instance.RegisterEnemy(ID);
        animator = GetComponent<Animator>();
        player = GameObject.Find("Player").transform;
        agent = GetComponent<NavMeshAgent>();
        healthbar = GetComponentInChildren<Healthbar>();
        centrePoint = this.transform;
        playerManager = GameObject.Find("Player").GetComponent<PlayerManager>();
        enemySpawner = GetComponentInParent<EnemySpawner>();
    }

    // Update is called once per frame
    void Update()
    {
        playerInSightRange = Physics.CheckSphere(transform.position, sightRange, playerMask);
        playerInAttackRange = Physics.CheckSphere(transform.position, attackRange, playerMask);
        
        if (playerInSightRange && !playerInAttackRange){
            Chase();
        }
        else if (agent.remainingDistance <= agent.stoppingDistance && !playerInSightRange){
           
            animator.SetFloat("Speed", 1, 0.1f, Time.deltaTime);
            Vector3 point;
            if (RandomPoint(centrePoint.position, range, out point)){
                agent.SetDestination(point);
            }
        }
    }

    public void Chase()
    {
        agent.SetDestination(player.transform.position);
        animator.SetFloat("Speed", 1, 0.1f, Time.deltaTime);
    }

    bool RandomPoint(Vector3 center, float range, out Vector3 result)
    {
        Vector3 randomPoint = center + Random.insideUnitSphere * range;
        NavMeshHit hit;
        if (NavMesh.SamplePosition(randomPoint, out hit, 1.0f, NavMesh.AllAreas)){
            result = hit.position;
            return true;
        }

        result = Vector3.zero;
        return false;
    }


    public void TakeDamage(int damage){
        currentAIHealth -= damage;

        healthbar.UpdateHealthBar(currentAIHealth, maxAIHealth);
        
        if (currentAIHealth <= 0){
            Destroy(gameObject);
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
