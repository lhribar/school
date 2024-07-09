using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using UnityEngine.UI;

public class ActiveQuestCanvas : MonoBehaviour
{
    public GameObject questPanel;
    public PlayerManager playerManager;
    public TMP_Text questName;
    public TMP_Text questDescription;
    public TMP_Text currentAmount;
    public TMP_Text requiredAmount;
    public Image questFinishedBackground;

    private void Start() {
        questFinishedBackground.enabled = false;
    }

    public void UpdateQuestBar(){
        if (playerManager.quest.isCompleted){
            questFinishedBackground.enabled = true;
        }
        questName.SetText(playerManager.quest.title);
        questDescription.SetText(playerManager.quest.description);
        currentAmount.SetText(playerManager.quest.currentAmount.ToString());
        requiredAmount.SetText(playerManager.quest.requiredAmount.ToString());
    }

    public void CompletedQuestBar(){
        questFinishedBackground.enabled = false;
        questPanel.SetActive(false);
    }
}
