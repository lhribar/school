using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "New Item", menuName ="Item")]
[System.Serializable]
public class Item : ScriptableObject
{
    new public string name = "New Item";
    public int price;
    public Sprite icon = null;
    //public ItemType itemType;

    // public enum ItemType{
    //     Potion,
    //     Book,
    //     Key,
    //     Armor
    // }

    public virtual void Use(){
        Debug.Log("using " + name);
    }

    public void RemoveFromInventory(){
        InventoryManager.instance.Remove(this);
    }
}
