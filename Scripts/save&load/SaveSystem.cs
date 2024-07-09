using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

public static class SaveSystem
{

    public static void SavePlayer(PlayerHealth playerHealth, PlayerMovement playerMovement, int playerGold, int playerArmor, int playerDamage, int playerQuestsCompleted)
    {
        string path = Application.persistentDataPath + "/player.fun";
        PlayerData data = new PlayerData(playerHealth, playerMovement, playerGold, playerArmor, playerDamage, playerQuestsCompleted);
        using (FileStream file = File.Create(path)){
            new BinaryFormatter().Serialize(file, data);
        }
    }


    public static PlayerData LoadPlayer()
    {
        string path = Application.persistentDataPath + "/player.fun";
        if (File.Exists(path)){
            BinaryFormatter formatter = new BinaryFormatter();
            FileStream stream = new FileStream(path, FileMode.Open);

            PlayerData data = formatter.Deserialize(stream) as PlayerData;
            stream.Close();
            
            return data;
        }
        else{
            Debug.LogError("save file not found in " + path);
            return null;
        }
    }

        public static void SaveEnemy()
    {

        string path = Application.persistentDataPath + "/enemies.fun";
        using (FileStream file = File.Create(path)){


        for (int i = 0; i < EnemySpawner.allEnemies.Count; i++){
            if (EnemySpawner.allEnemies[i] != null){
                EnemyData data = new EnemyData(EnemySpawner.allEnemies[i].GetComponent<EnemyMovement>().currentAIHealth, EnemySpawner.allEnemies[i].GetComponent<EnemyMovement>());
                new BinaryFormatter().Serialize(file, data);
                
            }
            else{
                EnemyData data = new EnemyData(0, null);
                new BinaryFormatter().Serialize(file, data);
            }
        }       

        }
    }

    public static EnemyData LoadEnemy(int index)
    {
        
        string path = Application.persistentDataPath + "/enemies.fun";
        if (File.Exists(path)){
            BinaryFormatter formatter = new BinaryFormatter();
            FileStream stream = new FileStream(path, FileMode.Open);
            EnemyData data;
            for (int i = 0; i < index; i++){
                
                data = formatter.Deserialize(stream) as EnemyData;
            }
   
            data = formatter.Deserialize(stream) as EnemyData;
            stream.Close();
            
            return data;
        }
        else{
            Debug.LogError("save file not found in " + path);
            return null;
        }
    }

    public static void SaveQuestGivers()
    {
        string path = Application.persistentDataPath + "/questGivers.fun";
        using (FileStream file = File.Create(path)){
            for (int i = 0; i < QuestSave.questGiversList.Count; i++){
                QuestGiverData data = new QuestGiverData(QuestSave.questGiversList[i].GetComponent<QuestGiver>().quest.isCompleted);
                new BinaryFormatter().Serialize(file, data);
            }       
        }
    }

    public static QuestGiverData LoadQuestGivers(int index)
    {
        string path = Application.persistentDataPath + "/questGivers.fun";
        if (File.Exists(path)){
            BinaryFormatter formatter = new BinaryFormatter();
            FileStream stream = new FileStream(path, FileMode.Open);
            QuestGiverData data;
            for (int i = 0; i < index; i++)
                data = formatter.Deserialize(stream) as QuestGiverData;
            
            data = formatter.Deserialize(stream) as QuestGiverData;
            stream.Close();
            return data;
        }
        else{
            Debug.LogError("save file not found in " + path);
            return null;
        }
        
    }

}
