using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using GoogleMobileAds.Api;

public class CAdmob : MonoBehaviour {


    private void RequestBanner()
    {
#if UNITY_EDITOR
        string adUnitId = "unused";
#elif UNITY_ANDROID
        //string adUnitId = "INSERT_ANDROID_BANNER_AD_UNIT_ID_HERE";
        string adUnitId = "ca-app-pub-3940256099942544/6300978111";
#elif UNITY_IPHONE
        string adUnitId = "INSERT_IOS_BANNER_AD_UNIT_ID_HERE";
#else
        string adUnitId = "unexpected_platform";
#endif

        // Create a 320x50 banner at the top of the screen.
        BannerView bannerView = new BannerView(adUnitId, AdSize.SmartBanner, AdPosition.Top);
        // Create an empty ad request.
        AdRequest request = new AdRequest.Builder().Build();
        // Load the banner with the request.
        bannerView.LoadAd(request);
    }


    private void OnGUI()
    {
        if(GUI.Button(new Rect(100,200,200,80),"admob"))
        {
            RequestBanner();
        }
        if (GUI.Button(new Rect(100, 300, 200, 80), "admob event handler"))
        {
            RequestBannerToEventHandler();
        }

        GUI.Label(new Rect(100, 400, 480, 800), mLog);
    }

    string mLog = "TEst";

    private void RequestBannerToEventHandler()
    {
#if UNITY_EDITOR
        string adUnitId = "unused";
#elif UNITY_ANDROID
        //string adUnitId = "INSERT_ANDROID_BANNER_AD_UNIT_ID_HERE";
        string adUnitId = "ca-app-pub-3940256099942544/6300978111";
#elif UNITY_IPHONE
        string adUnitId = "INSERT_IOS_BANNER_AD_UNIT_ID_HERE";
#else
        string adUnitId = "unexpected_platform";
#endif
        BannerView bannerView = new BannerView(adUnitId, AdSize.Banner, AdPosition.Top);
        // Called when an ad request has successfully loaded.
        bannerView.OnAdLoaded += HandleOnAdLoaded;
        // Called when an ad request failed to load.
        bannerView.OnAdFailedToLoad += HandleOnAdFailedToLoad;
        // Called when an ad is clicked.
        bannerView.OnAdOpening += HandleOnAdOpened;
        // Called when the user returned from the app after an ad click.
        bannerView.OnAdClosed += HandleOnAdClosed;
        // Called when the ad click caused the user to leave the application.
        bannerView.OnAdLeavingApplication += HandleOnAdLeavingApplication;


        AdRequest request = new AdRequest.Builder().Build();
        bannerView.LoadAd(request);
    }

    public void HandleOnAdLoaded(object sender, System.EventArgs args)
    {
        print("OnAdLoaded event received.");
        mLog += "\nOnAdLoaded event received.";
        // Handle the ad loaded event.
    }
    public void HandleOnAdFailedToLoad(object sender, AdFailedToLoadEventArgs args)
    {
        print("Interstitial Failed to load: " + args.Message);
        // Handle the ad failed to load event.
        mLog += "\nInterstitial Failed to load: " + args.Message;

    }
    public void HandleOnAdOpened(object sender, System.EventArgs args)
    {
        print("HandleOnAdOpened event received.");
        // Handle the ad loaded event.
        mLog += "\nHandleOnAdOpened event received.";

    }
    public void HandleOnAdClosed(object sender, System.EventArgs args)
    {
        print("HandleOnAdClosed event received.");
        // Handle the ad loaded event.
        mLog += "\nHandleOnAdClosed event received.";

    }
    public void HandleOnAdLeavingApplication(object sender, System.EventArgs args)
    {
        print("HandleOnAdLeavingApplication event received.");
        // Handle the ad loaded event.
        mLog += "\nHandleOnAdLeavingApplication event received.";

    }
}
