using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BulletCtrl : MonoBehaviour
{
    public int mDamage = 20;
    public float mSpeed = 1000.0f;

    private void Start()
    {
        GetComponent<Rigidbody>().AddForce(transform.forward * mSpeed);
    }
}
