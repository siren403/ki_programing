using UnityEngine;
using System.Collections;

public class CSceneRenderTexture : MonoBehaviour {


	protected GameObject mpCamera_0 = null;
	protected GameObject mpCamera_1 = null;

	//public Camera[] tCameraArray;





	protected int mState = 0;



	// Use this for initialization
	void Start () {

		//검색하여 대입한다.
		mpCamera_0 = GameObject.FindGameObjectWithTag ("tagCamera_0");
		mpCamera_1 = GameObject.FindGameObjectWithTag ("tagCamera_1");

		//tCameraArray = FindObjectsOfType<Camera> ();

		//mpCamera_0 = tCameraArray [1];


		mState = 0;

		mpCamera_0.SetActive (true);
		mpCamera_1.SetActive (false);

	}
	
	// Update is called once per frame
	void Update () {
	
	}

	public void DoToggleRenderCamera()
	{
		switch (mState) 
		{
		case 0:
			{
				mpCamera_0.SetActive (false);
				mpCamera_1.SetActive (true);
				
				mState = 1;
			}
			break;

		case 1:
			{
				mpCamera_0.SetActive (true);
				mpCamera_1.SetActive (false);
				
				mState = 0;
			}
			break;
				
		}
	}
		
}
