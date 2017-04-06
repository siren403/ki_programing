﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using UniRx;
using UniRx.Triggers;

public class CUITitle : MonoBehaviour
{
    public Image mImgFadeOut = null;
    public Text mTxtHighScore = null;
    public Text mTxtGold = null;

    private bool mIsStart = false;

    private void Start()
    {
        //this.UpdateAsObservable()
        Observable.EveryGameObjectUpdate()
            .Where((t) => Input.GetKeyDown(KeyCode.Space))
            .First()
            .Subscribe((t) => OnClickBtnStartGame())
            .AddTo(this.gameObject);

        SetTextHighScore(CGameDataMgr.GetInst().HighScore.Value);
        SetTextGold(CGameDataMgr.GetInst().Gold.Value);
    }

    private void SetTextHighScore(int value)
    {
        mTxtHighScore.text = string.Format("HighScore : {0}", value);
    }
    private void SetTextGold(int value)
    {
        mTxtGold.text = string.Format("Gold : {0}", value);
    }

    public void OnClickBtnStartGame()
    {
        if(mIsStart == false)
        {
            StartCoroutine(OnStartGame());
        }
    }

    private IEnumerator OnStartGame()
    {
        mIsStart = true;
        Color tColor = mImgFadeOut.color;
        while (tColor.a <= 1)
        {
            tColor.a += 0.04f;
            mImgFadeOut.color = tColor;
            yield return null;
        }
        yield return new WaitForSeconds(1.0f);
        SceneManager.LoadScene("CScenePlayGame");
        SceneManager.LoadScene("CScenePlayGameUI",LoadSceneMode.Additive);
        SceneManager.LoadScene("CScenePlayGameMap",LoadSceneMode.Additive);
    }

    public void OnClickBtnReset()
    {
        CGameDataMgr.GetInst().HighScore.Value = 0;
        CGameDataMgr.GetInst().Gold.Value = 0;
        SetTextHighScore(CGameDataMgr.GetInst().HighScore.Value);
        SetTextGold(CGameDataMgr.GetInst().Gold.Value);
    }
}