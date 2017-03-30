using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CSceneLectureLoadSave : MonoBehaviour {


	public int mLevel = 0;
	public int mExp = 0;

	public float mPosition = 0.0f;

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}

	public void OnClickBtnLoadData(){

		mLevel 		= PlayerPrefs.GetInt("mLevel", 0);

		mExp 		= PlayerPrefs.GetInt("mExp", 0);
		mPosition 	= PlayerPrefs.GetFloat("mPosition", 0 );
		
	}
	public void OnClickBtnSaveData(){

		PlayerPrefs.SetInt("mLevel", 		mLevel );

		PlayerPrefs.SetInt("mExp", 			mExp);
		PlayerPrefs.SetFloat("mPosition", 	mPosition );

		PlayerPrefs.Save();

		

	}

	public void OnClickBtnNewData()
	{
		PlayerPrefs.DeleteAll();

		mLevel = 0;
		mExp = 0;
		mPosition = 0.0f;
	}


	public void OnClickBtnDoit()
	{
		mExp += 10;

		mLevel = (int)(mExp/100);

		mPosition += 25.0f;
	}


	void OnGUI()
	{
		GUI.Label(new Rect(0, 0, 250, 50), "현재 레벨: " + mLevel.ToString() );
		GUI.Label(new Rect(0, 50, 250, 50), "현재 경험치: " + mExp.ToString() );

		GUI.Label(new Rect(0, 150, 250, 50), "현재 위치: " + mPosition.ToString() + "km");
	}
}
