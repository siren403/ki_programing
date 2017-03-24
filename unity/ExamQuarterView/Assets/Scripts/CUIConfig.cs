using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;


public class CUIConfig : MonoBehaviour
{

    public void OnClickBtnGoSceneTitle()
    {
        SceneManager.LoadScene("CSceneTitle");
    }

   
    public void OnClickBtnSelectKR()
    {
        CMyGameDataMgr.GetInst().BuildLangType(0);
    }

    public void OnClickBtnSelectEN()
    {
        CMyGameDataMgr.GetInst().BuildLangType(1);
    }

}
