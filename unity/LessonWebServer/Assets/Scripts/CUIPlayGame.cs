using System.Collections;
using System.Collections.Generic;
using UnityEngine;


using UnityEngine.UI;

using System.Xml;

public struct CUserInfo
{
    public string id;
    public int coin;

    public override string ToString()
    {
        return string.Format("id : {0}, coin : {1}",
             id, coin);
    }
}
public struct CPVPResult
{
    public bool isLeftValid;
    public int leftUserCoin;
    public bool isRightValid;
    public int rightUserCoin;
    public int result;

    public override string ToString()
    {
        return string.Format("[LeftUser] isValid : {0}, Coin : {1}\n[RightUser] isValid : {2}, Coin : {3}\n[PVP Result] {4}",
            isLeftValid, leftUserCoin, isRightValid, rightUserCoin,
            result == -1 ? "Left User Win" : result == 1 ? "Right User Win" : "Draw");
    }
}

public class CUIPlayGame : MonoBehaviour
{

    //ui
    public Text mTxtResult = null;
    public InputField mInputFieldLeftUser = null;
    public InputField mInputFieldRightUser = null;
    public InputField mInputFieldTargetUser = null;

    //data
    private CClient mClient = null;
    private string mResultString = "";

    private int mGoldCoin = 0;


    // Use this for initialization
    void Start()
    {
        //네트워크 초기화
        mClient = new CClient();
        mClient.Create("test", "127.0.0.1/test"); //아이디, 로컬주소(포트포함)

        //UI초기화
        BuildUI();
    }


    public void BuildUI()
    {
        mResultString = "GoldCoin: " + mGoldCoin.ToString();

        mTxtResult.text = mResultString;
    }
    public void BuildUI(string tMsg = "")
    {
        if ("" == tMsg)
        {
            mResultString = "GoldCoin: " + mClient.mCoin.ToString();
        }
        else
        {

            mResultString = tMsg;
        }


        mTxtResult.text = mResultString;
    }

    //버튼 핸들러: Request코드 
    public void OnClickBtnGetCoin()
    {
        Debug.Log("OnClickBtnGetCoin");

        mGoldCoin = mGoldCoin + 5;

        BuildUI();
    }



    public void OnClickBtnLoadPlayGameInfo()
    {
        if (string.IsNullOrEmpty(mInputFieldTargetUser.text) == false)
        {
            this.mClient.mTestPlayerID = mInputFieldTargetUser.text.Trim();
            this.mClient.SendReq("load_playgameinfo.php", this, OnAckLoadFromServer);
        }
        else
        {
            Debug.Log("Target User Id is Empty");
        }
    }
    public void OnClickBtnSavePlayGameInfo()
    {
        this.mClient.mCoin = mGoldCoin;
        this.mClient.SendReq("save_playgameinfo.php", this, OnAckSaveToServer);
    }
    public void OnClickBtnRefreshAllPlayer()
    {
        this.mClient.SendReq("refresh_allplayer_gameinfo.php", this, OnAckRefreshAllPlayerGameInfo);
    }
    public void OnAckRefreshAllPlayerGameInfo(XmlDocument tXML)
    {
        Debug.Log("=======OnAckRefreshAllPlayerGameInfo Success!!!!!");
        List<CUserInfo> userinfoList = new List<CUserInfo>();
        CUserInfo userinfoData = new CUserInfo();

        System.Text.StringBuilder tStringBuilder = new System.Text.StringBuilder();
        XmlNodeList responseData = tXML["response"].ChildNodes;
        for (int i = 0; i < responseData.Count; i++)
        {
            userinfoData.id = responseData.Item(i)["id"].InnerText;
            userinfoData.coin = System.Convert.ToInt32(responseData.Item(i)["coin"].InnerText);
            userinfoList.Add(userinfoData);

            tStringBuilder.AppendLine(userinfoData.ToString());
        }

        BuildUI(tStringBuilder.ToString());
    }
    public void OnClickBtnPVP()
    {
        this.mClient.SendReqPVP("pvp_playgameinfo.php"
            ,mInputFieldLeftUser.text.Trim()
            ,mInputFieldRightUser.text.Trim()
            , this
            , (data)=> 
            {
                CPVPResult pvpResult = new CPVPResult();

                var leftUser = data["response"]["left_user"];
                pvpResult.isLeftValid = System.Convert.ToBoolean(leftUser["is_valid"].InnerText);
                if (pvpResult.isLeftValid)
                {
                    pvpResult.leftUserCoin = System.Convert.ToInt32(leftUser["coin"].InnerText);
                }

                var rightUser = data["response"]["right_user"];
                pvpResult.isRightValid = System.Convert.ToBoolean(rightUser["is_valid"].InnerText);
                if (pvpResult.isRightValid)
                {
                    pvpResult.rightUserCoin = System.Convert.ToInt32(rightUser["coin"].InnerText);
                }
                pvpResult.result = System.Convert.ToInt32(data["response"]["pvp_result"].InnerText);


                System.Text.StringBuilder tStringBuiler = new System.Text.StringBuilder();

                if(pvpResult.isLeftValid && pvpResult.isRightValid)
                {
                    tStringBuiler.AppendLine("[PVP 결과]\n");
                    tStringBuiler.AppendFormat("Left Coin : {0}\n vs \nRight Coin : {1}\n\n", pvpResult.leftUserCoin, pvpResult.rightUserCoin);
                    tStringBuiler.Append(pvpResult.result == -1 ? "Left Win!!" : pvpResult.result == 1 ? "Right Win!!" : "Draw");
                }
                else
                {
                    if (pvpResult.isLeftValid == false)
                        tStringBuiler.AppendLine("Left User Id가 유효하지 않습니다.");

                    tStringBuiler.AppendLine();

                    if (pvpResult.isRightValid == false)
                        tStringBuiler.AppendLine("Right User Id가 유효하지 않습니다.");
                }

                BuildUI(tStringBuiler.ToString());

            });
    }


    //게임서버에 로드 요청한 것에 대한 응답
    public void OnAckLoadFromServer(XmlDocument tXML)
    {
        Debug.Log("=======OnAckLoadFromServer Success!!!!!");
        mGoldCoin = System.Convert.ToInt32(tXML["response"]["user"]["coin"].InnerText);
        BuildUI();
    }

    //게임서버에 세이브 요청한 것에 대한 응답
    public void OnAckSaveToServer(XmlDocument tXML)
    {
        Debug.Log("=======OnAckSaveToServer Success!!!!!");

        BuildUI();
    }




}
