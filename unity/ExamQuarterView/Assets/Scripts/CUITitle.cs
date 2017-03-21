using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CUITitle : MonoBehaviour {

    private CSceneTitle mpScene = null;


	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}


    public void SetScene(CSceneTitle tpScene)
    {
        mpScene = tpScene;
    }

    public void OnClickBtnGoPlayGame()
    {
        mpScene.GoPlayGame();
    }
}
