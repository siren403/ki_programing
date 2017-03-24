using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;


public class CExamEditor : EditorWindow
{

    string mInputString = "";

    bool mIsFoldout = false;

    [MenuItem("CExamEditor/Show CExamEditor")]
    public static new void Show()
    {
        EditorWindow.GetWindow<CExamEditor>();
        EditorApplication.update();
    }

    private void OnEnable()
    {
        Debug.Log("CExamEditor.OnEnable");
    }
    private void OnGUI()
    {
        ////label
        //GUI.Label(new Rect(0, 0, 240, 100), "this is text for test OnGUI.");

        ////button
        //if (true == GUI.Button(new Rect(0, 100, 240, 100), "TestButton"))
        //{
        //    Debug.Log("TestButton is clicked.");
        //}

        ////textfield
        //mInputString = GUI.TextField(new Rect(0, 200, 240, 100), mInputString);
        //Debug.Log(mInputString);



        EditorGUILayout.BeginVertical();

        if(true == GUILayout.Button("TestGUILayoutButton_0",GUILayout.Width(240),GUILayout.Height(50)))
        {

        }

        GUILayout.Space(10);

        if(true == GUILayout.Button("TestGUILayoutButton_1",GUILayout.Width(240),GUILayout.Height(50)))
        {

        }

        EditorGUILayout.EndVertical();

        mIsFoldout = EditorGUILayout.Foldout(mIsFoldout, "Test FoldOut");
        if (true == mIsFoldout)
        {
            EditorGUILayout.BeginVertical();
            int ti = 0;
            for (ti = 0; ti < 5; ti++)
            {
                EditorGUILayout.LabelField("LabelField_" + ti.ToString(), EditorStyles.helpBox);
            }

            if(true == GUILayout.Button("Button",EditorStyles.miniButton,GUILayout.Width(100),GUILayout.Height(20)))
            {

            }
            mInputString = EditorGUILayout.TextField(mInputString);

            EditorGUILayout.EndVertical();
        }
        EditorGUILayout.LabelField("Input : " + mInputString,EditorStyles.helpBox);

    }


}
