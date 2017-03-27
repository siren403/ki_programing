using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CScenePlayGame : MonoBehaviour
{
    public CPlayer mPlayer = null;

    // Use this for initialization
    void Start()
    {
        CGameDataMgr.GetInst().Create();
    }

    // Update is called once per frame
    void Update()
    {

    }
    private void LateUpdate()
    {
    }

}
