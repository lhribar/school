using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;


public class Healthbar : MonoBehaviour
{

    public GameObject healthbarUI;
    [SerializeField] private Image healthbarSprite;

    private Camera cam;

    private void Start(){
        cam = Camera.main;
    }

    public void UpdateHealthBar(float currentHealth, float maxHealth){
        healthbarSprite.fillAmount = currentHealth / maxHealth;
        if (currentHealth / maxHealth < 1){
            healthbarUI.SetActive(true);
        }
    }

    private void Update(){
        transform.rotation = Quaternion.LookRotation(transform.position - cam.transform.position);
    }

}
