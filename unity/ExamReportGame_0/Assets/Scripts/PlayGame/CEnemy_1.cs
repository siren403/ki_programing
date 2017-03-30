using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CEnemy_1 : CEnemy
{
    protected override void Start()
    {
        base.Start();
        mATK = 2;
    }

    protected override IEnumerator MoveStateFunc()
    {
        if(mTargetPlayer != null)
        {
            Vector3 dir = mTargetPlayer.transform.position - this.transform.position;
            dir.Normalize();
            var tMissile = CreateMissile(dir, Color.cyan);
            tMissile.transform.localScale = Vector2.one * 2;
        }

        SetState(State.Attack);
        yield return new WaitForSeconds(1.0f);
    }

    protected override IEnumerator AttackStateFunc()
    {
        for (int i = 0; i < 15; i++)
        {
            if (mTargetPlayer != null)
            {
                CreateMissile(mTargetPlayer.transform.position - this.transform.position, Color.cyan);
            }
            yield return new WaitForSeconds(0.6f);
        }

        SetState(State.Idle);
    }

    protected override IEnumerator DeadStateFunc()
    {
        yield return base.DeadStateFunc();
        mScene.OnGameClear();
    }
}
