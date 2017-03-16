using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CSlime : MonoBehaviour
{
    private CScenePlayGame mpScene = null;

    protected Animator mpAnimator = null;

    // Use this for initialization
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {

    }

    public void CreateMy()
    {
        mpAnimator = GetComponentInChildren<Animator>();
    }
    public void UpdateMy()
    {
        this.transform.position = Vector3.MoveTowards(this.transform.position,
            mpScene.mAlberto.transform.position, 0.01f);
    }
    public void SetScene(CScenePlayGame tpScene)
    {
        mpScene = tpScene;
    }
}
