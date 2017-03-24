using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;


public class CSceneDialogue : MonoBehaviour
{
    public CUIDialogue mUIDialogue = null;

    public GameObject mUnityChan = null;


    public Text mpTxtDialogue = null;

    public int mDialogueIndex = 0;

    public bool mIsDialoguePlay = false;

    private float mCurrentTime = 0.0f;
    private int mDialogueCharIndex = 0;
    private float mDialogueSpeed = 0.1f;

    private CDialogueInfo mCurrentDialogue = null;

    private bool mIsTranslateScene = false;

    // Use this for initialization
    void Start()
    {
        mUIDialogue.SetScene(this);
        DoNextDialogue();
    }

    void Update()
    {
        if (mIsDialoguePlay)
        {
            mCurrentTime += Time.deltaTime;

            if (mCurrentTime >= mDialogueSpeed)
            {
                mCurrentTime = 0;

                if (mDialogueCharIndex < mCurrentDialogue.mDialogue.Length)
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

    public void DoNextDialogue()
    {
        if(mIsTranslateScene)
        {
            return;
        }

        if (mIsDialoguePlay == false)
        {
            mIsDialoguePlay = true;

            mCurrentDialogue = CMyGameDataMgr.GetInst().mDialogueList.mDialogues[mDialogueIndex];

            mDialogueIndex++;

            if (mDialogueIndex >= CMyGameDataMgr.GetInst().mDialogueList.mDialogues.Count)
            {
                mIsDialoguePlay = false;
                mIsTranslateScene = true;
                mDialogueIndex = 0;
                mUnityChan.GetComponentInChildren<Animator>().CrossFade("RUN00_F", 0);
                Invoke("GoSceneSpotLoad", 3.0f);
            }
        }
        else
        {
            mDialogueCharIndex = mCurrentDialogue.mDialogue.Length - 1;
        }
    }

    public void GoSceneSpotLoad()
    {
        SceneManager.LoadScene("CSceneSpotLoad");
    }
}
