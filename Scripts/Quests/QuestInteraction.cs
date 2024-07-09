using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class QuestInteraction : Interactable
{
    public GameObject questAvaiable;
    public GameObject questInProgress;
    public GameObject questCompleted;
    public QuestGiver questGiver;
    public PlayerManager playerManager;

    public override void Interact(){
        questCompleted.transform.Find("ClaimButton").GetComponent<Button>().onClick.RemoveAllListeners();
        if (playerManager.quest.isActive){
            if (questGiver.quest.isActive && !questGiver.quest.isCompleted && (playerManager.quest.questID == questGiver.ID)){
                questInProgress.SetActive(!questInProgress.activeSelf);
                questGiver.detailedDescriptionText.text = questGiver.quest.detailedDescription;
                questGiver.comeBackTextInprogress.text = questGiver.quest.comeBack;
                
            }
            else if(playerManager.quest.isCompleted && (playerManager.quest.questID == questGiver.ID)){
                questGiver.questCompletedRewardIcon.sprite = questGiver.quest.reward.icon;
                questGiver.questCompletedRewardName.text = questGiver.quest.reward.name;
                questGiver.questCompletedGoldReward.text = questGiver.quest.goldReward.ToString();
                questCompleted.transform.Find("ClaimButton").GetComponent<Button>().onClick.AddListener(questGiver.ClaimReward);
                questInProgress.SetActive(false);
                questCompleted.SetActive(!questCompleted.activeSelf);
                Cursor.visible = true;
            }
        }
        else {
            questGiver.titleText.text = questGiver.quest.title;
            questGiver.descriptionText.text = questGiver.quest.description;
            questGiver.comeBackTextAvaiable.text = questGiver.quest.comeBack;
            questGiver.questNotActivatedRewardIcon.sprite = questGiver.quest.reward.icon;
            questGiver.questNotActivatedRewardName.text = questGiver.quest.reward.name;
            questGiver.questNotActivatedGoldReward.text = questGiver.quest.goldReward.ToString();
            questAvaiable.SetActive(!questAvaiable.activeSelf);
            questAvaiable.transform.Find("AcceptButton").GetComponent<Button>().onClick.AddListener(questGiver.AcceptQuest);
            
            if (questAvaiable.active)
                Cursor.visible = true;
            else 
                Cursor.visible = false;
        }
        
    }
}
