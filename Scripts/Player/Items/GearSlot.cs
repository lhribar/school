using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using TMPro;


public class GearSlot : MonoBehaviour, IPointerEnterHandler, IPointerExitHandler
{
    public Image icon;
    public EquipmentManager equipmentManager;
    public GameObject logoText;
    public TMP_Text itemName;
    public TMP_Text itemValue;
    public int id;

    private void Start() {
        equipmentManager = EquipmentManager.instance;
        //logoText.SetActive(false);
    }

    public void ChangeItem(Item newItem){
        icon.sprite = newItem.icon;
        icon.enabled = true;
    }

    public void OnPointerEnter(PointerEventData eventData){
        if (equipmentManager.currentEquipment[eventData.pointerCurrentRaycast.gameObject.GetComponent<GearSlot>().id] != null){
            itemName.text = equipmentManager.currentEquipment[eventData.pointerCurrentRaycast.gameObject.GetComponent<GearSlot>().id].name;

            if (equipmentManager.currentEquipment[eventData.pointerCurrentRaycast.gameObject.GetComponent<GearSlot>().id].damageModifier != 0)
                itemValue.text = equipmentManager.currentEquipment[eventData.pointerCurrentRaycast.gameObject.GetComponent<GearSlot>().id].damageModifier.ToString();
            else 
                itemValue.text = equipmentManager.currentEquipment[eventData.pointerCurrentRaycast.gameObject.GetComponent<GearSlot>().id].armorModifier.ToString();
            
            logoText.SetActive(true);
        }
        
    }


    public void OnPointerExit(PointerEventData eventData){
        logoText.SetActive(false);
    }

    

}
