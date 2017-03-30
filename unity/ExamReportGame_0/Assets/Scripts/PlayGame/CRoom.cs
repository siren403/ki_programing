using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class CRoom : MonoBehaviour
{
    [System.Serializable]
    public class SpawnData
    {
        public CUnit PFEnemy = null;
        public Transform mSpawnPosition = null;
    }



    [SerializeField]
    private List<CDoor> mDoorList = null;

    private CScenePlayGame mScene = null;

    public List<SpawnData> mSpawnEnemyList = null;

    private int mEnemyCount = 0;

    private bool mIsClear = false;

    private void Awake()
    {
        mDoorList = new List<CDoor>(this.GetComponentsInChildren<CDoor>());
        foreach(var door in mDoorList)
        {
            door.gameObject.SetActive(false);
        }
        mEnemyCount = mSpawnEnemyList != null ? mSpawnEnemyList.Count : 0;
    }

    public void SetScene(CScenePlayGame tScene)
    {
        mScene = tScene;
        foreach(var door in mDoorList)
        {
            door.SetScene(tScene);
        }
    }

    public void OpenDoor()
    {
        foreach(var door in mDoorList)
        {
            door.gameObject.SetActive(true);
        }
    }
    public void CloseDoor()
    {
        if (mIsClear == false)
        {
            foreach (var door in mDoorList)
            {
                door.gameObject.SetActive(false);
            }
        }
    }

    public void OnPlayerEnter()
    {
        if(mIsClear == false && mSpawnEnemyList != null)
        {
            foreach(var data in mSpawnEnemyList)
            {
                var unit = Instantiate(data.PFEnemy, data.mSpawnPosition.position, Quaternion.identity);
                unit.transform.SetParent(this.transform);
                unit.SetScene(mScene);
            }

        }
    }

    public void DeadEnemy()
    {
        mEnemyCount--;
        if(mEnemyCount <= 0)
        {
            mIsClear = true;
            OpenDoor();
        }
    }
}
