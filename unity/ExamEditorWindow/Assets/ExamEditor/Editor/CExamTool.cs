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
        //if(null == mDialogueInfoList)
        //{
        //    mDialogueInfoList = new List<CDialogueInfo>();
        //}
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
            //mDialogueInfoList.Add(tDialogueInfo);

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
            //LoadTestFromFile("Assets/Resources/dialogue_list.xml");

            using (StreamReader reader = new StreamReader("Assets/Resources/dialogue_list_json.json"))
            {
                string data = reader.ReadToEnd();

                mDialogueList.mDialogues.Clear();
                mDialogueList.mDialogues = null;
                mDialogueList = null;

                mDialogueList = JsonUtility.FromJson<CDialogueInfoList>(data);

            }




            //EditorApplication.update();
        }


        if (true == GUILayout.Button("Save", GUILayout.Width(60), GUILayout.Height(50)))
        {
            //SaveTestToFile("Assets/Resources/dialogue_list.xml");
            using (StreamWriter writer = new StreamWriter("Assets/Resources/dialogue_list_json.json"))
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


    //protected void LoadTestFromFile(string tFileName)
    //{
    //    mDialogueInfoList.Clear();

    //    FileInfo tFileInfo = new FileInfo(tFileName);
    //    if (false == tFileInfo.Exists)
    //    {
    //        Debug.Log("File is not founded.");
    //    }



    //    System.Xml.XmlDocument Doc = new System.Xml.XmlDocument();
    //    Doc.Load(tFileName);

    //    XmlElement tElementRoot = Doc["DialogueInfoList"];



    //    CDialogueInfo tDialogueInfo = null;
    //    int ti = 0;
    //    int tCount = 0;
    //    XmlElement tElement_0 = null;

    //    tCount = tElementRoot.ChildNodes.Count;

    //    for (ti = 0; ti < tCount; ti++)
    //    {
    //        tElement_0 = null;
    //        tElement_0 = tElementRoot.ChildNodes[ti] as XmlElement;


    //        tDialogueInfo = null;
    //        tDialogueInfo = new CDialogueInfo();
    //        tDialogueInfo.mId = System.Convert.ToInt32(tElement_0.ChildNodes[0].InnerText);


    //        tDialogueInfo.mDialogue = tElement_0.ChildNodes[1].InnerText;

    //        mDialogueInfoList.Add(tDialogueInfo);
    //    }



    //}
    //public void SaveTestToFile(string tFileName)
    //{
    //    FileInfo tFileInfo = new FileInfo(tFileName);
    //    if (false == tFileInfo.Exists)
    //    {
    //        mStreamWriter = tFileInfo.CreateText();
    //    }
    //    else
    //    {
    //        tFileInfo.Delete();
    //        mStreamWriter = tFileInfo.CreateText();
    //    }
    //    mStreamWriter.Close();




    //    XmlDocument tDoc = new System.Xml.XmlDocument();

    //    XmlElement tElementRoot = tDoc.CreateElement("DialogueInfoList");
    //    tDoc.AppendChild(tElementRoot);





    //    int ti = 0;
    //    int tCount = mDialogueInfoList.Count;

    //    CDialogueInfo tInfo = null;
    //    XmlElement tElement_0 = null;

    //    for (ti = 0; ti < tCount; ti++)
    //    {
    //        tInfo = mDialogueInfoList[ti];

    //        XmlElement tElement = tDoc.CreateElement("DialogueInfo");

    //        tElement_0 = null;
    //        tElement_0 = tDoc.CreateElement("mId");
    //        tElement_0.InnerText = tInfo.mId.ToString();
    //        tElement.AppendChild(tElement_0);

    //        tElement_0 = null;
    //        tElement_0 = tDoc.CreateElement("mDialogue");
    //        tElement_0.InnerText = tInfo.mDialogue;
    //        tElement.AppendChild(tElement_0);

    //        tElementRoot.AppendChild(tElement);
    //    }

    //    tDoc.Save(tFileName);
    //}
}
