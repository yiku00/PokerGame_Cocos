package com.newzensoft.inApp;


import static org.cocos2dx.lib.Cocos2dxHelper.getActivity;

import com.gaa.sdk.iap.AcknowledgeListener;
import com.gaa.sdk.iap.AcknowledgeParams;
import com.gaa.sdk.iap.ConsumeListener;
import com.gaa.sdk.iap.ConsumeParams;
import com.gaa.sdk.iap.IapResult;
import com.gaa.sdk.iap.IapResultListener;
import com.gaa.sdk.iap.ProductDetail;
import com.gaa.sdk.iap.ProductDetailsListener;
import com.gaa.sdk.iap.ProductDetailsParams;
import com.gaa.sdk.iap.PurchaseClient;
import com.gaa.sdk.iap.PurchaseClientStateListener;
import com.gaa.sdk.iap.PurchaseData;
import com.gaa.sdk.iap.PurchaseFlowParams;
import com.gaa.sdk.iap.PurchasesListener;
import com.gaa.sdk.iap.PurchasesUpdatedListener;
import com.gaa.sdk.iap.RecurringProductListener;
import com.gaa.sdk.iap.RecurringProductParams;
import com.gaa.sdk.iap.StoreInfoListener;


/*import com.skplanet.dodo.IapPlugin;
import com.skplanet.dodo.IapResponse;
import com.skplanet.dodo.helper.PaymentParams;
import com.skplanet.dodo.helper.PaymentParams.Builder;*/

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.DialogInterface;
import android.content.SharedPreferences;
import android.os.Handler;
import android.os.StrictMode;
import android.util.Log;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Random;
import java.util.Set;


import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;


public class IapManager extends AppCompatActivity implements PurchasesUpdatedListener {

	private final String TAG = IapManager.class.getSimpleName();
	private List<ProductDetail> skuDetailsList = new ArrayList<>();

	private Activity mActivity;
	private PurchaseClient mPurchaseClient;
	private ProgressDialog mProgressDialog;
	private static IapManager iapMgr = null;

	private Set<String> mTokenToBe;
	private boolean isServiceConnected;

	public static native void OnIapResult(boolean sucess , String errMsg , String tid , String ToServToken, String pid);
	//public static native void OnIapRemainResult(boolean sucess , String errMsg , String tid , String ToServToken, String pid);
	/*public static native String CallPurchaseStart(String pid);*/

	private static String ToServTID ="";
	private static String globalTID="";
	private static String GProducerName="";
	private static String PdToken="";
	public String url = "";
	public String data = "";
	public Boolean Check_Payment = false;
	public Boolean Repay_Flag = false;



	public static Object instance() {
		System.out.println("instance 1");
		getActivity().runOnUiThread(new Runnable() {
			public void run() {
				if (iapMgr == null) {
					System.out.println("instance 2");
					iapMgr = new IapManager(getActivity());
				}
				System.out.println("instance 3");
			}
		});

		while(true) {
			if (iapMgr != null){
				System.out.println("instance 4");
				return iapMgr;
			}

		}

	}

	public IapManager(@NonNull Activity activity) {
		StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
		StrictMode.setThreadPolicy(policy);
		mActivity = activity;

		mPurchaseClient = PurchaseClient.newBuilder(activity)
				.setBase64PublicKey(null)
				.setListener(this)
				.build();
		Log.d(TAG, "before setup");
		startConnection(new Runnable() {  //????????? ???????????? ???????????? ????????? ?????? ??????
			@Override
			public void run() {
				onPurchaseClientSetupFinished();
				Log.d(TAG, "Setup successful. Querying inventory.");
				queryPurchasesAsync();
			}
		});
	}

	public void startConnection(final Runnable executeOnSuccess) {
		mPurchaseClient.startConnection(new PurchaseClientStateListener() {

			@Override
			public void onSetupFinished(IapResult iapResult) {
				Log.e(TAG, " setup END!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ");

				if (iapResult.isSuccess()) {  //the purchasesclient is ready   , you can query purchases here
					Log.e(TAG, " @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@iapResult isSUccess @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");

					isServiceConnected = true;
					//????????? ?????? ?????? ????????????
					/*showBuyProductDialog();*/

/*					if (executeOnSuccess != null) {
						executeOnSuccess.run();
					}*/

					queryProductDetailsAsync();
					return;
				}

				new Handler().postDelayed(new Runnable() {
					@Override
					public void run() {
						handleErrorCode(iapResult);
					}
				}, 300);
			}

			@Override
			public void onServiceDisconnected() {    // ???????????? ????????????
				Log.e(TAG,"Log Has Disconnect");
				isServiceConnected = false;
			}
		});
	}


	public void onPurchaseClientSetupFinished() {
		iapMgr.getStoreCode(new StoreInfoListener() {
			@Override
			public void onStoreInfoResponse(IapResult iapResult, String storeCode) {
				if (iapResult.isSuccess()) {
					Log.d(TAG, "onPurchaseClientSetupFinished: storeCode: " + storeCode);
					saveStoreCode(storeCode);
				}
			}
		});
	}
	@Override
	protected void onDestroy() {
		Log.d(TAG, " onDestroy has Activate! ");
		super.onDestroy();
		if (mPurchaseClient != null) {
			mPurchaseClient.endConnection();
			mPurchaseClient = null;
		}
	}

	private void queryProductDetailsAsync()
	{
		List<String> strList = new ArrayList<>();
		strList.add("m_ruby_01");
		strList.add("ruby_01");
		strList.add("ruby_02");
		strList.add("ruby_03");
		strList.add("ruby_04");
		strList.add("ruby_05");
		strList.add("jackpot_01");
		strList.add("jackpot_02");
		strList.add("made_01");
		strList.add("made_02");
		strList.add("allin_01");
		strList.add("allin_02");
		strList.add("onetime_01");
		ProductDetailsParams params = ProductDetailsParams.newBuilder()
				.setProductIdList(strList)
				.setProductType(PurchaseClient.ProductType.INAPP)
				.build();


		//??????????????? ????????? ????????? ???????????? ???????????? ?????????????????????, ???????????????.  ==>??????
		mPurchaseClient.queryProductDetailsAsync(params, new ProductDetailsListener(){
			@Override
			public void onProductDetailsResponse(IapResult iapResult, @Nullable List<ProductDetail> list) {
				Log.d(TAG, iapResult.toJsonString());
				/*buyProduct(list.get(1).getProductId());*/  //??????????????? ??? id ?????? ????????? ????????? ??????????????? ?????? ??????????????????.
				Log.d(TAG, " iam in the queryProductDetailsAsyncqueryProductDetailsAsyncqueryProductDetailsAsyncqueryProductDetailsAsyncqueryProductDetailsAsync ");
				Check_Payment = true;
			}
		});
	}



	private void buyProduct(final String productId,final String ProducerName, final String productTid) {

		while(true)
		{
			if(iapMgr.Check_Payment) {
				Check_Payment = false;
				break;
			}
		}

		ToServTID = productTid;
		GProducerName = ProducerName;
		Log.d(TAG, " I Am in buy product method!!!! ");
		Log.d(TAG, "buyProduct() - productId:" + productId + " ProducerName " + ProducerName);

		String devPayload = generatePayload();
		ProductDetail sku = getSkuDetail(productId);

		Log.d(TAG, " I Am in buy product method22222222222222222222 ");

/*		savePayloadString(devPayload);
		showProgressDialog();*/
		Log.d(TAG, " I Am in buy product method33333333333333333333333 ");
		PurchaseFlowParams params = PurchaseFlowParams.newBuilder()
				.setProductId(productId)
				.setProductType(PurchaseClient.ProductType.INAPP)
				.setDeveloperPayload(devPayload)
				.setPromotionApplicable(false)
				.build();
		launchPurchaseFlow(params);
	}


	private ProductDetail getSkuDetail(String pid) {
		for(ProductDetail item : skuDetailsList) {
			if(item.getProductId().equals(pid)) {
				return item;
			}
		}
		return null;
	}


	private void executeServiceRequest(Runnable runnable) {
		if (isServiceConnected) {
			runnable.run();
		} else {
			startConnection(runnable);
		}
	}

	private void handleErrorCode(IapResult iapResult) {
		if(iapResult.isSuccess()){
			Log.w(TAG, "the purchase is ready. we can query at here");
		}

		else if (iapResult.getResponseCode() == PurchaseClient.ResponseCode.RESULT_NEED_LOGIN) {
			Log.w(TAG, "handleErrorCode() RESULT_NEED_LOGIN");
			onNeedLogin();
		} else if (iapResult.getResponseCode() == PurchaseClient.ResponseCode.RESULT_NEED_UPDATE) {
			Log.w(TAG, "handleErrorCode() RESULT_NEED_UPDATE");
			onNeedUpdate();
		} else {
			String message = iapResult.getMessage() + "(" + iapResult.getResponseCode() + ")";
			Log.d(TAG, "handleErrorCode() error: " + message);
			onError(message);
		}
	}

	// =================================================================================================================
	// implements PurchasesUpdatedListener
	// =================================================================================================================

	@Override
	public void onPurchasesUpdated(IapResult iapResult, @Nullable List<PurchaseData> list) {
		Log.d(TAG, "=========================== Now I am in onPurchasesUpdated ===========================");
		if(iapResult.isSuccess() && list != null) {
			for(PurchaseData purchase : list){
				consumeAsync(purchase);
				Log.d(TAG, "=========================== Now I am in onPurchasesUpdated 2222===========================");
			}
		}else if(iapResult.getResponseCode() == PurchaseClient.ResponseCode.RESULT_USER_CANCELED){
			Log.d(TAG, "=========================== Now I am in onPurchasesUpdated3333 ===========================");
			Log.d(TAG, iapResult.toJsonString());
		}else {
			Log.d(TAG, "=========================== Now I am in onPurchasesUpdated4444 ===========================");
			Log.d(TAG, iapResult.toJsonString());
		}
	}

/*
	@Override
	public void onPurchasesUpdated(IapResult iapResult, List<PurchaseData> purchaseData) {
		if (iapResult.isSuccess()) {
			Log.e(TAG, "onpurchasesupdated");

			onPurchaseUpdated(purchaseData);

			return;
		}

		handleErrorCode(iapResult);
	}
*/

	public void launchLoginFlow(IapResultListener listener) {
		mPurchaseClient.launchLoginFlowAsync(mActivity, listener);
	}

	public void launchUpdateOrInstall(IapResultListener listener) {
		mPurchaseClient.launchUpdateOrInstallFlow(mActivity, listener);
	}


	public void launchPurchaseFlow(final PurchaseFlowParams params) {
		Log.e(TAG, "Before going in run purchase flow");
		executeServiceRequest(new Runnable() {
			@Override
			public void run() {
				Log.e(TAG, "ready to run purchase flow");
				mPurchaseClient.launchPurchaseFlow(mActivity, params);
				Log.e(TAG, "After run purchase flow");

			}
		});
	}



	public void onNeedLogin() {
		launchLoginFlow(null);
	}

	public void onNeedUpdate() {
		Log.e(TAG, "Before updateOrInstallPaymentModule");
		updateOrInstallPaymentModule();
	}

	private void updateOrInstallPaymentModule() {
		Log.e(TAG, "Inside updateOrInstallPaymentModule");
		launchUpdateOrInstall(new IapResultListener() {
			@Override
			public void onResponse(IapResult iapResult) {
				if (iapResult.isSuccess()) {
					startConnection(new Runnable() {
						@Override
						public void run() {
							onPurchaseClientSetupFinished();
							queryPurchasesAsync();
						}
					});
				} else {
					Log.w(TAG, "launchUpdateOrInstall() got an error response code: " + iapResult.getResponseCode());
				}
			}
		});
	}

	public void onError(String message) {
		showDialog(message);
	}

	private void savePayloadString(String payload) {
		SharedPreferences.Editor spe = getPreferences(MODE_PRIVATE).edit();
		spe.putString("PAYLOAD", payload);
		spe.apply();
	}

	public static String generatePayload() {
		char[] payload;
		final char[] specials = {'~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '-', '{', '}', '|', '\\', '/', '.',
				'.', '=', '[', ']', '?', '<', '>'};
		StringBuilder buffer = new StringBuilder();
		for (char ch = '0'; ch <= '9'; ++ch) {
			buffer.append(ch);
		}
		for (char ch = 'a'; ch <= 'z'; ++ch) {
			buffer.append(ch);
		}
		for (char ch = 'A'; ch <= 'Z'; ++ch) {
			buffer.append(ch);
		}

		for (char ch : specials) {
			buffer.append(ch);
		}

		payload = buffer.toString().toCharArray();

		StringBuilder randomString = new StringBuilder();
		Random random = new Random();

		//length : 20???
		for (int i = 0; i < 20; i++) {
			randomString.append(payload[random.nextInt(payload.length)]);
		}

		return randomString.toString();
	}

	public void consumeAsync(final PurchaseData data) {
		Log.i(TAG, "inside consumeAsyncconsumeAsyncconsumeAsyncconsumeAsync");
		if (mTokenToBe == null) {
			mTokenToBe = new HashSet<>();
		} else if (mTokenToBe.contains(data.getPurchaseToken())) {
			Log.i(TAG, "Token was already scheduled to be consumed - skipping...");
			return;
		}

		mTokenToBe.add(data.getPurchaseToken());

		executeServiceRequest(new Runnable() {
			@Override
			public void run() {
				ConsumeParams params = ConsumeParams.newBuilder()
						.setPurchaseData(data)
						.build();

				mPurchaseClient.consumeAsync(params, new ConsumeListener() {
					@Override
					public void onConsumeResponse(IapResult iapResult, PurchaseData purchaseData) {
						if (iapResult.isSuccess()) {
							if (purchaseData.getPurchaseToken().equals(data.getPurchaseToken())) {
								mTokenToBe.remove(data.getPurchaseToken());
								try {
									onConsumeFinished(purchaseData, iapResult);
								} catch (Exception e) {
									e.printStackTrace();
								}
							} else {
								onError("purchaseToken not equal");
							}
						} else {
							handleErrorCode(iapResult);
						}
					}
				});
			}
		});
	}



	//NZ?????? ===========================0902===========================
	public void restorePurchases(final String pid, final String tid, final String uid) //??????????????? ????????? pid tid ?????????
	{
		Repay_Flag= true;
		/*globalTID = tid;*/
		Log.d(TAG, "Unused Data Java Android Logic Start1");
		mPurchaseClient.queryPurchasesAsync(PurchaseClient.ProductType.INAPP, new PurchasesListener() {
			@Override
			public void onPurchasesResponse(IapResult iapResult, @Nullable List<PurchaseData> list) {
				Log.d(TAG, "Unused Data Java Android Logic Start2");

				if (iapResult.isSuccess() && list != null) {
					if(list.size() != 0){
						for(PurchaseData purchaseData : list){
							Log.d(TAG, "PPAAYY"+ purchaseData.toString()); // ????????? ?????? ????????????

							if(purchaseData.getProductId().equals(pid)){
								unConsumedListExecute(purchaseData, pid, tid, uid);    //pid, tid, uid??? ????????????
							}
						}
					}

					else{
						Log.d(TAG, "list size 0");

					}
				} else {
					Log.d(TAG, iapResult.toJsonString());
				}
			}
		});
	}



	//???????????? ?????? ??????????????? ??????
	private void unConsumedListExecute(final PurchaseData purchaseData, final String pid, final String tid, final String uid)   //?????? ????????? ?????????. => ????????? ?????? ?????? ????????? ????????????.
	//?????? for ?????? ????????? ????????? ???????????????, ??????
	{

		ConsumeParams params = ConsumeParams.newBuilder().setPurchaseData(purchaseData).build();
		mPurchaseClient.consumeAsync(params, new ConsumeListener() {
			@Override
			public void onConsumeResponse(IapResult iapResult, @Nullable PurchaseData purchaseData) {
				if (iapResult.isSuccess() && purchaseData != null) {

					if (purchaseData.getPurchaseToken().equals(purchaseData.getPurchaseToken())) {
						Log.d(TAG, "IINNSSIIDDEE"+ purchaseData.toString());


						//url = "http://106.243.69.210:8080/OneStorePayCheck";
						url = "http://43.200.41.21:8080/OneStorePayCheck";
						globalTID = tid;
						data = String.format("pid=%s&uid=%s&tid=%s&token=%s", pid, uid, tid, purchaseData.getPurchaseToken());
						Log.d(TAG, "After data parsing");
						/*Check_Repayment = true;*/
						httpGetConnection(url, data, purchaseData, pid);


						Log.d(TAG, "onConsumeResponse");

					}


					else{
						Log.d(TAG, "purchaseToken not equal");
					}
				}

				else if(iapResult.getResponseCode() == PurchaseClient.ResponseCode.RESULT_ITEM_NOT_OWNED) //	???????????? ???????????? ?????? ?????? ?????? ??? ??? ????????????.
				{
					Log.d(TAG, "Item RESULT_ITEM_NOT_OWNED!!!!!!!!");
				}
				else if(iapResult.getResponseCode() == PurchaseClient.ResponseCode.RESULT_ITEM_UNAVAILABLE) //	???????????? ???????????? ?????? ?????? ?????? ??? ??? ????????????.
				{
					Log.d(TAG, "Item RESULT_ITEM_UNAVAILABLE!!!!!!!!");
				}


				else {
					Log.d(TAG, iapResult.toJsonString());
				}
			}
		}); //consumeAsync End
	}


	public void onConsumeFinished(PurchaseData purchaseData, IapResult iapResult) throws Exception {

		Log.e(TAG, "onConsumeFinishedonConsumeFinishedonConsumeFinishedonConsumeFinished");
		if (iapResult.isSuccess()) {
/*			updateCoinsPurchased(purchaseData.getProductId());
			Spanned message = Html.fromHtml(
					String.format("asd", getPurchasedCoins(purchaseData.getProductId()))
			);*/
			/*showDialog(message);*/

			//????????? acknowledgeasync??? ????????????????
			//????????? pid ????????? ???????????? ?????????????????????????

			Log.e(TAG, "@@@@@@" + purchaseData.getProductId() + "@@@@@@@" + purchaseData.getPurchaseToken() + "@@@@@@");
			//NZ??????
			//OnIapResult(true , null , ToServTID , purchaseData.getPurchaseToken());
			//????????? ????????? ?????? ??? ????????? ?????? ??? +UID ?????? ????????? , ??????????????????
			// ?????? ?????? ????????? lobbyoptionalPanel??? recvw_payres??? ????????? ???
			PdToken = purchaseData.getPurchaseToken();
			System.out.println("[HttpURLConnection ?????????  get ?????? ????????? ?????? ??? ?????? ??? ?????? ??????]");
			//url = "http://106.243.69.210:8080/OneStorePayCheck";
			url = "http://43.200.41.21:8080/OneStorePayCheck";

			data = String.format("pid=%s&uid=%s&tid=%s&token=%s", purchaseData.getProductId(), GProducerName, ToServTID, PdToken);
			httpGetConnection(url, data, purchaseData, purchaseData.getProductId());
		}
	}

	public static void httpGetConnection(String UrlData, String ParamData, PurchaseData purchaseData, String ppid) {
		System.out.println("111111111");

		//http ?????? ??? url ????????? ???????????? ???????????? ???????????? ?????? ?????? ??????
		String totalUrl = "";
		if(ParamData != null && ParamData.length() > 0 &&
				!ParamData.equals("") && !ParamData.contains("null")) { //???????????? ?????? ????????? ????????? ??????
			totalUrl = UrlData.trim().toString() + "?" + ParamData.trim().toString();
		}
		else {
			totalUrl = UrlData.trim().toString();
		}
		System.out.println("2222222222222222222222222222");
		//http ????????? ???????????? ?????? ?????? ??????
		URL url = null;
		HttpURLConnection conn = null;
		System.out.println("333333333333333333333333333333");
		//http ?????? ?????? ??? ?????? ?????? ???????????? ?????? ?????? ??????
		String responseData = "";
		BufferedReader br = null;
		StringBuffer sb = null;
		System.out.println("44444444444444444444444444444444");
		//????????? ?????? ???????????? ???????????? ?????? ??????
		String returnData = "";
		System.out.println("555555555555555555555555555555555");
		try {
			System.out.println("6666666666666666666666666666666666");
			//??????????????? ????????? url??? ????????? connection ??????
			url = new URL(totalUrl);
			conn = (HttpURLConnection) url.openConnection();
			System.out.println("7777777777777777777777777777777");
			//http ????????? ????????? ?????? ?????? ??????
			conn.setRequestProperty("Accept", "application/json");
			conn.setRequestMethod("GET");

			//http ?????? ??????
			conn.connect();
			System.out.println("http ?????? ?????? : "+"GET");
			System.out.println("http ?????? ?????? : "+"application/json");
			System.out.println("http ?????? ?????? : "+UrlData);
			System.out.println("http ?????? ????????? : "+ParamData);
			System.out.println("");
			System.out.println("888888888888888888888888888888888888");
			//http ?????? ??? ?????? ?????? ???????????? ????????? ?????????
			br = new BufferedReader(new InputStreamReader(conn.getInputStream(), "UTF-8"));
			sb = new StringBuffer();
			while ((responseData = br.readLine()) != null) {
				sb.append(responseData); //StringBuffer??? ???????????? ????????? ??????????????? ?????? ??????
			}
			System.out.println("999999999999999999999999999999999999999");
			//????????? ?????? ?????? ??? ???????????? ????????? ?????? ????????? ?????? ??????
			returnData = sb.toString();



			//http ?????? ?????? ?????? ?????? ??????
			String responseCode = String.valueOf(conn.getResponseCode());
			System.out.println("http ?????? ?????? : "+responseCode);
			System.out.println("http ?????? ????????? : "+returnData); //0?????????????????? ??????

			if(returnData.equals("0")) {
				if(!ToServTID.equals("") || !PdToken.equals(""))
					OnIapResult(returnData.equals("0"), null, ToServTID, PdToken, purchaseData.getProductId());   // ?????? ?????? ?????????
				else if(iapMgr.Repay_Flag) {
					OnIapResult(true, null, globalTID, purchaseData.getPurchaseToken(), ppid); //??????????????? ????????? ???????????? 200 / 0?????? ???????????? ?????? ?????? ??????
					iapMgr.Repay_Flag = false;
				}
			}
			else if(returnData.equals("1") && iapMgr.Repay_Flag){
				OnIapResult(true , null , globalTID , purchaseData.getPurchaseToken(), ppid);
				iapMgr.Repay_Flag = false;
			}

			//OnIapResult(true , null , globalTID , purchaseData.getPurchaseToken(), ppid);
			/*if(returnData.equals("0")){
				if(iapMgr.Repay_Flag)
				{
					OnIapResult(true , null , globalTID , purchaseData.getPurchaseToken(), ppid);
					iapMgr.Repay_Flag=false;
				}
				else{
					OnIapResult(returnData.equals("0") , null , ToServTID , PdToken, purchaseData.getProductId());
				}
			}

			else //?????????
			{
				if(iapMgr.Repay_Flag){

					iapMgr.Repay_Flag=false;
				}

			}*/


		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			//http ?????? ??? ?????? ?????? ??? BufferedReader??? ???????????????
			try {
				if (br != null) {
					br.close();
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}


	public void acknowledgeAsync(final PurchaseData data) {
		if (mTokenToBe == null) {
			mTokenToBe = new HashSet<>();
		} else if (mTokenToBe.contains(data.getPurchaseToken())) {
			Log.i(TAG, "Token was already scheduled to be acknowledged - skipping...");
			return;
		}

		mTokenToBe.add(data.getPurchaseToken());

		executeServiceRequest(new Runnable() {
			@Override
			public void run() {
				AcknowledgeParams params = AcknowledgeParams.newBuilder().setPurchaseData(data).build();
				mPurchaseClient.acknowledgeAsync(params, new AcknowledgeListener() {
					@Override
					public void onAcknowledgeResponse(IapResult iapResult, PurchaseData purchaseData) {
						if (iapResult.isSuccess()) {
							if (data.getPurchaseToken().equals(purchaseData.getPurchaseToken())) {
								mTokenToBe.remove(data.getPurchaseToken());

								onAcknowledgeFinished(purchaseData, iapResult);
							} else {
								onError("purchaseToken not equal");
							}
						} else {
							handleErrorCode(iapResult);
						}
					}
				});
			}
		});
	}
	public void onAcknowledgeFinished(PurchaseData purchase, IapResult iapResult) {
		Log.e(TAG, "onAcknowledgeFinished in come");
	}



	/**
	 * TODO: ?????????????????? ???????????? ?????? ???????????????(inapp)??? ??????, ????????????????????? ????????? life cycle ??? ?????? ????????????????????? ?????? ??? ????????? ?????????????????????.
	 * <p>
	 * ?????????????????? API??? ???????????? ???????????? ?????? ???????????????(inapp)??? ?????????????????? ???????????????(auto) ????????? ???????????????.
	 * ???????????????(inapp)??? ?????? ????????? ?????? ?????? ?????? ?????????????????? ????????? ????????? ?????? ????????????. ???, ?????? ????????? ????????? ??????????????? ????????? ????????????????????????.
	 * ???????????????(auto)??? ?????? ?????????????????? ??? recurringState ????????? ????????? ????????????????????? ????????? ??? ????????????. -> recurringState 0(?????? ?????????), 1(?????? ?????????)
	 * manageRecurringProduct API??? ?????? ????????????????????? ??? ?????? recurringState??? 0 -> 1??? ???????????????. ???????????? ??????????????? ????????? recurringState??? 1 -> 0??? ???????????????.
	 * <p>
	 * ???????????????(auto)??? 11??? 10?????? ????????? ??? ?????? ???????????????????????? ?????????????????? recurringState??? 0(?????? ?????????)?????? ???????????????.
	 * ?????????????????? ?????? ?????????(12??? 10???)??? ??????????????? ??????????????? 11??? 10??? ~ 12??? 9????????? ?????? ????????? ???????????????.
	 * 11??? 15?????? ?????????????????????API??? ???????????? ????????????(cancel)??? ????????? ??????, 12??? 9????????? ??????????????? ??????(recurringState)??? 1(?????? ?????????)??? ?????????.
	 * 12??? 9??? ????????? ?????????????????????API??? ???????????? ???????????? ??????(reactivate)??? ????????? ??????, ?????? ????????? ??????(recurringState)??? 0(?????? ?????????)??? ?????????.
	 */



	public void queryPurchasesAsync() {
		final List<PurchaseData> result = new ArrayList<>();
		final long time = System.currentTimeMillis();
		Log.d(TAG, "Finally we enter queryPurchasesAsync and before new runnable");
		final Runnable auto = new Runnable() {
			@Override
			public void run() {
				Log.d(TAG, "============queryPurchasesAsync inside============");

				mPurchaseClient.queryPurchasesAsync(PurchaseClient.ProductType.AUTO, new PurchasesListener() {
					@Override
					public void onPurchasesResponse(IapResult iapResult, List<PurchaseData> purchaseData) {
						Log.i(TAG, "AUTO - Querying purchases elapsed time: " + (System.currentTimeMillis() - time + "ms"));
						if (iapResult.isSuccess()) {
							result.addAll(purchaseData);
						} else {
							Log.w(TAG, "AUTO - queryPurchasesAsync() got an error response code: " + iapResult.getResponseCode());
						}

						onPurchasesUpdated(iapResult, result);
						Log.d(TAG, "============AFTER            queryPurchasesAsync============");
					}
				});
			}
		};

		executeServiceRequest(new Runnable() {
			@Override
			public void run() {
				mPurchaseClient.queryPurchasesAsync(PurchaseClient.ProductType.INAPP, new PurchasesListener() {
					@Override
					public void onPurchasesResponse(IapResult iapResult, List<PurchaseData> purchaseData) {
						Log.i(TAG, "INAPP - Querying purchases elapsed time: " + (System.currentTimeMillis() - time + "ms"));
						if (iapResult.isSuccess()) {
							result.addAll(purchaseData);
						} else {
							Log.w(TAG, "INAPP - queryPurchasesAsync() got an error response code: " + iapResult.getResponseCode());
						}
						auto.run();
					}
				});
			}
		});
	}

	public void queryPurchasesAsync(@PurchaseClient.ProductType String productType) {
		final long time = System.currentTimeMillis();
		executeServiceRequest(new Runnable() {
			@Override
			public void run() {
				mPurchaseClient.queryPurchasesAsync(productType, new PurchasesListener() {
					@Override
					public void onPurchasesResponse(IapResult iapResult, List<PurchaseData> purchaseData) {
						Log.i(TAG, productType + " - Querying purchases elapsed time: " + (System.currentTimeMillis() - time + "ms"));
						if (iapResult.isSuccess()) {
							//onPurchaseUpdated(purchaseData);
							Log.e(TAG,"onpurchase res");
						} else {
							Log.w(TAG, productType + " - queryPurchasesAsync() got an error response code: " + iapResult.getResponseCode());
							handleErrorCode(iapResult);
						}
					}
				});
			}
		});
	}

	public void manageRecurringProductAsync(final PurchaseData purchaseData, final String recurringAction, final RecurringProductListener listener) {
		executeServiceRequest(new Runnable() {
			@Override
			public void run() {
				RecurringProductParams params = RecurringProductParams.newBuilder()
						.setPurchaseData(purchaseData)
						.setRecurringAction(recurringAction)
						.build();
				mPurchaseClient.manageRecurringProductAsync(params, listener);
			}
		});
	}

	public void getStoreCode(final StoreInfoListener listener) {
		executeServiceRequest(new Runnable() {
			@Override
			public void run() {
				mPurchaseClient.getStoreInfoAsync(listener);
			}
		});
	}


	private void saveStoreCode(String storeCode) {
		SharedPreferences.Editor spe = getPreferences(MODE_PRIVATE).edit();
		spe.putString(null, storeCode);
		spe.apply();
	}

	//======================== ?????????????????? MainActivity ?????? ???????????? ?????? ====================================

	private void showProgressDialog() {
		Log.e(TAG,"ShowProgressDialog");
		if (!isFinishing() && !isShowingProgressDialog()) {
			if (mProgressDialog == null) {
				Log.e(TAG,"ShowProgressDialog NULL");
				mProgressDialog = new ProgressDialog(this);
			}
			mProgressDialog.setMessage("Service connection...");
			mProgressDialog.show();
		}
	}

	private boolean isShowingProgressDialog() {
		return mProgressDialog != null && mProgressDialog.isShowing();
	}

	private void showDialog(CharSequence message) {
		new AlertDialog.Builder(this)
				.setMessage(message)
				.setPositiveButton(android.R.string.ok, null)
				.create().show();
	}

	private void showDialog(CharSequence message, DialogInterface.OnClickListener listener) {
		new AlertDialog.Builder(this)
				.setMessage(message)
				.setPositiveButton(android.R.string.ok, listener)
				.setNegativeButton(android.R.string.cancel, null)
				.create().show();
	}





	private void updateCoin(int coin) {
/*		SharedPreferences sp = getPreferences(MODE_PRIVATE);
		SharedPreferences.Editor spe = getPreferences(MODE_PRIVATE).edit();

		int savedCoins = sp.getInt(AppConstants.KEY_TOTAL_COIN, 0);
		savedCoins += coin;
		spe.putInt(AppConstants.KEY_TOTAL_COIN, savedCoins);
		spe.apply();

		mCoinView.setText(String.valueOf(savedCoins));*/
	}


}
