using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class CDialogueInfo
{
    public int mId = 0;
    public string mDialogue = string.Empty; 
}

[System.Serializable]
public class CDialogueInfoList
{
    public List<CDialogueInfo> mDialogues = null;
}
