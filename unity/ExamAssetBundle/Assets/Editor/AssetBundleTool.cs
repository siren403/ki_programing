using UnityEngine;
using UnityEditor;
using System.IO;
using System;


public class AssetBundleTool : EditorWindow
{
    private const string ROOT_NAME = "AssetBundles";
    private string PATH
    {
        get
        {
            return string.Format("{0}\\{1}", Environment.CurrentDirectory, ROOT_NAME);
        }
    }
    
    [MenuItem("AssetBundle/Tool")]
    public static void OpenWindow()
    {
        EditorWindow.GetWindow<AssetBundleTool>().Initialize();
    }
    private void Initialize()
    {
        if(Directory.Exists(PATH) == false)
        {
            Directory.CreateDirectory(PATH);
            Debug.Log("Create Bundle Directory");
        }
    }

    private void OnGUI()
    {
        if(GUILayout.Button("Open Directory"))
        {
            OpenDirectory();
        }
        if(GUILayout.Button("Build"))
        {
            BuildAssetBundleOptions tOptions;
            tOptions = BuildAssetBundleOptions.None;

            BuildTarget tBuildTarget;
            tBuildTarget = BuildTarget.StandaloneWindows64;

            BuildPipeline.BuildAssetBundles(PATH, tOptions, tBuildTarget);

            OpenDirectory();

        }
    }

    private void OpenDirectory()
    {
        UnityEngine.Debug.Log(PATH);
        System.Diagnostics.Process.Start("explorer.exe", PATH);
    }
}
