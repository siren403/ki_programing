using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class CAlberto : CMyUnit
{


    private void OnTriggerEnter(Collider other)
    {
        if(other.CompareTag("tagNextPoint"))
        {
            CMySoundMgr.GetInst().Stop(1);
            SceneManager.LoadScene("CSceneSpotLoad");
        }
    }


}
