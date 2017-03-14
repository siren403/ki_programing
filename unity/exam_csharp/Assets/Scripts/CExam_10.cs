using System.Collections;
using System.Collections.Generic;
using UnityEngine;




public class CExam_10 : MonoBehaviour
{
    public delegate void TestHandler();
    TestHandler mHandler = null;

    int[] mIntArray = null;
    TestHandler[] mHandlerArray = null;


    // Use this for initialization
    void Start()
    {
        mIntArray = new int[2];
        mIntArray[0] = 2;
        mIntArray[1] = 3;


        mHandlerArray = new TestHandler[2];
        mHandlerArray[0] = OnHandler_0;
        mHandlerArray[1] = OnHandler_1;


        mHandlerArray[0]();
        mHandlerArray[1].Invoke();

    }

    // Update is called once per frame
    void Update()
    {

    }

    void OnHandler_0()
    {
        Debug.Log("Call OnHandler_0");
    }
    void OnHandler_1()
    {
        Debug.Log("Call OnHandler_1");
    }
}
