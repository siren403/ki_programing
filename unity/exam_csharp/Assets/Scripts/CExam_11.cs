using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;


/*

	created by pokpoongryu


	C#에서 포인터를 사용할 수 있다.
	다음 두 가지 전제가 있어야만 한다. 

	1. unsafe 키워드를 표시한 코드블록안에서만 가능하다.

	2. /unsafe 옵션을 지정하여 컴파일하여야 한다. 

		mcs.rsp 파일을 만들고 -unsafe를 적어주고 Assets폴더에 위치시켜야 한다.



	unsafe
	
		형식이나 형식의 멤버 또는 문장 블록에 unsafe키워드를 붙이면 
		해당 범위 안에서는 포인터 형식을 이용해서 메모리에 대해 C++스타일의 포인터 연산을 수행할 수 있다. 

		unsafe code는 그에 상응하는 safe구현보다 빠르게 실행된다. 
		unsafe 하게 C#메서드를 call하는 것은 외부C함수를 call하는 것보다 빠를 수도 있다. 왜냐하면, 
			managed 실행환경을 벗어나는데 관련된 추가부담이 없기 때문이다. 



*/
public class CExam_11 : MonoBehaviour
{

    // Use this for initialization
    void Start()
    {
        int[,] tBitmap = new int[48, 48];

        Debug.Log("@@==Bitmap");
        int tRow = 0;
        int tCol = 0;
        for (tRow = 0; tRow < tBitmap.GetLength(0); tRow++)
        {
            for (tCol = 0; tCol < tBitmap.GetLength(1); tCol++)
            {
                Debug.Log(tBitmap[tRow, tCol]);
            }
        }

        #region FUNCTION_USE_POINTER

        BlueFilter(tBitmap);

        #endregion

        Debug.Log("@@==Bitmap BlueFiler");
        for (tRow = 0; tRow < tBitmap.GetLength(0); tRow++)
        {
            for (tCol = 0; tCol < tBitmap.GetLength(1); tCol++)
            {
                Debug.Log(tBitmap[tRow, tCol]);
            }
        }

    }
    /*

	I strongly recommend to not use pointers and unsafe code at all. Keep in mind that some platforms don't support unsafe code for safety such as the webplayer for example.
	If you really need an unsafe context, you have to create a "smcs.rsp" file in your asset folder and add the line

	-unsafe

	to that file. This should add this parameter to the c# compiler options when compiling your project.
	Again, using unsafe doesn't give you much advantages,
	it just opens up for a huge variety of errors,
	mistakes and unexpected behaviour. Unless you know exactly what you do and you use pointers sparsely you shouldn't go for an unsafe context.


	Restarted unity and everything is working right now, thanks!
	*/
    unsafe private void BlueFilter(int[,] tBitmap)
    {
        int tLength = tBitmap.Length;

        fixed (int* tpB = tBitmap)
        {
            int* tpPtr = tpB;
            for (int ti = 0; ti < tLength; ti++)
            {
                *tpPtr++ &= 0xFF;
            }
        }
    }

    // Update is called once per frame
    void Update()
    {

    }
}
