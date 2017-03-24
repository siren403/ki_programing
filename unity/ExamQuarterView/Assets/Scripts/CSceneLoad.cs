using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class CSceneLoad : MonoBehaviour
{

    void Start()
    {
        CMySoundMgr.GetInst().CreateMy();
        CMySoundMgr.GetInst().SetAudioBundle(FindObjectOfType<CAudioBundle>());
        CMySoundMgr.GetInst().BuildMy();

        CMyGameDataMgr.GetInst().Create();

        SceneManager.LoadScene("CSceneTitle");
    }
}
