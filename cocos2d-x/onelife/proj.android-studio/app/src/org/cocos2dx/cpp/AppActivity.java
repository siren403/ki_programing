/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
Copyright (c) 2015 Adrian Dawid
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;
//import your.app.id.*;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.MobileAds;
import com.ngot.onelife.R;
import org.cocos2dx.cpp.MainActivity;

import android.annotation.TargetApi;
import android.graphics.Color;
import android.graphics.Point;
import android.os.Build;
import android.os.Bundle;
import com.google.android.gms.common.api.ResultCallback;
import com.google.android.gms.games.Games;
import com.google.android.gms.games.Games.*;
import android.content.Context;
import android.util.Log;
import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.GooglePlayServicesUtil;
import com.google.android.gms.games.GamesStatusCodes;
import com.google.android.gms.games.leaderboard.LeaderboardVariant;
import com.google.android.gms.games.leaderboard.Leaderboards;
import com.google.example.games.basegameutils.BaseGameActivity;

import android.content.Intent;
import android.app.Activity;
import android.util.Log;
import android.view.Display;
import android.view.View;
import android.view.WindowManager;
import android.widget.LinearLayout;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class AppActivity extends BaseGameActivity {

    //admob
    private static AppActivity _appActiviy;
    private AdView adView;

    //테스트용 광고단위 식별자
    private static final String AD_UNIT_ID = "ca-app-pub-3940256099942544/6300978111";

    static int currentID;
    static int currentAchievementID;
    static boolean gpgAvailable;

    static String[] leaderboardIDs;
    static String[] achievementIDs;
    static Context currentContext;

    static int currentScore;

    //admob
    // Helper get display screen to avoid deprecated function use
    private Point getDisplaySize(Display d) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB) {
            return getDisplaySizeGE11(d);
        }
        return getDisplaySizeLT11(d);
    }

    @TargetApi(Build.VERSION_CODES.HONEYCOMB_MR2)
    private Point getDisplaySizeGE11(Display d) {
        Point p = new Point(0, 0);
        d.getSize(p);
        return p;
    }

    private Point getDisplaySizeLT11(Display d) {
        try {
            Method getWidth = Display.class.getMethod("getWidth", new Class[]{});
            Method getHeight = Display.class.getMethod("getHeight", new Class[]{});
            return new Point(((Integer) getWidth.invoke(d, (Object[]) null)).intValue(), ((Integer) getHeight.invoke(d, (Object[]) null)).intValue());
        } catch (NoSuchMethodException e2) // None of these exceptions should ever occur.
        {
            return new Point(-1, -1);
        } catch (IllegalArgumentException e2) {
            return new Point(-2, -2);
        } catch (IllegalAccessException e2) {
            return new Point(-3, -3);
        } catch (InvocationTargetException e2) {
            return new Point(-4, -4);
        }
    }


    public static native void callCppCallback();

    @Override
    public void onSignInSucceeded() {
        gpgAvailable = true;
    }

    @Override
    public void onSignInFailed() {
        gpgAvailable = false;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        String leaderboardIdsRaw = getString(R.string.leaderboard);
        String achievementIdsRaw = getString(R.string.archievement_0);

//        Log.i("myLog", achievementIdsRaw);

        leaderboardIDs = leaderboardIdsRaw.split(";");
        achievementIDs = achievementIdsRaw.split(";");

        currentContext = this;

        super.onCreate(savedInstanceState);

        //admob
        //테스트용 앱 단위
        MobileAds.initialize(getApplicationContext(), "ca-app-pub-3940256099942544~3347511713");
        //MobileAds.initialize(getApplicationContext(), "ca-app-pub-2197670717324929~7887461497");


        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        int width = getDisplaySize(getWindowManager().getDefaultDisplay()).x;


        LinearLayout.LayoutParams adParams = new LinearLayout.LayoutParams(
                width,
                LinearLayout.LayoutParams.WRAP_CONTENT);
        //adParams.gravity = Gravity.BOTTOM;


        //admob
        adView = new AdView(this);
        adView.setAdSize(AdSize.SMART_BANNER);

        adView.setAdUnitId(AD_UNIT_ID);

        //이 구문은 테스트를 위한 용도이다 테스트에 쓸 디바이스들을 등록할 수 있다
        AdRequest adRequest = new AdRequest.Builder()
                .addTestDevice(AdRequest.DEVICE_ID_EMULATOR)
                .addTestDevice("HASH_DEVICE_ID")
                .build();

        //이 구문은 실제 동작 구문이다. 광고요청을 빌드한다
        //AdRequest adRequest = new AdRequest.Builder().build();

        adView.loadAd(adRequest);
        adView.setBackgroundColor(Color.WHITE);//BLACK);
        adView.setBackgroundColor(0);
        addContentView(adView, adParams);

        _appActiviy = this;

    }

    /*@brief Changes the actvie leaderboard
      @param The index of the leaderboard
    */
    static public void openLeaderboard(int leaderboardID) {
        currentID = leaderboardID;
    }

    /*@brief This function opens the leaderboards ui for an leaderboard id*/
    static public void openLeaderboardUI() {
        if (gpgAvailable) {
            ((AppActivity) currentContext).runOnUiThread(new Runnable() {
                public void run() {
                    ((AppActivity) currentContext).startActivityForResult(Games.Leaderboards.getLeaderboardIntent(((AppActivity) currentContext).getGameHelper().getApiClient(), leaderboardIDs[currentID]), 2);
                }
            });
        }
    }

    static public boolean isGPGSupported() {
        return gpgAvailable;
    }

    /*@brief Submits a score to the leaderboard that is currently actvie*/
    static public void submitScoreToLeaderboard(int score) {
        if (gpgAvailable) {
            Games.Leaderboards.submitScore(((AppActivity) currentContext).getGameHelper().getApiClient(), leaderboardIDs[currentID], score);
        }
    }

    static public void requestScoreFromLeaderboard() {
        if (gpgAvailable) {
            Games.Leaderboards.loadCurrentPlayerLeaderboardScore(((AppActivity) currentContext).getGameHelper().getApiClient(), leaderboardIDs[currentID], LeaderboardVariant.TIME_SPAN_ALL_TIME, LeaderboardVariant.COLLECTION_PUBLIC).setResultCallback(new ResultCallback<Leaderboards.LoadPlayerScoreResult>() {
                @Override
                public void onResult(final Leaderboards.LoadPlayerScoreResult scoreResult) {
                    if (scoreResult.getStatus().getStatusCode() == GamesStatusCodes.STATUS_OK) {
                        AppActivity.currentScore = (int) scoreResult.getScore().getRawScore();
                        AppActivity.callCppCallback();
                    }
                }
            });
        }
    }

    static public int collectScore() {
        return AppActivity.currentScore;
    }

    /*@brief Shows the achievements ui*/
    static public void showAchievements() {
        if (gpgAvailable) {
            ((AppActivity) currentContext).runOnUiThread(new Runnable() {
                public void run() {
                    ((AppActivity) currentContext).startActivityForResult(Games.Achievements.getAchievementsIntent(((AppActivity) currentContext).getGameHelper().getApiClient()), 5);
                }
            });
        }
    }

    /*@brief Changes the actvie Achievement
      @param The index of the achievement in the list*/
    static public void openAchievement(int achievementID) {
        currentAchievementID = achievementID;
    }

    static public void updateAchievement(int percentage) {
        if (gpgAvailable) {
            Games.Achievements.unlock(((AppActivity) currentContext).getGameHelper().getApiClient(), achievementIDs[currentAchievementID]);
        }
    }

    static public void exitGame() {
        Intent intent = new Intent(currentContext, MainActivity.class);
        MainActivity.exiting = true;
        currentContext.startActivity(intent);
    }

    //admob
    public static void hideAd() {
        _appActiviy.runOnUiThread(new Runnable() {

            @Override
            public void run() {
                if (_appActiviy.adView.isEnabled())
                    _appActiviy.adView.setEnabled(false);
                if (_appActiviy.adView.getVisibility() != 4)
                    _appActiviy.adView.setVisibility(View.INVISIBLE);
            }
        });

    }


    public static void showAd() {
        _appActiviy.runOnUiThread(new Runnable() {

            @Override
            public void run() {
                if (!_appActiviy.adView.isEnabled())
                    _appActiviy.adView.setEnabled(true);
                if (_appActiviy.adView.getVisibility() == 4)
                    _appActiviy.adView.setVisibility(View.VISIBLE);
            }
        });

    }

    @Override
    protected void onResume() {
        super.onResume();
        if (adView != null) {
            adView.resume();
        }
    }

    @Override
    protected void onPause() {
        if (adView != null) {
            adView.pause();
        }
        super.onPause();
    }

    @Override
    protected void onDestroy() {
        adView.destroy();
        super.onDestroy();
    }
}


