using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;


public class Boss : MonoBehaviour
{
    public float currentHealth;
    public float maxHealth;
    public Healthbar healthbar;
    public bool invicible = false;

    public Animator animator;
    private int notAvaiableAbility = 0;
    private int currentAbility = 1;

    public float sightRange, attackRange;
    public int randomAbility;

    public GameObject player;
    public PlayerHealth playerHealth;

    //ABILITIES

    //BLIZZARD
    public GameObject[] blizzardCircle;
    public GameObject blizzardCirclePrefab;
    public GameObject[] icicles;
    public GameObject iciclePrefab;


    //SUMMONING ARMY
    public GameObject[] golems;
    public GameObject golemPrefab;
    public GameObject[] projectileEnemies;
    public GameObject projectileEnemyPrefab;

    


    public GameObject[] numberOfOrbs;
    public GameObject orbPrefab;


    //ORB SPAWNER
    public GameObject[] numberOfSnowBalls;
    public GameObject snowballPrefab;
    public float speed = 2f;
    public float radius = 5f;

    
    //MOVING ZONE + TORNADO
    public GameObject[] numberOfLines;
    public GameObject linePrefab;
    
    public GameObject tornado;
    public GameObject TornadoPrefab;



    //reseting abilites in update
    public AnimationClip[] animationClips; //1-blizzard, 2-orbs, 3-golems, 4-zone 
    
    private float timePassed = 0f;
    public bool animationIsPlaying = false;
    private float timeToReset; // vse delimo z speed animationa v animator tab
    private int startAbilitiesTime = 2;
    private bool startAbilities = false; //ability pocaka 1 sec animationa, preden se zacne



    private void Start() {
        animator = GetComponent<Animator>();
        healthbar = GetComponentInChildren<Healthbar>();
    }

    

    private void Update() {
        Debug.Log(invicible);
        timePassed += Time.deltaTime;
        if (!(animator.GetCurrentAnimatorStateInfo(0).IsName("attack1") && animator.GetCurrentAnimatorStateInfo(0).IsName("attack2") && animator.GetCurrentAnimatorStateInfo(0).IsName("attack3") && animator.GetCurrentAnimatorStateInfo(0).IsName("attack4")) && !animationIsPlaying){ // če se ne playa noben animation
            randomAbility = GetRandomAbility();
            TakeDamage(50);
            timePassed = 0f;
            startAbilities = false;
        
            switch(randomAbility){
                
                case 1:
                    animator.SetTrigger("attack1");
                    timeToReset = animationClips[0].length;
                    break;

                case 2:
                    animator.SetTrigger("attack2");
                    timeToReset = animationClips[1].length / 0.3f;
                    SummonOrbs();
                    Invoke("DestroyOrbs", timeToReset);
                    break;

                case 3:
                    
                    animator.SetTrigger("attack3");

                    Invoke("SummonArmy", 5f);
                    timeToReset = animationClips[2].length / 0.2f;
                    invicible = true;
                    Invoke("SetInvincibleToFalse", timeToReset);
                    break;

                case 4:
                    animator.SetTrigger("attack4");
                    timeToReset = animationClips[3].length / 0.5f;
                    MovingZone();
                    SpawnTornado();
                    Invoke("resetBossPosition", timeToReset);
                    Invoke("DestroyZone", timeToReset);
                    Invoke("DestroyTornado", timeToReset);
                    Invoke("ZoneIsTriggerIsTrue", startAbilitiesTime);
                    break;
            }

            animationIsPlaying = true;
            Invoke("ResetAnimationIsPlaying", timeToReset + 5);
            Invoke("StartAbilities", 2.0f);
        }
        
        else if (animator.GetCurrentAnimatorStateInfo(0).IsName("attack1")){
            if (timePassed >= timeToReset / 3.5){
                Blizzard();
                timePassed = 0f;
            }
        }

        else if (animator.GetCurrentAnimatorStateInfo(0).IsName("attack2")){
            if (timePassed > timeToReset / 6){
                SpawnSnowballs();
                timePassed = 0f;
            }
        }


        else if (animator.GetCurrentAnimatorStateInfo(0).IsName("attack4") && startAbilities){
            MoveTornado();
            if (numberOfLines[0] == null){
                return;
            }
            if (timePassed <= timeToReset / 2){
                transform.transform.RotateAround(transform.position, Vector3.up, 10 * Time.deltaTime);
                RotateZoneClockWise();
            }
            else{
                RotateZoneCounterClockWise();
                transform.transform.RotateAround(transform.position, Vector3.up, -10 * Time.deltaTime);
            }
                
        }
    }
    public int GetRandomAbility(){
        do{
            currentAbility = Random.Range(1, 5);
        }while(currentAbility == notAvaiableAbility);
        notAvaiableAbility = currentAbility;
        Debug.Log(currentAbility);
        
        return currentAbility;
    }

    public void resetBossPosition(){
        transform.rotation = Quaternion.Euler(transform.rotation.x, 0, transform.rotation.z);
    }

    private void StartAbilities(){
        startAbilities = true;
    }

    public void ResetAnimationIsPlaying()
    {
        animationIsPlaying = false;
    }


    public void Blizzard(){
        float rand;
        float randomX;
        float randomZ;
        for (int i = 0; i < blizzardCircle.Length; i++){
            rand = Random.value;
            randomX = Random.Range(-attackRange, attackRange);
            randomZ = Random.Range(-attackRange, attackRange);
            blizzardCircle[i] = Instantiate(blizzardCirclePrefab, new Vector3(randomX * Mathf.Sin(rand)+ transform.position.x, -10.7f, randomZ * Mathf.Cos(rand) + transform.position.z), Quaternion.identity);
            icicles[i] = Instantiate(iciclePrefab, new Vector3(blizzardCircle[i].transform.position.x, 5.7f, blizzardCircle[i].transform.position.z), Quaternion.Euler(90.0f, 0.0f, 0.0f));
            Invoke("BlizzardFall", 1.0f);
            Destroy(blizzardCircle[i], 3.0f);
            Destroy(icicles[i], 3.0f);
        }

    }

    public void BlizzardFall(){
        for (int i = 0; i < icicles.Length; i++){
            icicles[i].GetComponent<Rigidbody>().constraints = RigidbodyConstraints.None;
        }
    }

    public void SummonArmy(){
        float randomX;
        float randomZ;
        float rand;
        for (int i = 0; i < golems.Length; i++){
            rand = Random.value;
            randomX = Random.Range(-attackRange, attackRange);
            randomZ = Random.Range(-attackRange, attackRange);
            golems[i] = Instantiate(golemPrefab, new Vector3(randomX * Mathf.Sin(rand)+ transform.position.x, -10.7f, randomZ * Mathf.Cos(rand) + transform.position.z), Quaternion.identity);
        }
        for (int i = 0; i < projectileEnemies.Length; i++){
            rand = Random.value;
            randomX = Random.Range(-attackRange, attackRange);
            randomZ = Random.Range(-attackRange, attackRange);
            projectileEnemies[i] = Instantiate(projectileEnemyPrefab, new Vector3(randomX * Mathf.Sin(rand)+ transform.position.x, -10.7f, randomZ * Mathf.Cos(rand) + transform.position.z), Quaternion.identity);
        }
    }

    public void SetInvincibleToFalse()
    {
        invicible = false;
    }

    public void SummonOrbs(){
        float nextAngle = 2 * Mathf.PI / numberOfOrbs.Length;
        float angle = 0;

        for (int i = 0; i < numberOfOrbs.Length; i++){
            float x = Mathf.Cos(angle);
            float z = Mathf.Sin(angle);
            numberOfOrbs[i] = Instantiate(orbPrefab, new Vector3(transform.position.x + (attackRange * x), transform.position.y, transform.position.z + (attackRange * z)), Quaternion.identity);
            angle += nextAngle;

        }
    }

    public void DestroyOrbs(){
        for (int i = 0; i < numberOfOrbs.Length; i++){
            if (numberOfOrbs[i] != null){
                Destroy(numberOfOrbs[i]);
                playerHealth.UpdateHealth(-22);
            }
        }
    }

    public void SpawnSnowballs(){
        float nextAngle = 2 * Mathf.PI / numberOfSnowBalls.Length;
        float angle = 0;
        for (int j = 0; j < numberOfSnowBalls.Length; j++){
           
            float x = Mathf.Cos(angle) * radius;
            float z = Mathf.Sin(angle) * radius;

            numberOfSnowBalls[j] = Instantiate(snowballPrefab, new Vector3(transform.position.x, transform.position.y - transform.position.y / 6, transform.position.z), Quaternion.identity);
            Rigidbody rigidbody = numberOfSnowBalls[j].GetComponent<Rigidbody>(); 
        
            rigidbody.AddForce(transform.forward, ForceMode.Impulse);
            rigidbody.velocity = new Vector3(x * speed, 0, z * speed);
        
            Destroy(numberOfSnowBalls[j], 2.0f);
            angle += nextAngle;
        }
    }

    public void SpawnTornado(){
        tornado = Instantiate(TornadoPrefab, new Vector3(player.transform.position.x , -7.5f, player.transform.position.z), Quaternion.identity);
        Invoke("tornadoIsTriggerIsTrue", 2f);
    }

    private void tornadoIsTriggerIsTrue(){
        tornado.GetComponent<CapsuleCollider>().enabled = true;
    }

    private void MoveTornado(){
        if (tornado != null){
            tornado.transform.position = Vector3.MoveTowards(tornado.transform.position, new Vector3(player.transform.position.x, -7.5f, player.transform.position.z), 3f * Time.deltaTime);
        }
    }

    public void DestroyTornado(){
        Destroy(tornado);
    }

    public void MovingZone(){
        float nextAngle = 2 * Mathf.PI / numberOfLines.Length;
        float rotateAngle = 0;
        float angle = 0;

        for (int i = 0; i < numberOfLines.Length; i++){
            float x = Mathf.Cos(angle);
            float z = Mathf.Sin(angle);
            numberOfLines[i] = Instantiate(linePrefab, new Vector3(((x * attackRange / 2)+transform.position.x), transform.position.y, (transform.position.z + (attackRange * z / 2)) ), Quaternion.Euler(0, rotateAngle, 0));
            angle += nextAngle;
            rotateAngle -= 360 /numberOfLines.Length;
        }
    }

    private void ZoneIsTriggerIsTrue(){
        for (int i = 0; i < numberOfLines.Length; i++){
            numberOfLines[i].GetComponent<BoxCollider>().enabled = true;
        }
    }
    
    public void RotateZoneClockWise(){
        for (int i = 0; i < numberOfLines.Length; i++){
            if (numberOfLines[i] != null)
                numberOfLines[i].transform.RotateAround(transform.position, Vector3.up, 10 * Time.deltaTime);
        }
    }

    public void RotateZoneCounterClockWise(){
        for (int i = 0; i < numberOfLines.Length; i++){
            if (numberOfLines[i] != null)
                numberOfLines[i].transform.RotateAround(transform.position, Vector3.up, -10 * Time.deltaTime);
        }
    }

    public void DestroyZone(){
        for (int i = 0; i < numberOfLines.Length; i++){
            Destroy(numberOfLines[i]);
        }
    }

    public void TakeDamage(int damage){
        if (!invicible){
            currentHealth -= damage;
            healthbar.UpdateHealthBar(currentHealth, maxHealth);
            if (currentHealth <= 0){

                Destroy(gameObject);
                SceneManager.LoadScene("GameOver");
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
