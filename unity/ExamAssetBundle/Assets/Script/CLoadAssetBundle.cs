using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public struct GUIRect
{
    private Rect mRect;
    public Rect rect
    {
        get
        {
            mRect.x = mCenter.x - mSize.x * 0.5f;
            mRect.y = mCenter.y - mSize.y * 0.5f;

            mRect.size = mSize;
            return mRect;
        }
    }

    private Vector2 mCenter;
    private Vector2 mSize;

    public Vector2 center
    {
        set
        {
            mCenter = value;
        }
    }
    public Vector2 size
    {
        set
        {
            mSize = value;
        }
    }
    
    public GUIRect(float x, float y,float width,float height)
    {
        mCenter = new Vector2(x, y);
        mSize = new Vector2(width, height);
        mRect = Rect.zero;
    }
}


public class CLoadAssetBundle : MonoBehaviour
{

    //Load
    public enum LoadType { StreamingAssets, WebServer }
    public LoadType mLoadType = LoadType.StreamingAssets;
    private bool isLoading = false;
    public string SampleURL = string.Empty;

    //AssetBundle Manage
    private List<GameObject> LoadInstanceList = null;
    private Dictionary<string, AssetBundle> CachedAssetBundle = null;
    private string LoadedAssetBundleName = string.Empty;
    private string LoadAssetName = string.Empty;

    void Start()
    {
        DontDestroyOnLoad(this.gameObject);
        LoadInstanceList = new List<GameObject>();
        CachedAssetBundle = new Dictionary<string, AssetBundle>();
    }

    private void OnGUI()
    {
        float width = Screen.width;
        float height = Screen.height;

        GUIRect guiRect = new GUIRect();
        Vector2 btnSize = new Vector2(width * 0.65f, height * 0.05f);


        guiRect.center = new Vector2(width * 0.25f, height * 0.03f);
        guiRect.size = new Vector2(width * 0.4f, height * 0.03f);
        LoadedAssetBundleName = GUI.TextField(guiRect.rect, LoadedAssetBundleName);
        guiRect.center = new Vector2(width * 0.75f, height * 0.03f);
        LoadAssetName = GUI.TextField(guiRect.rect, LoadAssetName);

        guiRect.center = new Vector2(width * 0.5f, height * 0.1f);
        guiRect.size = btnSize;
        if (GUI.Button(guiRect.rect, "Load AssetBundle"))
        {
            AssetBundle assetBundle = null;
            if (CachedAssetBundle.TryGetValue(LoadedAssetBundleName, out assetBundle))
            {
                GameObject pfGO = assetBundle.LoadAsset<GameObject>(LoadAssetName);
                LoadInstanceList.Add(Instantiate(pfGO));
            }
        }
        guiRect.center = new Vector2(width * 0.5f, height * 0.15f);
        if (GUI.Button(guiRect.rect, "Next Scene"))
        {
            AssetBundle assetBundle = null;
            if (CachedAssetBundle.TryGetValue(LoadedAssetBundleName, out assetBundle))
            {
                UnityEngine.SceneManagement.SceneManager.LoadScene("CSceneEmpty");
            }
        }
        guiRect.center = new Vector2(width * 0.5f, height * 0.2f);
        if (GUI.Button(guiRect.rect, "Unload AssetBundles"))
        {
            foreach (var bundle in CachedAssetBundle)
            {
                bundle.Value.Unload(false);
            }
        }




        guiRect.center = new Vector2(width * 0.5f, height * 0.5f);
        guiRect.size = btnSize;
        if (GUI.Button(guiRect.rect, "Load All Asset Bundle"))
        {
            if(isLoading == false)
            {
                StartCoroutine(LoadAllAssetBundles());
            }
        }
        guiRect.center = new Vector2(width * 0.5f, height * 0.6f);
        if (GUI.Button(guiRect.rect, "Sample Download"))
        {
            StartCoroutine(LoadSampleAssetBundle());
        }

        guiRect.center = new Vector2(width * 0.5f, height * 0.7f);
        if (GUI.Button(guiRect.rect, "Destroy Objects"))
        {
            foreach(var obj in LoadInstanceList)
            {
                Destroy(obj);
            }
            LoadInstanceList.Clear();
        }
        guiRect.center = new Vector2(width * 0.5f, height * 0.8f);
        if(GUI.Button(guiRect.rect,"Remove Cache"))
        {
            bool result = Caching.CleanCache();
            Debug.Log("result : " + result);
        }
        guiRect.center = new Vector2(width * 0.5f, height * 0.9f);
        if (GUI.Button(guiRect.rect, "GC Collect"))
        {
            System.GC.Collect();
        }

    }

    public IEnumerator LoadAllAssetBundles()
    {
        isLoading = true;
        string URL = string.Empty;
        string path = string.Empty;
#if UNITY_EDITOR

        switch (mLoadType)
        {
            case LoadType.StreamingAssets:
                URL = "file:///" + Application.streamingAssetsPath + "/";
                break;
            case LoadType.WebServer:
                URL = "http://cjcj09.dothome.co.kr/AssetBundles/";
                break;
        }
        path = URL + "AssetBundles";
#elif UNITY_STANDALONE_WIN
        path = "";
#endif
        Debug.Log(path);

        AssetBundleManifest assetBundleManifest = null;
        using (WWW www = new WWW(path))
        {
            yield return www;

            AssetBundle bundleManifest = www.assetBundle;

            assetBundleManifest = bundleManifest.LoadAsset<AssetBundleManifest>("AssetBundleManifest");

        }

        if (assetBundleManifest != null)
        {
            foreach (var assetBundleName in assetBundleManifest.GetAllAssetBundles())
            {
                Debug.Log("---------------------");

                Debug.Log(assetBundleName);
                bool isCaching = Caching.IsVersionCached(URL + assetBundleName, assetBundleManifest.GetAssetBundleHash(assetBundleName));
                Debug.Log(string.Format("isCaching : {0}\nURL : {1}\nHash : {2}", isCaching, URL + assetBundleName, assetBundleManifest.GetAssetBundleHash(assetBundleName)));

                using (WWW www = WWW.LoadFromCacheOrDownload(URL + assetBundleName, assetBundleManifest.GetAssetBundleHash(assetBundleName)))
                {
                    yield return www;

                    AssetBundle bundle = www.assetBundle;

                    if(CachedAssetBundle.ContainsKey(assetBundleName) == false)
                    {
                        Debug.Log("[CacheAssetBundle] " + assetBundleName);
                        CachedAssetBundle.Add(assetBundleName, bundle);
                    }


                    //foreach (var name in bundle.GetAllAssetNames())
                    //{
                    //    Debug.Log(assetBundleName + " : " + name);
                    //    GameObject prefab = bundle.LoadAsset<GameObject>(name);
                    //    if (prefab != null)
                    //    {
                    //        LoadInstanceList.Add(Instantiate(prefab));
                    //    }
                    //}
                    //bundle.Unload(false);
                }

                Debug.Log("---------------------");

            }
        }
        isLoading = false;
    }

    public IEnumerator LoadSampleAssetBundle()
    {
        using (WWW www = WWW.LoadFromCacheOrDownload(SampleURL, 0))
        {
            yield return www;

            AssetBundle assetBundle = www.assetBundle;

            foreach (var name in assetBundle.GetAllAssetNames())
            {
                Debug.Log(name);
                GameObject prefab = assetBundle.LoadAsset<GameObject>(name);
                if (prefab != null)
                {
                    LoadInstanceList.Add(Instantiate(prefab));
                }
                else
                {
                    Debug.Log("Prefab is null");
                }
            }

            assetBundle.Unload(true);
        }
    }

}
