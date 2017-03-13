using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/*
	created by pokpoongryu

	Generic

		타입을 매개변수로 한다.
		서로 다른 타입들에 대해 재사용할 수 있는 코드를 작성할 수 있다.

		type argument, placeholder



		C++의 template 는 컴파일 시점에 추론으로 인한 형식이 결정되지만 
		Generic은 실행 시점에 결정된다. 
		( Generic은 컴파일 시점에는 그 자체로 컴파일된다. )
*/


//CStack<T>는 모든 타입에 대해 '일반적으로' 작동하도록 한번만 작성된다.
public class CStack<T>
{
    int mCurIndex = 0;
    T[] mArray = new T[100];

    public void Push(T tObject)
    {
        mArray[mCurIndex++] = tObject;
    }
    public T Pop()
    {
        return mArray[--mCurIndex];
    }
}


public class CExam_7 : MonoBehaviour
{

    // Use this for initialization
    void Start()
    {
        CStack<int> tStack = new CStack<int>();
        tStack.Push(5);
        tStack.Push(10);

        int ta = tStack.Pop();
        int tb = tStack.Pop();
        Debug.Log(ta);
        Debug.Log(tb);


        int tA_0 = 5;
        int tB_0 = 777;
        DoSwap(ref tA_0, ref tB_0);
        Debug.Log(tA_0);
        Debug.Log(tB_0);

        //런타임이 추론에 헷갈리지 않게 표기하여 지정해줄 수도 있다.
        DoSwap<int>(ref tA_0, ref tB_0);
        Debug.Log(tA_0);
        Debug.Log(tB_0);


    }

    // Update is called once per frame
    void Update()
    {

    }

    static void DoSwap<T>(ref T tA, ref T tB)
    {
        T tTemp = tA;
        tA = tB;
        tB = tTemp;
    }
}
