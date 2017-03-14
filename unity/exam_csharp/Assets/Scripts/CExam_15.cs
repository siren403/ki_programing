using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/*
	created by pokpoongryu

	LinkedList<T>

	더블 링크드리스트로 구현된다.
*/
public class CExam_15 : MonoBehaviour
{

    // Use this for initialization
    void Start()
    {
        Debug.Log("@LinkedList를 살펴본다");

        LinkedList<string> tStringLinkedList = new LinkedList<string>();

        tStringLinkedList.AddFirst("도");
        tStringLinkedList.AddLast("솔");

        //색인 연산을 지원하지 않음.
        //Debug.Log("@======");
        //for( ti = 0; ti<tStringLinkedList.Count; ti++ )
        //{
        //	Debug.Log(tStringLinkedList[ti]);
        //}
        Debug.Log("@======");
        foreach (string tString in tStringLinkedList)
        {
            Debug.Log(tString);
        }


        tStringLinkedList.AddAfter(tStringLinkedList.First, "레");
        tStringLinkedList.AddAfter(tStringLinkedList.First.Next, "mi");
        tStringLinkedList.AddBefore(tStringLinkedList.Last, "fa");
        Debug.Log("@======");
        foreach (string tString in tStringLinkedList)
        {
            Debug.Log(tString);
        }

        tStringLinkedList.RemoveFirst();
        tStringLinkedList.RemoveLast();
        Debug.Log("@======");
        foreach (string tString in tStringLinkedList)
        {
            Debug.Log(tString);
        }

        LinkedListNode<string> tNode = tStringLinkedList.Find("mi");
        if(tNode != null)
        {
            tStringLinkedList.Remove(tNode);
            tStringLinkedList.AddFirst(tNode);
        }


        Debug.Log("@======");
        foreach (string tString in tStringLinkedList)
        {
            Debug.Log(tString);
        }

    }

    // Update is called once per frame
    void Update()
    {

    }
}
