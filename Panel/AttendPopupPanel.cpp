#include "pch.h"
#include "AttendPopupPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"
#include "PokerResourceHelper.h"

AttendPopupPanel::AttendPopupPanel()
{
	initPanel();
	
}

AttendPopupPanel::~AttendPopupPanel()
{
}

void AttendPopupPanel::onClicked(const string& name)
{	
	if (name == getButtonName(mCloseBtn)) {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		LayerManager::getSingleton().popLayer(this);
	}
}

void AttendPopupPanel::initPanel()
{
	addMouseBlockPanel(this , true);
	construct(getMxmlPath() + "dmy_attendance.mxml");
	mTitle = getSkel("skel_title");
	mPanelBg = getSkel("skel_panel_7day");
	mCloseBtn = getButton("sbtn_cancel");
	m7TitleLabel = getLabel("txt_7day");
	m7RewardLabel = getLabel("txt_7day_sum");	
	mRewardIcon = getSkel("skel_icon");
	mUserPhoto = getImage("dmy_img_character_s");
	setButtonListener(this);
	initContentPanel();
	initDesc();
}

void AttendPopupPanel::refresh()
{

}

void AttendPopupPanel::initDesc()
{
	if (isBasicAttend())
		mTitle->playAnimation("title_ko_new");
	else
		mTitle->playAnimation("title_ko");
	
	string attendStr = NxGetFormatString(GameStringDepot::getSingleton().getString("AttendDescTitle"));
	if (isBasicAttend())
		attendStr = NxGetFormatString(GameStringDepot::getSingleton().getString("AttendBasicDescTitle"));

	int fontSize = GameStringDepot::getSingleton().getStringSize("AttendDescTitle");
	Script* descScript = Script::create(attendStr, getDummy("dmy_attend_info").size, fontSize , kCCTextAlignmentLeft, "KBIZgo H");
	int gapHeight = getFontGap("fonts/KBIZgo H.ttf", fontSize);
	descScript->setCenterPos(getImage("dmy_attend_info")->getPosition(), gapHeight);
	addChild(descScript);
}

void AttendPopupPanel::initContentPanel()
{
	W_AttendSevenInfo* senvenInfo = GameDataManager::getSingleton().getAttendSevenInfo();
	for (int i = 0; i < 6; i++)
	{
		string dmyStr = "dmy_attpanel_day" + StringConverter::toString(i + 1);
		AttendContentPanel* pPanel = new AttendContentPanel();
		addChild(pPanel);
		pPanel->release();
		W_AttendSevenData attendSevenData = GameDataManager::getSingleton().getAttendSevenData(i);
		pPanel->setRewardData(i, attendSevenData.rewardset(), getAttendDay());
		pPanel->setPosition(getImage(dmyStr)->getPosition());
		mContents.push_back(pPanel);
	}

	W_AttendSevenData attendSevenData = GameDataManager::getSingleton().getAttendSevenData(6);
	string attendStr = NxGetFormatString(GameStringDepot::getSingleton().getString("AttendDayTitle"),7);
	m7TitleLabel->setString(attendStr.c_str());
	
	string labelStr = PokerResourceHelper::getRewardIconStr(attendSevenData.rewardset()) + "_b";
	if (mRewardIcon->hasAnimation(labelStr))
		mRewardIcon->playAnimation(labelStr);

	if (attendSevenData.rewardset().type() == GAMEMONEY) {
		string gameMoneyStr = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(attendSevenData.rewardset().amount()));
		m7RewardLabel->setString(gameMoneyStr.c_str());
	
	}
	else if (attendSevenData.rewardset().type() == CHARACTER) {
		mRewardIcon->setVisible(false);		
		mUserPhoto->setSpriteFrameWithFile(PokerResourceHelper::getCharacterImgName(attendSevenData.rewardset().id()));
		CCRect rect = getDummy("dmy_img_character_s");
		mUserPhoto->fit(CCSize(rect.getMaxX() - rect.getMinX(), rect.getMaxY() - rect.getMinY()));
		string amountStr = StringConverter::toString(attendSevenData.rewardset().amount()) + GameStringDepot::getSingleton().getString("TXT_DAY");
		m7RewardLabel->setString(amountStr.c_str());
	}
	else {
		string amountStr = StringConverter::toString(attendSevenData.rewardset().amount()) + GameStringDepot::getSingleton().getString("TXT_COUNT_THING");
		m7RewardLabel->setString(amountStr.c_str());
	}
	
	if (getAttendDay() == 7) {
		mPanelBg->playAnimation("panel_7day_on", true);
		m7TitleLabel->setColor(StringConverter::parseColor3B("fff7af"));
		m7TitleLabel->setStrokeColor((ccColor4B)StringConverter::parseColor3B("7b4301"));
		m7RewardLabel->setColor(StringConverter::parseColor3B("fffbd1"));
		m7RewardLabel->setStrokeColor((ccColor4B)StringConverter::parseColor3B("784100"));

		CCPoint point = getDummy("dmy_att_clear2").origin;
		point.y = -point.y;
		Panel* completePanel = new Panel();
		addChild(completePanel);
		completePanel->release();
		completePanel->construct(getMxmlPath() + "dmy_att_clear2.mxml");
		completePanel->setPosition(point);
		completePanel->getSkel("skel_clear2")->playAnimation("clear2_start");
		completePanel->getSkel("skel_clear2")->appendAnimation("clear2_loop", true);
	}
	else {
		m7TitleLabel->setColor(StringConverter::parseColor3B("f38a8a"));
		m7TitleLabel->setStrokeColor((ccColor4B)StringConverter::parseColor3B("622128"));
		m7RewardLabel->setColor(StringConverter::parseColor3B("793339"));
		m7RewardLabel->setStrokeColor((ccColor4B)StringConverter::parseColor3B("1f080a"));
	}
}

int AttendPopupPanel::getAttendDay()
{
	W_AttendSevenInfo* attendSevenInfo = GameDataManager::getSingleton().getAttendSevenInfo();	
	if (attendSevenInfo)
		return attendSevenInfo->attendday();
	
	return -1;
}

void AttendPopupPanel::onRefresh()
{
	setVisible(true);
}

bool AttendPopupPanel::isBasicAttend()
{
	W_AttendSevenInfo* senvenInfo = GameDataManager::getSingleton().getAttendSevenInfo();
	return senvenInfo->isfinishfirstattend() == false;
}
