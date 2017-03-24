using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CGameDataMgr
{
    private static CGameDataMgr mInstance = null;

    public CDialogueInfoList mDialogueList = null;

    private CGameDataMgr()
    {

    }

    public static CGameDataMgr GetInst()
    {
        if(null == mInstance)
        {
            mInstance = new CGameDataMgr();
        }
        return mInstance;
    }
 

    public void CreateMy()
    {
        string dialogueData = Resources.Load<TextAsset>("dialogue_list_json").text;
        mDialogueList = JsonUtility.FromJson<CDialogueInfoList>(dialogueData);
    }
}
