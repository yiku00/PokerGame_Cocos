#include "pch.h"
#include "SeasonResultPanel.h"
#include "HeroUtil.h"
#include "GameStringDepot.h"
#include "GameDataManager.h"
#include "PokerRankHelper.h"
#include "PokerResourceHelper.h"

const ccColor3B ccMenuGrayColor = { 134, 134, 134 };
const ccColor3B ccPointGrayColor = { 156, 156, 156 };

SeasonResultPanel::SeasonResultPanel()
{
	W_TourOfInfo* tourofInfo = GameDataManager::getSingletonPtr()->m_TourOfInfo;
	mResultInfo.CopyFrom(tourofInfo->resultinfo());
	mVipIndex = mResultInfo.vip();
	initPanel();
	refreshVipData();
	refreshResult();
}

SeasonResultPanel::~SeasonResultPanel()
{
	//destruct();
}

void SeasonResultPanel::onClicked(const string& name)
{
	if (name == getButtonName(mCloseBtn)) {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		LayerManager::getSingleton().popLayer(this);
	}
}

void SeasonResultPanel::initPanel()
{
	addMouseBlockPanel(this, true);
	construct(getMxmlPath() + "dmy_season_end1.mxml");
	setButtonListener(this);

	mCloseBtn = getButton("sbtn_cancel");
	mVipAmountLabel = getLabel("txt_vip_sum");
	mNextSeasonDesc = getLabel("txt_time_sum");
	
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

	mRankIcon = getSkel("skel_rankicon");
	CCSize originSize = getDummy("skel_rankicon").size;
	CCSize iconSize = getDummy("dmy_rankicon").size;
	mRankIcon->setScale(getScaleFit(originSize, iconSize));
	mRankTitle = getLabel("str_rank_name");
	mConfirmBtn = new SmallButtonPanel(SmallButtonPanel::LOBBY_UI_CONFIRM);
	addChild(mConfirmBtn);
	mConfirmBtn->release();
	CCPoint pos = getDummy("dmy_button_smiddle").origin;
	pos.y = -pos.y;
	mConfirmBtn->setPosition(pos);
	mConfirmBtn->m_Button->setName(getButtonName(mCloseBtn));
	mConfirmBtn->SetButtonListener(this);
	mConfirmBtn->SetBtnText(GameStringDepot::getSingleton().getString("TXT_OK_LABEL"));

	getLabel("txt_season_info")->setString(GameStringDepot::getSingletonPtr()->getString("VipInfo_NextSeasonDesc").c_str());	//다음 시즌동안 아래와 같은 효과가 적용됩니다.
	getLabel("txt_time")->setString(GameStringDepot::getSingletonPtr()->getString("VipInfo_NextSeasonTitle").c_str());	//다음시즌
	getLabel("txt_title_under")->setString(GameStringDepot::getSingletonPtr()->getString("SeasonResultPanel_SEASONEND").c_str());
	getLabel("txt_title")->setString(GameStringDepot::getSingletonPtr()->getString("SeasonResultPanel_SEASONEND").c_str());
}

void SeasonResultPanel::refreshVipData()
{
	setVipBonus();
}

void SeasonResultPanel::SetVipOption(W_VipData_VipOption _data)
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

void SeasonResultPanel::setVipBonus()
{
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

void SeasonResultPanel::refreshResult()
{
	PokerRankHelper::setRankIcon(mRankIcon, mResultInfo.rating());
	mRankTitle->setString(PokerRankHelper::getRankTitleStr(mResultInfo.rating()).c_str());
	mRankTitle->setColor(StringConverter::parseColor3B(PokerRankHelper::getRankTitleColorStr(mResultInfo.rating())));
	//결과 표시
	mNextSeasonDesc->setString(mResultInfo.nextdesc().c_str());			
}

void SeasonResultPanel::onRefresh()
{
	setVisible(true);
}
