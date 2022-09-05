#include "pch.h"
#include "LobbyMyHomeTap2.h"

#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "CustomPopupPanel.h"
#include "GameStringDepot.h"
#include "PokerRankHelper.h"
#include "RankInfoContentPanel.h"
#include "PanelHelper.h"

const ccColor3B ccMenuGrayColor = { 134, 134, 134 };
const ccColor3B ccPointGrayColor = { 156, 156, 156 };

LobbyMyHomeTap2::LobbyMyHomeTap2()
{
	mLoginProcess = false;

	InitPanel();
	InitImage();
	initButton();

	setTouchable(true, 1, false);
	setButtonListener(this);
	

	UpdateRankInfo();
}

LobbyMyHomeTap2::~LobbyMyHomeTap2()
{
	removeAllChildren();
}

void LobbyMyHomeTap2::InitPanel()
{
	construct(getMxmlPath() + "dmy_vipinfo.mxml");
	mVipIcon = getSkel("skel_mark_vipb");
	mVipAmount = getLabel("txt_vip_sum");
	mRankIcon = getSkel("skel_rankicon");
	CCSize originSize = getDummy("skel_rankicon").size;
	CCSize iconSize = getDummy("dmy_rankicon").size;
	mRankIcon->setScale(getScaleFit(originSize, iconSize));
	mVipDesc = getLabel("txt_vipguide");
	mVipPeriodDesc = getLabel("txt_day_now");

	CCPoint pos = getDummy("dmy_button_lsmall").origin;
	pos.y = -pos.y;
	Panel* pPanel = new Panel();
	pPanel->construct(getMxmlPath() + "dmy_button_lsmall.mxml");
	addChild(pPanel);
	pPanel->release();
	pPanel->setPosition(pos);
	mInfoBtn = pPanel->getButton("sbtn_button");
	mInfoBtn->setListener(this);
	mInfoBtn->setName("sbtn_info");	
	mInfoBtnLabel = pPanel->getLabel("txt_button");
	mInfoBtnUnderLabel = pPanel->getLabel("txt_button_under");
	mInfoBtnLabel->setString(GameStringDepot::getSingleton().getString("VIP_INFO_HELP_BTN").c_str());
	mInfoBtnUnderLabel->setString(GameStringDepot::getSingleton().getString("VIP_INFO_HELP_BTN").c_str());

	mVipTitle = getLabel("txt_giftnumber");
	mVipTitleUnder = getLabel("txt_giftnumber_under");
}


void LobbyMyHomeTap2::InitImage()
{
	//vip 정보
	getLabel("txt_title_rank")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_MYHOME_TAP2_TITLE").c_str());
	getLabel("txt_title_rank_under")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_MYHOME_TAP2_TITLE").c_str());

	//Vip 표시
	int _vipLevel = PokerRankHelper::getVip();
	if (_vipLevel == 0) {  
		mVipIcon->playAnimation("mark_vipb_off");
		mVipAmount->setString(StringConverter::toString(_vipLevel).c_str());
		mVipAmount->setColor(ccc3(108, 68, 38));
		mVipDesc->setString(GameStringDepot::getSingleton().getString("VIP_INFO_DESC_0").c_str());
		mVipDesc->setColor(StringConverter::parseColor3B("7e5735"));
	}
	else {
		mVipIcon->playAnimation("mark_vipb");
		mVipAmount->setString(StringConverter::toString(_vipLevel).c_str());
		mVipDesc->setString(GameStringDepot::getSingleton().getString("VIP_INFO_DESC").c_str());
	}

	//rankIcon //기존 
	int rank = PokerRankHelper::getVip();
	PokerRankHelper::setRankIcon(mRankIcon, _vipLevel);
	//이정 시즌
	W_TourOfInfo* _pInfoData = GameDataManager::getSingletonPtr()->m_TourOfInfo;
	string periodStr = NxGetFormatString(GameStringDepot::getSingleton().getString("LobbyMyHomeTap2_VIP_DESC"), _pInfoData->title());
	//혜택 적용 기간
	mVipPeriodDesc->setString(periodStr.c_str());
	//혜택 관련 _________________
	string boonStr = NxGetFormatString(GameStringDepot::getSingleton().getString("LobbyMyHomeTap2_VIP_BOON"), _vipLevel);
	mVipTitle->setString(boonStr.c_str());
	mVipTitleUnder->setString(boonStr.c_str());		

	getLabel("txt_seasoninfo")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_SEASONINFO_UNIT").c_str());
	getLabel("txt_refill")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_CHARACTER_EFFECT3").c_str());
	getLabel("txt_gold")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_VIP_EFFECT4").c_str());
	getLabel("txt_chip")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_VIP_EFFECT2").c_str());
	getLabel("txt_bank")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_VIP_EFFECT5").c_str());
	

	getLabel("txt_refill")->setGrayColor(ccMenuGrayColor);
	getLabel("txt_gold")->setGrayColor(ccMenuGrayColor);
	getLabel("txt_chip")->setGrayColor(ccMenuGrayColor);
	getLabel("txt_bank")->setGrayColor(ccMenuGrayColor);
	
	getLabel("txt_refill_sum")->setGrayColor(ccPointGrayColor);
	getLabel("txt_gold_sum")->setGrayColor(ccPointGrayColor);
	getLabel("txt_chip_sum")->setGrayColor(ccPointGrayColor);
	getLabel("txt_bank_sum")->setGrayColor(ccPointGrayColor);

}

void LobbyMyHomeTap2::initButton()
{	
}


bool LobbyMyHomeTap2::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	
	return false;
}


void LobbyMyHomeTap2::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	
}


void LobbyMyHomeTap2::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	
}

void LobbyMyHomeTap2::resume()
{
}

void LobbyMyHomeTap2::onClicked(const string& name)
{
	if (name == getButtonName(mInfoBtn)) {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		PanelHelper::pushVipInfoPanel();
	}
}

void LobbyMyHomeTap2::update(float dt)
{
}

bool LobbyMyHomeTap2::handling(STCMD &stCmd)
{
	return false;
}

void LobbyMyHomeTap2::UpdateRankInfo()
{
	//set cur rank info
	int _curFame = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Repute;
	m_SelectedRank = PokerRankHelper::getVip();
	
	SetRankPercentBar(_curFame);
	SetVipBonus(PokerRankHelper::getVip());

	W_TourOfInfo* _pInfoData = GameDataManager::getSingletonPtr()->m_TourOfInfo;
	string periodStr = GameStringDepot::getSingleton().getString("TOURMENT_PERIOD") + _pInfoData->title();
	//getLabel("txt_dayinfo")->setString(periodStr.c_str());	
}

void LobbyMyHomeTap2::SetRankPercentBar(int _now)
{	
}

void LobbyMyHomeTap2::SetVipBonus(int _vipLevel)
{
	int _DataSize = GameDataManager::getSingletonPtr()->GetGameDataPtr()->vipdata_size();

	if (_vipLevel < 0)
		_vipLevel = 0;

	if (GameDataManager::getSingletonPtr()->GetGameDataPtr()->vipdata(_DataSize - 1).level() < _vipLevel)
		_vipLevel = GameDataManager::getSingletonPtr()->GetGameDataPtr()->vipdata(_DataSize - 1).level();

	m_SelectedRank = _vipLevel;

	if (PokerRankHelper::getVip() == m_SelectedRank) {
		//getLabel("txt_seasoninfo")->setVisible(true);
	}
	else {
		//getLabel("txt_seasoninfo")->setVisible(false);
	}

	for (int _i = 0; _i < _DataSize; _i++)
	{
		W_VipData _vipData = GameDataManager::getSingletonPtr()->GetGameDataPtr()->vipdata(_i);
		if (_vipLevel == _vipData.level())
		{
			int _size = _vipData.vipoption_size();
			for (int _index = 0; _index < _size; _index++)
			{
				SetVipOption(_vipData.vipoption(_index));
			}			
			string _text = GameStringDepot::getSingletonPtr()->getString("TXT_CHAMPION_UNIT");
			_text += " " + StringConverter::toString(_vipData.level());
			_text += GameStringDepot::getSingletonPtr()->getString("TXT_LEVEL_BONUS_UNIT");
			//getLabel("txt_rankgiftnumber")->setString(_text.c_str());

			return;
		}
	}
}

void LobbyMyHomeTap2::SetVipOption(W_VipData_VipOption _data)
{
	int64 _amount = _data.amount();
	string _amountTxt = "";

	switch (_data.type())
	{
	case W_VipData_eVipType_FreeRefillCount:
		
		if (_amount > 0)
		{
			_amountTxt = "+" + StringConverter::toString(_amount);
			getSkel("skel_refill")->playAnimation("image_refill");
			getSkel("skel_gtable1")->playAnimation("table_g_gold");
			getLabel("txt_refill_sum")->setString(_amountTxt.c_str());
			getLabel("txt_refill_sum")->setGrayscale(false);
			getLabel("txt_refill")->setGrayscale(false);
		}
		else
		{
			getSkel("skel_refill")->playAnimation("image_refill_off");
			getSkel("skel_gtable1")->playAnimation("table_g_off");
			getLabel("txt_refill_sum")->setString(GameStringDepot::getSingleton().getString("NO_APPLY").c_str());
			getLabel("txt_refill_sum")->setGrayscale(true);
			getLabel("txt_refill")->setGrayscale(true);
		}		
		break;
	case W_VipData_eVipType_DailyChipAddLimit:
		if (_amount > 0)
		{
			_amountTxt = "+" + StringConverter::toString(_amount);
			getLabel("txt_chip_sum")->setString(_amountTxt.c_str());
			getSkel("skel_chip")->playAnimation("image_chip");
			getSkel("skel_gtable4")->playAnimation("table_g_fame");
			getLabel("txt_chip_sum")->setGrayscale(false);
			getLabel("txt_chip")->setGrayscale(false);			
		}
		else
		{
			getSkel("skel_chip")->playAnimation("image_chip_off");
			getSkel("skel_gtable4")->playAnimation("table_g_off");
			getLabel("txt_chip_sum")->setString(GameStringDepot::getSingleton().getString("NO_APPLY").c_str());
			getLabel("txt_chip_sum")->setGrayscale(true);
			getLabel("txt_chip")->setGrayscale(true);
		}

		break;
	case W_VipData_eVipType_GameMoneyMaxUp:
		if (_amount > 0)
		{
			_amountTxt = "+" + GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_amount), 1);
			getLabel("txt_gold_sum")->setString(_amountTxt.c_str());
			getSkel("skel_gold")->playAnimation("image_gold");
			getSkel("skel_gtable2")->playAnimation("table_g_gold");
			getLabel("txt_gold_sum")->setGrayscale(false);
			getLabel("txt_gold")->setGrayscale(false);
		}
		else
		{
			getLabel("txt_gold_sum")->setString(GameStringDepot::getSingleton().getString("NO_APPLY").c_str());
			getSkel("skel_gold")->playAnimation("image_gold_off");
			getSkel("skel_gtable2")->playAnimation("table_g_off");
			getLabel("txt_gold_sum")->setGrayscale(true);
			getLabel("txt_gold")->setGrayscale(true);
		}

		
		break;
	case W_VipData_eVipType_BankMaxUp:
		if (_amount > 0)
		{
			_amountTxt = "+" + GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_amount), 1);
			getLabel("txt_bank_sum")->setString(_amountTxt.c_str());
			getSkel("skel_bank")->playAnimation("image_bank");
			getSkel("skel_gtable3")->playAnimation("table_g_bank");
			getLabel("txt_bank_sum")->setGrayscale(false);
			getLabel("txt_bank")->setGrayscale(false);
		}
		else
		{			
			getLabel("txt_bank_sum")->setString(GameStringDepot::getSingleton().getString("NO_APPLY").c_str());
			getSkel("skel_bank")->playAnimation("image_bank_off");
			getSkel("skel_gtable3")->playAnimation("table_g_off");
			getLabel("txt_bank_sum")->setGrayscale(true);
			getLabel("txt_bank")->setGrayscale(true);
		}

		
		break;
	}
}
