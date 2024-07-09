using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class Quest
{
    public int questID;
    public bool isActive = false;
    public string title;
    public string description;
    public string detailedDescription;
    public string comeBack;
    
    public Item reward;
    public int goldReward;

    public bool isCompleted;

    public ActiveQuestCanvas activeQuestCanvas;

    public GoalType goalType;

    public int IDAi;
    
    public int requiredAmount;
    public int currentAmount;

    public bool IsReached(){
        return (currentAmount >= requiredAmount);
    }

    public void EnemyKilled(int ID){
        if (goalType == GoalType.Kill && IDAi == ID){
            Debug.Log("sussy");
            currentAmount++;
            activeQuestCanvas.UpdateQuestBar();
            if (IsReached()){
                QuestCompleted();
            }
        }
    }

    public bool ItemPickup(int ID){
        if (goalType == GoalType.Gather && IDAi == ID){
            currentAmount++;
            activeQuestCanvas.UpdateQuestBar();
            if (IsReached()){
                QuestCompleted();
            }
            return true;
        }
        return false;
    }

    public void QuestCompleted(){
        isCompleted = true;
        activeQuestCanvas.UpdateQuestBar();
    }
}

public enum GoalType{
    Kill,
    TalkToNpc,
    Gather
}

