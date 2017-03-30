using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CEnemy_0 : CEnemy
{
    protected override IEnumerator MoveStateFunc()
    {
        while (mState != State.Dead)
        {
            if (mTargetPlayer != null)
            {
                float tTime = 0.0f;
                Vector3 targetPos = mTargetPlayer.transform.position;

                while (tTime < 4.0f)
                {
                    tTime += Time.deltaTime;
                    this.transform.position = Vector3.Lerp(this.transform.position,
                        targetPos, 0.03f);
                    yield return null;
                }
                SetState(State.Attack);
            }
            else
            {
                SetState(State.Idle);
            }
            yield return null;
        }
    }

    protected override IEnumerator AttackStateFunc()
    {
        for (int i = 0; i < 5; i++)
        {
            if (mTargetPlayer != null)
            {
                CreateMissile(mTargetPlayer.transform.position - this.transform.position, Color.red);
            }
            yield return new WaitForSeconds(0.2f);
        }
        SetState(State.Idle);
    }
}
