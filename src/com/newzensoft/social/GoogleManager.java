package com.newzensoft.social;

import static org.cocos2dx.cpp.AppActivity.getActivity;


import com.google.android.gms.auth.api.Auth;
import com.google.android.gms.auth.api.signin.GoogleSignIn;
import com.google.android.gms.auth.api.signin.GoogleSignInAccount;
import com.google.android.gms.auth.api.signin.GoogleSignInClient;
import com.google.android.gms.auth.api.signin.GoogleSignInOptions;
import com.google.android.gms.auth.api.signin.GoogleSignInResult;
import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.api.ApiException;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.AuthCredential;
import com.google.firebase.auth.AuthResult;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.auth.GoogleAuthProvider;
import com.newzensoft.poker.R;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

import androidx.annotation.NonNull;

import org.cocos2dx.cpp.AppActivity;
import org.cocos2dx.lib.Cocos2dxHelper;
public class GoogleManager{
  private Activity activity;
  
  private static GoogleManager googleMgr = null;
  
  private static final String TAG = "GoogleManager";

  private FirebaseAuth mAuth;
  private GoogleSignInClient mGoogleSignInClient;
  private static final int RC_SIGN_IN = 9001;
  
  private boolean isPrint = true;
  
  private boolean googleLogin = false;

  private String googleID;
  
  private String googleName;
  
  private String googleEmail;
  
  private String googlePhotoUrl;
  
  private boolean isActivate = false;
  
  private static final int RC_UNUSED = 5001;
  
  public static Object instance() {
    System.out.println("instance 1");
    if (googleMgr == null) {
      System.out.println("instance 2");
      googleMgr = new GoogleManager();
    } 
    System.out.println("instance 3");
    return googleMgr;
  }

  public  GoogleManager(){
    System.out.println("GoogleManager init");
    this.activity = (Activity)getActivity();
    this.mAuth = FirebaseAuth.getInstance();
    GoogleSignInOptions gso = new GoogleSignInOptions.Builder(GoogleSignInOptions.DEFAULT_SIGN_IN)
            .requestIdToken("209585710996-ijk2ue8h1crg5fsme57e6qbenktpb1ss.apps.googleusercontent.com")
            .requestEmail()
            .build();
    this.mGoogleSignInClient = GoogleSignIn.getClient(activity, gso);
    FirebaseUser currentUser = mAuth.getCurrentUser();

  }
  
  private void println(String string) {
    if (this.isPrint)
      System.out.println(string); 
  }
  
  public void onActivityResult(int requestCode, int resultCode, Intent data) {
    println("onActivityResult");
    if (requestCode == 9001) {
      println("onActivityResult 1244");
      GoogleSignInResult result = Auth.GoogleSignInApi.getSignInResultFromIntent(data);
      println("onActivityResult 1244a1a21");
      ActivateHandleSignInResult(result);
    } 
  }

  private void handleSignInResult(GoogleSignInResult result) {
    Log.d("GoogleManager", "handleSignInResult:" + result.isSuccess());
    this.googleLogin = result.isSuccess();
    if (result.isSuccess()) {
      GoogleSignInAccount acct = result.getSignInAccount();
      this.googleID = acct.getId();
      this.googleName = acct.getDisplayName();
      this.googleEmail = acct.getEmail();
      if (acct.getPhotoUrl() == null) {
        this.googlePhotoUrl = "";
      } else {
        this.googlePhotoUrl = acct.getPhotoUrl().toString();
      } 
      println("result handleSignInResult sucess 1");
      println("result handleSignInResult sucess 2");
    } else {
      this.googleID = "";
      this.googleName = "";
      this.googleEmail = "";
      this.googlePhotoUrl = "";
      println("result fail");
    } 
  }
  
  private void ActivateHandleSignInResult(GoogleSignInResult result) {
    Log.d("GoogleManager", "ActivateHandleSignInResult:" + result.isSuccess());
    this.googleLogin = result.isSuccess();
    if (result.isSuccess()) {
      GoogleSignInAccount acct = result.getSignInAccount();
      this.googleID = acct.getId();
      this.googleName = acct.getDisplayName();
      this.googleEmail = acct.getEmail();
      if (acct.getPhotoUrl() == null) {
        this.googlePhotoUrl = "";
      } else {
        this.googlePhotoUrl = acct.getPhotoUrl().toString();
      } 
      println("result handleSignInResult sucess 1");
      OnGoogleLoginResult(true, this.googleID, this.googleName, this.googleEmail, this.googlePhotoUrl);
      println("result handleSignInResult sucess 2");
    } else {
      OnGoogleLoginResult(false, "", "", "", "");
      this.googleID = "";
      this.googleName = "";
      this.googleEmail = "";
      this.googlePhotoUrl = "";
      println("result fail");
    } 
  }
  
  public void googleInit() {
    println("googleInit");
    GoogleData(this.googleLogin, this.googleID, this.googleName, this.googleEmail, this.googlePhotoUrl);
  }
  
  public void signIn() {
    this.isActivate = true;
    println("signIn 123");
    Intent signInIntent = mGoogleSignInClient.getSignInIntent();
    activity.startActivityForResult(signInIntent, RC_SIGN_IN);
  }

  public void firebaseAuthWithGoogle(GoogleSignInAccount acct) {
    AuthCredential credential = GoogleAuthProvider.getCredential(acct.getIdToken(), null);
    mAuth.signInWithCredential(credential)
            .addOnCompleteListener(activity, new OnCompleteListener<AuthResult>() {
              @Override
              public void onComplete(@NonNull Task<AuthResult> task) {
                if (task.isSuccessful()) {
                  // Sign in success, update UI with the signed-in user's information
                  FirebaseUser user = mAuth.getCurrentUser();
                  println("getEmail = " + user.getEmail());
                  println("getDisplayName = " + user.getDisplayName());
                  println("getPhotoUrl = " + user.getPhotoUrl());
                  println("getProviderId = " + user.getProviderId());
                  println("getUid = " + user.getUid());
                  println("getPhoneNumber = " + user.getPhoneNumber());
                  OnGoogleLoginResult(true,user.getUid(),user.getDisplayName(),user.getEmail(),user.getPhotoUrl().toString());
                } else {
                  // If sign in fails, display a message to the user.

                }
              }
            });
  }



  public void signOut() {
    println("signOut");

  }
  
  public void revokeAccess() {
    println("revokeAccess");

  }
  
  public void onConnectionFailed(ConnectionResult arg0) {}

  public void onConnectionSuspended(int arg0) {}
  
  public void onStart() {
    println("signIn onStart");

  }
  
  public void onStop() {
    println("signIn onStop");

  }
  
  public void achieveUnlock() {
    println("achieveUnlock");
  }
  
  public void achieveIncrement() {
    println("achieveIncrement");
  }
  
  public void leaderBoardSubmit(int score) {
    println("leaderBoardSubmit");
  }
  
  public void leaderBoardShow() {
    println("leaderBoardShow");
  }
  
  public void showAchieve() {}
  
  public static native void OnLoginConnected();
  
  public static native void OnGameConnected();
  
  public static native void OnGameConnectionFailed();
  
  public static native void OnGoogleLogOut(boolean paramBoolean);
  
  public static native void OnGoogleLoginResult(boolean paramBoolean, String paramString1, String paramString2, String paramString3, String paramString4);
  
  public static native void GoogleData(boolean paramBoolean, String paramString1, String paramString2, String paramString3, String paramString4);
}
