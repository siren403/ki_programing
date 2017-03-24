using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CMySoundMgr 
{
    private static CMySoundMgr mInstance = null;

    private CAudioBundle mpAudioBundle = null;

    private List<AudioSource> mAudioArray = null;

    private CMySoundMgr()
    {
        mInstance = null;
    }

    public static CMySoundMgr GetInst()
    {
        if(mInstance == null)
        {
            mInstance = new CMySoundMgr();
        }
        return mInstance;
    }


    public void CreateMy()
    {
        mAudioArray = new List<AudioSource>();
    }

    public void DestroyMy()
    {

    }

    public void SetAudioBundle(CAudioBundle tBundle)
    {
        mpAudioBundle = tBundle;
        GameObject.DontDestroyOnLoad(mpAudioBundle);
    }

    public void BuildMy()
    {
        int ti = 0;
        int tCount = mpAudioBundle.mArray.Length;

        for(ti = 0;ti<tCount;ti++)
        {
            mAudioArray.Add(mpAudioBundle.mArray[ti]);
        }
    }


    public void Play(int tIndex)
    {
        int tCount = mpAudioBundle.mArray.Length;

        if(tIndex < tCount - 1)
        {
            mAudioArray[tIndex].Play();
        }
    }

    public void Stop(int tIndex)
    {
        int tCount = mpAudioBundle.mArray.Length;

        if(tIndex < tCount - 1)
        {
            mAudioArray[tIndex].Stop();
        }
    }

    public bool IsPlaying(int tIndex)
    {
        bool tResult = false;

        if(tIndex < 0)
        {
            return tResult;
        }

        if(tIndex > mAudioArray.Count - 1)
        {
            return tResult;
        }

        tResult = mAudioArray[tIndex].isPlaying;

        return tResult;
    }


    public void DoSoundOff()
    {
        if (null == mAudioArray)
        {
            return;
        }

        int ti = 0;
        int tCount = 0;
        AudioSource tAS = null;

        tCount = mAudioArray.Count;

        for (ti = 0; ti < tCount; ti++)
        {
            tAS = null;
            tAS = mAudioArray[ti];
            tAS.mute = true;
        }
    }

    public void DoSoundOn()
    {
        if(null == mAudioArray)
        {
            return;
        }

        int ti = 0;
        int tCount = 0;
        AudioSource tAS = null;

        for (ti = 0; ti < tCount; ti++)
        {
            tAS = null;
            tAS = mAudioArray[ti];
            tAS.mute = false;
        }
    }
}

