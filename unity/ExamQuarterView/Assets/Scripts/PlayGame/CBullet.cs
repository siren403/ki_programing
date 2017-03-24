using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CBullet : MonoBehaviour
{

    // Use this for initialization
    void Start()
    {
        this.GetComponent<Rigidbody>().AddTorque(this.transform.right * 1.0f, ForceMode.Impulse);
    }

    // Update is called once per frame
    void Update()
    {
        if (this.transform.position.x < -5.0f || this.transform.position.x > 5.0f)
        {
            Destroy(this.gameObject);
        }

        if (this.transform.position.z < -5.0f || this.transform.position.z > 5.0f)
        {
            Destroy(this.gameObject);
        }
    }

    private void OnCollisionEnter(Collision tCollision)
    {
        if (tCollision.collider.CompareTag("tagEnemy"))
        {
            Debug.Log("Enemy vs Bullet is Collision");

            tCollision.collider.GetComponent<CMyEnemy>().DoDamage();
            Destroy(this.gameObject);
            Destroy(tCollision.collider.gameObject, 0.5f);
        }
    }
}
