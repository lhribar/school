using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class QuestGiverData
{
    public bool questCompleted = false;
    public QuestGiverData(bool completed)
    {
        questCompleted = completed;
    }
}
