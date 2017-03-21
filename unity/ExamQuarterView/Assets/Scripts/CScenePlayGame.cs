using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CScenePlayGame : MonoBehaviour
{
    //Instance
    private CAlberto mpAlberto = null;
    private CEnemy_0 mpEnemy_0 = null;

    public CUIPlayGame mpUIPlayGame = null;



    // Use this for initialization
    void Start()
    {
        CMyGameDataMgr.GetInst().Create();

        mpAlberto = Instantiate<CAlberto>(CMyGameDataMgr.GetInst().PFAlberto, new Vector3(0, 0, 0), Quaternion.identity);
        mpEnemy_0 = Instantiate<CEnemy_0>(CMyGameDataMgr.GetInst().PFEnemy_0, new Vector3(1, 0, 0), Quaternion.identity);

        mpUIPlayGame = GameObject.FindObjectOfType<CUIPlayGame>();
        mpUIPlayGame.SetScene(this);
    }

    public void DoMoveAlberto()
    {
        mpAlberto.DoMove(Vector3.forward);
    }
    public void DoRotateAlberto()
    {
        mpAlberto.DoRotate(90);
    }
    // Update is called once per frame
    void Update()
    {

    }
}
