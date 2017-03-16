using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;


public class CScenePlayGame : MonoBehaviour
{

    //Prefab Link
    public CAlberto PFAlberto = null;
    public CSlime PFSlime = null;
    public CBullet PFBullet = null;


    public CUIPlayGame mpUIPlayGame = null;

    [SerializeField]
    private CAlberto mpAlberto = null;
    public CAlberto mAlberto { get { return mpAlberto; } }

    public CSlime mpSlime = null;

    public GameObject mpPanelGameOver = null;

    public Text mpTextScore = null;

    // Use this for initialization
    void Start()
    {
        Debug.Log("CScenePlayGame.Start");

        mpUIPlayGame.SetScene(this);
        mpUIPlayGame.CreateMy();

        mpAlberto = Instantiate<CAlberto>(PFAlberto, Vector3.zero, Quaternion.identity);
        mpAlberto.SetScene(this);
        mpAlberto.CreateMy();

        mpSlime = Instantiate<CSlime>(PFSlime, new Vector3(2,0,0), Quaternion.identity);
        mpSlime.SetScene(this);
        mpSlime.CreateMy();
    }

    // Update is called once per frame
    void Update()
    {
        mpSlime.UpdateMy();
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

        mpSlime.transform.position = new Vector3(2, 0, 0);
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