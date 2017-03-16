using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CBullet : MonoBehaviour
{
    //private float mDirX = 0;
    //public float DirX
    //{
    //    set
    //    {
    //        mDirX = value;
    //    }
    //}

    private CScenePlayGame mpScene = null;
    private float mXSpeed = -1.0f;


    // Update is called once per frame
    //void Update()
    //{
    //    Vector3 pos = this.transform.position;
    //    pos.x += (mDirX * 5) * Time.deltaTime;
    //    this.transform.position = pos;

    //}

    //public void OnTriggerEnter2D(Collider2D collision)
    //{
    //    if (collision.CompareTag("tagEnemy"))
    //    {
    //        collision.gameObject.SetActive(false);
    //        Destroy(this.gameObject);
    //    }
    //}

    private void Update()
    {
        UpdateMy();
    }
    public void UpdateMy()
    {
        this.transform.Translate(new Vector3(mXSpeed * Time.deltaTime, 0.0f, 0.0f));

        if(this.transform.position.x < -3.0f || this.transform.position.x > 3.0f)
        {
            Destroy(this.gameObject);
        }
    }
    public void SetXSpeed(float tXSpeed)
    {
        mXSpeed = tXSpeed;
    }
    public void SetScene(CScenePlayGame tpScene)
    {
        mpScene = tpScene;
    }
    public void OnTriggerEnter2D(Collider2D collision)
    {
        if(true == collision.CompareTag("tagEnemy"))
        {
            Debug.Log("CBullet.OnTriggerEnter2D");
            mpScene.AddScore();
            Destroy(this.gameObject);
        }
    }
}
