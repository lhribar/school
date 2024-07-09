using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BossReset : MonoBehaviour
{
    public Boss boss;
    public GameObject bossArena;
    public GameObject gates;


    public void Reset()
    {
        boss.currentHealth = boss.maxHealth;
        boss.healthbar.UpdateHealthBar(boss.currentHealth, boss.maxHealth);
        gates.SetActive(false);
        bossArena.SetActive(true);
        boss.enabled = false;

        switch(boss.randomAbility){
            case 1:
                boss.animator.Rebind();
                boss.animationIsPlaying = false;
                break;

            case 2:
                for (int i = 0; i < boss.numberOfOrbs.Length; i++){
                    if (boss.numberOfOrbs[i] != null)
                        Destroy(boss.numberOfOrbs[i]);
                }
                boss.animator.Rebind();
                boss.animationIsPlaying = false;
                break;

            case 3:
                for (int i = 0; i < boss.golems.Length; i++){
                    if (boss.golems[i] != null)
                        Destroy(boss.golems[i]);
                }
                for (int i = 0; i < boss.projectileEnemies.Length; i++){
                    if (boss.projectileEnemies[i] != null)
                        Destroy(boss.projectileEnemies[i]);
                }
                boss.animator.Rebind();
                boss.animationIsPlaying = false;
                boss.invicible = false;
                break;
                
            case 4:
                boss.resetBossPosition();
                boss.DestroyZone();
                boss.DestroyTornado();
                boss.animator.Rebind();
                boss.animationIsPlaying = false;
                break;
            }

        }
}
