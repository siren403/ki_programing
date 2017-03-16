using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CAlberto : MonoBehaviour
{
    public enum STATE
    {
        IDLE = 0,
        ATTACK = 1,
        DEAD = 2,
    }


    STATE mState = STATE.IDLE;


    private CScenePlayGame mpScene = null;
    protected Animator mpAnimator = null;
    protected SpriteRenderer mpSprite = null;


    public void CreateMy()
    {
        mpAnimator = GetComponentInChildren<Animator>();
        mpSprite = GetComponentInChildren<SpriteRenderer>();
    }
    public void SetScene(CScenePlayGame tpScene)
    {
        mpScene = tpScene;
    }

    public void DoAttack(float dir)
    {
        SetState(STATE.ATTACK);
        DoAni();
        this.transform.localScale = new Vector3(dir, 1, 1);
    }

    public void OnTriggerEnter2D(Collider2D collision)
    {
        if (mState != STATE.DEAD)
        {
            if (collision.CompareTag("tagEnemy"))
            {
                SetState(STATE.DEAD);
                DoAni();
                mpScene.ShowGameOver();
            }
        }
    }

    public void SetState(STATE tState)
    {
        mState = tState;
    }
    public STATE GetState()
    {
        return mState;
    }

    public void DoAni()
    {
        switch (mState)
        {
            case STATE.IDLE:
                mpAnimator.SetTrigger("mTrigAniIdle");
                break;
            case STATE.ATTACK:
                mpAnimator.SetTrigger("mTrigAniAttack");
                break;
            case STATE.DEAD:
                mpAnimator.SetTrigger("mTrigAniDead");
                break;
        }

    }
}
