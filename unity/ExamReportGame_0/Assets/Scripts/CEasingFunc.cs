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
    public static float EaseExpoInOut(float currentTime, float startValue, float changeValue, float duration)
    {
        currentTime /= duration / 2;
        if (currentTime < 1) return changeValue / 2 * Mathf.Pow(2, 10 * (currentTime - 1)) + startValue;
        currentTime--;
        return changeValue / 2 * (-Mathf.Pow(2, -10 * currentTime) + 2) + startValue;
    }

}
