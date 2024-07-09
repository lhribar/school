using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
[System.Serializable]
public class InventorySlot : MonoBehaviour
{
    public Image icon;
    public Button removeButton;
    Item item;
    [SerializeField] PlayerHealth playerHealth;

    InventoryManager inventory;


    public void AddItem (Item newItem){
        item = newItem;
        icon.sprite = item.icon;
        icon.enabled = true;
        removeButton.interactable = true;
    }

    private void Start() {
        inventory = InventoryManager.instance;
    }

    public void clearSlot(){
        item = null;
        icon.sprite = null;
        icon.enabled = false;
        removeButton.interactable = false;
    }

    public void OnRemoveButton(){
        InventoryManager.instance.Remove(item);
    }

    public void UseItem(){
        if (item != null){
            item.Use();
        }
    }

}
