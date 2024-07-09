using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class ShopManager : MonoBehaviour
{
    //shopSlot
    public Item item;
    public TMP_Text itemPrice;
    public TMP_Text itemName;
    public Image itemIcon;

    InventoryManager inventoryManager;
    public InventoryUI inventoryUI;
    public PlayerManager playerManager;

    private void Start()
    {
        inventoryManager = InventoryManager.instance;
        itemPrice.SetText(item.price.ToString());
        itemName.SetText(item.name);
        itemIcon.sprite = item.icon;
    }
    public void BuyItem()
    {

        if ((playerManager.gold - item.price) >= 0){


            playerManager.gold -= item.price;
            inventoryUI.UpdateGold();
            inventoryManager.Add(item);
        }
        
    }

}
