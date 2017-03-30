using UnityEngine;
using System.Collections;

public class CSceneMain_0 : MonoBehaviour {

	//public CUI mpUI = null;
	//public CCube mpCubeActor = null;
	protected CUI mpUI 			= null;
	protected CActor mpActor 	= null;
	protected CEnemy mpEnemy 	= null;

	// Use this for initialization
	void Start () {
	
		CreateRyu ();

	}
	
	// Update is called once per frame
	void Update () {
	
	}


	public void CreateRyu()
	{
		//툴에서 연결하지 않고 소스코드상에서 연결한다.
		mpUI 			= FindObjectOfType<CUI> ();
		mpActor 		= FindObjectOfType<CActor> ();
		mpEnemy 		= FindObjectOfType<CEnemy> ();	


		mpUI.CreateRyu ();
		mpUI.SetScene (this);
	}


	public CActor GetCubeActor()
	{
		return mpActor;
	}

	public CEnemy GetEnemy()
	{
		return mpEnemy;
	}


}
