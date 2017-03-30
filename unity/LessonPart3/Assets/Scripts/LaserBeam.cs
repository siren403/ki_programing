using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LaserBeam : MonoBehaviour
{

    private LineRenderer line;
    private RaycastHit hit;

    // Use this for initialization
    void Start()
    {
        line = GetComponent<LineRenderer>();

        line.useWorldSpace = false;
        line.enabled = false;
        line.startWidth = 0.3f;
        line.endWidth = 0.01f;
    }

    // Update is called once per frame
    void Update()
    {
        Ray ray = new Ray(transform.position + (Vector3.up * 0.02f), transform.forward);

        Debug.DrawRay(ray.origin, ray.direction * 100, Color.blue);

        if(Input.GetMouseButtonDown(0))
        {
            line.SetPosition(0, transform.InverseTransformPoint(ray.origin));

            if(Physics.Raycast(ray,out hit,100.0f))
            {
                line.SetPosition(1, transform.InverseTransformPoint(hit.point));
            }
            else
            {
                line.SetPosition(1, transform.InverseTransformPoint(ray.GetPoint(100.0f)));
            }

            StartCoroutine(this.ShowLaserBeam());
        }
    }

    IEnumerator ShowLaserBeam()
    {
        line.enabled = true;
        yield return new WaitForSeconds(Random.Range(0.01f, 0.2f));
        line.enabled = false;
    }
}
