using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

/*
	created by pokpoongryu

	람다표현식( 람다식 )

		대리자 인스턴스가 쓰이는 곳에 대리자 인스턴스 대신 지정할 수 있는 이름 없는 메서드

		(매개변수들) =>표현식-또는-문장-블록



		<--어디에 유용한가?
		--> 일단의 기능을 만들어 적용해야 하고 표기의 양을 줄이며 변경의 국지화를 하려고 할 때 유용하다.


	익명메소드: (생략하자)
		람다식이 도입된 후 잘 쓰이지 않는다.



	익명형식anonymouse type

		익명 형식은 일단의 값들을 저장하기 위해 컴파일러가 컴파일 도주엥 즉석에서 생성하는 간단한 클래스이다. 
		익명 형식의 인스턴스를 생성할 때에는 
			new키워드 다음에 객체 초기치를 지정하면 된다.  

		<--어디에 유용한가?
		--> 일단의 값들을 만들어 적용해야 하고 표기의 양을 줄이며 변경의 국지화를 하려고 할 때 유용하다.

*/
public class CExam_13 : MonoBehaviour
{

    delegate int MyCallFunc(int value);
    Func<int, int> mMyFuncWithFactor = null;

    // Use this for initialization
    void Start()
    {
        Debug.Log("@람다표현식");


        MyCallFunc tMyCall = (value) => { return value * value; };
        tMyCall = value => value * value;
        //매개변수가 단 하나이고, 그 형식을 추론할 수 있는 경우에는 중괄호쌍을 생략하고 더 간단히 표기할 수도 있다.

        //Func, Action대리자와 함께 쓰이는 예시.
        //( Func, Action대리자는 C#에서 제공하는 범용 대리자이다. )
        Func<int, int> tMyFunc = value => value * value;
        Debug.Log(tMyFunc(4));


        //외부변수 갈무리
        //outer variable, captured variable, closure
        int tFactor = 777;
        Func<int, int> tMyFuncWithFactor = value => value * tFactor;
        Debug.Log(tMyFuncWithFactor(4));
        tFactor = 111;
        Debug.Log(tMyFuncWithFactor(4));


        Debug.Log("@익명형식");
        //익명 형식( anonymouse type )을 '참조'할 때에는 반드시 var키워드를 사용해야 한다. 
        //왜냐하면 표기할 타입이름이 없기 때문에 표기할 수 없어서이다. 
        //var : type추론키워드, C++의 auto와 유사하다. 

        var tDude = new { Name = "Bob", Age = 23 };
        Debug.Log(tDude);
        Debug.Log(tDude.Name);
        Debug.Log(tDude.Age);


    }

    // Update is called once per frame
    void Update()
    {

    }
}
