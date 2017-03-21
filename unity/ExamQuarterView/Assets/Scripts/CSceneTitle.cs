using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class CSceneTitle : MonoBehaviour
{
    public CUITitle mpUITitle = null;

    // Use this for initialization
    void Start()
    {
        mpUITitle.SetScene(this);
    }

    // Update is called once per frame
    void Update()
    {

    }

    public void GoPlayGame()
    {
        SceneManager.LoadScene("CScenePlayGame");
        SceneManager.LoadScene("CScenePlayGameGrid_0", LoadSceneMode.Additive);
        SceneManager.LoadScene("CScenePlayGameUI", LoadSceneMode.Additive);
    }
}
