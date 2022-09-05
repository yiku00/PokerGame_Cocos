#include "pch.h"
#include "CouponPopupPanel.h"
#include "HeroUtil.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	#include "android/AndroidUtilManager.h"
#endif
#include "GameDataManager.h"
#include "W_CouponReq.pb.h"
#include "W_CouponRes.pb.h"
#include "PanelHelper.h"
#include "GameStringDepot.h"


CouponPopupPanel::CouponPopupPanel() : Panel("CouponPopupPanel")
{
	initPanel();		
}

CouponPopupPanel::~CouponPopupPanel()
{
}

void CouponPopupPanel::onClicked(const string& name)
{
	if (name == getButtonName(mCloseBtn)) {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		LayerManager::getSingleton().popLayer(this);
	}
	else if (name == getButtonName(mSendBtn)) {
		//보낸다.
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		string name = getLabel("fld_coupon")->getString();
		sendW_CouponReq(name);
	}
	else if (name == getButtonName(mAttachBtn)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)				
		GameDataManager::getSingletonPtr()->m_bEditTextField = false;
		GameDataManager::getSingletonPtr()->m_onFocusTextFeild = getTextField("fld_coupon");
		std::string _fieldText = getTextField("fld_coupon")->getString();
		//AndroidUtilManager::getSingletonPtr()->ReleaseCustomEditTextField();
		AndroidUtilManager::getSingletonPtr()->InitCustomEditTextField();
		AndroidUtilManager::getSingletonPtr()->ShowCustomEditTextField(_fieldText);

#else
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);				
		getTextField("fld_coupon")->attachWithIME();
#endif
	}	
}

void CouponPopupPanel::initPanel()
{
	addMouseBlockPanel(this , true);	
	construct(getMxmlPath() + "dmy_coupon_input.mxml");
	setButtonListener(this);
	mCloseBtn = getButton("sbtn_cancel");
	mSendBtn = getButton("sbtn_button");
	mAttachBtn = getButton("sbtn_intable2");
	getLabel("txt_title_under")->setString(GameStringDepot::getSingleton().getString("COUPON_TITLE").c_str());
	getLabel("txt_title")->setString(GameStringDepot::getSingleton().getString("COUPON_TITLE").c_str());
	getLabel("txt_info1")->setString(GameStringDepot::getSingleton().getString("COUPON_DESC_1").c_str());
	getLabel("txt_info2")->setString(GameStringDepot::getSingleton().getString("COUPON_DESC_2").c_str());
	getLabel("txt_info3")->setString(GameStringDepot::getSingleton().getString("COUPON_DESC_3").c_str());
	getLabel("txt_info4")->setString(GameStringDepot::getSingleton().getString("COUPON_DESC_4").c_str());

	getTextField("fld_coupon")->setListener(this);
	getTextField("fld_coupon")->setPlaceHolder(GameStringDepot::getSingleton().getString("CouponPopupPanel_FLD").c_str());	

	mButtonNameLabel = getLabel("txt_button_under");
	mButtonNameUnderLabel = getLabel("txt_button");
	mButtonNameLabel->setString(GameStringDepot::getSingleton().getString("TXT_OK_LABEL").c_str());
	mButtonNameUnderLabel->setString(GameStringDepot::getSingleton().getString("TXT_OK_LABEL").c_str());

}

void CouponPopupPanel::onDetached()
{
	CCLog("CouponPopupPanel::onDetached()");
	//getTextField("fld_coupon")->setListener(nullptr);
	//string _field = getTextField("fld_coupon")->getString();
}

void CouponPopupPanel::sendW_CouponReq(string coupon)
{
	W_CouponReq req;
	req.set_coupon(coupon);
	HttpMessage msg(req, HttpResponseHandler(CouponPopupPanel::recvW_CouponRes), this);
	HttpManager::getSingleton().send(msg);
}

void CouponPopupPanel::recvW_CouponRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_CouponRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success()) {
		if (res.has_playerinfo())
			GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());			

		if (res.has_rewardinfo())
		{
			PanelHelper::pushReceiveAllPanel(res.rewardinfo());
		}
	}
	else {
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
	}
}
