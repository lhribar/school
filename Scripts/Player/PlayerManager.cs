using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class PlayerManager : MonoBehaviour
{
    public GameObject spawn;
    Animator animator;
    public PlayerMovement playerMovement;
    CameraManager cameraManager;

    //quest + portal
    
    public Quest quest;
    public GameObject portal;
    public int numberOfQuestCompleted;

    public PlayerHealth playerHealth;

    private Interactable interactable = null;

    
    public int gold;
    public int armor;
    public int damage;


    //INTERACTIONS
    public ShopInteraction shopInteraction;
    public QuestNavigation questNavigation;
    public QuestInteraction questInteraction;
    public GameObject interactionText; 
    



    private void Awake()
    {
        this.transform.position = spawn.transform.position;
        animator = GetComponentInChildren<Animator>();
        cameraManager = FindObjectOfType<CameraManager>();
        playerMovement = GetComponent<PlayerMovement>();
        playerHealth = GetComponent<PlayerHealth>();
        Cursor.visible = false;
    }



    private void Update()
    {
        //playerMovement.HandleAllMovement();
        InteractWithObject();
        cameraManager.HandleAllCameraMovement();
    }


    public void InteractWithObject()
    {
        if (Input.GetKeyDown(KeyCode.F)){
            interactionText.SetActive(false);
            ItemInteract();
        }
    }

    public void ItemInteract()
    {
        if (interactable != null){
            interactable.Interact();
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag("QuestGiver")){
            if (other.gameObject.GetComponent<QuestInteraction>()){
                interactionText.SetActive(true);
                interactable = other.GetComponent<Interactable>();
                return;
            }
        }
        if (other.CompareTag("Shop")){
            interactable = other.GetComponent<Interactable>();
            interactionText.SetActive(true);
            return;
        }
        if (other.CompareTag("QuestItem")){
            if (quest.isActive && quest.questID == 2){
                interactable = other.GetComponent<Interactable>();
                interactionText.SetActive(true);
            }
            return;
        }
        if (other.CompareTag("Navigation")){
            interactable = other.GetComponent<Interactable>();
            interactionText.SetActive(true);
            return;
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.CompareTag("QuestGiver")){
            interactionText.SetActive(false);

            interactable = null;

            
            return;
        }

        if (other.CompareTag("Shop")){
            interactionText.SetActive(false);
            shopInteraction.LeaveShop();
            interactable = null;
            return;
        }
        
        if (other.CompareTag("QuestItem")){
            interactionText.SetActive(false);
            interactable = null;
            return;
        }

        if (other.CompareTag("Navigation")){
            interactionText.SetActive(false);
            interactable = null;
            questNavigation.LeaveInteract();
            return;
        }

    }
    public void LoadPlayer(){
        PlayerData data = SaveSystem.LoadPlayer();
        if (data != null){
            Debug.Log(data.health);
            playerHealth.currentHealth = data.health;
            playerHealth.UpdateHealthBar(100, playerHealth.currentHealth);
            playerHealth.DisplayHealth(playerHealth.currentHealth);

            Vector3 position;
            position.x = data.position[0];
            position.y = data.position[1];
            position.z = data.position[2];

            gold = data.gold;
            armor = data.armor;
            damage = data.damage;
            numberOfQuestCompleted = data.questsCompleted;
            
            CharacterController characterController = GetComponent(typeof(CharacterController)) as CharacterController;
            characterController.enabled = false;
            transform.position = position;
            characterController.enabled = true;
        }
    }

    public void CheckForPortal(){
        if (numberOfQuestCompleted > 0){
            
            portal.SetActive(true);
        }
    }
}
