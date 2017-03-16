using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;


public class CScenePlayGame : MonoBehaviour
{
    private const int ENEMY_SLIME_COUNT = 3;
    private const int ENEMY_REDSLIME_COUNT = 3;

    //Prefab Link
    public CAlberto PFAlberto = null;

    public CSlime PFSlime = null;
    public CRedSlime PFRedSlime = null;
    public CSkeleton PFSKeleton = null;
    public CRabbit PFRabbit = null;

    public CBullet PFBullet = null;


    //Instance
    public CUIPlayGame mpUIPlayGame = null;
    [SerializeField]
    private CAlberto mpAlberto = null;
    public CAlberto mAlberto { get { return mpAlberto; } }
    public GameObject mpPanelGameOver = null;
    public Text mpTextScore = null;
    public List<CEnemy> mEnemyList = null;

    // Use this for initialization
    void Start()
    {
        Debug.Log("CScenePlayGame.Start");

        mpUIPlayGame.SetScene(this);
        mpUIPlayGame.CreateMy();

        mpAlberto = Instantiate<CAlberto>(PFAlberto, Vector3.zero, Quaternion.identity);
        mpAlberto.SetScene(this);
        mpAlberto.CreateMy();


        mEnemyList = new List<CEnemy>();

        CEnemy tpEnemy = null;
        for (int i = 0; i < ENEMY_SLIME_COUNT; i++)
        {
            tpEnemy = Instantiate(PFSKeleton, new Vector3((3 + i * 0.5f), 0, 0), Quaternion.identity);
            tpEnemy.SetScene(this);
            tpEnemy.CreateMy();
            mEnemyList.Add(tpEnemy);
        }

        for (int i = 0; i < ENEMY_REDSLIME_COUNT; i++)
        {
            tpEnemy = Instantiate(PFRabbit, new Vector3(-(3 + i * 0.5f), 0, 0), Quaternion.identity);
            tpEnemy.SetScene(this);
            tpEnemy.CreateMy();
            mEnemyList.Add(tpEnemy);
        }
    }

    // Update is called once per frame
    void Update()
    {
        for(int ti = 0;ti < mEnemyList.Count;ti++)
        {
            mEnemyList[ti].UpdateMy();
        }
    }

    public void ShowGameOver()
    {
        mpPanelGameOver.SetActive(true);
    }
    public void HideGameOver()
    {
        mpPanelGameOver.SetActive(false);
    }
    public void RestartGame()
    {
        mpAlberto.SetState(CAlberto.STATE.IDLE);
        mpAlberto.DoAni();

        for (int i = 0; i < mEnemyList.Count; i++)
        {
            mEnemyList[i].transform.position = new Vector3(2 + i * 0.5f, 0, 0);
        }
        CMyMgr.GetInst().mScore = 0;
        mpTextScore.text = CMyMgr.GetInst().mScore.ToString();
    }
    public void AddScore()
    {
        CMyMgr.GetInst().mScore += 1;
        mpTextScore.text = CMyMgr.GetInst().mScore.ToString();
    }

    //public void DoFire(float tDirX)
    //{
    //    Vector3 tBulletPos = mpAlberto.transform.position;
    //    tBulletPos.y += 0.3f;
    //    CBullet bullet = Instantiate<CBullet>(PFBullet, tBulletPos, Quaternion.identity);
    //    bullet.DirX = tDirX;
    //}
    public void DoAttack(float tXSpeed)
    {
        Vector3 tVector = mpAlberto.transform.position;
        tVector.y = tVector.y + 0.5f;
        CBullet tBullet = Instantiate<CBullet>(PFBullet, Vector3.zero, Quaternion.identity);
        tBullet.SetScene(this);
        tBullet.SetXSpeed(tXSpeed);
    }
}