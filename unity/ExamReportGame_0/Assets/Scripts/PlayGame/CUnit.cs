using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UniRx;

public class CUnit : MonoBehaviour
{
    private IntReactiveProperty mHP = new IntReactiveProperty();
    protected IntReactiveProperty HP
    {
        get
        {
            if (mHP == null)
            {
                mHP = new IntReactiveProperty();
            }
            return mHP;
        }
    }
    public ReadOnlyReactiveProperty<int> ReadHP
    {
        get
        {
            return mHP.ToReadOnlyReactiveProperty<int>();
        }
    }
    public int mATK = 0;
    protected CScenePlayGame mScene = null;

    public void SetScene(CScenePlayGame tScene)
    {
        mScene = tScene;
    }

    public virtual void Hit(int tDamage)
    {
    }
}
