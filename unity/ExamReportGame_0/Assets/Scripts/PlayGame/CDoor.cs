using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CDoor : MonoBehaviour
{
    private CRoom mParentRoom = null;
    public CRoom ParentRoom
    {
        get
        {
            if(mParentRoom == null)
            {
                mParentRoom = GetComponentInParent<CRoom>();
            }
            return mParentRoom;
        }
    }
    public CDoor mNextDoor = null;
    private CScenePlayGame mScene = null;


    public void SetScene(CScenePlayGame tScene)
    {
        mScene = tScene;
    }

    private void OnTriggerEnter2D(Collider2D tCollision)
    {
        if(tCollision.CompareTag("tagPlayer"))
        {
            StartCoroutine(DoMoveRoom(tCollision.GetComponent<CPlayer>()));
        }
    }

    IEnumerator DoMoveRoom(CPlayer tPlayer)
    {
        tPlayer.SetState(CPlayer.State.NextRoom);
        tPlayer.transform.SetParent(mNextDoor.transform.parent);
        Vector3 tDoorPos = mNextDoor.transform.localPosition;

        Vector3 tDoorDir = (mNextDoor.transform.position - this.transform.position).normalized;
        tDoorPos += tDoorDir * 0.2f;

        tPlayer.transform.localPosition = tDoorPos;

        yield return StartCoroutine(DoMoveCamera());

        //mNextDoor.ParentRoom.CloseDoor();
        if (mNextDoor.ParentRoom != null)
            mNextDoor.ParentRoom.OnPlayerEnter();
        else
            Debug.Log("room is null");


        tPlayer.SetState(CPlayer.State.Idle);
    }

    IEnumerator DoMoveCamera()
    {
        Transform tParent = mNextDoor.transform.parent;
        Transform tCamera = tParent.GetComponentInParent<CMap>().Scene.mMainCamera.transform;


        float tTime = 0;
        float tDuration = 0.3f;
        Vector2 tStartPos = tCamera.position;

        while (tTime < tDuration)
        {
            
            Vector2 pos = tCamera.position;
            pos.x = CEasingFunc.EaseExpoInOut(tTime, tStartPos.x, tParent.position.x - tStartPos.x, tDuration);
            pos.y = CEasingFunc.EaseExpoInOut(tTime, tStartPos.y, tParent.position.y - tStartPos.y, tDuration);
            tCamera.position = pos;

            tTime += Time.deltaTime;
            yield return null;
        }
        tCamera.position = tParent.position;
    }

    private void OnDrawGizmos()
    {
        if (mNextDoor != null)
        {
            Gizmos.DrawLine(this.transform.position, mNextDoor.transform.position);
        }
    }
}
