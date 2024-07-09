using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class ShopInteraction : Interactable
{
    public GameObject shopInteraction;
    public override void Interact(){
        shopInteraction.SetActive(!shopInteraction.activeSelf);
        if (shopInteraction.active)
            Cursor.visible = true;
        else 
            Cursor.visible = false;
    }

    public void CloseShop(){
        shopInteraction.SetActive(!shopInteraction.activeSelf);
        
    }

    public void LeaveShop(){
        shopInteraction.SetActive(false);
        Cursor.visible = false;
    }


}
