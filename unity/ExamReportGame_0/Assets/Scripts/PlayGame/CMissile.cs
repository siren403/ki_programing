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

    // Use this for initialization
    void Start()
    {
    }

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

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.CompareTag("tagWall"))
        {
            Destroy(this.gameObject);
        }
    }

}
