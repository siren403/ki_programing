using System.Collections;
using System.Collections.Generic;
using UnityEngine;


/*
	created by pokpoongryu
	
    Queue<T>
	Queue

	Stack<T>
	Stack

	BitArray

    bool값 하나에 비트 하나만 사용하므로, 
	각 값을 1바이트에 저장하는 보통의 bool배열이나 bool형식의 제네릭List보다 메모리를 효율적으로 사용한다. 
*/
public class CExam_16 : MonoBehaviour
{

    // Use this for initialization
    void Start()
    {
        Debug.Log("@@ Queue");

        Queue<int> tQueue = new Queue<int>();
        tQueue.Enqueue(10);
        tQueue.Enqueue(20);
        int[] tData = tQueue.ToArray();
        Debug.Log(tQueue.Count);
        Debug.Log(tQueue.Peek());
        Debug.Log(tQueue.Dequeue());
        Debug.Log(tQueue.Dequeue());


        Debug.Log("@@ Stack");
        Stack<int> tStack = new Stack<int>();
        tStack.Push(1);
        tStack.Push(2);
        tStack.Push(3);
        Debug.Log(tStack.Count);
        Debug.Log(tStack.Peek());
        Debug.Log(tStack.Pop());
        Debug.Log(tStack.Pop());
        Debug.Log(tStack.Pop());



        Debug.Log("@@ BitArray");
        BitArray tBitArray = new BitArray(2);
        tBitArray[1] = true;

        foreach(bool tIs in tBitArray)
        {
            Debug.Log(tIs);
        }

        tBitArray.Xor(tBitArray);

        Debug.Log("@@ BitArray xor");
        foreach(bool tIs in tBitArray)
        {
            Debug.Log(tIs);
        }

    }

    // Update is called once per frame
    void Update()
    {

    }
}
