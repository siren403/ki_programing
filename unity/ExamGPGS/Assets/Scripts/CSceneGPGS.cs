using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.SceneManagement;

using GooglePlayGames;
using GooglePlayGames.BasicApi;
using UnityEngine.SocialPlatforms;

using UnityEngine.UI;

public class CSceneGPGS : MonoBehaviour
{
    public Image mImage = null;

    // Use this for initialization
    void Start()
    {
        PlayGamesClientConfiguration config = new PlayGamesClientConfiguration.Builder()
            // enables saving game progress.
            //.EnableSavedGames()
            // registers a callback to handle game invitations received while the game is not running.
            //.WithInvitationDelegate(<callback method>)
            // registers a callback for turn based match notifications received while the
            // game is not running.
            //.WithMatchDelegate(<callback method>)
            // require access to a player's Google+ social graph (usually not needed)
            .RequireGooglePlus()
            .Build();

        PlayGamesPlatform.InitializeInstance(config);
        PlayGamesPlatform.DebugLogEnabled = true;
        PlayGamesPlatform.Activate();

        Social.localUser.Authenticate((bool success) => {
            mImage.color = Color.red;
        });
    }

    // Update is called once per frame
    void Update()
    {

    }

    private void OnGUI()
    {
        Rect buttonRect_0 = new Rect(10, 10, 150, 100);
        if (GUI.Button(buttonRect_0, "show achievement"))
        {

            // show achievements UI
            Social.ShowAchievementsUI();
        }

        Rect buttonRect_1 = new Rect(10, 110, 150, 100);
        if (GUI.Button(buttonRect_1, "show leaderboard"))
        {

            // show leaderboard UI
            Social.ShowLeaderboardUI();
        }

        //archievement
        Rect buttonRect_2 = new Rect(250, 10, 150, 100);
        if (GUI.Button(buttonRect_2, "UNLOCK achievement"))
        {

            Debug.Log("unlock achievement");

            // unlock achievement (achievement ID "anything")
            Social.ReportProgress(GPGSIds.achievement_archievement_3, 100.0f, (bool success) => {

                // handle success or failure
                if (true == success)
                {
                }
                else
                {
                }

            });
        }

        //score for leaderboard
        Rect buttonRect_3 = new Rect(250, 110, 150, 100);
        if (GUI.Button(buttonRect_3, "post SCORE"))
        {

            Debug.Log("post score");

            // post score 12345 to leaderboard ID "anything")
            Social.ReportScore(12345, "CgkIl7e-85sIEAIQAg", (bool success) => {

                // handle success or failure
                if (true == success)
                {
                }
                else
                {
                }

            });
        }
    }
}
