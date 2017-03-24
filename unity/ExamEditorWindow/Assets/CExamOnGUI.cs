using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CExamOnGUI : MonoBehaviour
{
    string mInputString = "";

    public Vector2 mScrollPosition = Vector2.zero;


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
        GUI.Label(new Rect(0, 0, 240, 100), "this is text for test OnGUI.");

        if (true == GUI.Button(new Rect(0, 100, 240, 100), "TestButton"))
        {
            Debug.Log("TestButton is clicked");
        }

        mInputString = GUI.TextField(new Rect(0, 200, 240, 100), mInputString);
        if (string.IsNullOrEmpty(mInputString) == false)
        {
            Debug.Log(mInputString);
        }

        mScrollPosition = GUI.BeginScrollView(new Rect(0, 300, 240, 500)
            , mScrollPosition, new Rect(0, 0, 480, 800));

        GUI.Button(new Rect(0, 0, 50, 50), "Top-left");
        GUI.Button(new Rect(480 - 50, 0, 50, 50), "Top-Right");
        GUI.Button(new Rect(0, 800 - 50, 50, 50), "Bottom-left");
        GUI.Button(new Rect(480 - 50, 800 - 50, 50, 50), "Bottom-right");
        GUI.EndScrollView();

    }
}
