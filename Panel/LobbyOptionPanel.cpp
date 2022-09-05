#include "pch.h"
#include "LobbyOptionPanel.h"

#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "CustomPopupPanel.h"
#include "GameStringDepot.h"
#include "android/IGAWorksManager.h"
#include "android/AndroidUtilManager.h"
#include "LobbyUIPanel.h"
#include "NotiDataManager.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	#include "android/GoogleManager.h"
	#include "android/FacebookManager.h"
	#include "android/IapManager.h"
	#include "android/VungleManager.h"	
#endif 
#include "SceneUtil.h"
#include "GlobalDefine.h"
#include "W_PayReq.pb.h"
#include "W_PayRes.pb.h"
#include "PanelHelper.h"


//#define USE_TEST_BTN

LobbyOptionPanel::LobbyOptionPanel()
{
	mLoginProcess = false;
	mBeLogOut = false;
	m_pReplayListView = nullptr;
	m_pReplayListContainer = nullptr;

	InitPanel();
	InitImage();
	initButton();
	initNotiWidget();
	refreshFocusPanel(EN_ACCOUNT);
	setButtonListener(this);
	
	m_ViewDataIndex = 10;
	refreshAccountPanel();
}

LobbyOptionPanel::~LobbyOptionPanel()
{
	//destruct();
}

void LobbyOptionPanel::InitPanel()
{
	construct(getMxmlPath() + "dmy_option.mxml");
	initGameOptionPanel();
	initAccountOptionPanel();
	initNoticeOptionPanel();
	
	m_ShowPosition = getPosition();
	m_HiddenPosition = m_ShowPosition - ccp(0.f, DESIGN_HEIGHT);

	//setPosition(m_HiddenPosition);

	CCPoint _tapPos = getDummy("dmy_button_tab1").origin;
	_tapPos.y = -_tapPos.y;

	m_pTapPanel = new Panel();
	m_pTapPanel->construct(getMxmlPath() + "dmy_button_tab.mxml");
	m_pTapPanel->setPosition(_tapPos);
	addChild(m_pTapPanel);
	m_pTapPanel->release();
	m_pTapPanel->getLabel("txt_off_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_pTapPanel->getLabel("txt_on_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_pTapPanel->getLabel("txt_off_tab")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_OPTION_UNIT").c_str());
	m_pTapPanel->getLabel("txt_on_tab")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_OPTION_UNIT").c_str());
	m_pTapPanel->getLabel("txt_off_tab")->setVisible(false);
	m_pTapPanel->getButton("sbtn_button")->setType(Button::NoPressImg);
	m_pTapPanel->getButton("sbtn_button")->setSkelAnimation("tab_on");
	m_pTapPanel->getButton("sbtn_button")->setListener(this);
	m_pTapPanel->getButton("sbtn_button")->setName("openGameOptionBtn");


	_tapPos = getDummy("dmy_button_tab2").origin;
	_tapPos.y = -_tapPos.y;
	m_pTapAccountPanel = new Panel();
	m_pTapAccountPanel->construct(getMxmlPath() + "dmy_button_tab.mxml");
	m_pTapAccountPanel->setPosition(_tapPos);
	addChild(m_pTapAccountPanel);
	m_pTapAccountPanel->release();
	m_pTapAccountPanel->getLabel("txt_off_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_pTapAccountPanel->getLabel("txt_on_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_pTapAccountPanel->getLabel("txt_off_tab")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_ACCOUNT_UNIT").c_str());
	m_pTapAccountPanel->getLabel("txt_on_tab")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_ACCOUNT_UNIT").c_str());
	m_pTapAccountPanel->getLabel("txt_off_tab")->setVisible(false);
	m_pTapAccountPanel->getButton("sbtn_button")->setType(Button::NoPressImg);
	m_pTapAccountPanel->getButton("sbtn_button")->setSkelAnimation("tab_on");
	m_pTapAccountPanel->getButton("sbtn_button")->setListener(this);
	m_pTapAccountPanel->getButton("sbtn_button")->setName("openAccountOptionBtn");		

	// 공지사항 탭 버튼
	_tapPos = getDummy("dmy_button_tab3").origin;
	_tapPos.y = -_tapPos.y;
	m_pTapNoticePanel = new Panel();
	m_pTapNoticePanel->construct(getMxmlPath() + "dmy_button_tab.mxml");
	m_pTapNoticePanel->setPosition(_tapPos);
	addChild(m_pTapNoticePanel);
	m_pTapNoticePanel->release();
	m_pTapNoticePanel->getLabel("txt_off_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_pTapNoticePanel->getLabel("txt_on_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_pTapNoticePanel->getLabel("txt_off_tab")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_NOTICE_UNIT").c_str());
	m_pTapNoticePanel->getLabel("txt_on_tab")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_NOTICE_UNIT").c_str());
	m_pTapNoticePanel->getLabel("txt_off_tab")->setVisible(false);
	m_pTapNoticePanel->getButton("sbtn_button")->setType(Button::NoPressImg);
	m_pTapNoticePanel->getButton("sbtn_button")->setSkelAnimation("tab_on");
	m_pTapNoticePanel->getButton("sbtn_button")->setListener(this);
	m_pTapNoticePanel->getButton("sbtn_button")->setName("openNoticeOptionBtn");
}


void LobbyOptionPanel::InitImage()
{
	mGameOptionPanel->getLabel("str_music")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_MUSIC").c_str());
	mGameOptionPanel->getLabel("str_music_under")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_MUSIC").c_str());
	mGameOptionPanel->getLabel("txt_music_on")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_ON").c_str());
	mGameOptionPanel->getLabel("txt_music_off")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_OFF").c_str());
	mGameOptionPanel->getLabel("str_sound")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_EFFECT").c_str());
	mGameOptionPanel->getLabel("str_sound_under")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_EFFECT").c_str());
	mGameOptionPanel->getLabel("txt_sound_on")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_ON").c_str());
	mGameOptionPanel->getLabel("txt_sound_off")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_OFF").c_str());
	mGameOptionPanel->getLabel("str_voice")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_VOICE").c_str());
	mGameOptionPanel->getLabel("str_voice_under")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_VOICE").c_str());
	mGameOptionPanel->getLabel("txt_voice_on")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_ON").c_str());
	mGameOptionPanel->getLabel("txt_voice_off")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_OFF").c_str());
	mGameOptionPanel->getLabel("str_hiddencard")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_HIDDEN_CARD").c_str());
	mGameOptionPanel->getLabel("str_hiddencard_under")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_HIDDEN_CARD").c_str());
	mGameOptionPanel->getLabel("txt_hiddencard_on")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_MENUAL").c_str());
	mGameOptionPanel->getLabel("txt_hiddencard_off")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_AUTO").c_str());
	mGameOptionPanel->getLabel("str_Notice")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_POPUP_ALRAM").c_str());
	mGameOptionPanel->getLabel("str_Notice_under")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_POPUP_ALRAM").c_str());
	mGameOptionPanel->getLabel("txt_Notice_on")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_ON").c_str());
	mGameOptionPanel->getLabel("txt_Notice_off")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_OFF").c_str());
	mGameOptionPanel->getLabel("str_option_info")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_OPTION_DESC").c_str());

	mGameOptionPanel->getLabel("str_music_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mGameOptionPanel->getLabel("str_music")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mGameOptionPanel->getLabel("txt_music_on")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mGameOptionPanel->getLabel("txt_music_off")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mGameOptionPanel->getLabel("str_sound_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mGameOptionPanel->getLabel("str_sound")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mGameOptionPanel->getLabel("txt_sound_on")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mGameOptionPanel->getLabel("txt_sound_off")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mGameOptionPanel->getLabel("str_voice_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mGameOptionPanel->getLabel("str_voice")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mGameOptionPanel->getLabel("txt_voice_on")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mGameOptionPanel->getLabel("txt_voice_off")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mGameOptionPanel->getLabel("str_hiddencard_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mGameOptionPanel->getLabel("str_hiddencard")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mGameOptionPanel->getLabel("txt_hiddencard_on")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mGameOptionPanel->getLabel("txt_hiddencard_off")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mGameOptionPanel->getLabel("str_Notice_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mGameOptionPanel->getLabel("str_Notice")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mGameOptionPanel->getLabel("txt_Notice_on")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mGameOptionPanel->getLabel("txt_Notice_off")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mGameOptionPanel->getLabel("str_option_info")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

	m_MusicCheck[0] = mGameOptionPanel->getSkel("skel_checkframe1");
	m_MusicCheck[1] = mGameOptionPanel->getSkel("skel_checkframe2");
	m_EfxCheck[0] = mGameOptionPanel->getSkel("skel_checkframe3");
	m_EfxCheck[1] = mGameOptionPanel->getSkel("skel_checkframe4");
	m_VoiceCheck[0] = mGameOptionPanel->getSkel("skel_checkframe5");
	m_VoiceCheck[1] = mGameOptionPanel->getSkel("skel_checkframe6");
	m_HiddenCheck[0] = mGameOptionPanel->getSkel("skel_checkframe7");
	m_HiddenCheck[1] = mGameOptionPanel->getSkel("skel_checkframe8");
	m_PopupCheck[0] = mGameOptionPanel->getSkel("skel_checkframe9");
	m_PopupCheck[1] = mGameOptionPanel->getSkel("skel_checkframe10");

	OptionDefineValue* _val = GameDataManager::getSingletonPtr()->m_pOptionValue;
	if (_val->m_music)
	{
		m_MusicCheck[0]->setVisible(true);
		m_MusicCheck[1]->setVisible(false);
		m_MusicCheck[0]->playAnimation("checkframe_start", false);
		//GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_CHECK);
	}
	else
	{
		m_MusicCheck[0]->setVisible(false);
		m_MusicCheck[1]->setVisible(true);
		m_MusicCheck[1]->playAnimation("checkframe_start", false);
		//GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_CHECK);
	}

	if (_val->m_effect)
	{
		m_EfxCheck[0]->setVisible(true);
		m_EfxCheck[1]->setVisible(false);
		m_EfxCheck[0]->playAnimation("checkframe_start", false);
		//GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_CHECK);
	}
	else
	{
		m_EfxCheck[0]->setVisible(false);
		m_EfxCheck[1]->setVisible(true);
		m_EfxCheck[1]->playAnimation("checkframe_start", false);
		//GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_CHECK);
	}

	if (_val->m_voice)
	{
		m_VoiceCheck[0]->setVisible(true);
		m_VoiceCheck[1]->setVisible(false);
		m_VoiceCheck[0]->playAnimation("checkframe_start", false);
		//GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_CHECK);
	}
	else
	{
		m_VoiceCheck[0]->setVisible(false);
		m_VoiceCheck[1]->setVisible(true);
		m_VoiceCheck[1]->playAnimation("checkframe_start", false);
		//GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_CHECK);
	}

	if (_val->m_hiddenCard)
	{
		m_HiddenCheck[0]->setVisible(true);
		m_HiddenCheck[1]->setVisible(false);
		m_HiddenCheck[0]->playAnimation("checkframe_start", false);
		//GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_CHECK);
	}
	else
	{
		m_HiddenCheck[0]->setVisible(false);
		m_HiddenCheck[1]->setVisible(true);
		m_HiddenCheck[1]->playAnimation("checkframe_start", false);
		//GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_CHECK);
	}

	//if (_val->m_popupAlram)
	//{
	//	m_PopupCheck[0]->setVisible(true);
	//	m_PopupCheck[1]->setVisible(false);
	//	m_PopupCheck[0]->playAnimation("checkframe_start", false);
	//}
	//else
	//{
	//	m_PopupCheck[0]->setVisible(false);
	//	m_PopupCheck[1]->setVisible(true);
	//	m_PopupCheck[1]->playAnimation("checkframe_start", false);
	//}

	//getSkel("skel_option_back5")->setVisible(false);
	mGameOptionPanel->getSkel("skel_intable5")->setVisible(false);
	mGameOptionPanel->getSkel("skel_icon_notice")->setVisible(false);
	m_PopupCheck[0]->setVisible(false);
	m_PopupCheck[1]->setVisible(false);
	mGameOptionPanel->getLabel("txt_Notice")->setVisible(false);
	mGameOptionPanel->getLabel("txt_Notice_under")->setVisible(false);
	mGameOptionPanel->getLabel("txt_Notice_on")->setVisible(false);
	mGameOptionPanel->getLabel("txt_Notice_off")->setVisible(false);



}

void LobbyOptionPanel::initButton()
{
	//getButton("sbtn_tapbutton_on_stay1")->setType(Button::NoPressImg);
	//getButton("sbtn_tapbutton_on_stay1")->getButtonSkelObject()->setSkin("tab_game_option");

	//m_pGameRuleButton = getButton("sbtn_tab1_small_button_2_stay1");
	//m_pGameRuleButton->setType(Button::NoPressImg);
	//m_pGameRuleButton->setListener(this);
	//m_pGameRuleButton->getButtonSkelObject()->setSkin("txt_howtoplay");

	//m_pCustomerCenterButton = getButton("sbtn_tab1_small_button_2_stay2");
	//m_pCustomerCenterButton->setType(Button::NoPressImg);
	//m_pCustomerCenterButton->setListener(this);
	//m_pCustomerCenterButton->getButtonSkelObject()->setSkin("txt_customercenter");

	//m_pTermsButton = getButton("sbtn_tab1_small_button_2_stay3");
	//m_pTermsButton->setType(Button::NoPressImg);
	//m_pTermsButton->setListener(this);
	//m_pTermsButton->getButtonSkelObject()->setSkin("txt_show_agreement");

	//m_pCouponButton = getButton("sbtn_tab1_small_button_3_stay");
	//m_pCouponButton->setType(Button::NoPressImg);
	//m_pCouponButton->setListener(this);
	//m_pCouponButton->getButtonSkelObject()->setSkin("txt_Coupon_input");

	//ccColor3B _smallBtnColor = ccc3(192, 165, 142);
	for (int _i = 0; _i < 3; _i++)
	{
		m_pBtnPanel[_i] = new Panel();
		m_pBtnPanel[_i]->construct(getMxmlPath() + "dmy_button_smiddle.mxml");
		m_pBtnPanel[_i]->getButton("sbtn_button")->setListener(this);
		m_pBtnPanel[_i]->getLabel("txt_button_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_pBtnPanel[_i]->getLabel("txt_button")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		CCPoint _btnPos = mAccountOptionPanel->getDummy("dmy_button_smiddle" + StringConverter::toString(_i + 1)).origin;
		m_pBtnPanel[_i]->setPosition(ccp(_btnPos.x, -_btnPos.y));
		//m_pBtnPanel[_i]->getLabel("txt_button")->setColor(_smallBtnColor);
		mAccountOptionPanel->addChild(m_pBtnPanel[_i]);
		m_pBtnPanel[_i]->release();
		m_pBtnPanel[_i]->getLabel("txt_button_under2")->setVisible(false);
		m_pBtnPanel[_i]->getLabel("txt_button2")->setVisible(false);
		m_pBtnPanel[_i]->getImage("skel_icon_gold2")->setVisible(false);
	}	
	//logout button
	m_pBtnPanel[3] = new Panel();
	m_pBtnPanel[3]->construct(getMxmlPath() + "dmy_button_middle.mxml");
	m_pBtnPanel[3]->getButton("sbtn_button")->setListener(this);
	m_pBtnPanel[3]->getLabel("txt_button_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_pBtnPanel[3]->getLabel("txt_button")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	CCPoint _btnPos2 = mAccountOptionPanel->getDummy("dmy_button_middle").origin;
	m_pBtnPanel[3]->setPosition(ccp(_btnPos2.x, -_btnPos2.y));
	mAccountOptionPanel->addChild(m_pBtnPanel[3]);
	m_pBtnPanel[3]->release();

	string _gameRuleBtnTxt = GameStringDepot::getSingletonPtr()->getString("TXT_GAME_RULE_UNIT");
	m_pBtnPanel[0]->getButton("sbtn_button")->setName("BUTTON_RULE");
	m_pBtnPanel[0]->getLabel("txt_button_under")->setString(_gameRuleBtnTxt.c_str());
	m_pBtnPanel[0]->getLabel("txt_button")->setString(_gameRuleBtnTxt.c_str());

	string _centerBtnTxt = GameStringDepot::getSingletonPtr()->getString("TXT_USER_CENTER_UNIT");
	m_pBtnPanel[1]->getButton("sbtn_button")->setName("BUTTON_CENTER");
	m_pBtnPanel[1]->getLabel("txt_button_under")->setString(_centerBtnTxt.c_str());
	m_pBtnPanel[1]->getLabel("txt_button")->setString(_centerBtnTxt.c_str());

	string _termBtnTxt = GameStringDepot::getSingletonPtr()->getString("TXT_TERM_UNIT");
	m_pBtnPanel[2]->getButton("sbtn_button")->setName("BUTTON_TERM");
	m_pBtnPanel[2]->getLabel("txt_button_under")->setString(_termBtnTxt.c_str());
	m_pBtnPanel[2]->getLabel("txt_button")->setString(_termBtnTxt.c_str());

	string _logoutBtnTxt = GameStringDepot::getSingletonPtr()->getString("TXT_LOGOUT_UNIT");
	m_pBtnPanel[3]->getButton("sbtn_button")->setName("BUTTON_LOGOUT");
	m_pBtnPanel[3]->getLabel("txt_button_under")->setString(_logoutBtnTxt.c_str());
	m_pBtnPanel[3]->getLabel("txt_button")->setString(_logoutBtnTxt.c_str());	

	m_MusicButton[0] = mGameOptionPanel->getButton("sbtn_checkbox1");
	m_MusicButton[0]->setType(Button::NoPressImg);
	m_MusicButton[0]->setListener(this);
		
	m_MusicButton[1] = mGameOptionPanel->getButton("sbtn_checkbox2");
	m_MusicButton[1]->setType(Button::NoPressImg);
	m_MusicButton[1]->setListener(this);

	m_EfxButton[0] = mGameOptionPanel->getButton("sbtn_checkbox3");
	m_EfxButton[0]->setType(Button::NoPressImg);
	m_EfxButton[0]->setListener(this);

	m_EfxButton[1] = mGameOptionPanel->getButton("sbtn_checkbox4");
	m_EfxButton[1]->setType(Button::NoPressImg);
	m_EfxButton[1]->setListener(this);

	m_VoiceButton[0] = mGameOptionPanel->getButton("sbtn_checkbox5");
	m_VoiceButton[0]->setType(Button::NoPressImg);
	m_VoiceButton[0]->setListener(this);

	m_VoiceButton[1] = mGameOptionPanel->getButton("sbtn_checkbox6");
	m_VoiceButton[1]->setType(Button::NoPressImg);
	m_VoiceButton[1]->setListener(this);

	m_HiddenButton[0] = mGameOptionPanel->getButton("sbtn_checkbox7");
	m_HiddenButton[0]->setType(Button::NoPressImg);
	m_HiddenButton[0]->setListener(this);

	m_HiddenButton[1] = mGameOptionPanel->getButton("sbtn_checkbox8");
	m_HiddenButton[1]->setType(Button::NoPressImg);
	m_HiddenButton[1]->setListener(this);

	m_PopupButton[0] = mGameOptionPanel->getButton("sbtn_checkbox9");
	m_PopupButton[0]->setType(Button::NoPressImg);
	m_PopupButton[0]->setListener(this);
	m_PopupButton[0]->setVisible(false);
	m_PopupButton[0]->setEnable(false);

	m_PopupButton[1] = mGameOptionPanel->getButton("sbtn_checkbox10");
	m_PopupButton[1]->setType(Button::NoPressImg);
	m_PopupButton[1]->setListener(this);
	m_PopupButton[1]->setVisible(false);
	m_PopupButton[1]->setEnable(false);

	CCPoint _panelPos;
	Panel* googleBtnPanel = new Panel();
	googleBtnPanel->construct(getMxmlPath() + "dmy_button_google.mxml");
	googleBtnPanel->getButton("sbtn_google")->setListener(this);
	_panelPos = mAccountOptionPanel->getDummy("dmy_button_google").origin;
	googleBtnPanel->setPosition(ccp(_panelPos.x, -_panelPos.y));
	mAccountOptionPanel->addChild(googleBtnPanel);
	googleBtnPanel->release();
	Panel* facebookBtnPanel = new Panel();
	facebookBtnPanel->construct(getMxmlPath() + "dmy_button_facebook.mxml");
	facebookBtnPanel->getButton("sbtn_facebook")->setListener(this);
	_panelPos = mAccountOptionPanel->getDummy("dmy_button_facebook").origin;
	facebookBtnPanel->setPosition(ccp(_panelPos.x, -_panelPos.y));
	mAccountOptionPanel->addChild(facebookBtnPanel);
	facebookBtnPanel->release();

	mGoogleBtnParty.button = googleBtnPanel->getButton("sbtn_google");
	mGoogleBtnParty.button->setName("BUTTON_GOOGLE_CONNECT");
	mGoogleBtnParty.buttonLabel = "option_btn_google";
	mGoogleBtnParty.connect = googleBtnPanel->getLabel("txt_google");
	mGoogleBtnParty.connected = googleBtnPanel->getLabel("txt_google_on");

	mFaceBookBtnParty.button = facebookBtnPanel->getButton("sbtn_facebook");
	mFaceBookBtnParty.buttonLabel = "option_btn_facebook";
	mFaceBookBtnParty.button->setName("BUTTON_FACEBOOK_CONNECT");
	mFaceBookBtnParty.connect = facebookBtnPanel->getLabel("txt_facebook");
	mFaceBookBtnParty.connected = facebookBtnPanel->getLabel("txt_facebook_on");

	//로그인 설정 및
	mAccountOptionPanel->getLabel("txt_option_info")->setString(GameStringDepot::getSingletonPtr()->getString("LobbyOptionPanel_CONNECT_DESC2").c_str());
	//계정 연동
	mAccountOptionPanel->getLabel("txt_account_under")->setString(GameStringDepot::getSingletonPtr()->getString("LobbyOptionPanel_CONNECT_TITLE").c_str());
	mAccountOptionPanel->getLabel("txt_account")->setString(GameStringDepot::getSingletonPtr()->getString("LobbyOptionPanel_CONNECT_TITLE").c_str());
	//게스트 계정만 계정
	mAccountOptionPanel->getLabel("txt_login_info")->setString(GameStringDepot::getSingletonPtr()->getString("LobbyOptionPanel_CONNECT_DESC1").c_str());



#ifdef USE_TEST_BTN
	int addWidth = 150;
	int fontLabelSize = 12;
	Button* mTest1 = new Button("TEST_1", Button::Normal);
	mTest1->setSkel("ui/main_menu_button_8888", "button_small_g", CCSizeMake(70, 38));
	mTest1->setPosition(ccp(-70 + addWidth * 0, 150));
	mGameOptionPanel->addChild(mTest1);
	mTest1->release();
	mTest1->setLabel("Notice", fontLabelSize);
	//mTest1->setLabel("achieveUnlock", fontLabelSize);
	mTest1->setListener(this);

	Button* mTest2 = new Button("TEST_2", Button::Normal);
	mTest2->setSkel("ui/main_menu_button_8888", "button_small_g", CCSizeMake(70, 38));
	mTest2->setPosition(ccp(-70 + addWidth * 1, 150));
	mGameOptionPanel->addChild(mTest2);
	mTest2->release();
	mTest2->setLabel("offerwall_plus", fontLabelSize);
	mTest2->setListener(this);

	Button* mTest3 = new Button("TEST_3", Button::Normal);
	mTest3->setSkel("ui/main_menu_button_8888", "button_small_g", CCSizeMake(70, 38));
	mTest3->setPosition(ccp(-70 + addWidth * 2, 150));
	mGameOptionPanel->addChild(mTest3);
	mTest3->release();
	mTest3->setLabel("messagetoearn", fontLabelSize);
	mTest3->setListener(this);

	Button* mTest4 = new Button("TEST_4", Button::Normal);
	mTest4->setSkel("ui/main_menu_button_8888", "button_small_g", CCSizeMake(70, 38));
	mTest4->setPosition(ccp(-70 + addWidth * 3, 150));
	mGameOptionPanel->addChild(mTest4);
	mTest4->release();
	mTest4->setLabel("UserInitiated", fontLabelSize);
	mTest4->setListener(this);

	Button* mTest5 = new Button("TEST_5", Button::Normal);
	mTest5->setSkel("ui/main_menu_button_8888", "button_small_g", CCSizeMake(70, 38));
	mTest5->setPosition(ccp(-70 + addWidth * 4, 150));
	mGameOptionPanel->addChild(mTest5);
	mTest5->release();
	mTest5->setLabel("showLeaderBoard", fontLabelSize);
	mTest5->setListener(this);

	Button* mTest6 = new Button("TEST_6", Button::Normal);
	mTest6->setSkel("ui/main_menu_button_8888", "button_small_g", CCSizeMake(70, 38));
	mTest6->setPosition(ccp(-70 + addWidth * 5, 150));
	mGameOptionPanel->addChild(mTest6);
	mTest6->release();
	mTest6->setLabel("Iap Request", fontLabelSize);
	mTest6->setListener(this);
#endif 	
}


bool LobbyOptionPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return false;
}


void LobbyOptionPanel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	
}


void LobbyOptionPanel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	
}

void LobbyOptionPanel::resume()
{
}

void LobbyOptionPanel::onClicked(const string& name)
{
	if (mLoginProcess)
		return;

	OptionDefineValue* _val = GameDataManager::getSingletonPtr()->m_pOptionValue;
	
	if (name == "sbtn_checkbox1" && _val->m_music == false)
	{
		_val->m_music = true;
		m_MusicCheck[0]->setVisible(true);
		m_MusicCheck[1]->setVisible(false);
		m_MusicCheck[0]->playAnimation("checkframe_start", false);
		SoundManager::getSingletonPtr()->playBGM("BGM_Lobby");
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_CHECK);
	}

	if (name == "sbtn_checkbox2" && _val->m_music == true)
	{
		_val->m_music = false;
		m_MusicCheck[0]->setVisible(false);
		m_MusicCheck[1]->setVisible(true);
		m_MusicCheck[1]->playAnimation("checkframe_start", false);
		SoundManager::getSingletonPtr()->stopBGM();
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_CHECK);
	}

	if (name == "sbtn_checkbox3" && _val->m_effect == false)
	{
		_val->m_effect = true;
		m_EfxCheck[0]->setVisible(true);
		m_EfxCheck[1]->setVisible(false);
		m_EfxCheck[0]->playAnimation("checkframe_start", false);
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_CHECK);
	}
	
	if (name == "sbtn_checkbox4" && _val->m_effect == true)
	{
		_val->m_effect = false;
		m_EfxCheck[0]->setVisible(false);
		m_EfxCheck[1]->setVisible(true);
		m_EfxCheck[1]->playAnimation("checkframe_start", false);
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_CHECK);
	}

	if (name == "sbtn_checkbox5" && _val->m_voice == false)
	{
		_val->m_voice = true;
		m_VoiceCheck[0]->setVisible(true);
		m_VoiceCheck[1]->setVisible(false);
		m_VoiceCheck[0]->playAnimation("checkframe_start", false);
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_CHECK);
	}
	
	if (name == "sbtn_checkbox6" && _val->m_voice == true)
	{
		_val->m_voice = false;
		m_VoiceCheck[0]->setVisible(false);
		m_VoiceCheck[1]->setVisible(true);
		m_VoiceCheck[1]->playAnimation("checkframe_start", false);
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_CHECK);
	}

	if (name == "sbtn_checkbox7"&& _val->m_hiddenCard == false)
	{
		_val->m_hiddenCard = true;
		m_HiddenCheck[0]->setVisible(true);
		m_HiddenCheck[1]->setVisible(false);
		m_HiddenCheck[0]->playAnimation("checkframe_start", false);
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_CHECK);
	}
	
	if (name == "sbtn_checkbox8"&& _val->m_hiddenCard == true)
	{
		_val->m_hiddenCard = false;
		m_HiddenCheck[0]->setVisible(false);
		m_HiddenCheck[1]->setVisible(true);
		m_HiddenCheck[1]->playAnimation("checkframe_start", false);
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_CHECK);
	}

	if (name == "sbtn_checkbox9"&& _val->m_popupAlram == false)
	{
		_val->m_popupAlram = false;
		m_PopupCheck[0]->setVisible(true);
		m_PopupCheck[1]->setVisible(false);
		m_PopupCheck[0]->playAnimation("checkframe_start", false);
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_CHECK);
	}
	
	if (name == "sbtn_checkbox10"&& _val->m_popupAlram == true)
	{
		_val->m_popupAlram = true;
		m_PopupCheck[0]->setVisible(false);
		m_PopupCheck[1]->setVisible(true);
		m_PopupCheck[1]->playAnimation("checkframe_start", false);
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_CHECK);
	}

	if (name == "BUTTON_RULE")
	{
		//Rule//WEB VIEW
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		GameDataManager::getSingletonPtr()->ShowCustomWebview(WEB_HELP_TYPE);
	}

	if (name == "BUTTON_CENTER")
	{
		//Customer Center//WEB VIEW
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		GameDataManager::getSingletonPtr()->ShowCustomWebview(WEB_ASK_TYPE);
	}

	if (name == "BUTTON_TERM")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		GameDataManager::getSingletonPtr()->ShowCustomWebview(WEB_TERM_TYPE);
	}

	if (name == "BUTTON_LOGOUT")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		//LOGOUT
		string _title = "LOGOUT";
		string _content = GameStringDepot::getSingletonPtr()->getString("TXT_LOGOUT_QUESTION");
		string _OkMsg = "MSG_LOGOUT";
		SimplePopupPanel* panel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::LOG_OUT, _content, _title);
		if (panel)
		{
			panel->SetOkEventMsg(_OkMsg);
			panel->setListener(WebService::getSingletonPtr());
			LayerManager::getSingleton().pushDynamicLayer(panel, DYNAMIC_PUSH_LAYER);
		}
	}
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	if (name == "BUTTON_COUPON")
	{
		//COUPON//WEB VIEW
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		IGAWorksManager::getSingletonPtr()->OpenCouponDialog(true);
	}
#endif
	else if (name == "openGameOptionBtn") {
		//setGameOptionFocus(true);
		refreshFocusPanel(EN_OPTION);
	}
	else if (name == "openAccountOptionBtn") {
		//setGameOptionFocus(false);
		refreshFocusPanel(EN_ACCOUNT);
	}
	else if (name == "openNoticeOptionBtn") {
		//setGameOptionFocus(false);
		refreshFocusPanel(EN_NOTICE);
	}
	else if (name == "BUTTON_GOOGLE_CONNECT") {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
		//구글 연결을 눌렀다.
		if (mGoogleBtnParty.connected->isVisible()) {
			//이미 게스트라면
			if (GameDataManager::getSingleton().getUserInfo()->islogingoogle()) {				
				CCLog("GoogleManager sendPlatoformOutReq");
				WebService::getSingleton().sendPlatoformOutReq(GOOGLE);
			}			
		}
		else {
			CCLog("GoogleManager loginIn");
			GoogleManager::getSingleton().googleLogin();
		}
#endif
	}
	else if (name == "BUTTON_FACEBOOK_CONNECT") {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		string title = GameStringDepot::getSingletonPtr()->getString("TXT_INFORMATION");
		string detail = GameStringDepot::getSingletonPtr()->getString("UPDATE_DESC");
		PanelHelper::pushSimpleConfirmPopupPanel(detail, title);

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
//		if (mFaceBookBtnParty.connected->isVisible()) {
//			CCLog("facebook OUT");
//			WebService::getSingleton().sendPlatoformOutReq(FACEBOOK);
//
//			FacebookManager::getSingleton().LogOut();
//		}
//		else {
//			FacebookManager::getSingleton().ConnectFB();
//		}		
//#endif

	}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	else if (name == "TEST_1") {
		//GoogleManager::getSingleton().achieveUnlock();	//달성				
		//FacebookManager::getSingleton().RequestInvitableUserList(false);
// 		if (VungleManager::getSingleton().isReadyShowAds()) {			
// 			CCLog("TEST_2");
// 			int64 userId = GameDataManager::getSingleton().m_pPlayerData->GetUID();
// 			VungleManager::getSingleton().showAds(StringConverter::toString(userId));
// 		}		
// 		else {
// 			CCLog("TEST_ ERROR");
// 		}	

	}
	else if (name == "TEST_2") {
		//GoogleManager::getSingleton().achieveIncrement();		
		

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		//FacebookManager::getSingleton().appInviteOpenDialog();
		//IGAWorksManager::getSingleton().LoadPopup();
		
#endif
	}
	else if (name == "TEST_3") {
		//GoogleManager::getSingleton().showAchieve();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		
		//FacebookManager::getSingleton().appLink();
		//IGAWorksManager::getSingleton().OpenCouponDialog(true);
#endif
	}
	else if (name == "TEST_4") {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		
		//IGAWorksManager::getSingleton().OpenAdPopcorn("Test");
#endif
		//GoogleManager::getSingleton().submitLeaderBoard(100);
	}
	else if (name == "TEST_5") {
		GoogleManager::getSingleton().showLeaderBoard();
	}	
	else if (name == "TEST_6") {
		//IapManager::getSingleton().setDevelopMode(true);
		CCLog("sendWPayReserveReq TEST_6");
		//IapManager::getSingleton().sendWPayReserveReq(2);
		IapManager::getSingleton().launchPurchaseFlow("com.numixent.gamble.test.id1", "", "1");
	}
#endif	
}

void LobbyOptionPanel::update(float dt)
{
	/*
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	if (mBeLogOut) {
		if (GoogleManager::getSingleton().isConnected()) {
			GoogleManager::getSingleton().googleLogOut();			
			unscheduleUpdate();			
		}
	}
#endif
	*/
    updateNotiWidget();
}

bool LobbyOptionPanel::handling(STCMD &stCmd)
{
	if (!isVisible()) {
		CCLog("NO vislble false");
		return false;
	}

	if (auto *pstIt = castCMD<STCMD_GOOGLE_LOGIN_RESULT>(&stCmd))
	{
		//구글 로그인 결과
		STCMD_GOOGLE_LOGIN_RESULT res = *pstIt;
		if (res.isSucess) {
			//성공
			WebService::getSingleton().sendGooglePlatFormReq();
		}
		else {
			//실패
		}

		return true;
	}
	else if (auto *pstIt = castCMD<STCMD_GOOGLE_LOGOUT_RESULT>(&stCmd))
	{
// 				이미 게스트라면
// 				if (GameDataManager::getSingleton().getUserInfo()->islogingoogle()) {
// 					//서버에 logout 보낸다.
// 					CCLog("GOOGLE platform out");
// 					WebService::getSingleton().sendPlatoformOutReq(GOOGLE);
// 				}
// 				else {
// 					CCLog("GOOGLE out");
// 					CCUserDefault::sharedUserDefault()->setIntegerForKey(NSGameConfig::keyLoginType.c_str(), 0);
// 					CCUserDefault::sharedUserDefault()->flush();
// 					//구글 로그인 결과
// 					STCMD_GOOGLE_LOGOUT_RESULT res = *pstIt;
// 					if (res.isSucess) {
// 						//성공
// 						if (!mBeLogOut)
// 							SceneUtil::changeScene(SceneUtil::SceneTitle);
// 					}
// 					else {
// 						//실패
// 					}
// 					mBeLogOut = false;
// 				}		
		return true;
	}
	else if (auto *pstIt = castCMD<STCMD_IAP_ONESTORE_REQUEST_RESULT>(&stCmd))
	{
		STCMD_IAP_ONESTORE_REQUEST_RESULT res = *pstIt;
		if (res.isSucess) {
			CCLog("STCMD_IAP_REQUEST_RESULT sucess res.tid = %s , res.txid = %s , res.receipt = %s", res.tid.c_str(), res.txid.c_str(), res.receipt.c_str());
			sendW_PayReq(res.tid, res.txid, res.receipt);
		}
		else {
			CCLog("STCMD_IAP_REQUEST_RESULT false");
			SimplePopupPanel* panel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errMsg, "IAP Request");
			LayerManager::getSingleton().pushDynamicLayer(panel, DYNAMIC_PUSH_LAYER);
		}		
		return true;
	}
	else if (auto *pstIt = castCMD<STCMD_UNITADS_FINISH>(&stCmd)) {
		CCLog("STCMD_UNITADS_FINISH");
		return true;
	}
	return false;
}

void LobbyOptionPanel::ShowOptionStart()
{
	setVisible(true);
	//unscheduleUpdate();
	//scheduleUpdate();
	ShowOptionEnd();

	//runAction(CCSequence::create(
	//	CCMoveTo::create(0.4f, m_ShowPosition),
	//	CCCallFunc::create(this, callfunc_selector(LobbyOptionPanel::ShowOptionEnd)),
	//	NULL));
}

void LobbyOptionPanel::HideOptionStart()
{
	//hide title
	//getSkel("skel_title_back")->setVisible(false);
	//getSkel("skel_option_title")->setVisible(false);
	//getSkel("skel_option_mark")->setVisible(false);

	//runAction(CCSequence::create(
	//	CCMoveTo::create(0.4f, m_HiddenPosition),
	//	CCDelayTime::create(0.1f),
	//	CCCallFunc::create(this, callfunc_selector(LobbyOptionPanel::HideOptionEnd)),
	//	NULL));
}

void LobbyOptionPanel::ShowOptionEnd()
{
	//show title
	//getSkel("skel_title_back")->setVisible(true);
	//getSkel("skel_option_title")->setVisible(true);
	//getSkel("skel_option_mark")->setVisible(true);
	GameDataManager::getSingletonPtr()->FreeUiProcess();

	if (LayerManager::getSingletonPtr()->hasLayer("LobbyTopUI"))
	{
		LobbyTopUiPanel* _pTopUiPanel = dynamic_cast<LobbyTopUiPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyTopUI"));
		if (_pTopUiPanel)
		{
			_pTopUiPanel->SetTopTitle(LobbyUiStatus::LOBBY_UI_OPTION);
		}
	}

}

void LobbyOptionPanel::HideOptionEnd()
{
	setVisible(false);
	//unscheduleUpdate();
	SaveOption();

	GameDataManager::getSingletonPtr()->FreeUiProcess();

	if (LayerManager::getSingletonPtr()->hasLayer("LobbyTopUI"))
	{
		LobbyTopUiPanel* _pTopUiPanel = dynamic_cast<LobbyTopUiPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyTopUI"));
		if (_pTopUiPanel)
		{
			_pTopUiPanel->SetTopTitle(LobbyUiStatus::LOBBY_UI_MAIN);
		}
	}

	LayerManager::getSingleton().popLayer("LobbyOption");
	//LayerManager::getSingleton().popLayer("LobbyTopUI");
}

void LobbyOptionPanel::SaveOption()
{
	CCUserDefault* _pUserDefault = CCUserDefault::sharedUserDefault();

	_pUserDefault->setBoolForKey(gOptionKey[eOption_BGM], GameDataManager::getSingletonPtr()->m_pOptionValue->m_music);
	_pUserDefault->setBoolForKey(gOptionKey[eOption_EFX], GameDataManager::getSingletonPtr()->m_pOptionValue->m_effect);
	_pUserDefault->setBoolForKey(gOptionKey[eOption_VOICE], GameDataManager::getSingletonPtr()->m_pOptionValue->m_voice);
	_pUserDefault->setBoolForKey(gOptionKey[eOption_HIDDEN], GameDataManager::getSingletonPtr()->m_pOptionValue->m_hiddenCard);
	_pUserDefault->setBoolForKey(gOptionKey[eOption_POPUP], GameDataManager::getSingletonPtr()->m_pOptionValue->m_popupAlram);
	
	_pUserDefault->flush();
}

void LobbyOptionPanel::initGameOptionPanel()
{
	mGameOptionPanel = new Panel();
	addChild(mGameOptionPanel);
	mGameOptionPanel->release();
	mGameOptionPanel->construct(getMxmlPath() + "dmy_option_tab1.mxml");
	CCPoint _tapPos = getDummy("dmy_option_tab1").origin;
	_tapPos.y = -_tapPos.y;
	mGameOptionPanel->setPosition(_tapPos);
}

void LobbyOptionPanel::initAccountOptionPanel()
{
	mAccountOptionPanel = new Panel();
	addChild(mAccountOptionPanel);
	mAccountOptionPanel->release();
	mAccountOptionPanel->construct(getMxmlPath() + "dmy_option_tab2.mxml");
	CCPoint _tapPos = getDummy("dmy_option_tab2").origin;
	_tapPos.y = -_tapPos.y;
	mAccountOptionPanel->setPosition(_tapPos);
}

void LobbyOptionPanel::initNoticeOptionPanel()
{
	CCPoint _shop3Pos = getImage("dmy_option_tab3")->getPosition();
	mNoticeOptionPanel = new LobbyOptionNoticePanel();
	CCSize size = mNoticeOptionPanel->getContentSize();
	mNoticeOptionPanel->setPosition(_shop3Pos);
	addChild(mNoticeOptionPanel);
	mNoticeOptionPanel->release();
	mNoticeOptionPanel->setActivate(false);
}

void LobbyOptionPanel::refreshFocusPanel(TAP_BUTTON enButton)
{
	if (enButton == EN_OPTION)
	{
		m_pTapPanel->getButton("sbtn_button")->setSkelAnimation("tab_on");
		m_pTapAccountPanel->getButton("sbtn_button")->setSkelAnimation("tab_off");
		m_pTapNoticePanel->getButton("sbtn_button")->setSkelAnimation("tab_off");

		m_pTapPanel->getLabel("txt_off_tab")->setVisible(false);
		m_pTapPanel->getLabel("txt_on_tab")->setVisible(true);
		m_pTapAccountPanel->getLabel("txt_off_tab")->setVisible(true);
		m_pTapAccountPanel->getLabel("txt_on_tab")->setVisible(false);
		m_pTapNoticePanel->getLabel("txt_off_tab")->setVisible(true);
		m_pTapNoticePanel->getLabel("txt_on_tab")->setVisible(false);
		
		if (mGameOptionPanel->getPositionX() < 0)
			mGameOptionPanel->setPositionX(mGameOptionPanel->getPositionX() + DESIGN_WIDTH);

		if (mAccountOptionPanel->getPositionX() >= 0)
			mAccountOptionPanel->setPositionX(mAccountOptionPanel->getPositionX() - DESIGN_WIDTH);
		if (mNoticeOptionPanel->getPositionX() >= 0)
			mNoticeOptionPanel->setPositionX(mNoticeOptionPanel->getPositionX() - DESIGN_WIDTH);

		mGameOptionPanel->setVisible(true);
		mAccountOptionPanel->setVisible(false);
		mNoticeOptionPanel->setVisible(false);
	}
	else if (enButton == EN_ACCOUNT)
	{
		m_pTapPanel->getButton("sbtn_button")->setSkelAnimation("tab_off");
		m_pTapAccountPanel->getButton("sbtn_button")->setSkelAnimation("tab_on");
		m_pTapNoticePanel->getButton("sbtn_button")->setSkelAnimation("tab_off");

		m_pTapPanel->getLabel("txt_off_tab")->setVisible(true);
		m_pTapPanel->getLabel("txt_on_tab")->setVisible(false);
		m_pTapAccountPanel->getLabel("txt_off_tab")->setVisible(false);
		m_pTapAccountPanel->getLabel("txt_on_tab")->setVisible(true);
		m_pTapNoticePanel->getLabel("txt_off_tab")->setVisible(true);
		m_pTapNoticePanel->getLabel("txt_on_tab")->setVisible(false);


		if (mAccountOptionPanel->getPositionX() < 0)
			mAccountOptionPanel->setPositionX(mAccountOptionPanel->getPositionX() + DESIGN_WIDTH);

		if (mGameOptionPanel->getPositionX() >= 0)
			mGameOptionPanel->setPositionX(mGameOptionPanel->getPositionX() - DESIGN_WIDTH);
		if (mNoticeOptionPanel->getPositionX() >= 0)
			mNoticeOptionPanel->setPositionX(mNoticeOptionPanel->getPositionX() - DESIGN_WIDTH);

		mGameOptionPanel->setVisible(false);
		mAccountOptionPanel->setVisible(true);
		mNoticeOptionPanel->setVisible(false);
	}
	else if (enButton == EN_NOTICE)
	{
		m_pTapPanel->getButton("sbtn_button")->setSkelAnimation("tab_off");
		m_pTapAccountPanel->getButton("sbtn_button")->setSkelAnimation("tab_off");
		m_pTapNoticePanel->getButton("sbtn_button")->setSkelAnimation("tab_on");

		m_pTapPanel->getLabel("txt_off_tab")->setVisible(true);
		m_pTapPanel->getLabel("txt_on_tab")->setVisible(false);
		m_pTapAccountPanel->getLabel("txt_off_tab")->setVisible(true);
		m_pTapAccountPanel->getLabel("txt_on_tab")->setVisible(false);
		m_pTapNoticePanel->getLabel("txt_off_tab")->setVisible(false);
		m_pTapNoticePanel->getLabel("txt_on_tab")->setVisible(true);

		if (mNoticeOptionPanel->getPositionX() < 0)
			mNoticeOptionPanel->setPositionX(mNoticeOptionPanel->getPositionX() + DESIGN_WIDTH);

		if (mAccountOptionPanel->getPositionX() >= 0)
			mAccountOptionPanel->setPositionX(mAccountOptionPanel->getPositionX() - DESIGN_WIDTH);
		if (mGameOptionPanel->getPositionX() >= 0)
			mGameOptionPanel->setPositionX(mGameOptionPanel->getPositionX() - DESIGN_WIDTH);

		mGameOptionPanel->setVisible(false);
		mAccountOptionPanel->setVisible(false);
		mNoticeOptionPanel->setVisible(true);
		NotiDataManager::getSingletonPtr()->setNoticeNoti(false); //공지알림 해제
		CCUserDefault::sharedUserDefault()->setBoolForKey(NSGameConfig::keyNotiNotification.c_str(), false);

		mNoticeOptionPanel->SetLetterlList();
	}
}

void LobbyOptionPanel::refreshAccountPanel()
{
	//guest 라면
	eLoginType type = GameDataManager::getSingletonPtr()->m_LoginType;	

	bool isGoogleLogined = GameDataManager::getSingleton().getUserInfo()->islogingoogle();
	bool isFaceBookLogined = GameDataManager::getSingleton().getUserInfo()->isloginfacebook();
	
	CCLog("isGoogleLogined = %d , isFaceBookLogined = %d", isGoogleLogined, isFaceBookLogined);

	if (isGoogleLogined == true) {
		setConnected(mGoogleBtnParty);			
	}
	else {
		setPossibleConnect(mGoogleBtnParty);	//연결해주세요
	}
		
	if (isFaceBookLogined == true) {			
		setConnected(mFaceBookBtnParty);
	}
	else {
		setPossibleConnect(mFaceBookBtnParty);	//연결해주세요
	}	
}

void LobbyOptionPanel::setConnected(ACCOUNT_BTN_PARTY& party)
{
	//연결됨
	party.button->setEnable(true);
	party.button->setGrayscale(false);
	party.button->setSkelAnimation(party.buttonLabel + "_on");
	party.connect->setVisible(false);
	party.connected->setVisible(true);
}

void LobbyOptionPanel::setPossibleConnect(ACCOUNT_BTN_PARTY& party)
{
	party.button->setEnable(true);
	party.button->setGrayscale(false);
	party.button->setSkelAnimation(party.buttonLabel);
	party.connect->setVisible(true);
	party.connected->setVisible(false);
}

void LobbyOptionPanel::setNotConnected(ACCOUNT_BTN_PARTY& party)
{
	party.button->setEnable(false);
	party.button->setGrayscale(true);
	party.button->setSkelAnimation(party.buttonLabel);
	party.connect->setVisible(true);
	party.connected->setVisible(false);
}

void LobbyOptionPanel::onRefresh()
{
	if (mAccountOptionPanel)
		refreshAccountPanel();
}

void LobbyOptionPanel::beLogOut()
{
	mBeLogOut = true;
	//unscheduleUpdate();
	scheduleUpdate();
}

void LobbyOptionPanel::sendW_PayReq(string tID, string txId, string receipt)
{
	CCLog("sendW_PayReq");
	W_PayReq req;
	req.set_tid(tID);
	req.set_txid(txId);
	req.set_receipt(receipt);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	if (IapManager::getSingleton().getPaymentType() == IapManager::GOOGLE_STORE) {
		req.set_order_id(txId);
	}
#endif
	HttpMessage msg(req, HttpResponseHandler(LobbyOptionPanel::recvW_PayRes), this);
	HttpManager::getSingleton().send(msg);
}

void LobbyOptionPanel::recvW_PayRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_PayRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success()) {
		CCLog("recvW_PayRes sucess");
		LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, "Sucess"), DYNAMIC_PUSH_LAYER);
		//똑같은 걸 두번 보낼수도 있어서...
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if (IapManager::getSingleton().getPaymentType() == IapManager::GOOGLE_STORE) {
			CCLog("W_PayRes checkAsyncInventory");
			IapManager::getSingleton().checkAsyncInventory();
		}
#endif

	}
	else {
		CCLog("recvW_PayRes fail");
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
	}
	if (res.has_playerinfo())
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());
}

void LobbyOptionPanel::onDestroy()
{
	SaveOption();
	Panel::onDestroy();
}

void LobbyOptionPanel::initNotiWidget()
{
    {
        NotiWidget* notiWidget = new NotiWidget(NotiWidget::NOTI_OPTION_NOTICE);
        m_pTapNoticePanel->addChild(notiWidget);
        notiWidget->release();
        notiWidget->setPosition(m_pTapNoticePanel->getImage("dmy_notification_icon")->getPosition());
        mNotiWidgets.push_back(notiWidget);
    }
}

void LobbyOptionPanel::updateNotiWidget()
{
    for (int i = 0; i < mNotiWidgets.size(); i++)
    {
        mNotiWidgets[i]->refresh();
    }
}

void LobbyOptionPanel::onEnter()
{
	Panel::onEnter();

	setTouchable(true);
	scheduleUpdate();
}
