package com.newzensoft.nx;

import static org.cocos2dx.lib.Cocos2dxHelper.getActivity;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.app.AlarmManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.media.MediaDrm;
import android.media.UnsupportedSchemeException;
import android.net.Uri;
import android.os.AsyncTask;
import android.provider.Settings;
import android.text.ClipboardManager;
import android.widget.Toast;

import java.io.IOException;
import java.util.UUID;

import org.json.JSONObject;
import org.json.JSONException;

//import com.crittercism.app.Crittercism;

import com.google.android.gms.ads.identifier.AdvertisingIdClient;
import com.google.android.gms.common.GooglePlayServicesNotAvailableException;
import com.google.android.gms.common.GooglePlayServicesRepairableException;

import java.util.UUID;
import java.util.HashMap;
import java.util.Calendar;
import java.util.concurrent.ExecutionException;

//import ly.count.android.api.Countly;

public class Helper {

	private static Activity mActivity;
	private ClipboardManager mClipboardManager;

	public Helper(Activity activity) {
		mActivity = activity;
		mClipboardManager = (ClipboardManager)mActivity.getSystemService(Context.CLIPBOARD_SERVICE);
	}

	public static Object getActivityObject() { return mActivity; }

	public void openURL(String url) { 
        Intent i = new Intent(Intent.ACTION_VIEW);  
        i.setData(Uri.parse(url));
        mActivity.startActivity(i);
    }

	public void setClipboardText(String text) {
		mClipboardManager.setText(text);
	}

	public void setLocalNotification(int tag, int interval, String msg) {
        PendingIntent sender = getPendingIntent(tag, msg);
		if (null == sender)
			return;

        Calendar calendar = Calendar.getInstance();
        calendar.setTimeInMillis(System.currentTimeMillis());
        calendar.add(Calendar.SECOND, interval);

        AlarmManager am = (AlarmManager)mActivity.getSystemService(Context.ALARM_SERVICE);
        am.set(AlarmManager.RTC_WAKEUP, calendar.getTimeInMillis(), sender);
	}

	public void clearLocalNotification(int tag) {
		PendingIntent sender = getPendingIntent(tag, null);
		if (null == sender)
			return;

        AlarmManager am = (AlarmManager)mActivity.getSystemService(Context.ALARM_SERVICE);
        am.cancel(sender);
	}

	private PendingIntent getPendingIntent(int tag, String msg) {
		/*try {
			Intent i = new Intent(mActivity.getApplicationContext(), LocalNotificationReceiver.class);
			i.putExtra("notification_id", tag);
			i.putExtra("message", msg);
			PendingIntent sender = PendingIntent.getBroadcast(mActivity, tag, i, PendingIntent.FLAG_UPDATE_CURRENT);
			return sender;
		}
		catch (Exception e) {
			return null;
		}*/
		
		return null;
    }

	public static void critterSetUsername(String name) {
		//Crittercism.setUsername(name);
	}

	public static void critterSetMetadata(String key, String val) {
/*		
	try {
			JSONObject metadata = new JSONObject();
			// add arbitrary metadata
			metadata.put(key, val);
			Crittercism.setMetadata(metadata);
		}
		catch (JSONException e) {
			Crittercism.logHandledException(e);
		}
*/
	}

	public static void critterLeaveBreadcrumb(String crumb) {
		//Crittercism.leaveBreadcrumb(crumb);
	}

	public String gvGetUUID() throws ExecutionException, InterruptedException {
		System.out.println("gvGetUUID");
		AsyncTask<Void, Void, String> taskAdId = new AsyncTask<Void, Void, String>() {
			@Override
			protected String doInBackground(Void... params) {
				AdvertisingIdClient.Info idInfo = null;

				try {
					idInfo = AdvertisingIdClient.getAdvertisingIdInfo(getActivity().getApplicationContext());
				} catch (Exception e) {
					e.printStackTrace();
					System.out.println("ExceptionMessage: " + e.getMessage());
				}
				String deviceUuid = null;
				try{
					deviceUuid = idInfo.getId();
					System.out.println("TAG "+ "GAID:"+ deviceUuid);
				}catch (NullPointerException e){
					e.printStackTrace();
					System.out.println("ExceptionMessage2: " + e.getMessage());
				}
				return deviceUuid;
			}

			@Override
			protected void onPostExecute(String strAdId) {
				super.onPostExecute(strAdId);
				System.out.println("GAID: "+ strAdId);
			}
		};

		String result = taskAdId.execute().get();
		System.out.println("GetUUID deviceUuid = " + result);
		return result;
	}

	public static void countlyEvent(String key, int count) {
		//Countly.sharedInstance().recordEvent(key, count);
	}

	public static void countlyEvent(String key, int count, HashMap<String, String> seg) {
		//Countly.sharedInstance().recordEvent(key, seg, count);
	}

	public static void countlyEvent(String key, int count, double sum) {
		//Countly.sharedInstance().recordEvent(key, count, sum);
	}

	public static void countlyEvent(String key, int count, double sum, HashMap<String, String> seg) {
		//Countly.sharedInstance().recordEvent(key, seg, count, sum);
	}

//	public static void countlyFlush() {
//		Countly.sharedInstance().flush();
//	}
}
