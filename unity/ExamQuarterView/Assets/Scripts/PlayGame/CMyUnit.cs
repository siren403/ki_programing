using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CMyUnit : MonoBehaviour {

    protected float mSpeed = 0.0f;

    // Use this for initialization
    void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    public void DoMove(Vector3 tDir)
    {
        mSpeed = 1.0f;
        this.transform.Translate(tDir * mSpeed, Space.Self);

    }
    public void DoRotate(float tAngle)
    {
        this.transform.Rotate(Vector3.up, tAngle, Space.Self);
    }
}
