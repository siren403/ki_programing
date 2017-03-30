using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CMap : MonoBehaviour
{
    public List<CRoom> mRoomList = null;

    private CScenePlayGame mScene = null;
    public CScenePlayGame Scene
    {
        get
        {
            return mScene;
        }
    }

    private void Awake()
    {
        mRoomList = new List<CRoom>(this.GetComponentsInChildren<CRoom>());
        
    }

    public void SetScene(CScenePlayGame tScene)
    {
        mScene = tScene;
        foreach(var room in mRoomList)
        {
            room.SetScene(mScene);
        }
    }
    
}
