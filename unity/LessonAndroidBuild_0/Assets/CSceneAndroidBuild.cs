using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CSceneAndroidBuild : MonoBehaviour
{
    public GameObject mCube;

    // Use this for initialization
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {

    }

    private void OnGUI()
    {
        if(GUI.Button(new Rect(100,100,200,80),"Btn"))
        {
            mCube.transform.Translate(0.1f, 0, 0);
        }
    }
}
