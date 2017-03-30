using UnityEngine;
using System.Collections;

public class CEnemy : MonoBehaviour {

	protected Vector3 mVecTarget = Vector3.zero;


	public void DecidePosition()
	{
		float tX = this.transform.position.x;
		float tY = 10.0f*Random.Range (-1, 1+1);
		float tZ = this.transform.position.z;
		
		mVecTarget = new Vector3 (tX, tY, tZ);



		this.transform.position = mVecTarget;
	}
}
