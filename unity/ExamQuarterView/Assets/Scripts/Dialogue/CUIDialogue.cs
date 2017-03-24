using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class CUIDialogue : MonoBehaviour {

    private CSceneDialogue mpScene = null;

    private void Start()
    {
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void SetScene(CSceneDialogue tpScene)
    {
        mpScene = tpScene;
    }
        
    public void OnClickBtnNext()
    {
        mpScene.DoNextDialogue();
    }
}
