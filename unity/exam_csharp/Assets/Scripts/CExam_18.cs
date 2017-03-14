using System.Collections;
using System.Collections.Generic;
using UnityEngine;


//C#은 리플렉션이란 기능을 제공한다. 
//실행중에 타입에 대한 여러 정보를 조회할 수 있는 기능이다.
//이것이 가능한 이유는 CLR이 존재하기 때문이다.
//
//for MethodInfo
using System.Reflection;

/*
	created by pokpoongryu


	dictionary

	각 원소가 키-값 쌍인 컬렉션으로 주된 용도는 조회와 정렬된 목록이다. 
	dictionary중에서 'dictionary'와 '정렬된 dictionary'만 살펴본다.

	1) Dictionary

		해쉬테이블로 구현된다.

		중복된 키는 허용하지 않는다. 
		정렬되지 않는다. 
		항목 순서가 항목을 추가한 순서와 다르다.

	2) 정렬된 Dictionary

		중복된 키는 허용하지 않는다. 
		항상 정렬된 상태로 존재한다.(삽입시 정렬이 일어난다)
		

			SortedList<TKey, TValue>		: 배열 두 개로 구현된다.

			SortedDictionary<TKey, TValue>	: 트리로 구현된다.

	
*/
public class CExam_18 : MonoBehaviour
{

    // Use this for initialization
    void Start()
    {
        Debug.Log("@ Dictionary");

        Dictionary<string, int> tDictionary = new Dictionary<string, int>();

        tDictionary.Add("one", 1);
        tDictionary["two"] = 2;
        tDictionary["two"] = 22;
        tDictionary["three"] = 3;


        Debug.Log(tDictionary["two"]);
        Debug.Log(tDictionary.ContainsKey("one"));//키로 검색은 빠름
        Debug.Log(tDictionary.ContainsValue(3));//값으로 검색은 느림

        
        Debug.Log(tDictionary.ContainsKey("onE"));

        int tOutValue = 0;
        if (false == tDictionary.TryGetValue("onE", out tOutValue))
        {
            Debug.Log("그런 값 없음. " + tOutValue.ToString());
        }
        if (true == tDictionary.TryGetValue("one", out tOutValue))
        {
            Debug.Log("Value : " + tOutValue.ToString());
        }

        //나열하기
        foreach (string tString in tDictionary.Keys)
        {
            Debug.Log(tString);
        }
        foreach (int tValue in tDictionary.Values)
        {
            Debug.Log(tValue.ToString());
        }
        foreach (KeyValuePair<string, int> tKVP in tDictionary)
        {
            Debug.Log(tKVP.Key + " : " + tKVP.Value);
        }



        Debug.Log("@ SortedList");
        //var 은 C++로 치자면 auto키워드와 같다. 타입을 추론한다.
        //var tSortedList = new SortedList<string, MethodInfo>();
        SortedList<string, MethodInfo> tSortedList = new SortedList<string, MethodInfo>();
        foreach (MethodInfo tInfo in typeof(object).GetMethods())
        {
            //tSortedList.Add( tInfo.Name, tInfo); //이것은 예외를 일으킨다. 왜냐하면 중복된 내용을 처리하지 못하기 때문이다.
            tSortedList[tInfo.Name] = tInfo;
        }
        foreach (string tName in tSortedList.Keys)
        {
            Debug.Log(tName);
        }
        foreach(MethodInfo tInfo in tSortedList.Values)
        {
            Debug.Log(tInfo.Name + "의 반환 형식은 " + tInfo.ReturnType);
        }


        Debug.Log("@ Sorted Dictionary");


        SortedDictionary<string, MethodInfo> tSortedDictionary = new SortedDictionary<string, MethodInfo>();

        foreach(MethodInfo tInfo in typeof(object).GetMethods())
        {
            //tSortedDictionary.Add( tInfo.Name, tInfo); //이것은 예외를 일으킨다. 왜냐하면 중복된 내용을 처리하지 못하기 때문이다.
            tSortedDictionary[tInfo.Name] = tInfo;
        }
        foreach(string tName in tSortedDictionary.Keys)
        {
            Debug.Log(tName);
        }
        foreach(MethodInfo tInfo in tSortedDictionary.Values)
        {
            Debug.Log(tInfo.Name + "의 반환 형식은 " + tInfo.ReturnType);
        }
    }

    // Update is called once per frame
    void Update()
    {

    }
}
