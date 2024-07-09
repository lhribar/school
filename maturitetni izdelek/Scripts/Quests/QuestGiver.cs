using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class QuestGiver : MonoBehaviour
{
    public int ID;

    public Quest quest;

    public PlayerManager playerManager;
    public Text titleText;
    public Text descriptionText;
    public Text comeBackTextAvaiable;
    public Text comeBackTextInprogress;
    public Text detailedDescriptionText;
    public GameObject questProgressSign;
    public Image questNotActivatedRewardIcon;
    public Text questNotActivatedRewardName;
    public Text questNotActivatedGoldReward;
    public Image questCompletedRewardIcon;
    public Text questCompletedRewardName;
    public Text questCompletedGoldReward;

    
    InventoryManager inventoryManager;
    public InventoryUI inventoryUI;
    public ActiveQuestCanvas activeQuestCanvas;
    public QuestInteraction questInteraction;
    

    private void Start() {
        inventoryManager = InventoryManager.instance;
    }



    public void AcceptQuest(){
        quest.isActive=true;
        quest.isCompleted = false;
        playerManager.quest = quest;

        activeQuestCanvas.questPanel.SetActive(true);
        activeQuestCanvas.UpdateQuestBar();

        questInteraction.questAvaiable.SetActive(false);
        Cursor.visible = false;
    }


    public void ClaimReward(){
        questInteraction.questCompleted.transform.Find("ClaimButton").GetComponent<Button>().onClick.RemoveAllListeners();
        questInteraction.questCompleted.SetActive(false);

        
        inventoryManager.Add(quest.reward);
        playerManager.gold += quest.goldReward;
        inventoryUI.UpdateGold();
        quest.isActive = false;
        Destroy(GetComponent<QuestInteraction>());
        Destroy(questProgressSign);

        activeQuestCanvas.CompletedQuestBar();

        playerManager.numberOfQuestCompleted++;
        playerManager.CheckForPortal();
        Cursor.visible = false;
    }
}
