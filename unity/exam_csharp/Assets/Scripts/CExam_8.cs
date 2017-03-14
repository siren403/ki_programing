using System.Collections;
using System.Collections.Generic;
using UnityEngine;


/*

	created by pokpoongryu




	struct vs class 

		C#에서는 struct와 class가 다음과 같이 서로 다르다. 

		1) struct는 값 형식이고, class는 참조 형식이다. 
		2) struct는 상속을 지원하지 않는다.( 다만, System.ValueType을 상속받기는 한다.)


*/

public struct UnitInfo
{
    //이건 struct에서 안됨, 멤버변수 초기화.
    //public int mX = 0;

    public int mX;
    public int mY;

    //struct는 매개변수 없는 생성자를 가질 수 없다.
    //public SUnitInfo()
    //{
    //}

    public UnitInfo(int tX,int tY)
    {
        this.mX = tX;
        this.mY = tY;
    }

    public override string ToString()
    {
        return string.Format("info : {0}, {1}", this.mX, this.mY);
    }
}
//public struct SActorInfo: SUnitInfo
//{

//}

public class CExam_8 : MonoBehaviour
{

    // Use this for initialization
    void Start()
    {
        UnitInfo tInfo_0 = new UnitInfo();
        UnitInfo tInfo_1 = new UnitInfo(1, 1);

        Debug.Log(tInfo_0.ToString());
        Debug.Log(tInfo_1.ToString());

    }

    // Update is called once per frame
    void Update()
    {

    }
}
