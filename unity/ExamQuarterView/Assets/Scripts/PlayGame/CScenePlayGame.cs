using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class CScenePlayGame : MonoBehaviour
{
    //Instance
    private CAlberto mpAlberto = null;
    private CEnemy_0 mpEnemy_0 = null;
    private List<CMyEnemy> mpEnemyList = null;

    public CUIPlayGame mpUIPlayGame = null;



    // Use this for initialization
    void Start()
    {
        Invoke("StartBGMForPlayGame", 3.0f);

        mpAlberto = Instantiate<CAlberto>(CMyGameDataMgr.GetInst().PFAlberto, new Vector3(0, 0, 0), Quaternion.identity);
        mpEnemyList = new List<CMyEnemy>();
        InvokeRepeating("DoCreateEnemy", 1.0f, 1.5f);

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

    public void DoGoTitle()
    {
        CMySoundMgr.GetInst().Stop(1);
        SceneManager.LoadScene("CSceneTitle");
    }
    public void StartBGMForPlayGame()
    {
        CMySoundMgr.GetInst().Play(1);
    }
    public void DoCreateEnemy()
    {
        int tCount = 0;
        tCount = mpEnemyList.Count;

        if(tCount < 2)
        {
            CMyEnemy tEnemy = null;

            Vector3 tVectorPosition = new Vector3(0.5f, 0.0f, 0.5f);

            if(0 == tCount % 2)
            {
                tEnemy = null;
                tVectorPosition = new Vector3(0.5f - 5.0f, 0.0f, 0.5f);
                tEnemy = Instantiate<CEnemy_0>(CMyGameDataMgr.GetInst().PFEnemy_0, tVectorPosition, Quaternion.identity);
            }
            else
            {
                tEnemy = null;
                tVectorPosition = new Vector3(0.5f - 5.0f, 0.0f, 0.5f + 1.0f);
                tEnemy = Instantiate<CEnemy_1>(CMyGameDataMgr.GetInst().PFEnemy_1, tVectorPosition, Quaternion.identity);
            }
            mpEnemyList.Add(tEnemy);
        }

    }

    public void DoFireBullet()
    {
        Vector3 tVector = this.mpAlberto.transform.position;
        tVector.y += 0.5f;

        CBullet tBullet = Instantiate<CBullet>(CMyGameDataMgr.GetInst().PFBullet, tVector, mpAlberto.transform.localRotation);
        tBullet.GetComponent<Rigidbody>().AddForce(mpAlberto.transform.forward * 10.0f, ForceMode.Impulse);
    }
}

