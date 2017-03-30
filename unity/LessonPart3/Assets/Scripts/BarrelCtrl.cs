using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BarrelCtrl : MonoBehaviour
{
    public GameObject mExpEffect = null;

    private int mHitCount = 0;

    public Texture[] mTextures = null;

    // Use this for initialization
    void Start()
    {
        GetComponentInChildren<MeshRenderer>().material.mainTexture = mTextures[Random.Range(0, mTextures.Length)];
    }

    // Update is called once per frame
    void Update()
    {

    }
    private void OnCollisionEnter(Collision tCollision)
    {
        if(tCollision.collider.CompareTag("tagBullet"))
        {
            Destroy(tCollision.gameObject);

            if(++mHitCount >= 3)
            {
                ExpBarrel();
            }
        }
    }

    void ExpBarrel()
    {
        Collider[] colls = Physics.OverlapSphere(transform.position, 10.0f);
        foreach(Collider coll in colls)
        {
            Rigidbody rbody = coll.GetComponent<Rigidbody>();
            if(rbody !=null)
            {
                rbody.mass = 1.0f;
                rbody.AddExplosionForce(1000.0f, transform.position, 10.0f, 300.0f);
            }
        }

        Destroy(this.gameObject, 5.0f);
    }

}
