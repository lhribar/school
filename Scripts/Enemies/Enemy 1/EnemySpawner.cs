using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;
using UnityEngine.UI;

public class EnemySpawner : MonoBehaviour
{
    public int projectileEnemies;
    public GameObject projectileEnemyPrefab;
    public int golemEnemies;
    public GameObject golemPrefab;
    public GameObject terrain;
    //public List<EnemyData> enemySaveData = new List<EnemyData>();
    //public static List<GameObject> allEnemies = new List<GameObject>();
    public static List<GameObject> allEnemies;

    private void Start() {
        allEnemies = new List<GameObject>();
        for (int i = 0; i < projectileEnemies; i++){
            Vector3 point;
            do{
                
            }while (!RandomPoint(terrain.transform.position, 90, out point));

            GameObject spawnProjectileEnemy = Instantiate(projectileEnemyPrefab, point, Quaternion.identity);
            spawnProjectileEnemy.GetComponent<EnemyMovement>().enemySaveID = i;
            allEnemies.Add(spawnProjectileEnemy);
            //enemySaveData.Add(new EnemyData(100, GetComponentInChildren<EnemyMovement>(), i));
        }

        for (int i = projectileEnemies; i < golemEnemies + projectileEnemies; i++){
            Vector3 point;
            do{
                
            }while (!RandomPoint(terrain.transform.position, 90, out point));

            GameObject spawnGolem = Instantiate(golemPrefab, point, Quaternion.identity);
            spawnGolem.GetComponent<EnemyMovement>().enemySaveID = i;
            allEnemies.Add(spawnGolem);
            //GetComponent<EnemyMovement>().enemySaveID = i;
            //enemySaveData.Add(new EnemyData(100, GetComponent<EnemyMovement>(), i));
        }
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

    public void LoadEnemies()
    {
        
            for (int i = 0; i < allEnemies.Count; i++){
                EnemyData data = SaveSystem.LoadEnemy(i);
                if (data != null){
                    if (data.health == 0){
                        Destroy(allEnemies[i]);
                    }
                    else {
                        allEnemies[i].GetComponent<EnemyMovement>().currentAIHealth = data.health;
                        Vector3 position;
                        allEnemies[i].GetComponentInChildren<Healthbar>().healthbarUI.SetActive(false);
                        allEnemies[i].GetComponent<EnemyMovement>().transform.position = new Vector3(data.position[0], data.position[1], data.position[2]);
                        position.x = data.position[0];
                        position.y = data.position[1];
                        position.z = data.position[2];
                    }
                    

                }
        }
    }



}
