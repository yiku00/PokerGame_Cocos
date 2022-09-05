package com.newzensoft.gps;

import android.app.Activity;
import android.content.Context;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;

public class GpsManager {
	
	private static GpsManager gpsMgr = null;
	private LocationManager lm;	
	private Activity activity;
	private boolean isPrint = true;
	private double mLongitude = 0.0;
	private double mLatitude = 0.0;
	
	private GpsManager() {		
	}

	public static Object instance() {
		System.out.println("instance 1");
		if (gpsMgr == null) {
			System.out.println("instance 2");
			gpsMgr = new GpsManager();
		}
		System.out.println("instance 3");
		return gpsMgr;
	}
	
	private void println(String string) {
		// TODO Auto-generated method stub
		if (isPrint)
			System.out.println(string);
	}
		
	public void init(Object obj) {
		activity = (Activity) obj;
		Context context = (Context)activity;
		lm = (LocationManager)context.getSystemService(context.LOCATION_SERVICE);
		gpsStart(300);
	}
	
	public double[] getLocation() {
		System.out.println("getLo" + mLongitude + "mLatitude" + mLatitude );
		double[] doubleArray = { mLongitude , mLatitude };
		System.out.println("getLocation 2");		
		System.out.println("getLocation 4");
		return doubleArray;
	}
	
	public double getNowLongitude() {
		return mLongitude;	
	}
	
	public double getNowLatitude() {
		return mLatitude;
	}
	
	public void gpsStart(int millTime) {
		System.out.println("start");
		//millTime default 100
		lm.requestLocationUpdates(LocationManager.GPS_PROVIDER, // ����� ��ġ������
				millTime, // ���������� �ּ� �ð����� (miliSecond)
                1, // ���������� �ּ� ����Ÿ� (m)
                mLocationListener);
        lm.requestLocationUpdates(LocationManager.NETWORK_PROVIDER, // ����� ��ġ������
        		millTime, // ���������� �ּ� �ð����� (miliSecond)
                1, // ���������� �ּ� ����Ÿ� (m)
                mLocationListener);
	}
	
	private final LocationListener mLocationListener = new LocationListener() {
        public void onLocationChanged(Location location) {
            //���⼭ ��ġ���� ���ŵǸ� �̺�Ʈ�� �߻��Ѵ�.
            //���� Location ���·� ���ϵǸ� ��ǥ ��� ����� ������ ����.

        	println("onLocationChanged, location:" + location);
        	mLongitude = location.getLongitude(); //�浵
        	mLatitude = location.getLatitude();   //����
            double altitude = location.getAltitude();   //��
            float accuracy = location.getAccuracy();    //��Ȯ��
            String provider = location.getProvider();   //��ġ������
                                                        //Gps ��ġ�����ڿ� ���� ��ġ��ȭ. ���������� ����.
                                                        //Network ��ġ�����ڿ� ���� ��ġ��ȭ
                                                        //Network ��ġ�� Gps�� ���� ��Ȯ���� ���� ��������.
            //tv.setText("��ġ���� : " + provider + "\n���� : " + longitude + "\n�浵 : " + latitude  + "\n�� : " + altitude + "\n��Ȯ�� : "  + accuracy);
        }
        public void onProviderDisabled(String provider) {
            // Disabled��
        	println("onProviderDisabled, provider:" + provider);
        }

        public void onProviderEnabled(String provider) {
            // Enabled��
        	println("onProviderEnabled, provider:" + provider);
        }

        public void onStatusChanged(String provider, int status, Bundle extras) {
            // �����
        	println("onStatusChanged, provider:" + provider + ", status:" + status + " ,Bundle:" + extras);
        }		
    };
}
