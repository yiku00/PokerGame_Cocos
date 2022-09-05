/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.newzensoft.pfutil;

import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageManager;


import java.util.ArrayList;
import java.util.List;

import android.util.Log;

import androidx.annotation.NonNull;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;


/**
 * This class loads the Java Native Interface (JNI)
 * library, 'libheroad.so', and provides access to the
 * exposed C functions.
 * The library is packaged and installed with the application.
 * See the C file, /jni/heroad.c file for the
 * implementations of the native methods. 
 * 
 * For more information on JNI, see: http://java.sun.com/docs/books/jni/
 */

public class PermissionSupport {
	
	static final String TAG = PermissionSupport.class.getSimpleName();

	private Context context;
	private Activity activity;

	// 요청할 권한을 배열로 저장
	private static String[] permissions = {
		Manifest.permission.GET_ACCOUNTS,
		Manifest.permission.READ_EXTERNAL_STORAGE,
		Manifest.permission.WRITE_EXTERNAL_STORAGE,
		Manifest.permission.RECEIVE_SMS
	};

	private List<String> permissionList;

	private final int MULTIPLE_PERMISSIONS = 1023;

	public PermissionSupport(Activity _activity, Context _context) {
		this.activity = _activity;
		this.context = _context;
	}

	public boolean checkPermission() {
		int result;
		permissionList = new ArrayList<String>();
		
		for(String pm : permissions) {
			result = ContextCompat.checkSelfPermission(context, pm);
			if(result != PackageManager.PERMISSION_GRANTED) {
				permissionList.add(pm);
			}
		}

		if(!permissionList.isEmpty()){
			return false;
		}

		return true;
	}

	public void requestPermission() {
		Log.d(TAG, "requestPermission11");
		ActivityCompat.requestPermissions(activity, permissionList.toArray(new String[permissionList.size()]), MULTIPLE_PERMISSIONS);
	}

	public boolean permissionResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
		if(requestCode == MULTIPLE_PERMISSIONS && (grantResults.length > 0)) {
			for(int i=0;i<grantResults.length;i++) {
				if(grantResults[i] == -1) {
					return false;
				}
			}
		}
		return true;
	}
}