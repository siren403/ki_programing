using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CMissile : MonoBehaviour
{

    private Vector2 mDirection = Vector2.right;
    private float mSpeed = 2.0f;

    private float mHeightTime = 0.0f;
    private float mHeightDuration = 1.0f;

    public Vector2 Direction
    {
        set
        {
            mDirection = value;
        }
    }

    private string mTargetTag = string.Empty;

    private SpriteRenderer _mSpriteRenderer = null;
    private SpriteRenderer mSpriteRenderer
    {
        get
        {
            if(_mSpriteRenderer == null)
            {
                _mSpriteRenderer = GetComponentInChildren<SpriteRenderer>();
            }
            return _mSpriteRenderer;
        }
    }

    private int mATK = 0;

    void Update()
    {
        Vector2 pos = transform.position;

        pos.x += mDirection.x * mSpeed * Time.deltaTime;
        pos.y += mDirection.y * mSpeed * Time.deltaTime;


        mHeightTime += Time.deltaTime;
        float deltaY = CEasingFunc.EaseCircIn(mHeightTime, 0, 0.02f, mHeightDuration);
        pos.y -= deltaY;

        if ((mHeightTime / mHeightDuration) > 0.9f)
        {
            Destroy(this.gameObject);
        }

        transform.position = pos;

    }

    public void SetTargetTag(string tag)
    {
        mTargetTag = tag;
    }
    public void SetATK(int tATK)
    {
        mATK = tATK;
    }
    public void SetColor(Color tColor)
    {
        mSpriteRenderer.color = tColor;
    }

    private void OnTriggerEnter2D(Collider2D tCollision)
    {
        if(tCollision.CompareTag("tagWall"))
        {
            Destroy(this.gameObject);
        }
        else if(tCollision.CompareTag(mTargetTag))
        {
            CUnit tUnit = tCollision.GetComponent<CUnit>();
            tUnit.Hit(this.mATK);
            Destroy(this.gameObject);
        }
    }

}
