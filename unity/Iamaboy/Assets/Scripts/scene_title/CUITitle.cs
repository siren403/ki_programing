using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class CUITitle : MonoBehaviour
{

    // Use this for initialization
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {

    }

    public void OnClickBtnGoScenePlayGame()
    {
        Debug.Log("CUITitle.OnClickBtnGoScenePlayGame");
        SceneManager.LoadScene("CScenePlayGame");
        //SceneManager.LoadScene("CScenePlayGame",LoadSceneMode.Additive);
    }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       

}
