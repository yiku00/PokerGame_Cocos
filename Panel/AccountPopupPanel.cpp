#include "pch.h"
#include "AccountPopupPanel.h"
#include "HeroUtil.h"
#include "GameStringDepot.h"
#include "GameDataManager.h"
#include "PopupUserReplayPanel.h"
#include "SimplePopupPanel.h"
#include "SceneUtil.h"
#include "SynopsisUiPanel.h"
#include "LobbyUIPanel.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	#include "android/AndroidUtilManager.h"
#endif
#include "PokerResourceHelper.h"

AccountPopupPanel::AccountPopupPanel(AccountPopupType type, int param1, int param2) : Panel("PopupPanel")
{
	mType = type;
	mTarget = NULL;
	mGeneralListener = NULL;

	mParam1 = param1;
	mParam2 = param2;

	mIsAgree0 = 0, mIsAgree1 = 0;

	initPanel();	
	ShowPanel(true);

	GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_ACCOUNT_POPUP);
	LayerManager::getSingleton().pushDynamicLayer(this, DYNAMIC_PUSH_LAYER);
}

AccountPopupPanel::~AccountPopupPanel()
{
}

void AccountPopupPanel::onClicked(const string& name)
{
	//SoundManager::getSingleton().playEffect(BTN_CLICK);

	//GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
	////LOGOUT
	//string _title = "LOGOUT";
	//string _content = GameStringDepot::getSingletonPtr()->getString("TXT_LOGOUT_QUESTION");
	//string _OkMsg = "MSG_LOGOUT";
	//SimplePopupPanel* panel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::LOG_OUT, _content, _title);
	//if (panel)
	//{
	//	panel->SetOkEventMsg(_OkMsg);
	//	panel->setListener(WebService::getSingletonPtr());
	//	LayerManager::getSingleton().pushDynamicLayer(panel, DYNAMIC_PUSH_LAYER);
	//}

	mEventName = name;

	if (name == "sbtn_checkbox1")
	{
		AgreeCheck(0, mIsAgree0 ^ true);
	}
	else if (name == "sbtn_checkbox2")
	{
		AgreeCheck(1, mIsAgree1 ^ true);
	}
	else if (name == "sbtn_small_button_4_stay1")//개인정보
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		GameDataManager::getSingletonPtr()->ShowCustomWebview(WEB_POLICY_TYPE);
	}
	else if (name == "sbtn_small_button_4_stay2")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		GameDataManager::getSingletonPtr()->ShowCustomWebview(WEB_MOBLIE_USAGE);
	}
	else if (name == "sbtn_small_button_2_stay1")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		ShowPanel(false);
	}
	// 동의합니다. 버튼 클릭시 작동
	else if (name == "sbtn_small_button_2y_stay")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		//LOGOUT
		string _title = GameStringDepot::getSingletonPtr()->getString("TXT_CERTIFICATION");
		string _content = GameStringDepot::getSingletonPtr()->getString("TXT_CERTIFICATION_CONTENT");
		string _OkMsg = GameStringDepot::getSingletonPtr()->getString("TXT_CERTIFICATION_OK");
		SimplePopupPanel* panel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OK_CERTIFICATION, _content, _title);
		if (panel)
		{
			panel->SetOkEventMsg(_OkMsg);
			//panel->setButtonListener(this);
			panel->setListener(WebService::getSingletonPtr());
			LayerManager::getSingleton().pushDynamicLayer(panel, DYNAMIC_PUSH_LAYER);
		}

		/*GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		ShowPanel(false);
		SceneUtil::changeScene(SceneUtil::SceneSynopsis);*/
	}
	else if (name == "sbtn_small_button_2y_stay1") {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
	}
	else if (name == "sbtn_title_cancel_stay")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		if (mType == AccountPopupType::NICKNAME_TYPE)
		{
			ShowPanel(false);			
		}
		else
			ShowPanel(false);
	}
	else if (name == "sbtn_cancel")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		if (mType == AccountPopupType::NICKNAME_TYPE)
		{
			ShowPanel(false);
		}
		else
			ShowPanel(false);
	}
	else if (name == "sbtn_Ok_btn")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		if (mType == AccountPopupType::NICKNAME_TYPE || mType == AccountPopupType::NICKNAME_REPAIR_TYPE)
		{
			string name = getLabel("fld_nickname")->getString();

			int isCheck = GameDataManager::getSingletonPtr()->CheckNickname(name, 8);
			
			string msgText;
			switch (isCheck)
			{
				case NCE_LENGTH_ERROR :
					msgText = GameStringDepot::getSingleton().getString("TXT_NICKNAME_LENGTH_ERROR");
					LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, msgText), DYNAMIC_PUSH_LAYER);
					break;
				case NCE_SPECIAL_LETTER_ERROR :
					msgText = GameStringDepot::getSingleton().getString("TXT_NICKNAME_SPECIAL_LETTER_ERROR");
					LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, msgText), DYNAMIC_PUSH_LAYER);
					break;
				case NCE_SPACE_ERROR :
					msgText = GameStringDepot::getSingleton().getString("TXT_NICKNAME_SPACE_LETTER_ERROR");
					LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, msgText), DYNAMIC_PUSH_LAYER);
					break;
				case NCE_SUCCESS:
				{
					AccountCreateInfo * info = GameDataManager::getSingletonPtr()->GetAccountCreateInfo();
					GameDataManager::getSingletonPtr()->SetAccountNickname(name);
					
					string _title = GameStringDepot::getSingletonPtr()->getString("TXT_INFORMATION");
					string _content;
					string _OkMsg;

					if (!GameDataManager::getSingletonPtr()->m_pPlayerData->m_isNameChange)
						_content = GameStringDepot::getSingletonPtr()->getString("TXT_NICKNAME_NOTICE_FREE");
					else
						_content = GameStringDepot::getSingletonPtr()->getString("TXT_NICKNAME_NOTICE");
					

					if (mType == NICKNAME_TYPE)
					{
						_OkMsg = "sendPlayerInfo";
						_OkMsg += "/" + info->nickname + "/" + StringConverter::toString(info->characterIdx);
						WebService::getSingletonPtr()->onLayerMessage(_OkMsg);
					}
					else {
						SimplePopupPanel* panel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::ShopYESNONotice, _content, _title);
						int num = info->characterIdx;
						
						if (!panel)
							return;
						
						_OkMsg = "sendPlayerName";
						_OkMsg += "/" + info->nickname;

						panel->SetOkEventMsg(_OkMsg);
						panel->setListener(WebService::getSingletonPtr());
						LayerManager::getSingleton().pushDynamicLayer(panel, DYNAMIC_PUSH_LAYER);
					}

					
				}
			}
		}
	}
	else if (name == "sbtn_small_button_0")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		SelectCharacter(1);
	}
	else if (name == "sbtn_small_button_1")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		SelectCharacter(2);
	}
	else if (name == "sbtn_small_button_2")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		SelectCharacter(3);
	}
	else if (name == "sbtn_small_button_3")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		SelectCharacter(4);
	}
	else if (name == "sbtn_nickname_touch")
	{
		getTextField("fld_nickname")->setString(GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_NickName.c_str());
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		GameDataManager::getSingletonPtr()->m_bEditTextField = false;
		GameDataManager::getSingletonPtr()->m_onFocusTextFeild = getTextField("fld_nickname");
		std::string _fieldText = getTextField("fld_nickname")->getString();
		//AndroidUtilManager::getSingletonPtr()->ReleaseCustomEditTextField();
		AndroidUtilManager::getSingletonPtr()->InitCustomEditTextField();
		AndroidUtilManager::getSingletonPtr()->ShowCustomEditTextField(_fieldText);

#else		
		getTextField("fld_nickname");
		getTextField("fld_nickname")->setListener(this);
		getTextField("fld_nickname")->attachWithIME();


#endif
	}
	
}

void AccountPopupPanel::ShowPanel(bool isVisible)
{
	if (isVisible)
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_POPUPOPEN);

	if (!isVisible)
	{
		GameDataManager::getSingletonPtr()->PopUiState();
		clearThisPanel();
	}
		
}

void AccountPopupPanel::initPanel()
{
	addMouseBlockPanel(this , true);

	switch (mType)
	{
		case AGREE_TYPE:
			MakeAccountPanel();
			break;		
		case NICKNAME_TYPE:
			MakeNicknamePanel();
			break;
		case NICKNAME_REPAIR_TYPE :
			MakeNicknamePanel();
			break;
	}
}

void AccountPopupPanel::MakeAccountPanel()
{
	construct(getMxmlPath() + "dmy_account_created.mxml");

	// 약관1 체크
	getButton("sbtn_checkbox1")->setListener(this);
	getButton("sbtn_checkbox1")->setTouchable(true, 0, false);
	
	// 약관2 체크
	getButton("sbtn_checkbox2")->setListener(this);
	getButton("sbtn_checkbox2")->setTouchable(true, 0, false);
	
	// 비동의 버튼
	//getButton("sbtn_small_button_2_stay1")->setListener(this);
	//getButton("sbtn_small_button_2_stay1")->setTouchable(true, 0, false);
	////getButton("sbtn_small_button_2_stay1")->setType(Button::NoPressImg);
	//getButton("sbtn_small_button_2_stay1")->getButtonSkelObject()->setSkin("txt_not_agreement");

	// 동의 버튼
	//getButton("sbtn_small_button_2y_stay")->setListener(this);
	//getButton("sbtn_small_button_2y_stay")->setTouchable(true, 0, false);
	////getButton("sbtn_small_button_2_stay")->setType(Button::NoPressImg);
	//getButton("sbtn_small_button_2y_stay")->getButtonSkelObject()->setSkin("txt_agreement");

	// 약관 보기 1
	//getButton("sbtn_small_button_4_stay1")->setListener(this);
	//getButton("sbtn_small_button_4_stay1")->setTouchable(true, 0, false);
	//getButton("sbtn_small_button_4_stay1")->getButtonSkelObject()->setSkin("txt_contents_view");

	// 약관 보기 2
	//getButton("sbtn_small_button_4_stay2")->setListener(this);
	//getButton("sbtn_small_button_4_stay2")->setTouchable(true, 0, false);
	//getButton("sbtn_small_button_4_stay2")->getButtonSkelObject()->setSkin("txt_contents_view");

	string _btnString[4];
	_btnString[0] = GameStringDepot::getSingletonPtr()->getString("TXT_SHOWTERM_UNIT");
	_btnString[1] = GameStringDepot::getSingletonPtr()->getString("TXT_SHOWTERM_UNIT");
	_btnString[2] = GameStringDepot::getSingletonPtr()->getString("TXT_AGREE_UNIT");
	_btnString[3] = GameStringDepot::getSingletonPtr()->getString("TXT_DISAGREE_UNIT");

	for (int _i = 0; _i < 4; _i++)
	{
		CCPoint _pos;
		m_pBtnPanel[_i] = new Panel();
		if (_i == 0 || _i == 1)
		{
			m_pBtnPanel[_i]->construct(getMxmlPath() + "dmy_button_small.mxml");
			_pos = getDummy("dmy_button_small" + StringConverter::toString(_i + 1)).origin;
		}
		else if (_i == 2)
		{
			m_pBtnPanel[_i]->construct(getMxmlPath() + "dmy_button_middle.mxml");
			_pos = getDummy("dmy_button_middle").origin;
		}
		else if (_i == 3)
		{
			m_pBtnPanel[_i]->construct(getMxmlPath() + "dmy_button_smiddle.mxml");
			_pos = getDummy("dmy_button_smiddle").origin;

			m_pBtnPanel[_i]->getLabel("txt_button_under2")->setVisible(false);
			m_pBtnPanel[_i]->getLabel("txt_button2")->setVisible(false);
			m_pBtnPanel[_i]->getSkel("skel_icon_gold2")->setVisible(false);
		}

		m_pBtnPanel[_i]->getLabel("txt_button_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_pBtnPanel[_i]->getLabel("txt_button")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

		m_pBtnPanel[_i]->getLabel("txt_button_under")->setString(_btnString[_i].c_str());
		m_pBtnPanel[_i]->getLabel("txt_button")->setString(_btnString[_i].c_str());

		_pos.y = -_pos.y;
		m_pBtnPanel[_i]->setPosition(_pos);
		addChild(m_pBtnPanel[_i]);
		m_pBtnPanel[_i]->release();
	}
	
	m_pShowTerm1 = m_pBtnPanel[0]->getButton("sbtn_button");
	m_pShowTerm2 = m_pBtnPanel[1]->getButton("sbtn_button");
	m_pAgree = m_pBtnPanel[2]->getButton("sbtn_button");
	m_pCancel = m_pBtnPanel[3]->getButton("sbtn_button");

	m_pShowTerm1->setName("sbtn_small_button_4_stay1");
	m_pShowTerm2->setName("sbtn_small_button_4_stay2");
	m_pAgree->setName("sbtn_small_button_2y_stay");
	m_pCancel->setName("sbtn_small_button_2y_stay1");

	m_pShowTerm1->setListener(this);
	m_pShowTerm2->setListener(this);
	m_pAgree->setListener(this);
	m_pCancel->setListener(this);

	CCSize _contentSize = getDummy("dmy_account_created").size;
	CCPoint _pos = getDummy("dmy_account_created").origin;

	getLabel("txt_ useclause")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_data")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_playguide")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

	getLabel("txt_ useclause")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_TERMS_AND_CONDITIONS_AGREE").c_str());
	getLabel("txt_data")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_TERMS_AGREE").c_str());
	getLabel("txt_playguide")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_TERMS_DESC").c_str());

	EnableArgeeButton(false);
	
	AgreeCheck(0, mIsAgree0);
	AgreeCheck(1, mIsAgree1);
		
	setVisible(true);
}

void AccountPopupPanel::EnableArgeeButton(bool _enable)
{
	m_pBtnPanel[2]->setGrayscale(!_enable);
	m_pAgree->setEnable(_enable);
}

//void AccountPopupPanel::ButtonEnable(Button * button, bool enable)
//{
//	if (!enable)
//	{
//		button->setSkelAnimation("small_button_2_change");
//		button->setSkelAnimation("small_button_2_off");
//	}
//	else
//	{
//		button->setSkelAnimation("small_button_2_off_change");
//		button->setSkelAnimation("small_button_2_stay");
//	}
//
//	button->setEnable(enable);
//}

void AccountPopupPanel::AgreeCheck(int idx, bool check)
{
	if (idx == 0)
	{
		mIsAgree0 = check;
		getSkel("skel_checkframe1")->setVisible(check);
		if (check)
		{
			getSkel("skel_checkframe1")->playAnimation("checkframe_a_start", false);
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_CHECK);
		}

	}
	else
	{
		mIsAgree1 = check;
		getSkel("skel_checkframe2")->setVisible(check);
		if (check)
		{
			getSkel("skel_checkframe2")->playAnimation("checkframe_a_start", false);
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_CHECK);
		}
	}

	if (mIsAgree0 & mIsAgree1)
	{
		EnableArgeeButton(true);
	}
	else
		EnableArgeeButton(false);
}

void AccountPopupPanel::MakeCharacterCell(int idx)
{
// 	CCSize charSize = getDummy("dmy_pocha_panel" + StringConverter::toString(idx + 1)).size;
// 	CCPoint charPo = getDummy("dmy_pocha_panel" + StringConverter::toString(idx + 1)).origin;
// 
// 	Panel * chPanel = new Panel();
// 	chPanel->construct(getMxmlPath() + "dmy_pocha_panel.mxml");
// 	CCSize panelSize = chPanel->getDummy("dmy_pocha_panel").size;
// 
// 	chPanel->setPosition(ccp(charPo.x, -charPo.y));
// 
// 	chPanel->getButton("sbtn_small_button_2")->getButtonSkelObject()->setSkin("txt_use");
// 	chPanel->getButton("sbtn_small_button_2")->setListener(this);
// 	chPanel->getButton("sbtn_small_button_2")->setTouchable(true, 0, false);
// 	// 이름 다시 설정
// 	chPanel->getButton("sbtn_small_button_2")->setName("sbtn_small_button_" + StringConverter::toString(idx));
// 	chPanel->getButton("sbtn_small_button_2")->setType(Button::NoPressImg);
// 
// 	chPanel->getButton("sbtn_exclamation_mark_stay")->setListener(this);
// 	chPanel->getButton("sbtn_exclamation_mark_stay")->setTouchable(true, 0, false);
// 	chPanel->getButton("sbtn_exclamation_mark_stay")->setName("sbtn_exclamation_mark_stay" + StringConverter::toString(idx));
// 	chPanel->getButton("sbtn_exclamation_mark_stay")->setType(Button::NoPressImg);
// 
// 	addChild(chPanel);
// 	chPanel->release();
// 
// 	chPanel->getLabel("txt_character_name")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
// 	chPanel->getLabel("txt_character_name_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
// 	chPanel->getLabel("txt_limit")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
// 	chPanel->getLabel("txt_spec")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
// 
// 	chPanel->getLabel("txt_spec")->setString("");
// 	W_GameData * gameData = GameDataManager::getSingletonPtr()->GetGameDataPtr();
// 
// 	W_CharacterData data;
// 	for (int i = 0, j = gameData->characterdata_size(); i < j; i++)
// 	{
// 		data = GameDataManager::getSingletonPtr()->GetGameDataPtr()->characterdata(i);
// 		if (data.id() == idx + 1)
// 		{
// 			chPanel->getLabel("txt_character_name")->setString(data.name().c_str());
// 			break;
// 		}
// 	}
// 	chPanel->setVisible(true);
}

void AccountPopupPanel::MakeNicknamePanel()
{
	
	construct(getMxmlPath() + "dmy_nickname_input.mxml");
	Button * m_WeekGiftBtn = getButton("sbtn_cancel");
	m_WeekGiftBtn->setListener(this);
	m_WeekGiftBtn->setTouchable(true, 0, false);
	//m_WeekGiftBtn->getButtonSkelObject()->setSkin("mark_cancel");

	CCPoint _BtnPos = getDummy("dmy_button_small").origin;

	m_OkButtonPanel = new Panel;
	m_OkButtonPanel->construct(getMxmlPath() + "dmy_button_small.mxml");
	m_OkButtonPanel->getLabel("txt_button_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_OkButtonPanel->getLabel("txt_button")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_OkButtonPanel->getLabel("txt_button_under")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_OK_LABEL").c_str());
	m_OkButtonPanel->getLabel("txt_button")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_OK_LABEL").c_str());
	m_OkButtonPanel->setPositionX(_BtnPos.x);
	m_OkButtonPanel->setPositionY(-_BtnPos.y);
	addChild(m_OkButtonPanel);
	m_OkButtonPanel->release();
	m_OkButtonPanel->getButton("sbtn_button")->setListener(this);
	m_OkButtonPanel->getButton("sbtn_button")->setName("sbtn_Ok_btn");

	CCSize _contentSize = getDummy("dmy_nickname_input").size;
	CCPoint _pos = getDummy("dmy_nickname_input").origin;	

	getLabel("txt_nicknameguide")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_nicknameguide")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_CREATE_NICKNAME").c_str());

	getLabel("txt_nicknameguide2")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_nicknameguide2")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_CREATE_NICKNAME2").c_str());

	if (mType != NICKNAME_TYPE)
		GameDataManager::getSingletonPtr()->SetAccountNickname(GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_NickName);
	
	getTextField("fld_nickname")->setListener(this);
	getTextField("fld_nickname")->setPlaceHolder(GameStringDepot::getSingletonPtr()->getString("TXT_INPUT_NICKNAME").c_str());
	getTextField("fld_nickname")->setString(GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_NickName.c_str());
	
	getLabel("txt_number")->setVisible(false);

	getLabel("txt_title")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_title")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_INPUT_NICKNAME").c_str());

	//getButton("sbtn_small_button_4_stay")->getButtonSkelObject()->setSkin("txt_check");
	//getButton("sbtn_small_button_4_stay")->setListener(this);
	//getButton("sbtn_small_button_4_stay")->setTouchable(true, 0, false);

	getButton("sbtn_nickname_touch")->setVisible(false);
	getButton("sbtn_nickname_touch")->setListener(this);
	getButton("sbtn_nickname_touch")->setTouchable(true, 0, false);
	getButton("sbtn_nickname_touch")->setType(Button::NoPressImg);
	setVisible(true);

	string titleStr = GameStringDepot::getSingleton().getString("AccountPopupPanel_TITLE");
	mTitle = getLabel("txt_title");
	mTitleUnder = getLabel("txt_title_under");
	mTitle->setString(titleStr.c_str());
	mTitleUnder->setString(titleStr.c_str());
}

void AccountPopupPanel::clearThisPanel()
{
	GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
	if(this->isDynamic())
		LayerManager::getSingleton().popLayer(this);
}

void AccountPopupPanel::onRefresh()
{
	setVisible( true );

}


void AccountPopupPanel::onAnimationEnded(const string& ani)
{
	if (!isVisible())
		return;
}

void AccountPopupPanel::SelectCharacter(int idx)
{
	GameDataManager::getSingletonPtr()->SetAccountCharacter(idx);
	ShowPanel(false);
	new AccountPopupPanel(AccountPopupType::NICKNAME_TYPE);
}

void AccountPopupPanel::ExeEvent()
{
	clearThisPanel();	
}

void AccountPopupPanel::onDetached()
{
	
	string _field = getTextField("fld_nickname")->getString();
	_field = _field;
}
