using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using UnityEngine.Rendering;

public class Graphics : MonoBehaviour
{
    public TMP_Dropdown dropdown;
    public void ChangeGraphics(int value)
    {
        QualitySettings.SetQualityLevel(value);
        
    }
}
