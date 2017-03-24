using System.Collections;
using System.Collections.Generic;
using System.Xml;
using UnityEngine;
using UnityEngine.SceneManagement;

public class CMyGameDataMgr
{
    private static CMyGameDataMgr mInstance = null;

    //Prefabs
    public CAlberto PFAlberto = null;
    public CEnemy_0 PFEnemy_0 = null;
    public CEnemy_1 PFEnemy_1 = null;
    public CEnemy_2 PFEnemy_2 = null;
    public CBullet PFBullet = null;

    //Stage
    private List<string> mStageList = null;
    private int mCurrentStageIndex = 0;

    //Config
    public int mLangType = 0;
    public List<string> mLangTextList = null;


    //Dialogue
    public CDialogueInfoList mDialogueList = null;

    public static CMyGameDataMgr GetInst()
    {
        if(mInstance == null)
        {
            mInstance = new CMyGameDataMgr();
        }
        return mInstance;
    }
    private CMyGameDataMgr()
    {
        
    }

    public void Create()
    {
        PFAlberto = Resources.Load<CAlberto>("Prefabs/PFAlberto");
        PFEnemy_0 = Resources.Load<CEnemy_0>("Prefabs/PFEnemy_0");
        PFEnemy_1 = Resources.Load<CEnemy_1>("Prefabs/PFEnemy_1");
        PFEnemy_2 = Resources.Load<CEnemy_2>("Prefabs/PFEnemy_2");
        PFBullet = Resources.Load<CBullet>("Prefabs/PFBullet");

        mCurrentStageIndex = 0;

        mStageList = new List<string>();
        mStageList.Add("CScenePlayGameGrid_0");
        mStageList.Add("CScenePlayGameGrid_1");
        mStageList.Add("CScenePlayGameGrid_2");

        CreateWithLanguageType();

        LoadDialogueData();
    }

    private void CreateWithLanguageType()
    {
        mLangTextList = new List<string>();

        if(SystemLanguage.Korean == Application.systemLanguage)
        {
            BuildLangType(0);
        }
        else if(SystemLanguage.English == Application.systemLanguage)
        {
            BuildLangType(1);
        }
    }
    public void BuildLangType(int tLangType)
    {
        mLangType = tLangType;

        int ti = 0;
        int tCount = mLangTextList.Count;
        for(ti = 0;ti<tCount;ti++)
        {
            mLangTextList[ti] = "";
        }
        mLangTextList.Clear();

        switch(mLangType)
        {
            case 0:
                LoadLangText("Lang/ui_ko");
                break;
            case 1:
                LoadLangText("Lang/ui_en");
                break;
        }
    }
    protected bool LoadLangText(string tFileName)
    {
        TextAsset tTextAsset = null;
        tTextAsset = Resources.Load<TextAsset>(tFileName) as TextAsset;

        if(null == tTextAsset)
        {
            return false;
        }
        else
        {
            Debug.Log(tTextAsset.text);
        }

        XmlDocument Doc = new XmlDocument();
        Doc.LoadXml(tTextAsset.text);

        XmlElement tElementRoot = Doc["ui_lang"];

        foreach(XmlElement tElementScene in tElementRoot.ChildNodes)
        {
            foreach(XmlElement tElementText in tElementScene.ChildNodes)
            {
                mLangTextList.Add(tElementText.InnerText);
            }
        }

        foreach(string langText in mLangTextList)
        {
            Debug.Log(langText);
        }

        return true;
    }

    public void DoNextStage()
    {
        if (mCurrentStageIndex >= mStageList.Count)
        {
            mCurrentStageIndex = 0;
            SceneManager.LoadScene("CSceneTitle");
        }
        else
        {
            SceneManager.LoadScene("CScenePlayGame");
            SceneManager.LoadScene(mStageList[mCurrentStageIndex], LoadSceneMode.Additive);
            SceneManager.LoadScene("CScenePlayGameUI", LoadSceneMode.Additive);

            mCurrentStageIndex++;
        }
      
    }

    private void LoadDialogueData()
    {
        TextAsset tTextAsset = Resources.Load<TextAsset>("Dialogue/dialogue_list_json");
        mDialogueList = JsonUtility.FromJson<CDialogueInfoList>(tTextAsset.text);
    }
}
