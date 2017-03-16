using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class CUIPlayGame : MonoBehaviour
{
    private CScenePlayGame mpScene = null;

    // Use this for initialization
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {

    }

    public void SetScene(CScenePlayGame tpScene)
    {
        mpScene = tpScene;
    }
    public void CreateMy()
    {
    }

    public void OnClickBtnLeftAttack()
    {
        if (mpScene.mAlberto.GetState() == CAlberto.STATE.IDLE)
        {
            mpScene.mAlberto.transform.localScale = new Vector3(-1, 1, 1);
            mpScene.mAlberto.SetState(CAlberto.STATE.ATTACK);
            mpScene.mAlberto.DoAni();

            //mpScene.mAlberto.DoAttack(-1);
            //mpScene.DoFire(-1);
            mpScene.DoAttack(-1.0f);
        }
    }

    public void OnClickBtnRightAttack()
    {
        if (mpScene.mAlberto.GetState() == CAlberto.STATE.IDLE)
        {
            mpScene.mAlberto.transform.localScale = new Vector3(1, 1, 1);
            mpScene.mAlberto.SetState(CAlberto.STATE.ATTACK);
            mpScene.mAlberto.DoAni();

            //mpScene.mAlberto.DoAttack(1);
            //mpScene.DoFire(1);
            mpScene.DoAttack(1.0f);
        }
    }

    public void OnClickRestart()
    {
        mpScene.HideGameOver();
        mpScene.RestartGame();
    }

    public void OnClickGoTitle()
    {
        SceneManager.LoadScene("CSceneTitle");
    }

}
