using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/*
	created by pokpoongryu

	프로퍼티

	base키워드
*/

public class Unit
{
    public int mX = 0;
    public int mY = 0;

    public void Do()
    {
        Debug.Log("Unit.Do");
    }
}
public class Actor : Unit
{
    public void DoDo()
    {
        base.Do();
        Debug.Log("Actor.DoDo");
    }
}



public class CExam_5 : MonoBehaviour
{
    decimal mCurrentPrice;

    public decimal _currentPrice
    {
        get
        {
            return mCurrentPrice;
        }
        set
        {
            mCurrentPrice = value;
        }
    }


    // Use this for initialization
    void Start()
    {
        _currentPrice = 3;
        Debug.Log(_currentPrice.ToString());

        Actor tActor = null;
        tActor = new Actor();
        tActor.DoDo();
            
    }

    // Update is called once per frame
    void Update()
    {

    }
}
