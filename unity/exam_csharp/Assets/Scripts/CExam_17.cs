using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
/*
	created by pokpoongryu

	중복을 허용하지 않는다.

	HashSet<T> :정렬하지 않는다. 
		
		SortedSet<T>: 이것은 아직 유니티에서는 사용불가이다. 정렬한다.


	Contains 메소드는 해시 기반 조회(hash_based lookup)를 이용해서 빠르게 실행된다. 
	중복된 원소를 저장하지 않으며 중복된 원소를 추가하는 요청은 무시한다. 
	색인으로 특정 원소에 접근할 수 없다. 

	HashSet<T>는 키들만 저장하는 해시테이블로 구현된다.

	집합연산
*/
public class CExam_17 : MonoBehaviour
{

    // Use this for initialization
    void Start()
    {
        Debug.Log("@@ HashSet 중복을 허용하지 않음. 정렬하지 않는다.");

        var tLettersHashSet_0 = new HashSet<char>("the quick brown fox");

        Debug.Log(tLettersHashSet_0.Contains('t'));
        Debug.Log(tLettersHashSet_0.Contains('j'));

        foreach (char tC in tLettersHashSet_0)
        {
            Debug.Log(tC);
        }


        Debug.Log("@ z를 추가해봄.");
        tLettersHashSet_0.Add('z');
        tLettersHashSet_0.Add('z');
        foreach (char tC in tLettersHashSet_0)
        {
            Debug.Log(tC);
        }


        Debug.Log("@@ 집합연산 ExceptWith 해당하는 것들을 제외한다.");

        var tLettersHashSet_2 = new HashSet<char>("the quick brown fox");
        tLettersHashSet_2.ExceptWith("aeiou");
        foreach(char tC in tLettersHashSet_2)
        {
            Debug.Log(tC);
        }



        Debug.Log("@@ 집합연산 SymmerticExceptWith : 두 지합 모두에 존재하지 않는 것들만 남긴다.");

        var tLettersHashSet_3 = new HashSet<char>("the quick brown fox");
        //tLettersHashSet_3.SymmetricExceptWith("the lazy brown fox");	<--이것은 예상과는 다르게 동작한다. 버그로 보인다. 

        tLettersHashSet_3.SymmetricExceptWith("the lazy");
        foreach(char tC in tLettersHashSet_3)
        {
            Debug.Log(tC);
        }

        Debug.Log("System.Environment.Version : "+System.Environment.Version);
        //Unity 5.0은 .NET Framework 2.0기반이고 일부 3.5를 지원한다.HashSet
        //SortedSet은 .NET Framework 4.0부터 사용가능하다.
        /* 
		Debug.Log("@@SortedSet");

		var tLettersSortedSet = new SortedSet<char>("the quick brown fox");

		foreach( char tC in tLettersSortedSet)
		{
			Debug.Log(tC);
		}
		*/
    }

    // Update is called once per frame
    void Update()
    {

    }
}
