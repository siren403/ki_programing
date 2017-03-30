using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UniRx;

public class CUIPlayGame : MonoBehaviour
{

    public Text mTxtHP = null;
    public Text mTxtScore = null;
    public Text mTxtGold = null;

    private CScenePlayGame mScene = null;

    public void SetScene(CScenePlayGame tScene)
    {
        mScene = tScene;
        mScene.mPlayer.ReadHP.Where((hp) => mTxtHP != null)
            .Subscribe((hp) => 
            {
                mTxtHP.text = string.Format("HP <color='red'>{0}</color>", hp);
            })
            .AddTo(this);

        mScene.ReadScore.Where((score) => mTxtScore != null)
           .Subscribe((score) =>
           {
               mTxtScore.text = string.Format("SCORE <color='gray'>{0}</color>", score);
           })
           .AddTo(this);

        mScene.ReadGold.Where((gold) => mTxtGold != null)
          .Subscribe((gold) =>
          {
              mTxtGold.text = string.Format("GOLD <color='yellow'>{0}</color>", gold);
          })
          .AddTo(this);
    } 
}
