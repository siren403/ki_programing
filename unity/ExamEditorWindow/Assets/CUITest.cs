using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CUITest : MonoBehaviour
{

    public Text mpTxtDialogue = null;

    public int mDialogueIndex = 0;


    public bool mIsDialoguePlay = false;

    private float mCurrentTime = 0.0f;
    private int mDialogueCharIndex = 0;

    private CDialogueInfo mCurrentDialogue = null;

    // Use this for initialization
    void Start()
    {
        CGameDataMgr.GetInst().CreateMy();
    }

    // Update is called once per frame
    void Update()
    {
        if(mIsDialoguePlay)
        {
            mCurrentTime += Time.deltaTime;

            if(mCurrentTime >= 0.15f)
            {
                //mIsDialoguePlay = false;
                mCurrentTime = 0;

                if(mDialogueCharIndex < mCurrentDialogue.mDialogue.Length)
                {
                    mpTxtDialogue.text = string.Format("<color='green'>id : {0}</color>\n<color='white'>{1}</color>", mCurrentDialogue.mId, mCurrentDialogue.mDialogue.Substring(0, mDialogueCharIndex));
                    mDialogueCharIndex++;
                }
                else
                {
                    mDialogueCharIndex = 0;
                    mIsDialoguePlay = false;
                }

            }
        }
    }

    public void OnClickBtnNext()
    {
        if (mIsDialoguePlay == false)
        {
            mIsDialoguePlay = true;

            mCurrentDialogue = CGameDataMgr.GetInst().mDialogueList.mDialogues[mDialogueIndex];

            mDialogueIndex++;

            if (mDialogueIndex >= CGameDataMgr.GetInst().mDialogueList.mDialogues.Count)
            {
                mDialogueIndex = 0;
            }
        }
    }
}
