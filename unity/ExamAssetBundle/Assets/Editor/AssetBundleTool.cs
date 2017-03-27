using UnityEngine;
using UnityEditor;
using System.IO;
using System;
using System.Diagnostics;


public class AssetBundleTool : EditorWindow
{

    [MenuItem("AssetBundle/Tool")]
    public static void OpenWindow()
    {
        EditorWindow.GetWindow<AssetBundleTool>();
    }

    private void OnGUI()
    {
        if(GUILayout.Button("Build"))
        {
            string path = Environment.CurrentDirectory;
            UnityEngine.Debug.Log(path);

            Process.Start("explorer.exe", path);
        }
    }
}
