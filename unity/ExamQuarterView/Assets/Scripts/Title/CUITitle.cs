using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;


public class CUITitle : MonoBehaviour {

    private CSceneTitle mpScene = null;

    public Text mpTxtTitle = null;
    public Text mpTxtBtnGoScenePlayGame = null;
    public Text mpTxtBtnGoConfig = null;
    public Text mpTxtInfo = null;

    private void Start()
    {
        mpTxtTitle.text = CMyGameDataMgr.GetInst().mLangTextList[0];
        mpTxtBtnGoScenePlayGame.text = CMyGameDataMgr.GetInst().mLangTextList[1];
        mpTxtBtnGoConfig.text = CMyGameDataMgr.GetInst().mLangTextList[2];
        mpTxtInfo.text = CMyGameDataMgr.GetInst().mLangTextList[3];


    }

    public void SetScene(CSceneTitle tpScene)
    {
        mpScene = tpScene;
    }

    public void OnClickBtnGoPlayGame()
    {
        mpScene.GoPlayGame();
    }

    public void OnClickBtnGoConfig()
    {
        CMySoundMgr.GetInst().Stop(0);
        SceneManager.LoadScene("CSceneConfig");
    }

}
