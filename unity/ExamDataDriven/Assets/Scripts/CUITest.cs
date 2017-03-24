using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System;
using System.Xml;

public class CUITest : MonoBehaviour
{

    public Text mpTxtString = null;
    public CStageInfoList mStageInfoBundle = null;

    private void Start()
    {
        mStageInfoBundle = new CStageInfoList();
    }


    public void OnClickBtnFromJson()
    {
        string tJson = @"
            {
                ""mName"" : ""My"",
                ""mStringList"":
                [
                    ""weapon_0"",""weapon_777""
                ],
                ""mLevel"":10,
                ""mExp"":12345
            }
        ";


        CMyTestInfo tInfo = JsonUtility.FromJson<CMyTestInfo>(tJson);
        Debug.Log(tInfo.mName);
        Debug.Log(tInfo.mLevel);
        Debug.Log(tInfo.mExp);

        foreach(var tElement in tInfo.mStringList)
        {
            Debug.Log(tElement);
        }
    }
    public void OnClickBtnToJson()
    {
        CMyTestInfo tInfo = new CMyTestInfo();
        tInfo.mName = "알베르토";
        tInfo.mLevel = 999;
        tInfo.mExp = 12345;
        tInfo.mStringList = new List<string>();
        tInfo.mStringList.Add("weapon_777");
        tInfo.mStringList.Add("weapon_888");

        string tJson = "";
        tJson = JsonUtility.ToJson(tInfo);

        Debug.Log("<color='red'>" + tJson + "</color>");
    }
    public void OnClickBtnOverwriteFromJson()
    {
        string tJson = @"
            {
                ""mName"" : ""데이터"",
                ""mStringList"":
                [
                    ""weapon_0"",""weapon_777""
                ],
                ""mLevel"":10,
                ""mExp"":12345
            }
        ";


        CMyTestInfo tInfo = JsonUtility.FromJson<CMyTestInfo>(tJson);

        Debug.Log(tInfo.mName);
        Debug.Log(tInfo.mLevel);
        Debug.Log(tInfo.mExp);
        foreach (var tElement in tInfo.mStringList)
        {
            Debug.Log(tElement);
        }
        Debug.Log("======================");


        string tJson_0 = @"
            {
                ""mName"" : ""알베르토"",
                ""mLevel"":789,
                ""mExp"":564363,
                ""mStringList"":
                [
                    ""weapon_999"",""weapon_123""
                ]
            }
        ";

        JsonUtility.FromJsonOverwrite(tJson_0, tInfo);

        Debug.Log(tInfo.mName);
        Debug.Log(tInfo.mLevel);
        Debug.Log(tInfo.mExp);
        foreach (var tElement in tInfo.mStringList)
        {
            Debug.Log(tElement);
        }
    }
    public void OnClickBtnLoadFromJsonFile()
    {
        string tJsonStageInfoList = LoadResourceTextFile("data/stage_info_json");

        CStageInfoList tInfoList = JsonUtility.FromJson<CStageInfoList>(tJsonStageInfoList);

        Debug.Log("stage_info count : " + tInfoList.stage_info.Count.ToString());


        foreach(var tElement in tInfoList.stage_info)
        {
            Debug.Log("stage_info.id : " + tElement.id);
            Debug.Log("stage_info.total_enemy_count : " + tElement.total_enemy_count);

            foreach(var tElement_0 in tElement.unit_info)
            {
                Debug.Log("unit_info.x : " + tElement_0.x);
                Debug.Log("unit_info.y : " + tElement_0.y);
            }
        }
        mpTxtString.text = tJsonStageInfoList;

    }
    public static string LoadResourceTextFile(string tFileName)
    {
        TextAsset tTextAsset = null;
        tTextAsset = Resources.Load<TextAsset>(tFileName);

        if(null == tTextAsset)
        {
            return "";
        }

        return tTextAsset.text;
    }



    public void OnClickBtnLoadFromXmlFile()
    {
        LoadFromXmlFile("data/stage_info_xml");
    }
    protected bool LoadFromXmlFile(string tFileName)
    {
        TextAsset tTextAsset = null;
        tTextAsset = Resources.Load<TextAsset>(tFileName) as TextAsset;

        if(null == tTextAsset)
        {
            return false; 
        }

        mpTxtString.text = tTextAsset.text;


        XmlDocument tDoc = new XmlDocument();
        tDoc.LoadXml(tTextAsset.text);


        CStageInfo tStageInfo = null;
        CUnitInfo tUnitInfo = null;

        XmlElement tElementRoot = tDoc["response"];


        mStageInfoBundle.stage_info = new List<CStageInfo>();

        foreach(XmlElement tElementStageInfoList in tElementRoot.ChildNodes)
        {
            foreach(XmlElement tElementStageInfo in tElementStageInfoList.ChildNodes)
            {
                tStageInfo = null;
                tStageInfo = new CStageInfo();


                tStageInfo.id = Convert.ToInt32(tElementStageInfo.ChildNodes[0].InnerText);
                tStageInfo.total_enemy_count = Convert.ToInt32(tElementStageInfo.ChildNodes[1].InnerText);


                if(tElementStageInfo.ChildNodes[2].ChildNodes.Count>0)
                {
                    tStageInfo.unit_info = new List<CUnitInfo>();

                    foreach(XmlElement tElementUnitInfo in tElementStageInfo.ChildNodes[2])
                    {
                        tUnitInfo = null;
                        tUnitInfo = new CUnitInfo();

                        tUnitInfo.x = Convert.ToInt32(tElementUnitInfo.ChildNodes[0].InnerText);
                        tUnitInfo.y = Convert.ToInt32(tElementUnitInfo.ChildNodes[1].InnerText);

                        tStageInfo.unit_info.Add(tUnitInfo);
                    }
                }

                mStageInfoBundle.stage_info.Add(tStageInfo);
            }
        }



        return false;
    }
}
