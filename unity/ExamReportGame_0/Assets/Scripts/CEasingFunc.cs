using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CEasingFunc
{

    public static float EaseCircIn(float currentTime,float startValue,float changeValue,float duration)
    {
        currentTime /= duration;
        return -changeValue * (Mathf.Sqrt(1 - currentTime * currentTime) - 1) + startValue;
    }
}
