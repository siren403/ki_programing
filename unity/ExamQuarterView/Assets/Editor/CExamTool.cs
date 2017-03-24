using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

using System;
using System.Xml;
using System.Xml.Serialization;
using System.IO;
using System.Text;


public class CExamTool : EditorWindow
{

    

    int mCurCount = 0;

    private StreamWriter mStreamWriter = null;

    //protected List<CDialogueInfo> mDialogueInfoList = null;

    protected CDialogueInfoList mDialogueList = null;


    [MenuItem("CExamTool/Show CExamTool")]
    public static new void Show()
    {
        EditorWindow.GetWindow<CExamTool>();
        EditorApplication.update();
    }

    private void OnEnable()
    {
        Debug.Log("CExamTool.OnEnable");
        if(null == mDialogueList)
        {
            mDialogueList = new CDialogueInfoList();
            mDialogueList.mDialogues = new List<CDialogueInfo>();
        }
      
    }

    private void OnGUI()
    {
        int ti = 0;

        EditorGUILayout.BeginHorizontal();

        if(true == GUILayout.Button("Test",GUILayout.Width(60),GUILayout.Height(50)))
        {
            CDialogueInfo tDialogueInfo = null;
            tDialogueInfo = new CDialogueInfo();
            tDialogueInfo.mId = mCurCount;
            tDialogueInfo.mDialogue = mCurCount.ToString() + "번째 대화입니다.";

            mDialogueList.mDialogues.Add(tDialogueInfo);

            mCurCount++;

        }

        GUILayout.Space(50);

        if(true == GUILayout.Button("New",GUILayout.Width(60),GUILayout.Height(50)))
        {
            for(ti = 0;ti<mDialogueList.mDialogues.Count;ti++)
            {
                mDialogueList.mDialogues[ti] = null;
            }
            mDialogueList.mDialogues.Clear();

            EditorApplication.update();
        }

        if (true == GUILayout.Button("Load", GUILayout.Width(60), GUILayout.Height(50)))
        {

            using (StreamReader reader = new StreamReader("Assets/Resources/Dialogue/dialogue_list_json.json"))
            {
                string data = reader.ReadToEnd();

                mDialogueList.mDialogues.Clear();
                mDialogueList.mDialogues = null;
                mDialogueList = null;

                mDialogueList = JsonUtility.FromJson<CDialogueInfoList>(data);

            }

            EditorApplication.update();
        }


        if (true == GUILayout.Button("Save", GUILayout.Width(60), GUILayout.Height(50)))
        {
            using (StreamWriter writer = new StreamWriter("Assets/Resources/Dialogue/dialogue_list_json.json"))
            {
                Debug.Log(JsonUtility.ToJson(mDialogueList));
                writer.Write(JsonUtility.ToJson(mDialogueList));
            }
            AssetDatabase.Refresh();
        }

        EditorGUILayout.EndHorizontal();



        GUILayout.Space(5);



        EditorGUILayout.BeginVertical();

        EditorGUILayout.LabelField("dialogue", EditorStyles.helpBox);

        for(ti = 0;ti< mDialogueList.mDialogues.Count;ti++)
        {
            EditorGUILayout.LabelField(mDialogueList.mDialogues[ti].mId.ToString(), EditorStyles.helpBox);

            mDialogueList.mDialogues[ti].mDialogue = EditorGUILayout.TextField(mDialogueList.mDialogues[ti].mDialogue);
        }


        EditorGUILayout.EndVertical();

    }

}
