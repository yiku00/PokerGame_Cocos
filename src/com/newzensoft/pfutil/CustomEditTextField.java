package com.newzensoft.pfutil;

import android.app.Activity;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager.LayoutParams;
import android.view.inputmethod.EditorInfo;
import android.view.inputmethod.InputMethod;
import android.view.inputmethod.InputMethodManager;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.TextView.OnEditorActionListener;
import android.content.Context;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.text.Editable;
import android.text.method.KeyListener;

public class CustomEditTextField {

	public Handler m_ShowHandler;
	public Handler m_HideHandler;
	public Handler m_ReleaseHandler;
	public Handler m_InitHandler;
	
	private static CustomEditTextField m_textField;
	
	public View m_View;
	public View focused;
	public LinearLayout m_EditView;
	public CustomEditText m_EditTextField;
	public Button m_EditButton;
	boolean isShow;
	boolean isInit;
	
	public String m_fieldText; 
	
	Context m_context;
	
	static PFUtil m_util;
	

	
	public CustomEditTextField() {
		m_ShowHandler = null;
		m_HideHandler = null;
		m_ReleaseHandler = null;
		m_EditView	  = null;
		focused = null;
		isShow = false;
		isInit = false;
	}
	
	public static CustomEditTextField instance() {
		if(m_textField == null) {
			m_textField = new CustomEditTextField();
		}
		
		return m_textField;
	}
	
	public void init(Activity activity) {
//		System.out.println("!!CALL init customEdit ------------------------------------ !!");
		m_context = (Context)activity;

		focused = activity.getCurrentFocus();

		if(m_ShowHandler == null) {
			m_ShowHandler = new Handler(Looper.getMainLooper()) {
				@SuppressWarnings("deprecation")
				public void handleMessage(Message msg) {
//					System.out.println("!!CALL m_ShowHandler customEdit ------------------------------------ !!");
					if (m_EditView != null)
					{
						m_EditView.setVisibility(View.VISIBLE);
						isShow = true;
						
						m_EditTextField.requestFocus();
						//System.out.println("!!Focus on edit textfield------------------------------------ !!");
						InputMethodManager imm = (InputMethodManager)m_context.getSystemService(Context.INPUT_METHOD_SERVICE);
						imm.toggleSoftInput(InputMethodManager.SHOW_FORCED, InputMethodManager.HIDE_IMPLICIT_ONLY);
						
						//System.out.println("!!SHOW VIEW DONE ------------------------------------ !!");
						m_EditView.setEnabled(true);
						m_View.setEnabled(true);
						
					}
		
				}
			};
		}
		
		if(m_HideHandler == null) {
			m_HideHandler = new Handler(Looper.getMainLooper()) {
				@SuppressWarnings("deprecation")
				public void handleMessage(Message msg) {
//					System.out.println("!!CALL m_HideHandler customEdit ------------------------------------ !!");
					if (m_EditView != null)
					{
						m_EditView.setVisibility(View.GONE);
						isShow = false;
						
						if(focused != null)
						{
							//System.out.println("!!HIDE VIEW DONE ------------------------------------ !!");
							m_EditView.setEnabled(false);
							m_View.setEnabled(false);
							focused.requestFocus();
						}
						
						InputMethodManager imm = (InputMethodManager)m_context.getSystemService(Context.INPUT_METHOD_SERVICE);
						imm.hideSoftInputFromWindow(m_View.getWindowToken(), 0);
						
						int versionId = android.os.Build.VERSION.SDK_INT;
						if(versionId >= 14)
						{
							int _uiOption = View.SYSTEM_UI_FLAG_HIDE_NAVIGATION;
							if(versionId >= 16)
								_uiOption |= View.SYSTEM_UI_FLAG_FULLSCREEN;
							if(versionId >= 19)
								_uiOption |= View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY;
							
							((Activity)m_context).getWindow().getDecorView().setSystemUiVisibility(_uiOption);	
						}
						
						
							
					}

				}
			};
		}
	 	
		if(m_ReleaseHandler == null) {
			m_ReleaseHandler = new Handler(Looper.getMainLooper()){
				@SuppressWarnings("deprecation")
				public void handleMessage(Message msg) {
//					System.out.println("!!CALL m_ReleaseHandler customEdit ------------------------------------ !!");
					if (m_EditView != null)
						m_EditView.setVisibility(View.GONE);
					m_ShowHandler = null;
					m_HideHandler = null;
					m_ReleaseHandler = null;
					m_EditView	  = null;
					
					if(focused != null)
					{
//						System.out.println("!!RELEASE VIEW DONE ------------------------------------ !!");
						m_EditView.setEnabled(false);
						m_View.setEnabled(false);
						focused.requestFocus();
					}
						
					
				}
			};
		}
		
		if(m_InitHandler == null) {
			m_InitHandler = new Handler(Looper.getMainLooper()){
				@SuppressWarnings("deprecation")
				public void handleMessage(Message msg) 
				{
					if(isInit == false)
					{
//						System.out.println("!!CALL m_InitHandler customEdit ------------------------------------ !!");
						Activity activity = (Activity)m_context;
											
						int viewId = activity.getResources().getIdentifier("custom_textfield", "layout", activity.getPackageName());
						m_View = activity.getLayoutInflater().inflate(viewId, null);
						
						activity.addContentView(m_View, new ViewGroup.LayoutParams(LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT));

						int editViewId = activity.getResources().getIdentifier("edit_textview", "id", activity.getPackageName());
						m_EditView = (LinearLayout)activity.findViewById(editViewId);

						int editTextId = activity.getResources().getIdentifier("edit_textfield", "id", activity.getPackageName());
						System.out.println("activity.findViewById Package = " + activity.findViewById(editTextId).toString());
						m_EditTextField = activity.findViewById(editTextId);
						int buttonId = activity.getResources().getIdentifier("edit_textfield_button", "id", activity.getPackageName());
						m_EditButton = (Button)activity.findViewById(buttonId);

						m_View.setFocusable(true);
						
						m_View.setOnTouchListener(new OnTouchListener() {
							@Override
							public boolean onTouch(View v, MotionEvent event) {
								// no action
								return true;
							}
						});
						
						m_EditTextField.setOnEditorActionListener(new OnEditorActionListener() {
							
							@Override
							public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
								if(actionId == EditorInfo.IME_ACTION_DONE){ // ���� id�� �ĺ�, Ű������ �Ϸ� Ű �Է� ����
									m_fieldText = m_EditTextField.getText().toString();
									PFUtil.SetEditText(m_fieldText);
									
									HideEditTextField();
									
//									System.out.println("!!KEY DOWN ACTION DONE ------------------------------------ !!");
						        }								
								return false;
							}
						});
						
						m_EditButton.setOnClickListener(new OnClickListener() {
							
							@Override
							public void onClick(View v) {
								m_fieldText = m_EditTextField.getText().toString();
								PFUtil.SetEditText(m_fieldText);
								
								HideEditTextField();
								
//								System.out.println("!!KEY DOWN BUTTON DONE ------------------------------------ !!");
							}
						});
						
						isInit = true;
					}
										
					ShowEditTextField();
				}
			};
		}	
	}

	public void ShowEditTextFieldWithSoftKeyboard(String text) {

		m_fieldText = text;
		initTextField();
	}
	
	public void ShowEditTextField()
	{
//		System.out.println("!!CALL ShowEditTextFieldWithSoftKeyboard customEdit ------------------------------------ !!");
		if(m_ShowHandler == null) {
			return;
		}
		
		if(m_EditTextField == null) {
			return;
		}
//		System.out.println("!!complete ShowEditTextFieldWithSoftKeyboard customEdit ------------------------------------ !!");
		
		isShow = true;
				
		m_EditTextField.setText(m_fieldText);
		Message msg = m_ShowHandler.obtainMessage();
		m_ShowHandler.sendMessage(msg);
	}
	
	public void HideEditTextField()	{
//		System.out.println("!!CALL HideEditTextField customEdit ------------------------------------ !!");
		if (m_HideHandler == null)
			return;
//		System.out.println("!!complete HideEditTextField customEdit ------------------------------------ !!");
		Message msg = m_HideHandler.obtainMessage();
		m_HideHandler.sendMessage(msg);
	}
	
	public void ReleaseTextField() {
//		System.out.println("!!CALL ReleaseTextField customEdit ------------------------------------ !!");
		if (m_ReleaseHandler == null)
			return;
//		System.out.println("!!complete ReleaseTextField customEdit ------------------------------------ !!");
		Message msg = m_ReleaseHandler.obtainMessage();
		m_ReleaseHandler.sendMessage(msg);
	}
	
	public void initTextField() {
//		System.out.println("!!CALL initTextField ------------------------------------ !!");
		
		if (m_InitHandler == null)
			return;
//		System.out.println("!!complete initTextField customEdit ------------------------------------ !!");
		
		Message msg = m_InitHandler.obtainMessage();
		m_InitHandler.sendMessage(msg);
	}
	
}
