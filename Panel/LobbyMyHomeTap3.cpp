#include "pch.h"
#include "LobbyMyHomeTap3.h"

#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "CustomPopupPanel.h"
#include "W_VipData.pb.h"
#include "GameStringDepot.h"

LobbyMyHomeTap3::LobbyMyHomeTap3()
{
	mLoginProcess = false;

	m_pReplayListView = nullptr;
	m_pReplayListContainer = nullptr;

	InitPanel();
	InitImage();
	initButton();

	setTouchable(true, 1, false);
	setButtonListener(this);
	
	m_ViewDataIndex = 10;
	m_ClassDescId = 1;

	SetClassInfo();
}

LobbyMyHomeTap3::~LobbyMyHomeTap3()
{
	//destruct();
}

void LobbyMyHomeTap3::InitPanel()
{
	construct(getMxmlPath() + "dmy_classinfo.mxml");
	CCPoint _BtnPos = getDummy("dmy_button_small").origin;
	m_classShopBtnPanel = new Panel;
	m_classShopBtnPanel->construct(getMxmlPath() + "dmy_button_small.mxml");
	m_classShopBtnPanel->getLabel("txt_button_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_classShopBtnPanel->getLabel("txt_button")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_classShopBtnPanel->setPositionX(_BtnPos.x);
	m_classShopBtnPanel->setPositionY(-_BtnPos.y);
	addChild(m_classShopBtnPanel);
	m_classShopBtnPanel->release();

	getLabel("txt_silver")->setString(GameStringDepot::getSingleton().getString("LobbyMyHomeTap3_SILVER_TITLE").c_str());
	getLabel("txt_gold")->setString(GameStringDepot::getSingleton().getString("LobbyMyHomeTap3_GOLD_TITLE").c_str());

	mInstancePayTitle = getLabel("txt_instantlyg");
	mInstancePayUnderTitle = getLabel("txt_instantlyg_under");
	mInstancePayTitle->setString(GameStringDepot::getSingleton().getString("LobbyMyHomeTap3_INSTANCE_TITLE").c_str());
	mInstancePayUnderTitle->setString(GameStringDepot::getSingleton().getString("LobbyMyHomeTap3_INSTANCE_TITLE").c_str());

	//가변적 라벨
	mPrizeTitle_1 = getLabel("txt_prize1");
	mPrizeTitle_3 = getLabel("txt_prize3");

	//안 변하는 탭
	mPrizeTitle_2 = getLabel("txt_prize2");	
	mPrizeTitle_4 = getLabel("txt_prize4");
	mPrizeTitle_5 = getLabel("txt_prize5");
	mPrizeTitle_2->setString(GameStringDepot::getSingleton().getString("LobbyMyHomeTap3_PRIZE_2").c_str());
	mPrizeTitle_4->setString(GameStringDepot::getSingleton().getString("LobbyMyHomeTap3_PRIZE_4").c_str());
	mPrizeTitle_5->setString(GameStringDepot::getSingleton().getString("LobbyMyHomeTap3_PRIZE_5").c_str());
}

void LobbyMyHomeTap3::InitImage()
{
	mGoldIcon = getSkel("skel_class_mark");
	mSilverIcon = getSkel("skel_class_mark2");
	mClassLimitGold = getLabel("txt_gold_time");
	mClassLimitSiver = getLabel("txt_silver_time");

	m_pClassGrade = getLabel("txt_classnumber");
	m_pClassGradeUnder = getLabel("txt_classnumber_under");
	m_pClassDesc = getLabel("txt_classcontent");
	m_pClassTitleLabel = getLabel("txt_title_class");
	m_pClassTitleUnderLabel = getLabel("txt_title_class_under");
	m_pClassTitleLabel->setString(GameStringDepot::getSingletonPtr()->getString("TXT_MYHOME_TAP3_UNIT").c_str());
	m_pClassTitleUnderLabel->setString(GameStringDepot::getSingletonPtr()->getString("TXT_MYHOME_TAP3_UNIT").c_str());
}

void LobbyMyHomeTap3::initButton()
{
	m_GotoClassShopBtn = m_classShopBtnPanel->getButton("sbtn_button");
	m_GotoClassShopBtn->setName("GOTO_SHOP_CLASS");
	m_ClassLeftBtn = getButton("sbtn_movearrow_l");
	m_ClassRightBtn = getButton("sbtn_movearrow_r");	
}


bool LobbyMyHomeTap3::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	
	return false;
}


void LobbyMyHomeTap3::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	
}


void LobbyMyHomeTap3::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	
}

void LobbyMyHomeTap3::resume()
{
}

void LobbyMyHomeTap3::onClicked(const string& name)
{
	if (mLoginProcess)
		return;

	GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
	if (name == "sbtn_button")
	{
		
	}
	if (name == "sbtn_movearrow_l")
	{
		m_ClassDescId--;
		if (m_ClassDescId < 1)
			m_ClassDescId = 1;
		SetClassDesc(m_ClassDescId);
	}
	if (name == "sbtn_movearrow_r")
	{
		m_ClassDescId++;
		if (m_ClassDescId > 2)
			m_ClassDescId = 2;
		SetClassDesc(m_ClassDescId);
	}

}

void LobbyMyHomeTap3::update(float dt)
{
}

bool LobbyMyHomeTap3::handling(STCMD &stCmd)
{
	return false;
}

void LobbyMyHomeTap3::SetClassInfo()
{
	int _classId = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_MonthlyClassID;

	if (_classId == 0)
	{
		string _btnTxt = GameStringDepot::getSingletonPtr()->getString("TXT_BUY_UNIT");
		m_classShopBtnPanel->getLabel("txt_button_under")->setString(_btnTxt.c_str());
		m_classShopBtnPanel->getLabel("txt_button")->setString(_btnTxt.c_str());	
		mGoldIcon->playAnimation("bclass_gold_off");
		mSilverIcon->playAnimation("bclass_silver_off");
		mClassLimitGold->setString(GameStringDepot::getSingleton().getString("MEMBERINFO_NO").c_str());
		mClassLimitSiver->setString(GameStringDepot::getSingleton().getString("MEMBERINFO_NO").c_str());
	}
	else if (_classId == 1)
	{
		mGoldIcon->playAnimation("bclass_gold_off");
		mSilverIcon->playAnimation("bclass_silver");
		string _btnTxt = GameStringDepot::getSingletonPtr()->getString("TXT_CLASS_BUY_UNIT");
		m_classShopBtnPanel->getLabel("txt_button_under")->setString(_btnTxt.c_str());
		m_classShopBtnPanel->getLabel("txt_button")->setString(_btnTxt.c_str());
		mClassLimitGold->setString(GameStringDepot::getSingleton().getString("MEMBERINFO_NO").c_str());
		string _text = GameDataManager::getSingletonPtr()->GetRemainTime(GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_MonthlyClassDay, true, false , false);
		string silverStr = NxGetFormatString(GameStringDepot::getSingleton().getString("MEMBERINFO_REMAIN_TIME_STR"), _text);
		mClassLimitSiver->setString(silverStr.c_str());		
	}
	else if (_classId == 2)
	{
		string _btnTxt = GameStringDepot::getSingletonPtr()->getString("TXT_CLASS_BUY_UNIT");
		m_classShopBtnPanel->getLabel("txt_button_under")->setString(_btnTxt.c_str());
		m_classShopBtnPanel->getLabel("txt_button")->setString(_btnTxt.c_str());
		
		mGoldIcon->playAnimation("bclass_gold");
		string _text = GameDataManager::getSingletonPtr()->GetRemainTime(GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_MonthlyClassDay, true, false , false);
		string goldStr = NxGetFormatString(GameStringDepot::getSingleton().getString("MEMBERINFO_REMAIN_TIME_STR"), _text);
		mClassLimitGold->setString(goldStr.c_str());

		//silver 가 있으면 표시
		if (GameDataManager::getSingletonPtr()->getPlayerInfo().monthlyclasssilverexpiretime() > 0.f) {
			mSilverIcon->playAnimation("bclass_silver_off");
			mClassLimitSiver->setString(GameStringDepot::getSingleton().getString("TXT_STAY_TIME").c_str());			
		}
		else {
			mSilverIcon->playAnimation("bclass_silver_off");
			mClassLimitSiver->setString(GameStringDepot::getSingleton().getString("MEMBERINFO_NO").c_str());
		}
	}

	if (_classId == 0)
	{
		SetClassDesc(1);
	}
	else
	{
		m_ClassDescId = _classId;
		SetClassDesc(m_ClassDescId);
	}
}

void LobbyMyHomeTap3::SetClassDesc(int _classId)
{
	if (_classId < 1)
		_classId = 1;

	if (_classId > 2)
		_classId = 2;

	if (_classId == 1)
	{
		m_ClassLeftBtn->setVisible(false);
		m_ClassRightBtn->setVisible(true);
		m_pClassGrade->setString(GameStringDepot::getSingleton().getString("TXT_SLIVER_CLASS_LEVEL_EFFECT").c_str());
		m_pClassGradeUnder->setString(GameStringDepot::getSingleton().getString("TXT_SLIVER_CLASS_LEVEL_EFFECT").c_str());
	}
	else if (_classId == 2)
	{
		m_ClassLeftBtn->setVisible(true);
		m_ClassRightBtn->setVisible(false);
		m_pClassGrade->setString(GameStringDepot::getSingleton().getString("TXT_GOLD_CLASS_LEVEL_EFFECT").c_str());
		m_pClassGradeUnder->setString(GameStringDepot::getSingleton().getString("TXT_GOLD_CLASS_LEVEL_EFFECT").c_str());
	}

	int _size = GameDataManager::getSingletonPtr()->GetGameDataPtr()->monthlyclassdata_size();
	for (int _i = 0; _i < _size; _i++)
	{
		W_MonthlyClassData _pData = GameDataManager::getSingletonPtr()->GetGameDataPtr()->monthlyclassdata(_i);

		if (_pData.id() != _classId)
			continue;

		int _size = _pData.classoption_size();
		for (int _l = 0; _l < _size; _l++)
		{
			W_MonthlyClassData_eClassOption _optionData = _pData.classoption(_l);

			SetBonusTable(_optionData.type(), _optionData.amount(), _optionData.effect());
		}

		//int _line = _pData.desc_size();
		//string _sDesc = "";
		//for (int _l = 0; _l < _line; _l++)
		//{
		//	W_MonthlyClassData_ClassDesc _desc = _pData.desc(_l);
		//	if (_desc.has_content())
		//	{
		//		_sDesc += _desc.content();
		//	}
		//	if (_l != _line - 1)
		//	{
		//		_sDesc += "\n";
		//	}
		//}

		//m_pClassDesc->setString(_sDesc.c_str());
	}
}

void LobbyMyHomeTap3::SetBonusTable(W_MonthlyClassData_eClassType _type, int64 _amount, int64 _effect)
{
	switch (_type)
	{
	case W_MonthlyClassData_eClassType_OnceGameMoney:
	{
		string _txt = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_amount), 1);
		getLabel("str_instantlyg_sum_under")->setString(_txt.c_str());
		getLabel("txt_instantlyg_sum")->setString(_txt.c_str());
		break;
	}
	case W_MonthlyClassData_eClassType_AttendGameMoney:
	{
		string _desc = StringConverter::toString(_effect) + GameStringDepot::getSingletonPtr()->getString("TXT_ATTEND_GAMEMONEY_DESC");
		string _txt = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_amount), 1);
		mPrizeTitle_3->setString(_desc.c_str());
		getLabel("txt_prize3_sum")->setString(_txt.c_str());
		break;
	}
	case W_MonthlyClassData_eClassType_GameMoneyRefill:
	{
		string _desc = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_effect), 1);
		_desc += GameStringDepot::getSingletonPtr()->getString("TXT_GAMEMONEY_REFILL_DESC");
		string _txt = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_amount), 1);
		mPrizeTitle_1->setString(_desc.c_str());
		getLabel("txt_prize1_sum")->setString(_txt.c_str());
		break;
	}
	case W_MonthlyClassData_eClassType_GameMoneyMaxUp:
	{
		string _txt = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_amount), 1);
		getLabel("txt_prize2_sum")->setString(_txt.c_str());
		break;
	}
	case W_MonthlyClassData_eClassType_ChipMaxUp:
	{
		break;
	}
	case W_MonthlyClassData_eClassType_BankBuy:
	{
		string _txt = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_effect), 1);
		getLabel("txt_prize5_sum")->setString(_txt.c_str());
		break;
	}
	case W_MonthlyClassData_eClassType_CharacterBuyBonus:
	{
		string _txt = GameStringDepot::getSingletonPtr()->getString("TXT_GOLD_UNIT") + " +" + StringConverter::toString(_amount) + "%";
		getLabel("txt_prize4_sum")->setString(_txt.c_str());
		break;
	}
	default:
		break;
	}
}
