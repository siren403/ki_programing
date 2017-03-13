using UnityEngine;
using System.Text;

public class CExam_0 : MonoBehaviour
{


    // Use this for initialization
    void Start()
    {
        Debug.LogFormat("Hello World [{0}]","HI");

        int tA = 3;
        int tB = 2;
        int tResult = 0;

        tResult = tA + tB;

        Debug.LogFormat("Result = {0}", tResult);
        Debug.Log(tResult.ToString());

        int[] tArray = { 1, 2, 3, 4, 5 };
        //tArray = new int[5] { 3, 3, 3, 3, 3 };


        StringBuilder sb = new StringBuilder();
        sb.Append("[");
        for (int i = 0; i < tArray.Length; i++)
        {
            sb.AppendFormat("{0},",tArray[i]);
        }
        sb.Append("]");
        Debug.Log(sb.ToString());


        Debug.Log("@tVowels_0");
        char[] tVowels = null;
        tVowels = new char[5] { 'a', 'e' , 'i' , 'o' , 'u' };
        for(int i = 0;i<tVowels.Length;i++)
        {
            Debug.Log(tVowels[i]);
        }
    }

    // Update is called once per frame
    void Update()
    {

    }
}
