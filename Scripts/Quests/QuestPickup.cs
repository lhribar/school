using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class QuestPickup : Interactable
{
    public int ID;
    public QuestGiver questGiver;
    public override void Interact()
    {
        if (questGiver.quest.ItemPickup(ID)){
            Destroy(gameObject);
        }
    }
}
