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
        CMySoundMgr.GetInst().Play(0);

        mpUITitle.SetScene(this);
       
    }

   

    public void GoPlayGame()
    {
        CMySoundMgr.GetInst().Stop(0);
        //SceneManager.LoadScene("CSceneSpotLoad");
        SceneManager.LoadScene("CSceneDialogue");

    }
}
