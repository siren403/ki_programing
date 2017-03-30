using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CGameDataMgr
{
    //Singleton
    private static CGameDataMgr mInstance = null;
    public static CGameDataMgr GetInst()
    {
        if(mInstance == null)
        {
            mInstance = new CGameDataMgr();
        }
        return mInstance;
    }
    private CGameDataMgr()
    {

    }

    private bool mIsInit = false;

    //Prefabs
    public CMissile PFMissile = null;
    public CPlayer PFPlayer = null;

    //Save Data
    PlayerPrefsInt mHighScore = new PlayerPrefsInt("prefsScore");
    PlayerPrefsInt mSaveGold = new PlayerPrefsInt("prefsGold");

    public PlayerPrefsInt HighScore
    {
        get
        {
            return mHighScore;
        }
    }
    public PlayerPrefsInt Gold
    {
        get
        {
            return mSaveGold;
        }
    }

    public void Create()
    {
        if (mIsInit == false)
        {
            PFMissile = Resources.Load<CMissile>("Prefabs/PFMissile");
            PFPlayer = Resources.Load<CPlayer>("Prefabs/PFPlayer");
            mIsInit = true;
        }
    }
}

