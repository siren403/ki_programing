using System.Collections;
using System.Collections.Generic;
using UnityEngine;



/*
	created by pokpoongryu

	전처리기 지시자 preprocessor directive

		코드의 특정 영역에 대한 추가적인 정보를 컴파일러에게 제공한다. 

*/
public class CExam_12 : MonoBehaviour
{
    // Use this for initialization
    void Start()
    {
#if UNITY_EDITOR
        Debug.Log("Unity Editor");
#endif
#if UNITY_ANDROID
        Debug.Log("Android");
#endif
#if UNITY_STANDALONE_OSX
        Debug.Log("Stand Alone OSX");
#endif
#if UNITY_STANDALONE_WIN
        Debug.Log("Stand Alone Windows");
#endif
    }

    // Update is called once per frame
    void Update()
    {

    }

    #region Area
    void Doit()
    {

    }
    #endregion
}
