using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CUIPlayGame : MonoBehaviour
{
    private CScenePlayGame mpScene = null;




    public void SetScene(CScenePlayGame tpScene)
    {
        mpScene = tpScene;
    }

    public void OnClickBtnMove()
    {
        mpScene.DoMoveAlberto();
    }
    public void OnClickBtnRotate()
    {
        mpScene.DoRotateAlberto();
    }
    public void OnClickBtnGoTitle()
    {
        mpScene.DoGoTitle();
    }
    public void OnClickBtnDoFire()
    {
        mpScene.DoFireBullet();
    }
}
