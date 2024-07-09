using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;


public class MainMenu : MonoBehaviour
{

    public void PlayGame(){
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 1);
    }

    public void QuitGame(){
        Application.Quit();
    }

    // public void LoadPlayer(){
    //     PlayerData data = SaveSystem.LoadPlayer();
    //     if (data != null){
    //         Debug.Log(data.health);
    //         playerManager.playerHealth.currentHealth = data.health;
    //         playerManager.playerHealth.UpdateHealthBar(100, playerManager.playerHealth.currentHealth);
    //         playerManager.playerHealth.DisplayHealth(playerManager.playerHealth.currentHealth);

    //         Vector3 position;
    //         position.x = data.position[0];
    //         position.y = data.position[1];
    //         position.z = data.position[2];
    //         CharacterController characterController = GetComponent(typeof(CharacterController)) as CharacterController;
    //         characterController.enabled = false;
    //         transform.position = position;
    //         characterController.enabled = true;
    //     }
    // }
}
