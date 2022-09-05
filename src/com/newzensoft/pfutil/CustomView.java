package com.newzensoft.pfutil;

import static org.cocos2dx.lib.Cocos2dxHelper.getActivity;

import android.view.WindowManager;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.net.Uri;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.view.MotionEvent;
import android.view.View.OnTouchListener;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewManager;
import android.view.inputmethod.InputMethodManager;
import android.webkit.WebChromeClient;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.AbsoluteLayout;
import android.widget.Button;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;


public class CustomView {
    public View 	 m_View;
    public static CustomView CV;
    Context m_context;
    public int x;
    public int y;
    public int width;
    public int height;
    public Handler m_ShowHandler;
    public Handler m_HideHandler;
    public Handler m_ReleaseHandler;
    public Handler m_InitHandler;
    private String URL_FOR_CP = "poker_web/adultcheck/adultcheckplus.jsp?";
    private String URL_FOR_IPIN = "poker_web/adultcheck/adultipincheck.jsp?";



    public CustomView(){
        if(m_ShowHandler == null){
            m_ShowHandler = new Handler(Looper.getMainLooper()) {
                @SuppressWarnings("deprecation")
                public void handleMessage(Message msg) {
                    System.out.println("custom view  visible!!!!!!");
                    m_View.setVisibility(View.VISIBLE);


                    m_View.setEnabled(true);
                }
            };
        }

        if(m_HideHandler == null){
            m_HideHandler = new Handler(Looper.getMainLooper()) {
                @SuppressWarnings("deprecation")
                public void handleMessage(Message msg) {


                }
            };
        }

        if(m_ReleaseHandler == null){
            m_ReleaseHandler = new Handler(Looper.getMainLooper()){
                @SuppressWarnings("deprecation")
                public void handleMessage(Message msg) {

                    m_ShowHandler = null;
                    m_HideHandler = null;
                    m_ReleaseHandler = null;

                }
            };
        }

        if(m_InitHandler == null){
            m_InitHandler = new Handler(Looper.getMainLooper()){
                @SuppressWarnings("deprecation")
                public void handleMessage(Message msg)
                {
                    Activity activity = (Activity)m_context;
                    activity.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);

                    int viewId = activity.getResources().getIdentifier("custom_authselect", "layout", activity.getPackageName());
                    m_View = activity.getLayoutInflater().inflate(viewId, null);

                    activity.addContentView(m_View, new ViewGroup.LayoutParams(	AbsoluteLayout.LayoutParams.FILL_PARENT, AbsoluteLayout.LayoutParams.FILL_PARENT));

                    int btn1 = activity.getResources().getIdentifier("button_SAsuth", "id", activity.getPackageName());
                    Button button_checkplus = (Button) activity.findViewById(btn1) ;
                    button_checkplus.setOnClickListener(new Button.OnClickListener() {
                        @Override
                        public void onClick(View view) {
                            String realUrl = PFUtil.getRequestURL_For_Auth() +URL_FOR_CP + "uid=" + PFUtil.getUID_For_Auth() + "&ip=" + PFUtil.getIP_For_Auth();
                            CustomWebView.instance().init(activity,realUrl,0,0,m_View.getWidth(),m_View.getHeight());
                            DeleteView();
                        }
                    });

                    int btn2 = activity.getResources().getIdentifier("button_ipin", "id", activity.getPackageName());
                    Button button_ipin = (Button) activity.findViewById(btn2) ;
                    button_ipin.setOnClickListener(new Button.OnClickListener() {
                        @Override
                        public void onClick(View view) {
                            //Send ipin Req
                            String realUrl = PFUtil.getRequestURL_For_Auth() +URL_FOR_IPIN + "uid=" + PFUtil.getUID_For_Auth() + "&ip=" + PFUtil.getIP_For_Auth();
                            System.out.println("realUrl = " +realUrl);
                            CustomWebView.instance().init(activity,realUrl,0,0,m_View.getWidth(),m_View.getHeight());
                        }
                    });

                    showView();
                };
            };
        }
    }

    public static CustomView Instance(){
        if (CV == null)
            CV = new CustomView();

        return CV;
    }

    public void InitView(Activity activity, final int X, final int Y, final int Width, final int Height){
        m_context = activity;
        x = X;
        y = Y;
        width = Width;
        height = Height;

        Message msg = m_InitHandler.obtainMessage();
        m_InitHandler.sendMessage(msg);

    }

    public void showView(){
        if(m_ShowHandler == null || CV == null)
            return;

        Message msg = m_ShowHandler.obtainMessage();
        m_ShowHandler.sendMessage(msg);
    }

    public void DeleteView(){
        if(m_View != null)
        {
            System.out.println("DeleteView = "+ m_View.toString());
            ((ViewManager)this.m_View.getParent()).removeView(this.m_View);
        }
    }

}
