using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CMyEnemy : CMyUnit
{

    private void Start()
    {
    }

    public void StartAI()
    {
        StartCoroutine(UpdateAI());
    }
    private IEnumerator UpdateAI()
    {
        for (;;)
        {
            DoRotate(90.0f);

            Vector3 tPosition = this.transform.position;
            tPosition.y += 0.5f;

            Vector3 tDir = this.transform.forward;

            RaycastHit tRaycastHit;
            if(Physics.Raycast(tPosition, tDir, out tRaycastHit, 10.0f))
            {
                if (true == tRaycastHit.collider.CompareTag("tagActor"))
                {
                    yield return new WaitForSeconds(0.5f);

                    float distance = tRaycastHit.distance;
                    this.transform.position = Vector3.MoveTowards(this.transform.position, tRaycastHit.collider.transform.position, 1.0f);

                    Debug.Log(tRaycastHit.normal);
                }
            }

            yield return new WaitForSeconds(1.0f);
            
        }
    }
    private void OnDrawGizmos()
    {
        Vector3 pos = this.transform.position;
        pos.y += 0.5f;
        Debug.DrawRay(pos, this.transform.forward * 10, Color.red);
    }

    public void DoDamage()
    {

    }

}
