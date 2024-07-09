using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.AI;

public class PauseMenu : MonoBehaviour
{
    public GameObject pauseMenu;
    public static bool isPaused;
    public PlayerManager playerManager;
    public GameObject quitGamePannel;
    public InventoryUI inventoryUI;
    
    void Start()
    {
        pauseMenu.SetActive(false);
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Escape)){
            if (isPaused)
                ResumeGame();
            else
                PauseGame();
        }
    }

    public void PauseGame()
    {
        Cursor.visible = true;
        pauseMenu.SetActive(true);
        
        Time.timeScale = 0f;
        isPaused = true;
    }

    public void ResumeGame()
    {
        Cursor.visible = false;
        pauseMenu.SetActive(false);

        Time.timeScale = 1f;
        isPaused = false;
    }

    public void GoToMainMenu()
    {
        Time.timeScale = 1f;
        SceneManager.LoadScene("MainMenu");
        isPaused = false;
    }

    public void QuitGamePanel()
    {
        quitGamePannel.SetActive(true);
    }

    public void QuitGame()
    {
        Application.Quit();
    }

    public void DontToToMainMenu()
    {
        quitGamePannel.SetActive(false);
    }

    public void SavePlayer(){ //igralec lahko shrani le, če se ne bojuje z glavnim sovražnikom
        // SaveSystem.SavePlayer(playerManager.playerHealth, playerManager.playerMovement);
        // 
        NavMeshHit hit;
        if (!(NavMesh.SamplePosition(playerManager.transform.position, out hit, 1.0f, 1 << NavMesh.GetAreaFromName("Arena")) || playerManager.quest.isActive)){
            SaveSystem.SavePlayer(playerManager.playerHealth, playerManager.playerMovement, playerManager.gold, playerManager.armor, playerManager.damage, playerManager.numberOfQuestCompleted); //save player
            SaveSystem.SaveEnemy();
            SaveSystem.SaveQuestGivers();
            // for (int i = 0; i < EnemySpawner.allEnemies.Count; i++){ // save enemies
            //     Debug.Log("saving Enemy");
            //     if (!(EnemySpawner.allEnemies[i] == null)){
            //         SaveSystem.SaveEnemy(EnemySpawner.allEnemies[i].GetComponent<EnemyMovement>(), EnemySpawner.allEnemies[i].GetComponent<EnemyMovement>().enemySaveID);
            //     }
            // }

            
            GoToMainMenu();
        }
        else{
            Debug.Log("can not save");
        }
    }
}
