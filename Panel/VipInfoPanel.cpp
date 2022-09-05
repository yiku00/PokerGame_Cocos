#include "pch.h"
#include "VipInfoPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"
#include "PokerRankHelper.h"

const ccColor3B ccMenuGrayColor = { 134, 134, 134 };
const ccColor3B ccPointGrayColor = { 156, 156, 156 };

VipInfoPanel::VipInfoPanel()
{
	mVipIndex = PokerRankHelper::getRank();
	initPanel();
	refreshVipData();
	refreshBtnState();
}

VipInfoPanel::~VipInfoPanel()
{
	//destruct();
}

void VipInfoPanel::onClicked(const string& name)
{
	if (name == getButtonName(mCloseBtn)) {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		LayerManager::getSingleton().popLayer(this);
	}
	else if (name == getButtonName(mLeftArrowBtn)) {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		mVipIndex--;
		if (mVipIndex < 0)
			mVipIndex = 0;	

		refreshBtnState();
		refreshVipData();
	}
	else if (name == getButtonName(mRightArrowBtn)) {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		int dataSize = GameDataManager::getSingletonPtr()->GetGameDataPtr()->vipdata_size();
		mVipIndex++;
		if (mVipIndex >= dataSize)
			mVipIndex = dataSize - 1;
		refreshBtnState();
		refreshVipData();
	}
}

void VipInfoPanel::initPanel()
{
	addMouseBlockPanel(this, true);
	construct(getMxmlPath() + "dmy_vip_benefit.mxml");
	setButtonListener(this);

	mCloseBtn = getButton("sbtn_cancel");
	mLeftArrowBtn = getButton("sbtn_movearrow_l");
	mRightArrowBtn = getButton("sbtn_movearrow_r");

	mTitleLabel = getLabel("txt_title");
	mTitleUnderLabel = getLabel("txt_title_under");
	mSeasonTitleLabel = getLabel("txt_time");
	mSeasonLabel = getLabel("txt_time_sum");
	mVipAmountLabel = getLabel("txt_vip_sum");
	mRankIcon = getSkel("skel_rankicon");
	CCSize originSize = getDummy("skel_rankicon").size;
	CCSize iconSize = getDummy("dmy_rankicon").size;
	mRankIcon->setScale(getScaleFit(originSize, iconSize));
	mNowMyVipLabel = getLabel("txt_cvip");
	mVipDescLabel = getLabel("txt_cvip_info");
	mBenefitLabel = getLabel("txt_benefit");
	mNextSeasonDescLabel = getLabel("txt_vip_info");

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

	W_TourOfInfo* _pInfoData = GameDataManager::getSingletonPtr()->m_TourOfInfo;	
	mSeasonLabel->setString(_pInfoData->title().c_str());

	mTitleLabel->setString(GameStringDepot::getSingleton().getString("VipInfo_Title").c_str());
	mTitleUnderLabel->setString(GameStringDepot::getSingleton().getString("VipInfo_Title").c_str());
	mSeasonTitleLabel->setString(GameStringDepot::getSingleton().getString("VipInfo_NextSeasonTitle").c_str());
	mVipDescLabel->setString(GameStringDepot::getSingleton().getString("VipInfo_VipDesc").c_str());
	mBenefitLabel->setString(GameStringDepot::getSingleton().getString("VipInfo_Benefit").c_str());
	mNextSeasonDescLabel->setString(GameStringDepot::getSingleton().getString("VipInfo_NextSeasonDesc").c_str());
}

void VipInfoPanel::SetVipOption(W_VipData_VipOption _data)
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

void VipInfoPanel::refreshVipData()
{
	setVipBonus();
}

void VipInfoPanel::setVipBonus()
{
	string vipStr = NxGetFormatString(GameStringDepot::getSingleton().getString("VIP_EXPRESS"), mVipIndex);
	mNowMyVipLabel->setString(vipStr.c_str());
	PokerRankHelper::setRankIcon(mRankIcon, mVipIndex);
	mVipAmountLabel->setString(StringConverter::toString(mVipIndex).c_str());
	int _DataSize = GameDataManager::getSingletonPtr()->GetGameDataPtr()->vipdata_size();
	for (int _i = 0; _i < _DataSize; _i++)
	{
		W_VipData _vipData = GameDataManager::getSingletonPtr()->GetGameDataPtr()->vipdata(_i);
		if (mVipIndex == _vipData.level())
		{
			int _size = _vipData.vipoption_size();
			for (int _index = 0; _index < _size; _index++)
			{
				SetVipOption(_vipData.vipoption(_index));
			}						
			return;
		}
	}
}

void VipInfoPanel::refreshBtnState()
{
	int dataSize = GameDataManager::getSingletonPtr()->GetGameDataPtr()->vipdata_size();
	mLeftArrowBtn->setEnable(mVipIndex != 0);
	mLeftArrowBtn->setVisible(mVipIndex != 0);
	mRightArrowBtn->setEnable(mVipIndex < dataSize - 1);
	mRightArrowBtn->setVisible(mVipIndex < dataSize - 1);
}
