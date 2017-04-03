using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class CDetector2D : MonoBehaviour
{
    public delegate void TriggerFunc(Collider2D other);

    private Collider2D mCollider = null;
    private TriggerFunc mTriggerEnterFunc = null;
    private TriggerFunc mTriggerStayFunc = null;
    private TriggerFunc mTriggerExitFunc = null;



    private void Awake()
    {
        mCollider = GetComponent<Collider2D>();
        mCollider.isTrigger = true;
    }

    private void OnTriggerEnter2D(Collider2D other)
    {
        if(mTriggerEnterFunc != null)
        {
            mTriggerEnterFunc.Invoke(other);
        }
    }
    private void OnTriggerStay2D(Collider2D other)
    {
        if (mTriggerStayFunc != null)
        {
            mTriggerStayFunc.Invoke(other);
        }
    }
    private void OnTriggerExit2D(Collider2D other)
    {
        if (mTriggerExitFunc != null)
        {
            mTriggerExitFunc.Invoke(other);
        }
    }

    public void AddTriggerEnter(TriggerFunc func)
    {
        mTriggerEnterFunc += func;
    }
    public void AddTriggerStay(TriggerFunc func)
    {
        mTriggerStayFunc += func;
    }
    public void AddTriggerExit(TriggerFunc func)
    {
        mTriggerExitFunc += func;
    }
}
