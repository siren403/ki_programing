using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class Anim
{
    public AnimationClip mClipIdle = null;
    public AnimationClip mClipRunForward = null;
    public AnimationClip mClipRunBackward = null;
    public AnimationClip mClipRunRight = null;
    public AnimationClip mClipRunLeft = null;

}

public class PlayerCtrl : MonoBehaviour
{

    private float h = 0.0f;
    private float v = 0.0f;

    public float mMoveSpeed = 10.0f;
    public float mRotateSpeed = 100.0f;

    public Anim mAnim;

    public Animation mAnimation;
    public int HP = 100;

    // Use this for initialization
    void Start()
    {
        mAnimation = GetComponentInChildren<Animation>();

        mAnimation.clip = mAnim.mClipIdle;
        mAnimation.Play();
            
    }

    // Update is called once per frame
    void Update()
    {
        h = Input.GetAxis("Horizontal");
        v = Input.GetAxis("Vertical");

        Vector3 moveDir = (Vector3.forward * v) + (Vector3.right * h);
        transform.Translate(moveDir * mMoveSpeed * Time.deltaTime, Space.Self);

        transform.Rotate(Vector3.up * Time.deltaTime * mRotateSpeed * Input.GetAxis("Mouse X"));

        if(v >= 0.1f)
        {
            mAnimation.CrossFade(mAnim.mClipRunForward.name, 0.3f);
        }
        else if (v <= -0.1f)
        {
            mAnimation.CrossFade(mAnim.mClipRunBackward.name, 0.3f);
        }
        else if (h >= 0.1f)
        {
            mAnimation.CrossFade(mAnim.mClipRunRight.name, 0.3f);
        }
        else if (h <= -0.1f)
        {
            mAnimation.CrossFade(mAnim.mClipRunLeft.name, 0.3f);
        }
        else
        {
            mAnimation.CrossFade(mAnim.mClipIdle.name, 0.3f);
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if(other.CompareTag("PUNCH"))
        {
            HP -= 10;

            Debug.Log("Player HP = " + HP.ToString());

            if(HP <= 0)
            {
                PlayerDie();
            }
        }
    }

    void PlayerDie()
    {
        Debug.Log("Player Die!!");
    }
}
