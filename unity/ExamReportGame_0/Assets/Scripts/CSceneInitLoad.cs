using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class CSceneInitLoad : MonoBehaviour
{

    // Use this for initialization
    void Start()
    {
        CGameDataMgr.GetInst().Create();
        SceneManager.LoadScene("CScenePlayGame");
    }

}
