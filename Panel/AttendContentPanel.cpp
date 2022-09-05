#include "pch.h"
#include "AttendContentPanel.h"
#include "HeroUtil.h"
#include "GameStringDepot.h"
#include "GameDataManager.h"
#include "PokerResourceHelper.h"

AttendContentPanel::AttendContentPanel()
{
	initPanel();
}

AttendContentPanel::~AttendContentPanel()
{
}

void AttendContentPanel::initPanel()
{
	mMainPanel = new Panel();
	mMainPanel->construct(getMxmlPath() + "dmy_attpanel_day.mxml");
	addChild(mMainPanel);
	mMainPanel->release();
	CCSize _contentSize = mMainPanel->getContentSize();
	mMainPanel->setPositionY(_contentSize.height - DESIGN_HEIGHT - _contentSize.height / 2.f);
	mMainPanel->setPositionX(-_contentSize.width / 2.f);
	mMainPanel->setContentSize(_contentSize);
	this->setContentSize(_contentSize);
	this->setPositionX(DESIGN_WIDTH / 2);
	this->setPositionY(DESIGN_HEIGHT / 2);

	mPanelBg = mMainPanel->getSkel("skel_panel_day");
	mDayTitleLabel = mMainPanel->getLabel("txt_day");
	mRewardLabel = mMainPanel->getLabel("txt_day_sum");
	mRewardIcon = mMainPanel->getSkel("skel_icon");
	mUserPhoto = mMainPanel->getImage("dmy_img_character_s");
	//txt_day - "x일차" 비활성 d68d45 R214 B141 B69 / 활성 fff7af R255 G247 B175
	mDayTitleLabel->setGrayColor(StringConverter::parseColor3B("d68d45"));
	// txt_day_sum - x일차 보상 금액입니다. 비활성 7a4e2f R122 G78 B47 / 활성 fffbd1 R255 G251 B209
	mRewardLabel->setGrayColor(StringConverter::parseColor3B("7a4e2f"));
}

void AttendContentPanel::setRewardData(int day, W_RewardInfo_RewardSet rewardSet, int nowDay)
{
	string attendStr = NxGetFormatString(GameStringDepot::getSingleton().getString("AttendDayTitle"), day + 1);
	mDayTitleLabel->setString(attendStr.c_str());

	PokerResourceHelper::setRewardIcon(mRewardIcon, rewardSet);

	//게임머니일때
	if (rewardSet.type() == GAMEMONEY) {
		string gameMoneyStr = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(rewardSet.amount()));
		mRewardLabel->setString(gameMoneyStr.c_str());
	}
	else if (rewardSet.type() == CHARACTER) {
		mRewardIcon->setVisible(false);
		mUserPhoto->setSpriteFrameWithFile(PokerResourceHelper::getCharacterImgName(rewardSet.id()));
		CCRect rect = mMainPanel->getDummy("dmy_img_character_s");
		mUserPhoto->fit(CCSize(rect.getMaxX() - rect.getMinX(), rect.getMaxY() - rect.getMinY()));

		string amountStr = StringConverter::toString(rewardSet.amount()) + GameStringDepot::getSingleton().getString("TXT_DAY");
		mRewardLabel->setString(amountStr.c_str());
	}
	else {
		string amountStr = StringConverter::toString(rewardSet.amount()) + GameStringDepot::getSingleton().getString("TXT_COUNT_THING");
		mRewardLabel->setString(amountStr.c_str());
	}
	/*
	txt_day - "x일차" 비활성 d68d45 R214 B141 B69 / 활성 fff7af R255 G247 B175
	ast_day - x일차 글자 획입니다.비활성 77461c R119 G70 B28 / 활성 7b4301 R123 G67 B1
	txt_day_sum - x일차 보상 금액입니다.비활성 7a4e2f R122 G78 B47 / 활성 fffbd1 R255 G251 B209
	ast_day_sum - x일차 보상 금액 획입니다.비활성 150901 R21 G9 B1 / 활성 784100 R120 G65 B0
	*/

	//stroke 값 변경
	if (day <= nowDay - 1) {
		mDayTitleLabel->setColor(StringConverter::parseColor3B("fff7af"));
		mDayTitleLabel->setStrokeColor((ccColor4B)StringConverter::parseColor3B("7b4301"));
		mRewardLabel->setColor(StringConverter::parseColor3B("fffbd1"));
		mRewardLabel->setStrokeColor((ccColor4B)StringConverter::parseColor3B("784100"));
		CCPoint point = mMainPanel->getDummy("dmy_att_clear1").origin;
		point.y = -point.y;
		Panel* completePanel = new Panel();
		mMainPanel->addChild(completePanel);
		completePanel->release();
		completePanel->construct(getMxmlPath() + "dmy_att_clear1.mxml");
		completePanel->setPosition(point);
		if (day == nowDay - 1) {
			completePanel->getSkel("skel_clear1")->playAnimation("clear1_start");
			completePanel->getSkel("skel_clear1")->appendAnimation("clear1_loop", true);
			mPanelBg->playAnimation("panel_day_on", true);
		}
		else {
			completePanel->getSkel("skel_clear1")->playAnimation("clear1_loop");
		}
	}
	else {
		mDayTitleLabel->setColor(StringConverter::parseColor3B("d68d45"));
		mDayTitleLabel->setStrokeColor((ccColor4B)StringConverter::parseColor3B("77461c"));
		mRewardLabel->setColor(StringConverter::parseColor3B("7a4e2f"));
		mRewardLabel->setStrokeColor((ccColor4B)StringConverter::parseColor3B("150901"));
	}		
}
