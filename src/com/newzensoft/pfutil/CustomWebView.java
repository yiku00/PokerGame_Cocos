package com.newzensoft.pfutil;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.ActivityNotFoundException;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.graphics.Bitmap;
import android.net.Uri;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.View.OnTouchListener;
import android.view.ViewManager;
import android.webkit.WebChromeClient;
import android.webkit.WebResourceError;
import android.webkit.WebResourceRequest;
import android.webkit.WebResourceResponse;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.AbsoluteLayout;
import android.widget.AbsoluteLayout.LayoutParams;
import android.widget.LinearLayout;
import android.content.Context;

import java.net.URISyntaxException;


public class CustomWebView
{
	public Handler m_ShowHandler;
	public Handler m_HideHandler;
	public Handler m_ReleaseHandler;
	public Handler m_InitHandler;
	public Handler m_DeleteHandler;

	public WebView m_WebView;
	public View 	 m_View;

	public String url;
	
	int x, y, width, height;
	boolean isShow;
	
	Context m_context;
	
	private static CustomWebView cwView;


	public static native void OnAuthFinished();

	public CustomWebView()
	{

	}
	
	public static CustomWebView instance()
	{
		if (cwView == null)
			cwView = new CustomWebView();
		
		return cwView;
	}
	
	public void init(Activity activity, String setURL, final int X, final int Y, final int Width, final int Height)
	{
		m_context = (Context)activity;
		this.url = setURL;
		
		m_ShowHandler = new Handler(Looper.getMainLooper()) {
			@SuppressWarnings("deprecation")
			public void handleMessage(Message msg) {
				// setAdvertise();
				System.out.println("custom web view  visible!!!!!!");
				if (m_WebView != null)
				{
					m_WebView.setVisibility(View.VISIBLE);
					isShow = true;
				}

			}
		};
	 	m_HideHandler = new Handler(Looper.getMainLooper()) {
			@SuppressWarnings("deprecation")
			public void handleMessage(Message msg) {
				// setAdvertise();
				// System.out.println("message visible");
				if (m_WebView != null)
				{
					m_WebView.setVisibility(View.GONE);
					isShow = false;
				}

			}
		};
		
		m_ReleaseHandler = new Handler(Looper.getMainLooper()){
			@SuppressWarnings("deprecation")
			public void handleMessage(Message msg) {
				if (m_WebView != null)
					m_WebView.setVisibility(View.GONE);
				m_ShowHandler = null;
				m_HideHandler = null;
				m_ReleaseHandler = null;
				m_WebView	  = null;
			}
		};
		m_DeleteHandler = new Handler(Looper.getMainLooper()){
			public void handleMessage(Message msg) {
				DeleteView();
			}
		};
		m_InitHandler = new Handler(Looper.getMainLooper()){
			@SuppressWarnings("deprecation")
			public void handleMessage(Message msg) 
			{
				Activity activity = (Activity)m_context;

				int viewId = activity.getResources().getIdentifier("custom_view", "layout", activity.getPackageName());
				m_View = activity.getLayoutInflater().inflate(viewId, null);

				activity.addContentView(m_View, new ViewGroup.LayoutParams(	LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT));
				
				int webViewId = activity.getResources().getIdentifier("webview", "id", activity.getPackageName());
				m_WebView = (WebView) activity.findViewById(webViewId);

				if(m_WebView == null)
					return;

				m_WebView.getSettings().setJavaScriptEnabled(true); // 웹뷰 내 javascript 이용 여부
				m_WebView.getSettings().setDomStorageEnabled(true); // 웹뷰 내 로컬스토리지 이용 여부
				m_WebView.getSettings().setJavaScriptCanOpenWindowsAutomatically(true); // 웹뷰 내 window.open() 허용 여부
				m_WebView.setHorizontalScrollBarEnabled(true);
				m_WebView.setVerticalScrollBarEnabled(true);
				m_WebView.getSettings().setSupportZoom(true);
				m_WebView.getSettings().setUseWideViewPort(true);
				m_WebView.getSettings().setLoadWithOverviewMode(true);



				m_WebView.clearView();
				
				m_WebView.setFocusable(true); // true하면 Crash



				m_WebView.loadUrl(url);

				m_WebView.setWebViewClient(new WebViewClient() {


					public boolean shouldOverrideUrlLoading(WebView view, String url) {
						if (url.startsWith("intent://")) {
							Intent intent = null;
							try {
								intent = Intent.parseUri(url, Intent.URI_INTENT_SCHEME);
								if (intent != null) {
									m_context.startActivity(intent);
								}
							} catch (URISyntaxException e) {


							} catch (ActivityNotFoundException e) {
								String packageName = intent.getPackage();
								if (!packageName.equals("")) {
									m_context.startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse("market://details?id=" + packageName)));
								}
							}
							return true;
						}else if (url.startsWith("https://play.google.com/store/apps/details?id=") || url.startsWith("market://details?id=")) {
							Uri uri = Uri.parse(url);
							String packageName = uri.getQueryParameter("id");
							if (packageName != null && !packageName.equals("")) {
								// 援ш�留덉폆 �씠�룞
								m_context.startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse("market://details?id=" + packageName)));
							}

							return true;
						}

						return false;

					}

					@Override
					public void onReceivedError(WebView view, int errorCode, String description, String failingUrl) {
						super.onReceivedError(view, errorCode, description,failingUrl);

						switch (errorCode){
							case ERROR_AUTHENTICATION:
								break;
							case ERROR_BAD_URL:
								break;
							case ERROR_CONNECT:
								break;
							case ERROR_FAILED_SSL_HANDSHAKE:
								break;
							case ERROR_FILE:
								break;
							case ERROR_FILE_NOT_FOUND:
								break;
							case ERROR_HOST_LOOKUP:
								break;
							case ERROR_IO:
								break;
							case ERROR_PROXY_AUTHENTICATION:
								break;
							case ERROR_REDIRECT_LOOP:
								break;
							case ERROR_TIMEOUT:
								break;
							case ERROR_TOO_MANY_REQUESTS:
								break;
							case ERROR_UNKNOWN:
								break;
							case ERROR_UNSUPPORTED_AUTH_SCHEME:
								break;
							case ERROR_UNSUPPORTED_SCHEME:
								break;

						}

						System.out.println("WebView Error Code = " + errorCode);
						System.out.println("WebView Error Code = " + errorCode);
						System.out.println("WebView description = " + description);
						System.out.println("WebView failingUrl = " + failingUrl);
					}

					@Override
					public void onReceivedHttpError(WebView view, WebResourceRequest request, WebResourceResponse errorResponse) {
						super.onReceivedHttpError(view, request, errorResponse);
						System.out.println("WebView WebResourceRequest = " + request);
						System.out.println("WebView WebResourceResponse = " + errorResponse);
					}

					@Override
					public void onPageStarted(WebView view, String url, Bitmap favicon) {
						super.onPageStarted(view, url, favicon);
						System.out.println("WebView onPageStarted url= " + url);
						System.out.println("WebView onPageStarted favicon= " + favicon);
					}

					@Override
					public void onPageFinished(WebView view, String url) {
						super.onPageFinished(view, url);
						System.out.println("WebView onPageFinished url= " + url);

						if(url.contains("poker_server/NiceCheckPlusAuthorization") || url.contains("poker_server/NiceAuthorization")) {
							activity.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
							((ViewManager)m_View.getParent()).removeView(m_View);
							CustomView.Instance().DeleteView();
							OnAuthFinished();
						}
					}

					@Override
					public void onReceivedError(WebView view, WebResourceRequest request, WebResourceError error) {
						super.onReceivedError(view, request, error);
						System.out.println("WebView onReceivedError request= " + request);
						System.out.println("WebView onReceivedError error= " + error);
					}

					@Override
					public void onFormResubmission(WebView view, Message dontResend, Message resend) {
						super.onFormResubmission(view, dontResend, resend);
						System.out.println("WebView onFormResubmission dontResend= " + dontResend);
						System.out.println("WebView onFormResubmission resend= " + resend);
					}
				});
				
				m_WebView.setWebChromeClient(new WebChromeClient() {	//�˾�â
					   
					   @Override
					   public boolean onJsAlert(WebView view, String url, String message, final android.webkit.JsResult result){
					      new AlertDialog.Builder(view.getContext())
					         .setTitle("�޼���")
					         .setMessage(message)
					         .setPositiveButton(android.R.string.ok,
					               new AlertDialog.OnClickListener(){
									public void onClick(DialogInterface dialog,
											int which) {
										// TODO Auto-generated method stub

										 result.confirm();

									}
					               })
					         .setCancelable(true)
					         .create()
					         .show();
						   System.out.println("WebView onJsAlert message= " + message);
						   System.out.println("WebView onJsAlert url= " + url);
					      return true;
					   };
					   
					   @Override
					   public boolean onJsConfirm(WebView view, String url, String message, final android.webkit.JsResult result){
					      new AlertDialog.Builder(view.getContext())
					         .setTitle("�޼���")
					         .setMessage(message)
					         .setPositiveButton(android.R.string.ok,
					               new DialogInterface.OnClickListener() {
					                  public void onClick(DialogInterface dialog, int which) {
					                     result.confirm();
					                  }
					               })
					         .setNegativeButton(android.R.string.cancel, new DialogInterface.OnClickListener() {
					                  public void onClick(DialogInterface dialog, int which) {
					                     result.cancel();
					                  }
					               })
					         .create()
					         .show();
						   System.out.println("WebView onJsConfirm message= " + message);
						   System.out.println("WebView onJsConfirm url= " + url);
					      return true;
					   };
					   
					  });
				
				
				m_WebView.setOnTouchListener(new OnTouchListener() { // WebView�� ��ġ �̺�Ʈ

				
					public boolean onTouch(View v, MotionEvent event) {
					 
						switch (event.getAction()) { // ��ġ �̺�Ʈ�� ��� ����

						case MotionEvent.ACTION_DOWN: // ��ġ�� �ϰų�

						case MotionEvent.ACTION_UP: // ��ġ �� ���� ���� ��

							if (!v.hasFocus()) { // WebView�� ��Ŀ���� ������ �ʴٸ�
								// Focus 안씀
								//v.requestFocus(); // WebView�� �θ𿡰� ���� ��Ŀ���� �����ڴٰ�
													// �˸���.
							}

							break;

						}

						return false;

					}

				});

				m_WebView.clearCache(true);
				m_WebView.clearHistory();
				// mWebView.getSettings().setLoadWithOverviewMode(true);
				// mWebView.getSettings().setUseWideViewPort(true);

				m_WebView.setLayoutParams(new AbsoluteLayout.LayoutParams((int)(width), (int)(height), (int)(x), (int)(y)));
							
				m_WebView.setVisibility(View.VISIBLE);
				isShow = true;
			}
		};
		
		x = X;
		y = Y;
		width = Width;
		height = Height;
				
		InitWebView();
	}
	
	public void InitWebView()
	{
		if (m_InitHandler == null)
			return;
		
		Message msg = m_InitHandler.obtainMessage();
		m_InitHandler.sendMessage(msg);
	}
	
	public void ShowWebView()
	{
		if (m_ShowHandler == null)
			return;
		
		Message msg = m_ShowHandler.obtainMessage();
		m_ShowHandler.sendMessage(msg);
		m_WebView.setVisibility(View.VISIBLE);
	}
	
	public void HideWebView()
	{
		if (m_HideHandler == null)
		{
			return;
		}
		
		Message msg = m_HideHandler.obtainMessage();
		m_HideHandler.sendMessage(msg);
		//m_WebView.setVisibility(View.GONE);
	}
	
	public void ReleaseWebView()
	{
		if (m_ReleaseHandler == null)
			return;
		
		Message msg = m_ReleaseHandler.obtainMessage();
		m_ReleaseHandler.sendMessage(msg);
		
		isShow = false;
	}

	public void DeleteView(){
		if(m_View != null)
		{
			System.out.println("DeleteView = "+ m_View.toString());
			((ViewManager)this.m_View.getParent()).removeView(this.m_View);
			//((ViewManager)this.m_WebView.getParent()).removeView(this.m_WebView);
		}
	}
	
	public void loadUrl(String url)
	{
		//m_WebView.clearView();
		//m_WebView.clearCache(true);
		//m_WebView.clearHistory();
		
		m_WebView.loadUrl(url);
	}
	
}
