using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CLoadAssetBundle : MonoBehaviour
{

    public GameObject Sample = null;

    // Use this for initialization
    IEnumerator Start()
    {

        string path = string.Empty;
#if UNITY_EDITOR
        path = "file:///" + Application.streamingAssetsPath + "/AssetBundles";
#endif
        Debug.Log(path);

        using (WWW www = new WWW(path))
        {
            yield return www;

            AssetBundle bundleManifest = www.assetBundle;

            AssetBundleManifest assetBundleManifest = bundleManifest.LoadAsset<AssetBundleManifest>("AssetBundleManifest");

            foreach (var bundleName in assetBundleManifest.GetAllAssetBundles())
                Debug.Log(bundleName);

        }
    }

    // Update is called once per frame
    void Update()
    {

    }


}
