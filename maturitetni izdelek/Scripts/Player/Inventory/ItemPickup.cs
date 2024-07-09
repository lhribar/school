using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class ItemPickup : Interactable
{
    public Item item;
    public override void Interact(){
        bool wasPickedUp = InventoryManager.instance.Add(item);
        
        if (wasPickedUp){
            Destroy(gameObject);
        }
    }
}
