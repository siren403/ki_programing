using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Text;


struct MyPosition
{
    public int x;
    public int y;
}


public class HeroGame : MonoBehaviour
{

    enum TileState
    {
        None = 0,
        Player = 1,
        Path = 2
    }
    enum CompareResult
    {
        Draw = 0,
        Win = 1,
        Lose = 2,
    }



    private int[,] mMapArray = new int[10, 10];
    private MyPosition[] mPathArray = {
        new MyPosition(){ x = 0,y = 0 },

        new MyPosition(){ x = 0,y = 1 },
        new MyPosition(){ x = 1,y = 1 },
        new MyPosition(){ x = 2,y = 1 },
        new MyPosition(){ x = 3,y = 1 },
        new MyPosition(){ x = 4,y = 1 },
        new MyPosition(){ x = 5,y = 1 },
        new MyPosition(){ x = 6,y = 1 },
        new MyPosition(){ x = 7,y = 1 },
        new MyPosition(){ x = 8,y = 1 },
        new MyPosition(){ x = 9,y = 1 },

        new MyPosition(){ x = 9,y = 2 },

        new MyPosition(){ x = 9,y = 3 },
        new MyPosition(){ x = 8,y = 3 },
        new MyPosition(){ x = 7,y = 3 },
        new MyPosition(){ x = 6,y = 3 },
        new MyPosition(){ x = 5,y = 3 },
        new MyPosition(){ x = 4,y = 3 },
        new MyPosition(){ x = 3,y = 3 },
        new MyPosition(){ x = 2,y = 3 },
        new MyPosition(){ x = 1,y = 3 },
        new MyPosition(){ x = 0,y = 3 },

        new MyPosition(){ x = 0,y = 4 },

        new MyPosition(){ x = 0,y = 5 },
        new MyPosition(){ x = 1,y = 5 },
        new MyPosition(){ x = 2,y = 5 },
        new MyPosition(){ x = 3,y = 5 },
        new MyPosition(){ x = 4,y = 5 },
        new MyPosition(){ x = 5,y = 5 },
        new MyPosition(){ x = 6,y = 5 },
        new MyPosition(){ x = 7,y = 5 },

        new MyPosition(){ x = 7,y = 6 },
        new MyPosition(){ x = 7,y = 7 },
        new MyPosition(){ x = 7,y = 8 },
        new MyPosition(){ x = 7,y = 9 },

        new MyPosition(){ x = 8,y = 9 },
        new MyPosition(){ x = 9,y = 9 },
    };

    StringBuilder mMapPrintBuilder = new StringBuilder();

    bool mIsEncount
    {
        get { return Random.Range(0.0f, 1.0f) > 0.5f ? true : false; }
    }

    int mPlayerPosition = 0;
    bool mIsPlaying = true;
    public int mPlayerLife;

    // Use this for initialization
    void Start()
    {
        
        MapClear();
        var pos = mPathArray[mPlayerPosition];
        mMapArray[pos.y, pos.x] = (int)TileState.Player;


        PrintMap();
        
    }


    public void OnClickBtn()
    {
        if(mIsPlaying == false)
        {
            return;
        }

        MapClear();


        int moveCount = DoDice();
        mPlayerPosition += moveCount;
        if(mPlayerPosition >= mPathArray.Length)
        {
            mPlayerPosition = mPathArray.Length - 1;
        }
        MyPosition pos = mPathArray[mPlayerPosition];
        mMapArray[pos.y, pos.x] = (int)TileState.Player;
        PrintMap();

        bool isLastBoss = mPlayerPosition == mPathArray.Length - 1;

        if (isLastBoss == false)//일반 타일
        {
            if(mIsEncount)
            {
                Debug.Log("슬라임 교전");

                while (mPlayerLife > 0)
                {
                    int diceCount = DoDice();
                    Debug.LogFormat("주사위 결과 : {0}", diceCount.ToString());
                    if (diceCount >= 4)//승리
                    {
                        Debug.Log("==== 플레이어 승리 ====");
                        break;
                    }
                    else//패배
                    {
                        mPlayerLife--;
                        Debug.LogFormat("==== 플레이어 패배 생명 : {0} ====", mPlayerLife);
                        if(mPlayerLife == 0)
                        {
                            Debug.Log("GameOver");
                            mIsPlaying = false;
                        }
                    }
                }
            }
        }
        else//마지막 타일
        {
            while (mPlayerLife > 0)
            {
                int playerCard = DrawCard();
                int enemyCard = DrawCard();

                CompareResult result = CompareCard(playerCard, enemyCard);

                Debug.LogFormat("플레이어 : {0}, 보스 : {1}", GetCardString(playerCard), GetCardString(enemyCard));

                switch(result)
                {
                    case CompareResult.Draw:
                        Debug.Log("비김...");
                        break;
                    case CompareResult.Win:
                        Debug.Log("승리!! \n 게임 클리어");
                        mIsPlaying = false;
                        return;
                    case CompareResult.Lose:
                        mPlayerLife--;
                        Debug.LogFormat("패배!! 생명 : {0}", mPlayerLife);
                        if (mPlayerLife == 0)
                        {
                            Debug.Log("GameOver");
                            mIsPlaying = false;
                        }
                        break;
                }
            }
        }
    }

    private void MapClear()
    {
        for (int y = 0; y < mMapArray.GetLength(0); y++)
        {
            for (int x = 0; x < mMapArray.GetLength(1); x++)
            {
                mMapArray[y, x] = 0;
            }
        }

        for (int i = 0; i < mPathArray.Length; i++)
        {
            mMapArray[mPathArray[i].y, mPathArray[i].x] = (int)TileState.Path;
        }

        
    }

    private void PrintMap()
    {
        mMapPrintBuilder.Remove(0, mMapPrintBuilder.Length);
        for (int y = mMapArray.GetLength(0) - 1; y >= 0; y--)
        {
            for (int x = 0; x < mMapArray.GetLength(1); x++)
            {
                mMapPrintBuilder.AppendFormat("{0}, ", GetTileIcon((TileState)mMapArray[y, x]));
            }
            mMapPrintBuilder.AppendLine();
        }
        Debug.Log(mMapPrintBuilder.ToString());
    }

    private char GetTileIcon(TileState state)
    {
        char result = '0';
        switch (state)
        {
            case TileState.Path:
                result = '8';
                break;
            case TileState.Player:
                result = '*';
                break;
        }
        return result;
    }

    private int DoDice()
    {
        return Random.Range(1, 7);
    }

    private int DrawCard()
    {
        return Random.Range(0, 3);
    }
    private CompareResult CompareCard(int player,int enemy)
    {
        CompareResult result = CompareResult.Draw;

        if(player == enemy)
        {
            return result;
        }

        switch(player)
        {
            case 0://가위
                switch(enemy)
                {
                    case 1:
                        result = CompareResult.Lose;
                        break;
                    case 2:
                        result = CompareResult.Win;
                        break;
                }
                break;
            case 1://바위
                switch (enemy)
                {
                    case 0:
                        result = CompareResult.Win;
                        break;
                    case 2:
                        result = CompareResult.Lose;
                        break;
                }
                break;
            case 2://보
                switch (enemy)
                {
                    case 0:
                        result = CompareResult.Lose;
                        break;
                    case 1:
                        result = CompareResult.Win;
                        break;
                }
                break;
        }

        return result;
    }

    private string GetCardString(int card)
    {
        string str = "";
        switch(card)
        {
            case 0:
                str = "가위";
                break;
            case 1:
                str = "바위";
                break;
            case 2:
                str = "보";
                break;
        }
        return str;
    }
}
