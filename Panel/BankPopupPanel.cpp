#include "pch.h"
#include "BankPopupPanel.h"
#include "HeroUtil.h"
#include "GameStringDepot.h"
#include "GameDataManager.h"
#include "PopupUserReplayPanel.h"
#include "SimplePopupPanel.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "android/AndroidUtilManager.h"
#endif

BankPopupPanel::BankPopupPanel(int param1, int param2) : Panel("PopupPanel")
{
	mTarget = NULL;
	mGeneralListener = NULL;

	mParam1 = param1;
	mParam2 = param2;

	initPanel();		
}

BankPopupPanel::~BankPopupPanel()
{
}

void BankPopupPanel::onClicked(const string& name)
{
	//SoundManager::getSingleton().playEffect(BTN_CLICK);
	GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
	mEventName = name;

	if (name == "sbtn_checkbox1")
	{
	}
	else if (name == "sbtn_checkbox2")
	{
	}
	else if (name == getButtonName(mExcuteBtn))
	{
		InoutCheck();
	}
	else if (name == getButtonName(mCloseBtn))
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		LayerManager::getSingleton().popLayer(this);
	}
	else if (name == "sbtn_nickname_touch")
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		GameDataManager::getSingletonPtr()->m_bEditTextField = false;
		GameDataManager::getSingletonPtr()->m_onFocusTextFeild = getTextField("fld_nickname");
		std::string _fieldText = getTextField("fld_nickname")->getString();
		//AndroidUtilManager::getSingletonPtr()->ReleaseCustomEditTextField();
		AndroidUtilManager::getSingletonPtr()->InitCustomEditTextField();
		AndroidUtilManager::getSingletonPtr()->ShowCustomEditTextField(_fieldText);
#else
		getTextField("fld_nickname")->setListener(this);
		getTextField("fld_nickname")->attachWithIME();
#endif
	}
	else if (name == "sbtn_bank_1")
	{
		IncreaseMoney(1);
	}
	else if (name == "sbtn_bank_2")
	{
		IncreaseMoney(2);
	}
	else if (name == "sbtn_bank_3")
	{
		IncreaseMoney(3);
	}
	else if (name == "sbtn_bank_4")
	{
		IncreaseMoney(4);
	}
	else if (name == "sbtn_bank_5")
	{
		IncreaseMoney(5);
	}
	else if (name == "sbtn_bank_6")
	{
		IncreaseMoney(6);
	}
	else if (name == "sbtn_bank_7")
	{
		IncreaseMoney(7);
	}
	else if (name == "sbtn_bank_8")
	{
		IncreaseMoney(8);
	}
	else if (name == "sbtn_bank_9")
	{
		IncreaseMoney(9);
	}
	else if (name == "sbtn_bank_0")
	{
		IncreaseMoney(0);
	}
	else if (name == "sbtn_maximum")	// 최대
	{
		IncreaseMoney(10000000000);
	}
	else if (name == "sbtn_hunmillion")	// 억
	{
		IncreaseMoney(10000);
	}
	else if (name == "sbtn_trillion")	// 조
	{
		IncreaseMoney(100000000);
	}
	else if (name == "sbtn_back_space")	// 백
	{
		IncreaseMoney(-1);
	}
	else if (name == "BUTTON_INIT")	// 초기화
	{
		IncreaseMoney(-100);
	}
	else if (name == "sbtn_tab1")	// 입금 모드
	{
		SetBankInOut(BANK_IN);
	}
	else if (name == "sbtn_tab2")	// 출금 모드
	{
		SetBankInOut(BANK_OUT);
	}
	
}

void BankPopupPanel::IncreaseMoney(int64 num)
{
	int64 totalNum = mInputMoney;
	int64 yetNum = totalNum;

	int increaseNum = 0;
	if (num >= 0 && num <= 9)
	{
		increaseNum = num * 10000;
		totalNum *= 10;
		totalNum += increaseNum;

		if (totalNum >= 10000000000000000L)
			totalNum = yetNum;
	}
	else if (num == 10000 || num == 100000000)
	{
		if (totalNum == 0)
			return;

		int count = num == 10000 ? 4 : 8;
		for (int i = 0; i < count; i++)
		{
			yetNum = totalNum;
			totalNum *= 10;
			if (totalNum >= 10000000000000000L)
			{
				totalNum = yetNum;
				break;
			}
		}
	}
	else if (num == -1)
	{
		if (totalNum == 0)
			return;

		totalNum /= 10;
		//10을 하고
		if (totalNum < 10000) {
			totalNum = 0;
		}
		else{
			totalNum -= (totalNum % 10000);
		}
	}
	else if (num == -100)
	{
		if (totalNum == 0)
			return;
		totalNum = 0;
	}
	else if (num == 10000000000)	// 최대 머니
	{
		if (mBankInOut == BANK_IN)
		{
			int64 canBankMoney = GetCanBankMoney();
			int64 canMyMoney = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney;
			canMyMoney -= (canMyMoney % 10000);

			if (canBankMoney < canMyMoney)
				totalNum = canBankMoney;
			else
				totalNum = canMyMoney;
		}
		else
		{
			totalNum = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoneyBank;
		}
	}

	mInputMoney = totalNum;

	SetConsoleMoney();
}

void BankPopupPanel::InoutCheck()
{
	int64 canMoney = 0;
	string tmpTxt = "";
	switch (mBankInOut)
	{
		case BANK_IN :
			canMoney = GetCanBankMoney();
			if (mInputMoney > canMoney)
			{
				tmpTxt = NxGetFormatString(GameStringDepot::getSingletonPtr()->getString("TXT_INPUT_MAX_MONEY"),GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(canMoney)));
				LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, tmpTxt), DYNAMIC_PUSH_LAYER);
			}
			else if (mInputMoney > GameDataManager::getSingletonPtr()->m_pPlayerData->m_GameMoney)
			{
				tmpTxt = GameStringDepot::getSingletonPtr()->getString("TXT_INPUT_MONEY_OVER_MY_MONEY");
				LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, tmpTxt), DYNAMIC_PUSH_LAYER);
			}
			else if (mInputMoney == 0)
			{
				tmpTxt = GameStringDepot::getSingletonPtr()->getString("TXT_INOUTPUT_MIN_MONEY");
				LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, tmpTxt), DYNAMIC_PUSH_LAYER);
			}
			else
			{
				LayerManager::getSingleton().popLayer(this);
				WebService::getSingletonPtr()->_sendBankInReq(mInputMoney);				
			}
			break;
		case BANK_OUT :
			canMoney = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoneyBank;
			if (mInputMoney > canMoney)
			{
				tmpTxt = NxGetFormatString(GameStringDepot::getSingletonPtr()->getString("TXT_OUTPUT_MAX_MONEY"), GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(canMoney)));
				LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, tmpTxt), DYNAMIC_PUSH_LAYER);
			}
			else if (mInputMoney == 0)
			{
				tmpTxt = GameStringDepot::getSingletonPtr()->getString("TXT_INOUTPUT_MIN_MONEY");
				LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, tmpTxt), DYNAMIC_PUSH_LAYER);
			}
			else
			{
				LayerManager::getSingleton().popLayer(this); 
				WebService::getSingletonPtr()->_sendBankOutReq(mInputMoney);				
			}
			break;
	}
}

int64 BankPopupPanel::GetCanBankMoney()
{
	PlayerData * _playerData = GameDataManager::getSingletonPtr()->GetPlayerDataPtr();
	int64 canBankMoney = _playerData->m_BankMax - _playerData->m_GameMoneyBank;

	return canBankMoney;
}

void BankPopupPanel::SetConsoleMoney()
{
	string tmpTxt = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(mInputMoney));
	tmpTxt += GameStringDepot::getSingletonPtr()->getString("TXT_GOLD_UNIT");
	getLabel("txt_consolgold")->setString(tmpTxt.c_str());
}

void BankPopupPanel::initPanel()
{
	addMouseBlockPanel(this);
	MakeBankPanel();
}

void BankPopupPanel::MakeBankPanel()
{
	construct(getMxmlPath() + "dmy_bank.mxml");
	setButtonListener(this);
	mTitle = getLabel("txt_title");
	mTitleUnder = getLabel("txt_title_under");
	string titleStr = GameStringDepot::getSingleton().getString("BankPopupPanel_TITLE");
	mTitle->setString(titleStr.c_str());
	mTitleUnder->setString(titleStr.c_str());

	mBankIcon = getSkel("skel_markconsol");

	//소지머니
	getLabel("txt_now_gold")->setString(GameStringDepot::getSingletonPtr()->getString("BankPopupPanel_MY_MONEY").c_str());
	//금고머니
	getLabel("txt_bank")->setString(GameStringDepot::getSingletonPtr()->getString("BankPopupPanel_BANK_MONEY").c_str());
	//입금
	getLabel("txt_credit_on_under")->setString(GameStringDepot::getSingletonPtr()->getString("BankPopupPanel_IN").c_str());
	getLabel("txt_credit_on")->setString(GameStringDepot::getSingletonPtr()->getString("BankPopupPanel_IN").c_str());
	//출금
	getLabel("txt_credit_out_under")->setString(GameStringDepot::getSingletonPtr()->getString("BankPopupPanel_OUT").c_str());
	getLabel("txt_credit_out")->setString(GameStringDepot::getSingletonPtr()->getString("BankPopupPanel_OUT").c_str());
	// 버튼 10개
	string name;
	for (int i = 0; i < 10; i++)
	{
		name = "sbtn_bank_" + StringConverter::toString(i);
		mNumButton[i] = getButton(name);
		getButton(name)->setListener(this);
		getButton(name)->setTouchable(true, 0, false);
	}

	//초기화 버튼
	mInitBtnPanel = new Panel();
	mInitBtnPanel->construct(getMxmlPath() + "dmy_button_insmall.mxml");
	mInitBtnPanel->getButton("sbtn_reset")->setName("BUTTON_INIT");
	mInitBtnPanel->getButton("sbtn_reset")->setListener(this);
	mInitBtnPanel->getLabel("txt_reset")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mInitBtnPanel->getLabel("txt_reset")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_INIT_UNIT").c_str());
	CCPoint _btnPos1 = getDummy("dmy_button_insmall").origin;
	mInitBtnPanel->setPosition(ccp(_btnPos1.x, -_btnPos1.y));
	addChild(mInitBtnPanel);
	mInitBtnPanel->release();


	mCloseBtn = getButton("sbtn_cancel");
	mExcuteBtn = getButton("sbtn_button");
	mExcuteLabel = getLabel("txt_button");
	mExcuteUnderLabel = getLabel("txt_button_under");
	//m_pBtnPanel[0]->getLabel("txt_reset")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_INIT_UNIT").c_str());
	//m_pBtnPanel[1]->getLabel("txt_button_under")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_OK_LABEL").c_str());
	//m_pBtnPanel[2]->getLabel("txt_button_under")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_CANCEL_LABEL").c_str());
	// 입금
	getButton("sbtn_tab1")->setListener(this);
	getButton("sbtn_tab1")->setType(Button::NoPressImg);
	getButton("sbtn_tab1")->setTouchable(true, 0, false);

	// 출금
	getButton("sbtn_tab2")->setListener(this);
	getButton("sbtn_tab2")->setType(Button::NoPressImg);
	getButton("sbtn_tab2")->setTouchable(true, 0, false);

	// 백스페이스
	getButton("sbtn_back_space")->setListener(this);
	getButton("sbtn_back_space")->setTouchable(true, 0, false);

	// 억단위
	getButton("sbtn_hunmillion")->setListener(this);
	getButton("sbtn_hunmillion")->setTouchable(true, 0, false);

	// 조단위
	getButton("sbtn_trillion")->setListener(this);
	getButton("sbtn_trillion")->setTouchable(true, 0, false);
	
	// 맥스 
	getButton("sbtn_maximum")->setListener(this);
	getButton("sbtn_maximum")->setTouchable(true, 0, false);

	getLabel("txt_title")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_credit_on_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_credit_on")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_credit_out_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_credit_out")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_timelimit")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_now_gold")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_now_goldsum")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_bank")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_banksum")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_consolgold")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

	PlayerData * _playerData = GameDataManager::getSingletonPtr()->GetPlayerDataPtr();
	string tmpTxt;
	tmpTxt = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString((int64)_playerData->m_GameMoney)) + GameStringDepot::getSingletonPtr()->getString("TXT_GOLD_UNIT");
	getLabel("txt_now_goldsum")->setString(tmpTxt.c_str());
	tmpTxt = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString((int64)_playerData->m_GameMoneyBank)) + GameStringDepot::getSingletonPtr()->getString("TXT_GOLD_UNIT");
	getLabel("txt_banksum")->setString(tmpTxt.c_str());

	int64 _MaxGold = GameDataManager::getSingleton().getPlayerInfo().bankbax();
	string _sMaxGold = "(" + GameStringDepot::getSingleton().getString("TXT_LIMIT") + GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_MaxGold)) + ")";
	getLabel("txt_maximum")->setString(_sMaxGold.c_str());

	setVisible(true);

	mInputMoney = 0;

	SetConsoleMoney();
	SetBankInOut(BANK_IN);
	SetRemainTime();
}

void BankPopupPanel::ButtonEnable(Button * button, bool enable)
{
	if (!enable)
	{
		button->setSkelAnimation("small_button_2_change");
		button->setSkelAnimation("small_button_2_off");
	}
	else
	{
		button->setSkelAnimation("small_button_2_off_change");
		button->setSkelAnimation("small_button_2_stay");
	}

	button->setEnable(enable);
}

void BankPopupPanel::SetRemainTime()
{
	int64 _bankMax = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_BankMax;
	string _text = GameDataManager::getSingletonPtr()->GetRemainTime(GameDataManager::getSingleton().getPlayerInfo().bankexpiretime(), true, false);
	getLabel("txt_timelimit")->setString(_text.c_str());	
}

void BankPopupPanel::SetBankInOut(BankInOut inout)
{
	ccColor3B _onColor = ccc3(240, 216, 165);
	ccColor3B _offColor = ccc3(144, 130, 99);
	mBankInOut = inout;
	switch (inout)
	{
		case BANK_IN :
			mBankIcon->playAnimation("mark_in");
			getButton("sbtn_tab1")->getButtonSkelObject()->playAnimation("tab_bank_lon");
			getButton("sbtn_tab2")->getButtonSkelObject()->playAnimation("tab_bank_off");
			getLabel("txt_credit_out")->setColor(_offColor);
			getLabel("txt_credit_on")->setColor(_onColor);
			mExcuteLabel->setString(GameStringDepot::getSingletonPtr()->getString("BankPopupPanel_IN_BTN").c_str());
			mExcuteUnderLabel->setString(GameStringDepot::getSingletonPtr()->getString("BankPopupPanel_IN_BTN").c_str());
			break;
		case BANK_OUT :
			mBankIcon->playAnimation("mark_out");
			getButton("sbtn_tab1")->getButtonSkelObject()->playAnimation("tab_bank_loff");
			getButton("sbtn_tab2")->getButtonSkelObject()->playAnimation("tab_bank_on");
			getLabel("txt_credit_out")->setColor(_onColor);
			getLabel("txt_credit_on")->setColor(_offColor);
			mExcuteLabel->setString(GameStringDepot::getSingletonPtr()->getString("BankPopupPanel_OUT_BTN").c_str());
			mExcuteUnderLabel->setString(GameStringDepot::getSingletonPtr()->getString("BankPopupPanel_OUT_BTN").c_str());
			break;
	}
	mInputMoney = 0;
	SetConsoleMoney();
}


void BankPopupPanel::clearThisPanel()
{
	if(this->isDynamic())
		LayerManager::getSingleton().popLayer(this);
}

void BankPopupPanel::onRefresh()
{
	setVisible( true );

}


void BankPopupPanel::onAnimationEnded(const string& ani)
{
	if (!isVisible())
		return;
}

void BankPopupPanel::ExeEvent()
{
	clearThisPanel();
	/*
	if (mEventName == mMiddleOkBtn->getName())
	{
		clearThisPanel();
		if (mGeneralListener)
			(mTarget->*mGeneralListener)(mOkEventMsg);
		else
			fireMessage(mOkEventMsg);
	}
	else if (mEventName == mOkBtn->getName())
	{
		clearThisPanel();
		if (mGeneralListener)
			(mTarget->*mGeneralListener)(mOkEventMsg);
		else
			fireMessage(mOkEventMsg);
	}
	else if (mEventName == mCancelBtn->getName())
	{
		clearThisPanel();
		if (mGeneralListener)
			(mTarget->*mGeneralListener)(mCancelEventMsg);
		else
			fireMessage(mCancelEventMsg);
	}
	else if (mEventName == mExitBtn->getName())
	{
		clearThisPanel();
		if (mGeneralListener)
			(mTarget->*mGeneralListener)(mExitEventMsg);
		else
			fireMessage(mExitEventMsg);
	}
	*/
}

void BankPopupPanel::onDetached()
{
	getTextField("fld_nickname")->setListener(nullptr);
	string _field = getTextField("fld_nickname")->getString();

	_field = _field;
	

}

void BankPopupPanel::update(float delta)
{
	SetRemainTime();
}

void BankPopupPanel::onEnter()
{
	Panel::onEnter();
	
	scheduleUpdate();
}