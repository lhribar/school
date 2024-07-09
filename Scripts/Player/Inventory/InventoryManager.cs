using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class InventoryManager : MonoBehaviour
{
    #region Singleton
    public static InventoryManager instance;

    void Awake(){
        if (instance != null){
            Debug.LogWarning("more than one instance of inventory");
            return;
        }
        instance = this;
    }
    #endregion
    
    public delegate void OnItemChanged(); //vedno ko se v inventoryju nekaj spremeni, se to kliče
    
    public OnItemChanged onItemChangedCallBack;
    public int inventorySpace = 20;
    public List<Item> items = new List<Item>();

    public bool Add(Item item){
        if (items.Count >= inventorySpace){
            Debug.Log("not enough room");
            return false;
        }
        items.Add(item);

        if (onItemChangedCallBack != null){
            onItemChangedCallBack.Invoke();
        }

        return true;
    }

    public void Remove(Item item){
        items.Remove(item);

        if (onItemChangedCallBack != null){
            onItemChangedCallBack.Invoke();
        }
    }
}
