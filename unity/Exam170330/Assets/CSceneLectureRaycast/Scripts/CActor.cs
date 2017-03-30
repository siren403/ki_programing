using UnityEngine;
using System.Collections;

public class CActor : MonoBehaviour {

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {

		Vector3 tVecO = Vector3.zero;
		Vector3 tVecD = this.transform.forward * 20.0f;

		Debug.DrawRay (tVecO, tVecD, Color.blue);

		Debug.DrawLine (tVecO, this.transform.up * 10.0f, Color.red);
	}
}
