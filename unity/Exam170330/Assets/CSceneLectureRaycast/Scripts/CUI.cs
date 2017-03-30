using UnityEngine;
using System.Collections;

public class CUI : MonoBehaviour {


	public CSceneMain_0 mpScene = null;



	public void CreateRyu()
	{
		
	}


	public void SetScene( CSceneMain_0 tpScene )
	{
		mpScene = tpScene;
	}

	public void OnClickBtnFire()
	{
		//enemy behavior
		//클릭시마다 자신의 위치를 결정한다. 세가지 위치 중에서 랜덤하게 결정.

		CEnemy tpEnemy;
		tpEnemy = mpScene.GetEnemy ();

		tpEnemy.DecidePosition ();







		


		CActor tpCubeActor;
		tpCubeActor = mpScene.GetCubeActor ();


		Vector3 tVecFirePos 	= tpCubeActor.transform.position;
		Vector3 tVecD 			= tpCubeActor.transform.forward * 20.0f;


		RaycastHit tRaycastHit;

		if (true == Physics.Raycast (tVecFirePos, tpCubeActor.transform.forward, out tRaycastHit, 20.0f)) {

			Debug.Log ("===Hit!!!");

			//collider : 맞은 게임 오브젝트의 collider  반환 
			//transform: 맞은 게임 오브젝트의 Transform 반환
			//point: 맞은 위치의 월드좌표값 반환
			//distance: 발사 위치와 맞은 위치 사이의 거리
			//normal: Ray가 맞은 표면의 법선벡터


			Debug.Log ("GameObject.tag: " + tRaycastHit.collider.tag);
			Debug.Log ("GameObject.transform.position: " + 
						tRaycastHit.transform.position.x.ToString() + ", " + 
						tRaycastHit.transform.position.y.ToString() + ", " + 
						tRaycastHit.transform.position.z.ToString() );
			Debug.Log ("Hit Point: " + 
						tRaycastHit.point.x.ToString() + ", " + 
						tRaycastHit.point.y.ToString() + ", " + 
						tRaycastHit.point.z.ToString() );

			Debug.Log ("Distance: " + tRaycastHit.distance.ToString ());
			Debug.Log ("Normal: " + 
						tRaycastHit.normal.x.ToString() + ", " + 
						tRaycastHit.normal.y.ToString() + ", " + 
						tRaycastHit.normal.z.ToString() );




			//cross product
			Vector3 tCrossProduct = Vector3.Cross (tVecD, tRaycastHit.normal);

			Debug.Log("tCrossProduct: " + 
				tCrossProduct.x.ToString() + ", " + 
				tCrossProduct.y.ToString() + ", " + 
				tCrossProduct.z.ToString() );


			//dot product
			float tDotProduct = Vector3.Dot (tVecD, tRaycastHit.normal);

			Debug.Log("tDotProduct: " + 
				tDotProduct.ToString() );

		} 
		else 
		{
			Debug.Log ("===No Hit!!!");
		}











	}
}
