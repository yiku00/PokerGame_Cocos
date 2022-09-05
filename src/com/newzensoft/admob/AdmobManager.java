package com.newzensoft.admob;

import static org.cocos2dx.lib.Cocos2dxHelper.getActivity;

import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import com.google.android.gms.ads.AdError;
import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.LoadAdError;
import com.google.android.gms.ads.MobileAds;
import com.google.android.gms.ads.initialization.InitializationStatus;
import com.google.android.gms.ads.initialization.OnInitializationCompleteListener;
import com.google.android.gms.ads.InterstitialAd;
import com.google.android.gms.ads.rewarded.RewardedAd;
import com.google.android.gms.ads.rewarded.RewardItem;
import com.google.android.gms.ads.rewarded.RewardedAdCallback;
import com.google.android.gms.ads.rewarded.RewardedAdLoadCallback;


import android.annotation.TargetApi;
import android.app.Activity;
import android.content.Context;
import android.graphics.Point;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.view.Display;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.LinearLayout;

import androidx.annotation.NonNull;

public class AdmobManager{
  private static AdmobManager admobMgr = null;

  private Activity activity;
  
  private AdRequest adRequest = null;
  
  private AdView admobView;
  
  private String AD_UNIT_ID = "";
  
  private String AD_UNIT_ALL = "";
  
  private String AD_UNIT_REWARD = "";
  
  private String APP_ID = "";
  
  private String User_ID = "";
  
  private boolean isPrint = true;
  
  private InterstitialAd mInterstitialAd;
  
  private RewardedAd mRewardedAd;
  
  private boolean developerMode = false;
  
  public static Object instance() {
      if (admobMgr == null) {
      System.out.println("instance 2");
      admobMgr = new AdmobManager();

    }
     System.out.println("Reward instance()");
    return admobMgr;
  }
  
  private void println(String string) {
    if (this.isPrint)
      System.out.println(string); 
  }
  
  private Point getDisplaySize(Display d) {
    if (Build.VERSION.SDK_INT >= 11)
      return getDisplaySizeGE11(d); 
    return getDisplaySizeLT11(d);
  }
  
  @TargetApi(13)
  private Point getDisplaySizeGE11(Display d) {
    Point p = new Point(0, 0);
    d.getSize(p);
    return p;
  }
  
  private Point getDisplaySizeLT11(Display d) {
    try {
      Method getWidth = Display.class.getMethod("getWidth", new Class[0]);
      Method getHeight = Display.class.getMethod("getHeight", new Class[0]);
      return new Point(((Integer)getWidth.invoke(d, null)).intValue(), ((Integer)getHeight.invoke(d, null)).intValue());
    } catch (NoSuchMethodException e2) {
      return new Point(-1, -1);
    } catch (IllegalArgumentException e2) {
      return new Point(-2, -2);
    } catch (IllegalAccessException e2) {
      return new Point(-3, -3);
    } catch (InvocationTargetException e2) {
      return new Point(-4, -4);
    } 
  }

  public  AdmobManager(){
      getActivity().runOnUiThread(new Runnable() {
          public void run() {
              AD_UNIT_ID = getActivity().getResources().getString(getActivity().getResources().getIdentifier("ad_unit_id", "string", getActivity().getPackageName()));
              AD_UNIT_ALL = getActivity().getResources().getString(getActivity().getResources().getIdentifier("ad_unit_all_id", "string", getActivity().getPackageName()));
              AD_UNIT_REWARD = getActivity().getResources().getString(getActivity().getResources().getIdentifier("ad_unit_reward_id", "string", getActivity().getPackageName()));
              APP_ID = getActivity().getResources().getString(getActivity().getResources().getIdentifier("google_app_id", "string", getActivity().getPackageName()));
              loadRewardedVideoAd();
          }
      });

  }
  
  private void requestNewInterstitial() {
      AdRequest adRequest = (new AdRequest.Builder()).build();
      this.mInterstitialAd.loadAd(adRequest);
  }
  
  public void showInterstitialAd() {
    this.activity.runOnUiThread(new Runnable() {
          public void run() {
            if (AdmobManager.this.mInterstitialAd.isLoaded()) {
              AdmobManager.this.mInterstitialAd.show();
            } else {
              AdmobManager.this.println("mInterstitialAd not loady");
            } 
          }
        });
  }
 
  private void loadRewardedVideoAd() {
      System.out.println("Reward Loady Start");
      AdRequest ADREQUEST = (new AdRequest.Builder()).build();
      RewardedAdLoadCallback adLoadCallback = new RewardedAdLoadCallback() {
          @Override
          public void onRewardedAdLoaded() {
              System.out.println("Reward Loady Success");
          }

          @Override
          public void onRewardedAdFailedToLoad(LoadAdError adError) {
              System.out.println("Reward Loady Failed");
              CallBackFailRewardedVideoAd();
          }
      };
      mRewardedAd = new RewardedAd(getActivity(), "ca-app-pub-3940256099942544/5224354917");
      System.gc();
      mRewardedAd.loadAd(ADREQUEST, adLoadCallback);
	}

  public void showRewardad() {
      getActivity().runOnUiThread(new Runnable() {
	          public void run() {
	      		if(mRewardedAd.isLoaded()) {
                    RewardedAdCallback adCallback = new RewardedAdCallback() {
                        @Override
                        public void onRewardedAdOpened() {
                            // Ad opened.
                        }
                        @Override
                        public void onRewardedAdClosed() {
                            loadRewardedVideoAd();
                            System.out.println("onRewardedAdClosed");
                            CallBackOnRewardAdClosed();
                        }

                        @Override
                        public void onUserEarnedReward(@NonNull RewardItem reward) {
                            CallBackSuccessRewardedVideoAd();
                            System.out.println("onUserEarnedReward");
                        }

                        @Override
                        public void onRewardedAdFailedToShow(AdError adError) {
                            System.out.println("onRewardedAdFailedToShow");
                            CallBackFailRewardedVideoAd();
                        }
                    };

                    admobMgr.mRewardedAd.show(getActivity(), adCallback);
	    		}else {
	    			System.out.println("show Reward not Loaded");
                    //showRewardad();
	    		}
	          }
	        });
	}
  
  public void ShowAd() {
    this.activity.runOnUiThread(new Runnable() {
          public void run() {
            AdmobManager.this.admobView.setEnabled(true);
            AdmobManager.this.admobView.setVisibility(View.VISIBLE);
            AdmobManager.this.admobView.resume();
          }
        });
  }
  
  public void hideAd() {
    this.activity.runOnUiThread(new Runnable() {
          public void run() {
            AdmobManager.this.admobView.setEnabled(false);
            AdmobManager.this.admobView.setVisibility(View.INVISIBLE);
            AdmobManager.this.admobView.pause();
          }
        });
  }



private static native void CallBackSuccessRewardedVideoAd();
private static native void CallBackFailRewardedVideoAd();
private static native void CallBackOnRewardAdStarted();
private static native void CallbackOnRewardAdOpened();
private static native void CallBackOnRewardAdClosed();
private static native void CallBackOnRewardAdLoaded();
private static native void CallbackOnRewardAdFailToLoaded();


}
