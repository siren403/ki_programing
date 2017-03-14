using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;



/*
	created by pokpoongryu


	delegate

		임의의 메서드를 호출하는 방법을 담은 객체이다.
		( 콜하는 측과 콜받는 측의 결합을 끊을 수 있게 된다. )


		deleagte 변수에 메서드를 배정하는 연산은 실행시점에 일어난다. 

	다중캐스트대리자 multicast delegate

		여러 개의 메서드를 대상으로 할 수 있다.

*/
public class CUnit
{
    public int mX = 0;
    public int mY = 0;

    public int Doit(int tA)
    {
        Debug.Log("Unit.Doit " + tA.ToString());

        return 0;
    }
}


public class CExam_9 : MonoBehaviour
{
    delegate int MyCallFunc(int tA);

    delegate void MyCallExamMultiCase();


    // Use this for initialization
    void Start()
    {
        Debug.Log("@@========");

        int tResult = 0;
        tResult = DoSquare(3);
        Debug.Log(tResult);


        MyCallFunc tCallFunc = DoSquare;
        //tCallFunc = new MyCallFunc(DoSquare);
        tResult = tCallFunc(4);
        Debug.Log(tResult);

        tResult = tCallFunc.Invoke(2);
        Debug.Log(tResult);


        MyCallExamMultiCase tCall = null;
        tCall += InputControl;
        tCall += new MyCallExamMultiCase(DisplayToConsole);
        tCall += SaveToFile;

        tCall();


        tCall -= DisplayToConsole;
        tCall.Invoke();


        CUnit tUnit = new CUnit();
        MyCallFunc tUnitCallFunc = tUnit.Doit;
        tUnitCallFunc(777);
    }

    private int DoSquare(int v)
    {
        int tResult = 0;

        tResult = v * v;

        return tResult;
    }

    void InputControl()
    {
        Debug.Log("Input Control");
    }
    void DisplayToConsole()
    {
        Debug.Log("Display To Console");
    }
    void SaveToFile()
    {
        Debug.Log("Save To File");
    }
}
