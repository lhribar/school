using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class QuestSave : MonoBehaviour
{
    public static List<GameObject> questGiversList;
    void Start()
    {
        questGiversList = new List<GameObject>();
        
        foreach (Transform child in transform){
            questGiversList.Add(child.gameObject);
        }
    }

    public void LoadQuestGivers()
    {
        for (int i = 0; i < questGiversList.Count; i++){
            QuestGiverData data = SaveSystem.LoadQuestGivers(i);
            if (data != null){
                if (data.questCompleted)
                    Destroy(questGiversList[i].GetComponent<QuestInteraction>());
            }
        }
    }


}
