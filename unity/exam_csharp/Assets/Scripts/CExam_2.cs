using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CExam_2 : MonoBehaviour
{

    // Use this for initialization
    void Start()
    {
        Debug.Log("@rectanglar array");
        int tRow = 0;
        int tCol = 0;

        int[,] tArray = new int[4, 3];

        for (tRow = 0; tRow < tArray.GetLength(0); tRow++)
        {
            for (tCol = 0; tCol < tArray.GetLength(1); tCol++)
            {
                tArray[tRow, tCol] = tRow * 3 + tCol;
            }
        }

        for (tRow = 0; tRow < tArray.GetLength(0); tRow++)
        {
            for (tCol = 0; tCol < tArray.GetLength(1); tCol++)
            {
                Debug.Log(tArray[tRow, tCol].ToString());
            }
        }
        //이렇게 선언과 초기화를 동시에 할 수도 있다. 
        int[,] tArray_0 = new int[,]
        {
            {0,1,2},
            {3,4,5},
            {6,7,8}
        };


        Debug.Log("@jagged array");

        int[][] tJaggedArray = new int[4][];

        for (tRow = 0; tRow < tJaggedArray.Length; tRow++)
        {
            tJaggedArray[tRow] = new int[3];
            for (tCol = 0; tCol < tJaggedArray[tRow].Length; tCol++)
            {
                tJaggedArray[tRow][tCol] = tRow * 3 + tCol;
            }
        }
        for (tRow = 0; tRow < tJaggedArray.Length; tRow++)
        {
            for (tCol = 0; tCol < tJaggedArray[tRow].Length; tCol++)
            {
                Debug.Log(tJaggedArray[tRow][tCol].ToString());
            }
        }
        int[][] tJaggedArray_0 = new int[][]
        {
            new int[] {0,1,2},
            new int[] {3,4,5},
            new int[] {6,7,8,9}
        };


        for (tRow = 0; tRow < tJaggedArray_0.Length; tRow++)
        {
            for (tCol = 0; tCol < tJaggedArray_0[tRow].Length; tCol++)
            {
                Debug.Log(tJaggedArray_0[tRow][tCol].ToString());
            }
        }
    }

    // Update is called once per frame
    void Update()
    {

    }
}
