using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CEnemy_0 : CMyEnemy
{

    // Use this for initialization
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        this.transform.Rotate(Vector3.up, 10, Space.Self);
    }
}
