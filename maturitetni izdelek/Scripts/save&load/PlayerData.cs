using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class PlayerData
{
    public float health;
    public float[] position;
    public int gold;
    public int armor;
    public int damage;
    public int questsCompleted;


    public PlayerData(PlayerHealth playerHealth, PlayerMovement playerMovement, int playerGold, int playerArmor, int playerDamage, int playerQuestsCompleted)
    {
        health = playerHealth.currentHealth;

        position = new float[3];
        position[0] = playerMovement.transform.position.x;
        position[1] = playerMovement.transform.position.y;
        position[2] = playerMovement.transform.position.z;

            //solo
        gold = playerGold;
        armor = playerArmor;
        damage = playerDamage;
        questsCompleted = playerQuestsCompleted;
        
    }
}
