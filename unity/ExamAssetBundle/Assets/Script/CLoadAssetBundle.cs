using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CLoadAssetBundle : MonoBehaviour
{

    // Use this for initialization
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {

    }

    IEnumerator Load()
    {
        using(WWW.LoadFromCacheOrDownload(Application.dataPath + "/StreamingAssets/"))
    }
}
