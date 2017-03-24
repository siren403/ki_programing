using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CSceneSpotLoad : MonoBehaviour
{

    private void Start()
    {
        CMyGameDataMgr.GetInst().DoNextStage();
    }
}
