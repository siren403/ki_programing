using System.Collections;
using System.Collections.Generic;
using UnityEngine;

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

    public void OnClickBtnMove()
    {
        mpScene.DoMoveAlberto();
    }
    public void OnClickBtnRotate()
    {
        mpScene.DoRotateAlberto();
    }
}
