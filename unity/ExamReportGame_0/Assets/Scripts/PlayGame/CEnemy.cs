using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CEnemy : CUnit
{
    public delegate IEnumerator EnemyFunc();
    public enum State
    {
        Spawn = 0,
        Idle = 1,
        Move = 2,
        Attack = 3,
        Damage = 4,
        Dead = 5
    }

    private EnemyFunc[] mEnemyFunctions = null;
    protected State mState;
    protected Coroutine mCurrentCoroutine = null;

    protected SpriteRenderer mSpriteRenderer = null;

    protected CPlayer mTargetPlayer = null;

    public int mDeadScore = 100;
    public int mDeadGold = 10;

    // Use this for initialization
    protected virtual void Start()
    {
        mSpriteRenderer = GetComponentInChildren<SpriteRenderer>();

        int tStateCount = System.Enum.GetValues(typeof(CEnemy.State)).Length;
        mEnemyFunctions = new EnemyFunc[tStateCount];
        mEnemyFunctions[(int)State.Spawn] = SpawnStateFunc;
        mEnemyFunctions[(int)State.Idle] = IdleStateFunc;
        mEnemyFunctions[(int)State.Move] = MoveStateFunc;
        mEnemyFunctions[(int)State.Attack] = AttackStateFunc;
        mEnemyFunctions[(int)State.Damage] = DamageStateFunc;
        mEnemyFunctions[(int)State.Dead] = DeadStateFunc;

        CDetector2D tDetector = GetComponentInChildren<CDetector2D>();
        tDetector.AddTriggerEnter(this.OnDetectorEnter);
        tDetector.AddTriggerStay(this.OnDetectorStay);
        tDetector.AddTriggerExit(this.OnDetectorExit);  

        HP.Value = 5;
        mATK = 1;

        SetState(State.Spawn);
    }


    public void SetState(CEnemy.State tState)
    {
        if (mCurrentCoroutine != null)
        {
            StopCoroutine(mCurrentCoroutine);
        }
        mState = tState;
        mCurrentCoroutine = StartCoroutine(mEnemyFunctions[(int)mState]());
    }

    protected virtual IEnumerator SpawnStateFunc()
    {
        yield return new WaitForSeconds(1.0f);
        SetState(State.Idle);
    }
    protected virtual IEnumerator IdleStateFunc()
    {
        while (mState != State.Dead)
        {
            if(mTargetPlayer != null)
            {
                SetState(State.Move);
            }
            yield return null;
        }
    }
    protected virtual IEnumerator MoveStateFunc()
    {
        yield return null;
    }
    protected virtual IEnumerator AttackStateFunc()
    {
        yield return null;
    }
    protected virtual IEnumerator DamageStateFunc()
    {
        mSpriteRenderer.color = Color.white;
        for (int i = 0; i < 5; i++)
        {
            mSpriteRenderer.color = i % 2 == 0 ? Color.black : Color.white;
            yield return null;
        }
        mSpriteRenderer.color = Color.white;
        SetState(State.Idle);
    }
    protected virtual IEnumerator DeadStateFunc()
    {
        mScene.AddScore(mDeadScore);
        mScene.AddGold(mDeadGold);

        float tAlpha = 1;
        Color tColor = mSpriteRenderer.color;

        while (tAlpha > 0)
        {
            tColor.a = tAlpha;
            mSpriteRenderer.color = tColor;
            tAlpha -= 0.1f;
            yield return null;
        }

        CRoom room = GetComponentInParent<CRoom>();
        if (room != null)
        {
            room.DeadEnemy();
        }
        Destroy(this.gameObject);
    }
    protected CMissile CreateMissile(Vector3 dir,Color color)
    {
        CMissile tMissile = Instantiate<CMissile>(CGameDataMgr.GetInst().PFMissile, transform.position, Quaternion.identity);
        tMissile.Direction = dir.normalized;
        tMissile.SetTargetTag("tagPlayer");
        tMissile.SetColor(color);
        tMissile.SetATK(mATK);
        return tMissile;
    }
    public override void Hit(int tDamage)
    {
        if (mState != State.Damage && mState != State.Dead)
        {
            HP.Value = HP.Value - tDamage;
            if (HP.Value <= 0)
            {
                SetState(State.Dead);
            }
            else
            {
                SetState(State.Damage);
            }
        }
    }

    private void OnTriggerEnter2D(Collider2D other)
    {
        if(other.CompareTag("tagPlayer"))
        {
            other.GetComponent<CPlayer>().Hit(mATK);
        }
    }

    #region Detector CallBack
    void OnDetectorEnter(Collider2D other)
    {
        if (other.CompareTag("tagPlayer"))
        {
            mTargetPlayer = other.GetComponent<CPlayer>();
        }
    }
    void OnDetectorStay(Collider2D other)
    {
        if (mTargetPlayer == null)
        {
            if (other.CompareTag("tagPlayer"))
            {
                mTargetPlayer = other.GetComponent<CPlayer>();
            }
        }
    }
    void OnDetectorExit(Collider2D other)
    {
        if (other.CompareTag("tagPlayer"))
        {
            //mTargetPlayer = null;
        }
    }
    #endregion
}
