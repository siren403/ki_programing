using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerCtrl : MonoBehaviour
{

    private float h = 0.0f;
    private float v = 0.0f;

    public float mMoveSpeed = 10.0f;
    public float mRotateSpeed = 100.0f;
    // Use this for initialization
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        h = Input.GetAxis("Horizontal");
        v = Input.GetAxis("Vertical");

        Vector3 moveDir = (Vector3.forward * v) + (Vector3.right * h);
        transform.Translate(moveDir * mMoveSpeed * Time.deltaTime, Space.Self);

        transform.Rotate(Vector3.up * Time.deltaTime * mRotateSpeed * Input.GetAxis("Mouse X"));
    }
}
