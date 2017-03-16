using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CMyMgr
{
    private static CMyMgr mInstance = null;

    public int mScore = 0;

    private CMyMgr()
    {

    }

    public static CMyMgr GetInst()
    {
        if(mInstance == null )
        {
            mInstance = new CMyMgr();
        }
        return mInstance;
    }
}
