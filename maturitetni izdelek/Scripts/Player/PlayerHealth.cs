using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;
using UnityEngine.SceneManagement;

public class PlayerHealth : MonoBehaviour
{
    public float maxHealth = 100;
    public float currentHealth = 100;

    [SerializeField] private Image healthbarSprite;
    [SerializeField] private TMP_Text displayHealth;
    private PlayerManager playerManager;
    public BossReset bossReset;
    public GameObject takingDamagePanel;
    public GameObject receivingHealthPanel;

    void Start(){
        UpdateHealthBar(currentHealth, maxHealth);
        DisplayHealth(currentHealth);
        playerManager = GetComponent<PlayerManager>();
    }

    public void UpdateHealth(float amount){


        if (amount < 0){
            currentHealth += amount * (Mathf.Pow(0.99f, GetComponent<PlayerManager>().armor)); //dobis dmg vedno
            takingDamagePanel.SetActive(true);
            Invoke("RemoveTakingDamagePanel", 0.5f);
        }
        else{
            currentHealth += amount; //heal
            receivingHealthPanel.SetActive(true);
            Invoke("ReceivingHealthPanel", 0.5f);
        }
        UpdateHealthBar(currentHealth, maxHealth);
        DisplayHealth(currentHealth);
        if (currentHealth <= 0){
            //SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);
            // Debug.Log("dead");
            this.GetComponent<CharacterController>().enabled = false;
            this.transform.position = playerManager.spawn.transform.position;
            this.GetComponent<CharacterController>().enabled = true;
            currentHealth = maxHealth;
            UpdateHealthBar(currentHealth, maxHealth);
            DisplayHealth(currentHealth);
            bossReset.Reset();
        }
    }
    public void UpdateHealthBar(float currentHealth, float maxHealth){
        healthbarSprite.fillAmount = currentHealth / maxHealth;
    }
    public void RemoveTakingDamagePanel()
    {
        takingDamagePanel.SetActive(false);
    }

    public void ReceivingHealthPanel()
    {
        receivingHealthPanel.SetActive(false);
    }

    public void DisplayHealth(float currentHealth){
        displayHealth.text = Mathf.RoundToInt(currentHealth).ToString();
    }

    private void OnTriggerEnter(Collider other) {
        if (other.gameObject.CompareTag("Projectile") ){
            Destroy(other.gameObject);
            UpdateHealth(-10);
        }
        if (other.gameObject.CompareTag("MovingZone")){
            Destroy(other.gameObject);
            UpdateHealth(-10);
        }
    }
}
