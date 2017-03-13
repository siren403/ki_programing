using System.Collections;
using System.Collections.Generic;
using UnityEngine;
/*
	created by pokpoongryu

	object

		object형식은 모든 형식의 궁극적인 기반 클래스이다. 
		어떤 형식도 object로 상향캐스팅할 수 있다.




	boxing, unboxing 은 type system을 통합하기 위해 만들어진 것이다. 
	( 완벽하지는 않다. )
	저수준 언어인 C에서는 그냥 다 메모리로 취급하지만 
	고수준 언어에서는 의미론상 그렇지 않기 때문이다. 
	프로그램의 안전성을 위한 이론들이다. 
	잘 알고 사용하지 않으면 성능이 희생된다. 
	


	boxing

		값 형식 인스턴스를 참조 형식 인스턴스(인터페이스나 object클래스)로 캐스팅하는 것


	unboxing

		object를 값 형식 인스턴스로 캐스팅하는 것
		명시적 캐스티이 필수이다.


	boxing, unboxing 복사가 일어난다. 
*/
public class CExam_6 : MonoBehaviour
{

    //object
    private int mCurIndex = 0;
    private object[] mArray = new object[10];

    // Use this for initialization
    void Start()
    {
        Push("sausage");


        string tString = (string)Pop();

        Debug.Log(tString);

        Push(777);
        int tInt = (int)Pop();
        Debug.Log(tInt);


        //boxing
        int tA = 777;
        object tObjectA = tA;

        Debug.Log("Boxing " + tObjectA);

        //unboxing
        int tB = (int)tObjectA;
        Debug.Log("UnBoxing " + tB);

        //이 unboxing은 런타임이 에러를 낸다. 명시적으로 캐스팅한 형식이 일치하지 않기 때문이다.
        //object tC = 999;
        //long tLong = (long)tC;

        //unboxing 후 기본수치타입끼리 암묵적 형변환
        object tD = 999;
        long tLong_0 = (int)tD;
        Debug.Log(tLong_0);

        //unboxing 후 명시적 형변환
        object tE = 3.5;
        int tInt_0 = (int)(double)tE;
        Debug.Log(tInt_0);

        Debug.Log("@boxing, unboxing은 복사가 이루어지는 것이다.");
        int tInt_1 = 3;
        object tObject_1 = tInt_1;
        tInt_1 = 5;
        Debug.Log(tInt_1);
        Debug.Log(tObject_1);

        Debug.Log("@배열과 Generic은 참조변환만 되고 박싱변환은 지원하지 않는다.");
        object[] tA_0 = new string[3];

        string a = "test";
        string b = a;
        b = "pc";

        Debug.Log(a);
    }

    // Update is called once per frame
    void Update()
    {

    }

    //object
    public void Push(object tObject)
    {
        mArray[mCurIndex++] = tObject;
    }
    public object Pop()
    {
        return mArray[--mCurIndex];
    }
}
