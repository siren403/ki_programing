using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FollowCam : MonoBehaviour
{

    public Transform mTargetTransform = null;
    public float mDistance = 10.0f;
    public float mHeight = 3.0f;
    public float mDampTrace = 20.0f;



    // Use this for initialization
    void Start()
    {

    }

    // Update is called once per frame
    void LateUpdate()
    {
        transform.position = Vector3.Lerp(transform.position,
            mTargetTransform.position - (mTargetTransform.forward * mDistance) + (Vector3.up * mHeight), Time.deltaTime * mDampTrace);
        transform.LookAt(mTargetTransform);
    }
}
