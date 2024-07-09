using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using System;

[System.Serializable]
public class InventoryUI : MonoBehaviour
{
    public Transform itemsParent;
    public GameObject inventoryUI;
    InventoryManager inventory;
    
    public TMP_Text goldAmount;
    public PlayerManager playerManager;
    [SerializeField] public InventorySlot[] slots;
    
    void Start()
    {
        inventory = InventoryManager.instance;
        inventory.onItemChangedCallBack += UpdateUI;
        goldAmount.SetText(playerManager.gold.ToString());
        slots = itemsParent.GetComponentsInChildren<InventorySlot>();
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.I)){
            inventoryUI.SetActive(!inventoryUI.activeSelf);
            if (inventoryUI.active){
                Cursor.visible = true;
            }
            else 
                Cursor.visible = false;
            UpdateGold();
        }
    }

    public void UpdateGold()
    {
        goldAmount.SetText(playerManager.gold.ToString());
    }

    void UpdateUI(){
        for (int i = 0; i < slots.Length; i++){
            if (i < inventory.items.Count){
                slots[i].AddItem(inventory.items[i]);
            }
            else{
                slots[i].clearSlot();
            }
        }
    }
}
