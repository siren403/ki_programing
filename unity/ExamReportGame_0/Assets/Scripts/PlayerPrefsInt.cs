using UnityEngine;

public class PlayerPrefsInt
{
    public int Value
    {
        get
        {
            return PlayerPrefs.GetInt(mKey, 0);
        }
        set
        {
            PlayerPrefs.SetInt(mKey, value);
        }
    }
    private string mKey = "";


    public PlayerPrefsInt(string key, int value = 0)
    {
        mKey = key;
        if (PlayerPrefs.HasKey(key) == false)
        {
            PlayerPrefs.SetInt(mKey, value);
        }
    }
}
