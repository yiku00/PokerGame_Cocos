package com.newzensoft.social;

import static org.cocos2dx.lib.Cocos2dxHelper.getActivity;

import android.app.Activity;
import android.content.Context;
import android.net.Uri;
import android.os.Bundle;
import com.facebook.AccessToken;
import com.facebook.AccessTokenTracker;
import com.facebook.CallbackManager;
import com.facebook.FacebookCallback;
import com.facebook.FacebookException;
import com.facebook.FacebookSdk;
import com.facebook.GraphRequest;
import com.facebook.GraphResponse;
import com.facebook.HttpMethod;
import com.facebook.login.LoginManager;
import com.facebook.login.LoginResult;
import com.facebook.share.model.GameRequestContent;
import com.facebook.share.model.ShareContent;
import com.facebook.share.model.ShareLinkContent;
import com.facebook.share.widget.ShareDialog;
import com.google.android.gms.ads.rewarded.RewardedAd;
import com.google.firebase.auth.FirebaseAuth;

import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

public class FacebookMgr {
  private static FacebookMgr facebookMgr;
  
  public enum FacebookEvent {
    FB_ERROR(0),
    FB_LOGIN_START(1),
    FB_LOGIN_SUCCESS(2),
    FB_LOGIN_CANCEL(3),
    FB_LOGIN_FAIL(4),
    FB_LOGOUT(5),
    FB_FRIENDLIST_REQUEST_SUCCESS(6),
    FB_FRIENDLIST_REQUEST_FAIL(7),
    FB_FRIEND_INVITE_REQUEST_SUCCESS(8),
    FB_FRIEND_INVITE_REQUEST_ERROR(9),
    FB_FRIEND_INVITE_REQUEST_CANCEL(10),
    FB_SEND_EMAIL_SUCCESS(11),
    FB_SEND_EMAIL_FAIL(12),
    FB_ALREADY_LOGOUT(13),
    FB_LOGOUT_FAIL(14);
    
    int loc;
    
    FacebookEvent(int loc) {
      this.loc = loc;
    }
    
    public int getNumber() {
      return this.loc;
    }
  }
  
  private boolean isInit = false;
  
  private boolean isUse = false;
  
  private boolean isPrint = true;
  
  private LoginManager loginManager;
  
  private AccessToken accessToken;
  
  private AccessTokenTracker accessTokenTracker;
  
  private String facebookUserID= "";
  
  private String facebookUserName= "";
  
  private String facebookUserEmail= "";
  
  private String facebookUserPhotoUrl = "";
  
  private String facebookFriendNextPageKey = "";
  
  public CallbackManager callbackManager;
  
  private Activity activity;
  
  String appLinkUrl = "https://fb.me/1696103894019183";
  
  String previewImageUrl = "https://www.mydomain.com/my_invite_image.jpg";
  
  public static Object instance() {
    if (facebookMgr == null)
      facebookMgr = new FacebookMgr();
    System.out.println("Facebook instance is started!");
    return facebookMgr;
  }

  public FacebookMgr() {
    println("Facebook init is started!");
    if (!this.isInit) {
      this.activity = getActivity();
      System.out.println("Facebook Logged in 2");
      FacebookSdk.sdkInitialize((Context)this.activity, new FacebookSdk.InitializeCallback() {
            public void onInitialized() {
              if (AccessToken.getCurrentAccessToken() == null) {
                System.out.println("Facebook not logged in yet");
              } else {
                System.out.println("Facebook Logged in");
              } 
            }
          });
      this.callbackManager = CallbackManager.Factory.create();
      println("----------------------------Facebook loginManager init");
      this.loginManager = LoginManager.getInstance();
      this.loginManager.registerCallback(this.callbackManager,
          new FacebookCallback<LoginResult>() {
            public void onSuccess(LoginResult loginResult) {
              FacebookMgr.this.accessToken = loginResult.getAccessToken();
              FacebookMgr.this.println("----------------------------Facebook accessToken : " + FacebookMgr.this.accessToken.getToken());
              FacebookMgr.this.QueryMyInfo();
              FacebookMgr.this.println("----------------------------Facebook logined");
            }

            public void onCancel() {
              FacebookMgr.this.println("----------------------------Facebook Login cancel");
              FacebookMgr.OnFacebookEvent(FacebookMgr.FacebookEvent.FB_LOGIN_CANCEL.getNumber(), "");
            }

            public void onError(FacebookException exception) {
              FacebookMgr.this.println("----------------------------Facebook Login error");
              FacebookMgr.OnFacebookEvent(FacebookMgr.FacebookEvent.FB_LOGIN_FAIL.getNumber(), "");
              System.out.println("-------------Facebook" + exception.getMessage());
              exception.printStackTrace();
            }
          });
      println("----------------------------Facebook loginManager inited");
      println("----------------------------Facebook AccessTokenTracker Init");
      this.accessTokenTracker = new AccessTokenTracker() {
          protected void onCurrentAccessTokenChanged(AccessToken oldAccessToken, AccessToken currentAccessToken) {
            if (oldAccessToken != null) {
              FacebookMgr.this.println("----------------------------Facebook oldAccessToken : " + oldAccessToken.getToken() + "," + oldAccessToken.getUserId());
            } else {
              FacebookMgr.this.println("----------------------------Facebook oldAccessToken : null!!!");
            }
            if (currentAccessToken != null) {
              FacebookMgr.this.println("----------------------------Facebook currentAccessToken : " + currentAccessToken.getToken() + "," + currentAccessToken.getUserId());
            } else {
              FacebookMgr.this.println("----------------------------Facebook currentAccessToken : null!!!");
            }
            if (oldAccessToken == currentAccessToken)
              FacebookMgr.this.println("----------------------------Facebook already Logined!!!");
          }
        };
      this.accessTokenTracker.startTracking();
      println("----------------------------Facebook AccessTokenTracker inited");
      this.isUse = true;
      println("----------------------------Facebook is Initted!");
      this.isInit = true;
    } 
  }
  
  public void ConnectFB() {
    this.accessToken = AccessToken.getCurrentAccessToken();
    System.out.println("----------------------Facebook test bookmark2!!!!! ");
    if (this.accessToken == null) {
      println("Facebook -- Not Having accessToken, it is tried to call login!!");
      List<String> permissionNeeds =  Arrays.asList("user_photos", "email");
      this.loginManager.logInWithReadPermissions(this.activity, permissionNeeds);
      OnFacebookEvent(FacebookEvent.FB_LOGIN_START.getNumber(), "");
    } else {
      System.out.println("----------------------Facebook test bookmark3!!!!! accessToken.getPermissions()" + this.accessToken.getPermissions());
      System.out.println("----------------------Facebook test bookmark3!!!!! accessToken.getDeclinedPermissions()" + this.accessToken.getDeclinedPermissions());
      AccessToken.refreshCurrentAccessTokenAsync(new AccessToken.AccessTokenRefreshCallback() {
            public void OnTokenRefreshed(AccessToken accessToken) {
              accessToken = AccessToken.getCurrentAccessToken();
              FacebookMgr.this.println("Facebook -- Having accessToken, it is tried to call query My Info!!");
              FacebookMgr.this.QueryMyInfo();
            }
            
            public void OnTokenRefreshFailed(FacebookException arg0) {
              List<String> permissionNeeds = Arrays.asList(new String[] { "user_photos", "email", "user_friends" });
              FacebookMgr.this.loginManager.logInWithReadPermissions(getActivity(), permissionNeeds);
              FacebookMgr.OnFacebookEvent(FacebookMgr.FacebookEvent.FB_LOGIN_START.getNumber(), "");
            }
          });
    } 
  }
  
  private void ParsingLoginData(JSONObject response) throws JSONException {
    this.facebookUserID = response.getString("id");
    this.facebookUserName = response.getString("name");
    if (response.has("email")) {
      this.facebookUserEmail = response.getString("email");
    } else {
      this.facebookUserEmail = "";
    } 
    this.facebookUserPhotoUrl = response.getJSONObject("picture").getJSONObject("data").getString("url");
    GetFacebookUserData();
    OnFacebookEvent(FacebookMgr.FacebookEvent.FB_LOGIN_SUCCESS.getNumber(), "");
  }
  
  public void GetFacebookUserData() {
    println("Set Facebook UserData : " + this.facebookUserID + "/" + this.facebookUserName + "/" + this.facebookUserEmail + "/" + this.facebookUserPhotoUrl);
    FacebookUserData(this.facebookUserID, this.facebookUserName, this.facebookUserEmail, this.facebookUserPhotoUrl);
  }
  
  private void QueryMyInfo() {
    println("----------------------------Facebook Started QueryMyInfo!");
    GraphRequest request = GraphRequest.newMeRequest(
        this.accessToken, 
        new GraphRequest.GraphJSONObjectCallback() {
          public void onCompleted(JSONObject object, GraphResponse response) {
            FacebookMgr.this.println("----------------------------Facebook QueryMyInfo onCompleted : " + response.toString());
            try {
              FacebookMgr.this.ParsingLoginData(object);
            } catch (JSONException e) {
              FacebookMgr.this.println(e.getMessage());
              e.printStackTrace();
              FacebookMgr.OnFacebookEvent(FacebookMgr.FacebookEvent.FB_LOGIN_FAIL.getNumber(), "");
            } 
          }
        });
    Bundle parameters = new Bundle();
    parameters.putString("fields", "id,name,email,picture");
    request.setParameters(parameters);
    request.executeAsync();
    println("----------------------Facebook GraphRequest ver" + request.getVersion());
  }
  
  public void RequestInvitableUserList(boolean isNext) {
    println("----------------------invitableFriend List max check");
    String url = "/me/invitable_friends";
    println("----------------------Facebook invitableFriend Request Start : Url -> " + url);
    Bundle arges = new Bundle();
    arges.putInt("limit", 5000);
    (new GraphRequest(AccessToken.getCurrentAccessToken(), url, arges, HttpMethod.GET, 
        new GraphRequest.Callback() {
          public void onCompleted(GraphResponse response) {
            FacebookMgr.this.facebookFriendNextPageKey = "";
            FacebookMgr.this.println("----------------------response" + response);
            JSONObject object = response.getJSONObject();
            FacebookMgr.this.println("----------------------Facebook invitableFriend Parsing Start" + object);
            try {
              if (object != null) {
                JSONArray array = object.getJSONArray("data");
                FacebookMgr.this.println("----------------------Facebook invitableFriend List OnCompleted" + object.toString());
                String word = object.toString();
                FacebookMgr.this.println("123");
                try {
                  FacebookMgr.this.println("euc-kr -> utf-8:" + new String(word.getBytes("euc-kr"), "utf-8"));
                } catch (UnsupportedEncodingException e) {
                  FacebookMgr.this.println("UnsupportedEncodingException");
                  e.printStackTrace();
                } 
                FacebookMgr.this.println("456");
                FacebookMgr.OnFacebookEvent(FacebookMgr.FacebookEvent.FB_FRIENDLIST_REQUEST_SUCCESS.getNumber(), object.toString());
              } 
            } catch (JSONException e) {
              e.printStackTrace();
              FacebookMgr.OnFacebookEvent(FacebookMgr.FacebookEvent.FB_FRIENDLIST_REQUEST_FAIL.getNumber(), "");
              FacebookMgr.this.println("----------------------Facebook invitableFriend List OnFailed!!");
            } 
          }
        })).executeAsync();
    println("----------------------Facebook invitableFriend List end");
  }
  
  public void RequestUserList() {
    println("----------------------Facebook RequestUserList List max check");
    String url = "/me/friends";
    println("----------------------Facebook RequestUserList Request Start : Url -> " + url);
    Bundle arges = new Bundle();
    arges.putInt("limit", 5000);
    arges.putString("fields", "name,id,picture");
    (new GraphRequest(AccessToken.getCurrentAccessToken(), url, arges, HttpMethod.GET, 
        new GraphRequest.Callback() {
          public void onCompleted(GraphResponse response) {
            FacebookMgr.this.facebookFriendNextPageKey = "";
            FacebookMgr.this.println("----------------------response RequestUserList" + response);
            JSONObject object = response.getJSONObject();
            FacebookMgr.this.println("----------------------Facebook RequestUserList Parsing Start!!!!! " + object);
            try {
              if (object != null) {
                JSONArray array = object.getJSONArray("data");
                FacebookMgr.this.println("----------------------Facebook RequestUserList List OnCompleted" + object.toString());
                String word = object.toString();
                FacebookMgr.this.println("123");
                try {
                  FacebookMgr.this.println("euc-kr -> utf-8:" + new String(word.getBytes("euc-kr"), "utf-8"));
                } catch (UnsupportedEncodingException e) {
                  FacebookMgr.this.println("UnsupportedEncodingException");
                  e.printStackTrace();
                } 
                FacebookMgr.this.println("456");
                FacebookMgr.OnFacebookEvent(FacebookMgr.FacebookEvent.FB_FRIENDLIST_REQUEST_SUCCESS.getNumber(), object.toString());
              } 
            } catch (JSONException e) {
              e.printStackTrace();
              FacebookMgr.OnFacebookEvent(FacebookMgr.FacebookEvent.FB_FRIENDLIST_REQUEST_FAIL.getNumber(), "");
              FacebookMgr.this.println("----------------------Facebook RequestUserList List OnFailed!!");
            } 
          }
        })).executeAsync();
    println("----------------------Facebook invitableFriend List end");
  }
  
  public void appLink() {
    if (ShareDialog.canShow(ShareLinkContent.class)) {
      ShareLinkContent content = ((ShareLinkContent.Builder)(new ShareLinkContent.Builder())
        .setContentUrl(Uri.parse("http://ilovepoker-live-world.numixent.com:8200/poker_server/usage_terms.htm")))
        .build();
      ShareDialog.show(this.activity, (ShareContent)content);
    } 
  }
  
  public void LogOut() {
    if (AccessToken.getCurrentAccessToken() == null) {
      OnFacebookEvent(FacebookEvent.FB_ALREADY_LOGOUT.getNumber(), "");
      return;
    } 
    (new GraphRequest(AccessToken.getCurrentAccessToken(), "/me/permissions/", null, HttpMethod.DELETE, new GraphRequest.Callback() {
          public void onCompleted(GraphResponse graphResponse) {
            LoginManager.getInstance().logOut();
            FacebookMgr.OnFacebookEvent(FacebookMgr.FacebookEvent.FB_LOGOUT.getNumber(), "");
          }
        })).executeAsync();
  }
  
  public void setPrint(boolean isPrint) {
    this.isPrint = isPrint;
  }
  
  private void println(String data) {
    if (this.isPrint)
      System.out.println(data); 
  }
  
  public static native void OnFacebookEvent(int paramInt, String paramString);
  
  public static native void FacebookUserData(String paramString1, String paramString2, String paramString3, String paramString4);
}
