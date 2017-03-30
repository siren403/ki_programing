using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MyGizmo : MonoBehaviour {

    public Color mColor = Color.yellow;
    public float mRadius = 0.1f;

    private void OnDrawGizmos()
    {
        Gizmos.color = mColor;
        Gizmos.DrawSphere(transform.position, mRadius);
    }
}
