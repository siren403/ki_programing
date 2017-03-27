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


    public void Create()
    {
        if (mIsInit == false)
        {
            PFMissile = Resources.Load<CMissile>("Prefabs/PFMissile");


            mIsInit = true;
        }
    }
}

