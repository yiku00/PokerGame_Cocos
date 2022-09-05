// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   AlarmReceiver.java

package com.newzensoft.pfutil;

import java.net.URLDecoder;
import java.util.List;

import android.app.ActivityManager;
import android.app.AlarmManager;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.os.Bundle;
import android.util.Log;
import android.widget.Toast;
import dalvik.system.PathClassLoader;

// Referenced classes of package com.c2dm:
//            C2DMReceiver

public class AlarmReceiver extends BroadcastReceiver
{

    public AlarmReceiver()
    {
    }

    public void onReceive(Context context, Intent intent)
    {
        String msg;
        int repeat;
        int time;
        Bundle bundle;
        Boolean viewToast;
        Boolean viewNoti;
        Bundle rcvBundle = intent.getExtras();
        msg = (String)rcvBundle.get("msg");
        repeat = rcvBundle.getInt("repeat");
        time = rcvBundle.getInt("setTime");
        ApplicationInfo ai;
        try
        {
            //System.out.println(context.getPackageName());
            ai = context.getPackageManager().getApplicationInfo(context.getPackageName(), 128);
        }
        catch(android.content.pm.PackageManager.NameNotFoundException e)
        {
            return;
        }
        bundle = ai.metaData;
        viewToast = Boolean.valueOf(bundle.getBoolean("c2dm_view_toast"));
        viewNoti = Boolean.valueOf(bundle.getBoolean("c2dm_view_noti"));
        ActivityManager am = (ActivityManager)context.getSystemService("activity");
        List taskInfo = am.getRunningTasks(1);
        ComponentName topActivity = ((android.app.ActivityManager.RunningTaskInfo)taskInfo.get(0)).topActivity;
        String strClass = topActivity.getClassName();
        boolean isCurrentActivity = strClass.indexOf(context.getPackageName()) >= 0;
        String text;
        
        try
        {
        	text = URLDecoder.decode(intent.getStringExtra("msg"), "ksc5601");
        	//System.out.println(text);
        }
        catch (Exception e)
        {
        	System.out.println(e);
        	return;
        }
        			
        Intent amIntent;
        if(viewToast.booleanValue())
            Toast.makeText(context, text, 1000).show();
        String packageName = context.getPackageName();
        //System.out.println((new StringBuilder("packageName : ")).append(packageName).toString());
        int iconIndex;
        String title;
        Class mainClass;
        try
        {
            title = bundle.getString("c2dm_title");
            //System.out.println((new StringBuilder("c2dm_title")).append(title).toString());
            String sMainClass = bundle.getString("c2dm_main_class");
            //System.out.println((new StringBuilder("c2dm_main_class")).append(sMainClass).toString());
            String apkName = context.getPackageManager().getApplicationInfo(packageName, 0).sourceDir;
            //System.out.println((new StringBuilder("apkName : ")).append(apkName).toString());
            PathClassLoader myClassLoader = new PathClassLoader(apkName, ClassLoader.getSystemClassLoader());
            if(sMainClass.indexOf(".") >= 0)
                mainClass = Class.forName(sMainClass, false, myClassLoader);
            else
                mainClass = Class.forName((new StringBuilder(String.valueOf(packageName))).append(".").append(sMainClass).toString(), false, myClassLoader);
            //System.out.println(mainClass.toString());
            String iconStr = bundle.getString("c2dm_icon_name");
            String iconFolder = bundle.getString("c2dm_icon_folder");
            
            //System.out.println("cccccccccccc " + iconStr + "::" + iconFolder);
            if(iconStr == null)
                iconStr = "icon";
            if(iconFolder == null)
                iconFolder = "drawable";
            iconIndex = context.getResources().getIdentifier(iconStr, iconFolder, context.getPackageName());
        }
        catch(Exception e)
        {
            System.out.println(e);
            iconIndex = -1;
            title = null;
            mainClass = null;
        }
        if(title != null)
        {
            if(viewNoti.booleanValue())
            {
                String ns = "notification";
                NotificationManager notiManager = (NotificationManager)context.getSystemService(ns);
                CharSequence ticker = msg;
                /*
                Notification notification = new Notification(iconIndex, ticker, System.currentTimeMillis());
                */
                Context context2 = context.getApplicationContext();
                CharSequence contentTitle = title;
                CharSequence contentText = msg;
                
                Intent notificationIntent = new Intent(context, mainClass);
                notificationIntent.addFlags(0x34000000);
                PendingIntent contentIntent = PendingIntent.getActivity(context2, 1, notificationIntent, 0);
                
                Notification.Builder builder = new Notification.Builder(context2)
                		.setContentIntent(contentIntent)
                        .setSmallIcon(iconIndex)
                        .setContentTitle(contentTitle)
                        .setContentText(contentText)
                        .setDefaults(Notification.DEFAULT_SOUND | Notification.DEFAULT_VIBRATE)
                        .setTicker(ticker);
                Notification notification = builder.build();
                
                /*
                notification.setLatestEventInfo(context2, contentTitle, contentText, contentIntent);
                
                notification.defaults |= 2;
                notification.defaults |= 1;
                notification.flags |= 0x10;
                */
                
                notiManager.notify(1, notification);
            }
        } else
        {
            Log.e("ALARM Error", "Not Exist Title Name!");
        }
        
        if (repeat == 0)
        	return;

        amIntent = new Intent(context, AlarmReceiver.class);
        amIntent.putExtra("msg", msg);
        amIntent.putExtra("repeat", repeat);
        amIntent.putExtra("setTime", time);
        if(time < 60000)
        {
            System.out.println("Alarm Error : Too Short Time!! if repeat is ALARM_REPEAT_ON, Input long time than 1 minutes!");
            return;
        }
        try
        {
            PendingIntent sender = PendingIntent.getBroadcast(context, 0, amIntent, 0x8000000);
            AlarmManager am1 = (AlarmManager)context.getSystemService("alarm");
            am1.set(0, System.currentTimeMillis() + (long)time, sender);
        }
        catch(Exception e)
        {
            Log.e("ALARM Error", "handleMessage Error!");
            System.out.println(e);
        }
    }
}
