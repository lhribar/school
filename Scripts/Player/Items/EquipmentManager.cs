using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class EquipmentManager : MonoBehaviour
{
    public static EquipmentManager instance;
    public GameObject gearUI;
    public List<Image> gearSlots;
    private void Awake() {
        instance = this;
    }

    public Equipment[] currentEquipment;
    InventoryManager inventoryManager;
    public delegate void OnEquipmentChanged(Equipment newItem, Equipment oldItem);
    public OnEquipmentChanged onEquipmentChanged;
    public PlayerManager playerManager;


    private void Start() {
        inventoryManager = InventoryManager.instance;
        int numberOfSlots = System.Enum.GetNames(typeof(EquipmentSlot)).Length;
        currentEquipment = new Equipment[numberOfSlots];
    }

    private void Update(){
        if (Input.GetKeyDown(KeyCode.C)){
            gearUI.SetActive(!gearUI.activeSelf);
            if (gearUI.active)
                Cursor.visible = true;
            else
                Cursor.visible = false;
        }
    }

    public void UpdateArmor(){
        playerManager.armor = 0;
        playerManager.damage = 0;
        for (int i = 0; i < currentEquipment.Length; i++){
            if (currentEquipment[i] != null){
                playerManager.armor += currentEquipment[i].armorModifier;
                playerManager.damage += currentEquipment[i].damageModifier;
            }
        }
    }

    public void Equip (Equipment newItem){
        int slotIndex = (int)newItem.equipSlot;
        Equipment oldItem = null;

        if (currentEquipment[slotIndex] != null){
            oldItem = currentEquipment[slotIndex];
            inventoryManager.Add(oldItem);
        }

        if (onEquipmentChanged != null){
            onEquipmentChanged.Invoke(newItem, oldItem);
        }
        
        currentEquipment[slotIndex] = newItem;
        gearSlots[slotIndex].sprite = newItem.icon;
        UpdateArmor();
    }

    public void Unequip(int slotIndex){
        if (currentEquipment[slotIndex] != null){
            Equipment oldItem = currentEquipment[slotIndex];
            inventoryManager.Add(oldItem);
            currentEquipment[slotIndex] = null;

            if (onEquipmentChanged != null){
                onEquipmentChanged(null, oldItem);
            }
            gearSlots[slotIndex].sprite = null;
        }
         UpdateArmor();
    }
   
}
