package com.newzensoft.pfutil;
import android.content.Context;
import android.util.AttributeSet;
import android.view.KeyEvent;
import android.widget.EditText;

public class CustomEditText extends EditText {

	private OnBackPressListener _listener;
	     
	     
    public CustomEditText(Context context)
    {
        super(context);
    }
     
     
    public CustomEditText(Context context, AttributeSet attrs)
    {
        super(context, attrs);
    }
     
     
    public CustomEditText(Context context, AttributeSet attrs, int defStyle)
    {
        super(context, attrs, defStyle);
    }
     
     
    @Override
    public boolean onKeyPreIme(int keyCode, KeyEvent event)
    {
        if (keyCode == KeyEvent.KEYCODE_BACK)
        {
        	System.out.println("!!EVENT KEY BACK ------------------------------------ !!");
        	((PFUtil)PFUtil.instance()).HideEditTextField();
            return false;
        }
         
        return super.onKeyPreIme(keyCode, event);
    }
       
    public interface OnBackPressListener
    {
        public void onBackPress();
    }	

}