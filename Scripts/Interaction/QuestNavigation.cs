using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class QuestNavigation : Interactable
{
    public GameObject navigationWindow;

    // Update is called once per frame
    public override void Interact()
    {
        navigationWindow.SetActive(!navigationWindow.activeSelf);
    }

    public void LeaveInteract()
    {
        navigationWindow.SetActive(false);
    }
}
