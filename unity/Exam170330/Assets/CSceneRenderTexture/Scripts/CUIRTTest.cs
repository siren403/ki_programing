using UnityEngine;
using System.Collections;

public class CUIRTTest : MonoBehaviour {

	protected CSceneRenderTexture mpScene = null;

	// Use this for initialization
	void Start () {
	
		//여기서 CreateRyu, SetScene하는 것은 순서의 제어를 엔진에 맡기게 된다.
		//반면에 CSceneRenderTexture에서 하는 것은 순서의 제어를 작성자가 맡는다.
		CreateRyu();
	}
	
	// Update is called once per frame
	void Update () {
	
	}


	public void CreateRyu()
	{
		//검색하여 대입한다.
		mpScene = FindObjectOfType<CSceneRenderTexture> ();
	}

	/*
	직접 지정하여 바로 대입한다.
	public void SetScene( CSceneRenderTexture tpScene )
	{
		mpScene = tpScene;
	}
	*/


	public void OnClickBtnTest()
	{
		mpScene.DoToggleRenderCamera ();
	}
}
