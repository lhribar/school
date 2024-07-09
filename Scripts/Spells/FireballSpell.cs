using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FireballSpell : SpellCooldown
{

    private bool onCooldown = false;
    private float cooldownTime = 10.0f;
    private float cooldownTimer = 0.0f;

    [SerializeField] private GameObject player;

    [SerializeField] private GameObject projectile;


    private void Update() {
        if (Input.GetKeyDown(KeyCode.Q) && !onCooldown){
            UseSpell();
        }
        if (onCooldown){
            ApplyCooldown(cooldownTime, ref cooldownTimer, ref onCooldown);
        }
    }

    private void UseSpell(){
        onCooldown = true;
        cooldownTimer = cooldownTime;
        GameObject fireball = Instantiate(projectile, player.transform.position + new Vector3(0, 1, 0), Quaternion.identity);
        fireball.GetComponent<Rigidbody>().AddForce(player.transform.forward * 32f, ForceMode.Impulse);
        Destroy(fireball, 3f);
    }
}
