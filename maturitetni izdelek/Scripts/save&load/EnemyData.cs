using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class EnemyData 
{
    public float health;
    public float[] position;
    public int indexID;

    
    public EnemyData(float aihealth, EnemyMovement enemyMovement)
    {
        health = aihealth;

        if (enemyMovement != null){
            position = new float[3];
            position[0] = enemyMovement.transform.position.x;
            position[1] = enemyMovement.transform.position.y;
            position[2] = enemyMovement.transform.position.z;
        }

    }
}
