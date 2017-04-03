using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UniRx;

public class CScenePlayGame : MonoBehaviour
{
    public CPlayer mPlayer = null;
    public CMap mCurrentMap = null;

    public Camera mMainCamera = null;
    private CUIPlayGame mUIPlayGame = null;

    private IntReactiveProperty mCurrentScore = new IntReactiveProperty();
    private IntReactiveProperty mCurrentGold = new IntReactiveProperty();
    public ReadOnlyReactiveProperty<int> ReadScore
    {
        get
        {
            return mCurrentScore.ToReadOnlyReactiveProperty();
        }
    }
    public ReadOnlyReactiveProperty<int> ReadGold
    {
        get
        {
            return mCurrentGold.ToReadOnlyReactiveProperty();
        }
    }


    // Use this for initialization
    void Start()
    {
        CGameDataMgr.GetInst().Create();
        mCurrentMap = FindObjectOfType<CMap>();
        mCurrentMap.SetScene(this);

        mPlayer = Instantiate(CGameDataMgr.GetInst().PFPlayer, Vector2.zero, Quaternion.identity);
        mPlayer.transform.SetParent(mCurrentMap.mRoomList[0].transform);
        mPlayer.transform.localPosition = Vector3.zero;
        mPlayer.SetScene(this);

        mUIPlayGame = FindObjectOfType<CUIPlayGame>();
        mUIPlayGame.SetScene(this);

        mCurrentMap.mRoomList[0].OnPlayerEnter();
    }
    

    // Update is called once per frame
    void Update()
    {

    }

    private void LateUpdate()
    {

    }
    public void AddScore(int tScore)
    {
        mCurrentScore.Value += tScore;
    }
    public void AddGold(int tGold)
    {
        mCurrentGold.Value += tGold;
    }

    public void OnGameOver()
    {
        SceneManager.LoadScene("CSceneTitle");
    }
    public void OnGameClear()
    {
        StartCoroutine(SeqGameClear());
    }
    private IEnumerator SeqGameClear()
    {
        CGameDataMgr.GetInst().Gold.Value += mCurrentGold.Value;

        int prevScore = CGameDataMgr.GetInst().HighScore.Value;

        if (prevScore < mCurrentScore.Value)
        {
            CGameDataMgr.GetInst().HighScore.Value = mCurrentScore.Value;
        }

        yield return new WaitForSeconds(2.3f);

        SceneManager.LoadScene("CSceneTitle");
    }
}
