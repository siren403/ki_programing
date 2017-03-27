using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CPlayer : MonoBehaviour
{
    public float mMoveSpeed = 5.0f;
    private BoxCollider2D mCollider = null;

    private float mMapWidth = 1.6f;
    private float mMapHeight = 0.8f;

    public float mFireDelay = 0.35f;
    private float mFireTime = 0.0f;

    public Transform mFireTransform = null;

    private Animator mAnimator = null;
    private SpriteRenderer mSpriteBody = null;

    // Use this for initialization
    void Start()
    {
        mCollider = GetComponent<BoxCollider2D>();
        mMapWidth -= mCollider.size.x / 2;

        mAnimator = GetComponentInChildren<Animator>();
        mSpriteBody = GetComponentInChildren<SpriteRenderer>();
    }

    // Update is called once per frame
    void Update()
    {
        float tHorizontal = Input.GetAxis("Horizontal");
        float tVertical = Input.GetAxis("Vertical");

        mAnimator.SetInteger("aniMoveHorizontal", Mathf.CeilToInt(tHorizontal));
        if (mAnimator.GetInteger("aniMoveHorizontal") == -1)
        {
            mSpriteBody.flipX = true;
        }
        else
        {
            mSpriteBody.flipX = false;
        }
        mAnimator.SetInteger("aniMoveVertical", Mathf.CeilToInt(tVertical));
        

        Vector2 pos = transform.position;
        pos.x = Mathf.Clamp(pos.x + (tHorizontal * mMoveSpeed * Time.deltaTime), -mMapWidth, mMapWidth);
        pos.y = Mathf.Clamp(pos.y + (tVertical * mMoveSpeed * Time.deltaTime), -mMapHeight, mMapHeight - mCollider.size.y / 2);
        transform.position = pos;

        if (mFireTime >= mFireDelay)
        {
            Vector2 tFireDirection = Vector2.zero;
            tFireDirection.x = Input.GetAxisRaw("FireHorizontal");
            tFireDirection.y = Input.GetAxisRaw("FireVertical");
            if (tFireDirection.x != 0)
            {
                CMissile tMissile = Instantiate<CMissile>(CGameDataMgr.GetInst().PFMissile, mFireTransform.position, Quaternion.identity);
                tMissile.Direction = new Vector2(tFireDirection.x, 0);
                mFireTime = 0;
            }
            else if (tFireDirection.y != 0)
            {
                CMissile tMissile = Instantiate<CMissile>(CGameDataMgr.GetInst().PFMissile, mFireTransform.position, Quaternion.identity);
                tMissile.Direction = new Vector2(0, tFireDirection.y);
                mFireTime = 0;
            }
        }
        else
        {
            mFireTime += Time.deltaTime;
        }


    }


}
