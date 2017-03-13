using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public struct Point
{
    public int x;
    public int y;
}

public class MyPoint
{
    public int mX = 0;
    public int mY = 0;
}



public class CExam_1 : MonoBehaviour
{

    // Use this for initialization
    void Start()
    {
        Debug.Log("배열");
        Debug.Log("값형식vs참조형식");


        Point[] tPointArray_0 = null;
        tPointArray_0 = new Point[1000];

        for (int i = 0; i < tPointArray_0.Length; i++)
        {
            tPointArray_0[i].x = i;
            tPointArray_0[i].y = i;
        }
        Debug.Log("struct");
        var point = tPointArray_0[776];
        Debug.Log(point.x.ToString());
        Debug.Log(point.y.ToString());
        point.x = 0;
        point.y = 0;
        Debug.Log(tPointArray_0[776].x.ToString());
        Debug.Log(tPointArray_0[776].y.ToString());




        MyPoint[] tPointArray_1 = null;
        tPointArray_1 = new MyPoint[1000];
        for (int i = 0; i < tPointArray_1.Length; i++)
        {
            tPointArray_1[i] = new MyPoint() { mX = i, mY = i };
        }
        Debug.Log("class");

        var myPoint = tPointArray_1[776];
        Debug.Log(myPoint.mX.ToString());
        Debug.Log(myPoint.mY.ToString());
        myPoint.mX = 0;
        myPoint.mY = 0;
        Debug.Log(tPointArray_1[776].mX.ToString());
        Debug.Log(tPointArray_1[776].mY.ToString());



    }

    // Update is called once per frame
    void Update()
    {

    }
}
