using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WallCtrl : MonoBehaviour {

    public GameObject mSparkEffect = null;

    private void OnCollisionEnter(Collision tCollision)
    {
        if(tCollision.collider.CompareTag("tagBullet"))
        {
            GameObject go = Instantiate(mSparkEffect, tCollision.transform.position, Quaternion.identity);
            Destroy(go, 3.0f);

            Destroy(tCollision.gameObject);

        }
    }
}
