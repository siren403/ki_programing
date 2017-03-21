using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CMyGameDataMgr
{
    private static CMyGameDataMgr mInstance = null;

    //Prefabs
    public CAlberto PFAlberto = null;
    public CEnemy_0 PFEnemy_0 = null;


    public static CMyGameDataMgr GetInst()
    {
        if(mInstance == null)
        {
            mInstance = new CMyGameDataMgr();
        }
        return mInstance;
    }
    private CMyGameDataMgr()
    {
        
    }

    public void Create()
    {
        PFAlberto = Resources.Load<CAlberto>("Prefabs/PFAlberto");
        PFEnemy_0 = Resources.Load<CEnemy_0>("Prefabs/PFEnemy_0");
    }
}
