using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class SpellCooldown : MonoBehaviour
{
    [SerializeField] private Image imageCooldown;
    [SerializeField] private TMP_Text textCooldown;


    protected void ApplyCooldown(float cooldownTime, ref float cooldownTimer, ref bool onCooldown){
        cooldownTimer -= Time.deltaTime;

        if(cooldownTimer < 0.0f){
            onCooldown = false;
            textCooldown.text = "Q";
            imageCooldown.fillAmount = 0.0f;
        }
        else{
            textCooldown.text = Mathf.RoundToInt(cooldownTimer).ToString();
            imageCooldown.fillAmount = cooldownTimer / cooldownTime;
        }
    }
}
