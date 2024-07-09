using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class HealSpell : MonoBehaviour
{
    private float spellCastTime = 10f;
    private float currentCastTime = 0f;
    public int healAmount;
    private bool alreadyCasting = false;
    float currentPositionX;
    float currentPositionZ;
    float healthAtTheStartOfCasting;
    Vector3 positionAtTheStartOfCasting; //rabimo roundad ker ga idle animation premakne za 0.0001
    public GameObject spellUI;
    public Image CastingImage;
    public PlayerHealth playerHealth;

    private void Update() {
        if (Input.GetKeyDown(KeyCode.E)){
                if (!alreadyCasting){
                    currentCastTime = 0;
                    currentPositionX = Mathf.RoundToInt(transform.position.x);
                    currentPositionZ = Mathf.RoundToInt(transform.position.z);
                    healthAtTheStartOfCasting = playerHealth.currentHealth;
                    alreadyCasting = true;
                }
        }
        if (alreadyCasting){
            if (currentCastTime <= spellCastTime){
                if ((Mathf.RoundToInt(transform.position.x) == currentPositionX && Mathf.RoundToInt(transform.position.z) == currentPositionZ) && (playerHealth.currentHealth == healthAtTheStartOfCasting) && this.GetComponent<PlayerMovement>().characterController.isGrounded){
                    spellUI.SetActive(true);
                    currentCastTime += Time.deltaTime;
                    updateSpellUI();
                    Debug.Log(currentCastTime);
                }
                else{
                    spellUI.SetActive(false);
                    Debug.Log("canceled healing");
                    alreadyCasting = false;
                }
            }
            else{
                spellUI.SetActive(false);
                Heal();
                alreadyCasting = false;
            }
        }
    }

    public void updateSpellUI(){
        CastingImage.fillAmount = currentCastTime / spellCastTime;
    }

    public void Heal(){
        if (playerHealth.currentHealth + healAmount > 100){
            playerHealth.UpdateHealth(playerHealth.maxHealth - playerHealth.currentHealth);
        }
        else{
            playerHealth.UpdateHealth(healAmount);
        }
        
    }
}
