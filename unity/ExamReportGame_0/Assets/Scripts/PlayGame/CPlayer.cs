using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CPlayer : CUnit
{
    public enum State
    {
        Idle = 0,
        Move = 1,
        NextRoom = 2,
    }

    public float mMoveSpeed = 5.0f;
    private BoxCollider2D mCollider = null;

    private float mMapWidth = 1.6f;
    private float mMapHeight = 0.8f;

    public float mFireDelay = 0.35f;
    private float mFireTime = 0.0f;

    public Transform mFireTransform = null;

    private Animator mAnimator = null;
    private SpriteRenderer mSpriteBody = null;

    private State mState = State.Idle;



    // Use this for initialization
    void Start()
    {
        this.HP.Value = 1000;
        this.mATK = 1;

        mCollider = GetComponent<BoxCollider2D>();
        mMapWidth -= mCollider.size.x / 2;

        mAnimator = GetComponentInChildren<Animator>();
        mSpriteBody = GetComponentInChildren<SpriteRenderer>();
    }

    // Update is called once per frame
    void Update()
    {
        
        switch(mState)
        {
            case State.Idle:
            case State.Move:
                DoMove();
                break;
            case State.NextRoom:
                break;
        }

    }

  

    public void SetState(State tState)
    {
        mState = tState;
    }

    private void DoMove()
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


        Vector2 pos = transform.localPosition;
        pos.x = Mathf.Clamp(pos.x + (tHorizontal * mMoveSpeed * Time.deltaTime), -mMapWidth, mMapWidth);
        pos.y = Mathf.Clamp(pos.y + (tVertical * mMoveSpeed * Time.deltaTime), -mMapHeight, mMapHeight - mCollider.size.y / 2);
        transform.localPosition = pos;

        if (mFireTime >= mFireDelay)
        {
            Vector2 tFireDirection = Vector2.zero;
            tFireDirection.x = Input.GetAxisRaw("FireHorizontal");
            tFireDirection.y = Input.GetAxisRaw("FireVertical");
            if (tFireDirection.x != 0)
            {
                CMissile tMissile = Instantiate<CMissile>(CGameDataMgr.GetInst().PFMissile, mFireTransform.position, Quaternion.identity);
                tMissile.Direction = new Vector2(tFireDirection.x, 0);
                tMissile.SetTargetTag("tagEnemy");
                tMissile.SetATK(mATK);
                mFireTime = 0;
            }
            else if (tFireDirection.y != 0)
            {
                CMissile tMissile = Instantiate<CMissile>(CGameDataMgr.GetInst().PFMissile, mFireTransform.position, Quaternion.identity);
                tMissile.Direction = new Vector2(0, tFireDirection.y);
                tMissile.SetTargetTag("tagEnemy");
                tMissile.SetATK(mATK);
                mFireTime = 0;
            }
        }
        else
        {
            mFireTime += Time.deltaTime;
        }
    }

    public override void Hit(int tDamage)
    {
        HP.Value -= tDamage;
        if(HP.Value <= 0)
        {
            mScene.OnGameOver();
            Destroy(this.gameObject);
        }
    }

}
