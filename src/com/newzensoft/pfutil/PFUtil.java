package com.newzensoft.pfutil;

import static org.cocos2dx.lib.Cocos2dxHelper.getActivity;

import java.lang.reflect.Method;

import com.facebook.AccessToken.AccessTokenCreationCallback;

import android.app.Activity;
import android.app.AlarmManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.graphics.Point;
import android.os.Build;
import android.os.Message;
import android.telephony.TelephonyManager;
import android.util.DisplayMetrics;
import android.view.Display;
import android.view.ViewStructure;
import android.webkit.WebView;

import org.cocos2dx.cpp.AuthSelectActivity;

public class PFUtil
{
	private static PFUtil utilMgr;
	
	private static Activity activity = null;

	public static native void jnitest(String data);
	public static native void SetEditText(String data);
	private String Req_URL;
	private int UID;
	private String Target_IP;

	public static String getRequestURL_For_Auth(){return utilMgr.Req_URL;}
	public static int getUID_For_Auth(){return utilMgr.UID;}
	public static String getIP_For_Auth(){return utilMgr.Target_IP;}

	public static Object instance()
	{
		if (utilMgr == null)
			utilMgr = new PFUtil();

		return utilMgr;
	}
	
	public PFUtil()
	{
		this.activity = getActivity();
	}

	public void InitWebView(String url, int x, int y, int w, int h)
	{
		if (activity == null)
			return;
		CustomWebView.instance().init(activity, url,  x, y, w, h);
	}

	public void DeleteWebView()
	{
		if (activity == null)
			return;

		Message msg = CustomWebView.instance().m_DeleteHandler.obtainMessage();
		CustomWebView.instance().m_DeleteHandler.sendMessage(msg);
	}

	public void OpenAdultWebView(String url,int uid, String ip)
	{
		if (activity == null)
			return;
		utilMgr.Req_URL = url;
		utilMgr.UID = uid;
		utilMgr.Target_IP = ip;

		//ReleaseWebView();
		//String realUrl = url + "?uid=" + uid + "&ip=" + ip;
		//InitWebView(realUrl,0,0,GetScreenWidth(),GetScreenHeight());
		//System.out.println("realUrl = " +realUrl);


		if (activity == null)
			return;

		CustomView.Instance().InitView(getActivity(), 0, 0, GetScreenHeight() ,GetScreenWidth() );


		//CustomView.Instance().InitView(activity, 0, 0,GetScreenWidth() , GetScreenHeight());
		//getActivity().setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
		//ShowWebView();
	}

	public void ShowWebView()
	{
		if (activity == null)
			return;
		
		CustomWebView.instance().ShowWebView();
	}
	
	public void ReleaseWebView()
	{
		if (activity == null)
			return;
		
		CustomWebView.instance().ReleaseWebView();
	}
	
	public void HideWebView()
	{
		if (activity == null)
			return;
		
		CustomWebView.instance().HideWebView();
	}
	
	public String GetDeviceID()
	{
		if (activity == null)
			return "";
		
		String deviceID = null;
//		try 
//		{
//			TelephonyManager telManager = (TelephonyManager)activity.getSystemService(Context.TELEPHONY_SERVICE);
//			deviceID = telManager.getDeviceId();
//		} 
//		catch (Exception e) 
//		{
//			System.out.println(e);
//		}
		
		return deviceID;
	}
	
	public String GetPhoneNumber()
	{
		if (activity == null)
			return "";
		
		String phoneNumber = null;

		return phoneNumber;
	}
	
	public String GetOSVersion()
	{
		return android.os.Build.VERSION.RELEASE;
	}
	
	public int GetScreenWidth()
	{
		if (activity == null)
			return 0;
		
		Display display = activity.getWindowManager().getDefaultDisplay();
		int realWidth;

		if (Build.VERSION.SDK_INT >= 17){
	        //new pleasant way to get real metrics
	        DisplayMetrics realMetrics = new DisplayMetrics();
	        display.getRealMetrics(realMetrics);
	        realWidth = realMetrics.widthPixels;
	    } else if (Build.VERSION.SDK_INT >= 14) {
	        //reflection for this weird in-between time
	        try {
	            Method mGetRawW = Display.class.getMethod("getRawWidth");
	            realWidth = (Integer) mGetRawW.invoke(display);
	        } catch (Exception e) {
	            //this may not be 100% accurate, but it's all we've got
	            realWidth = display.getWidth();
	        }

	    } else {
	        //This should be close, as lower API devices should not have window navigation bars
	        realWidth = display.getWidth();
	    }
		return realWidth;
	}

	public int GetScreenHeight()
	{
		if (activity == null)
			return 0;
		
		Display display = activity.getWindowManager().getDefaultDisplay();
		int realHeight;
		
		if (Build.VERSION.SDK_INT >= 17){
	        //new pleasant way to get real metrics
	        DisplayMetrics realMetrics = new DisplayMetrics();
	        display.getRealMetrics(realMetrics);

	        realHeight = realMetrics.heightPixels;
	        
	        System.out.println("realHeight : " + realHeight + " - SDK17"); 

	    } else if (Build.VERSION.SDK_INT >= 14) {
	        //reflection for this weird in-between time
	        try {
	            Method mGetRawH = Display.class.getMethod("getRawHeight");
	            realHeight = (Integer) mGetRawH.invoke(display);
	            System.out.println("realHeight : " + realHeight + " - SDK14");
	        } catch (Exception e) {
	            //this may not be 100% accurate, but it's all we've got
	            realHeight = display.getHeight();
	            System.out.println("realHeight : " + realHeight + " - SDK14 ERR");
	        }

	    } else {
	        //This should be close, as lower API devices should not have window navigation bars
	        realHeight = display.getHeight();
	        
	        System.out.println("realHeight : " + realHeight + " - NO MATCHING");
	    }
		return realHeight;
	}
	
	public void initEditTextField()
	{
		if (activity == null)
			return;
		
		CustomEditTextField.instance().init(activity);
	}
	
	public void ShowEditTextField(String _text)
	{
		if (activity == null)
			return;
		
		CustomEditTextField.instance().ShowEditTextFieldWithSoftKeyboard(_text);
	}
	
	public void HideEditTextField()
	{
		if (activity == null)
			return;
		
		CustomEditTextField.instance().HideEditTextField();
	}
	
	public void ReleaseEditTextField()
	{
		if (activity == null)
			return;
		
		CustomEditTextField.instance().ReleaseTextField();
	}
	
	public void RegisterAlarm(int millis, String msg, int repeat)
    {
		RegisterAlarm(millis, msg, repeat, 0);
    }

    public void RegisterAlarm(int millis, String msg, int repeat, int idx)
    {
        if(millis < 60000 && repeat == 1)
        {
            System.out.println("Alarm Error : Too Short Time!! if repeat is ALARM_REPEAT_ON, Input long time than 1 minutes!");
            return;
        } 
        else
        {
        	Context context = (Context)activity;
            Intent intent = new Intent(context, AlarmReceiver.class);
            intent.putExtra("msg", msg);
            intent.putExtra("repeat", repeat);
            intent.putExtra("setTime", millis);
            PendingIntent sender = PendingIntent.getBroadcast(context, idx, intent, PendingIntent.FLAG_UPDATE_CURRENT);
            AlarmManager am = (AlarmManager)context.getSystemService(Context.ALARM_SERVICE);
            am.set(AlarmManager.ELAPSED_REALTIME, System.currentTimeMillis() + (long)millis, sender);
            return;
        }
    }

    public void UnregisterAlarm()
    {
    	UnregisterAlarm(0);
    }

    public void UnregisterAlarm(int idx)
    {
    	Context context = (Context)activity;
    	
        AlarmManager am = (AlarmManager)context.getSystemService(Context.ALARM_SERVICE);
        Intent in = new Intent(context, AlarmReceiver.class);
        PendingIntent pender = PendingIntent.getBroadcast(context, idx, in, PendingIntent.FLAG_UPDATE_CURRENT);
        am.cancel(pender);
    }

    public void CallSMSForShare()
	{
		Intent sharingIntent = new Intent(Intent.ACTION_SEND);
		sharingIntent.setType("text/plain");      // 고정 text
		sharingIntent.putExtra(Intent.EXTRA_TEXT, "hello~ shareText here");
		sharingIntent.setPackage("com.kakao.talk");   // 고정 text
		getActivity().startActivity(sharingIntent);
		return;
	}
}
