#include "pch.h"
#include "PokerBackgroundPanel.h"
#include "NxUtil.h"
#include "HeroUtil.h"
#include "RefDefine.h"

#include "GameDataManager.h"
#include "PokerPlayerInfoPanel.h"

#include "JokboList.h"

PokerBackgroundPanel::PokerBackgroundPanel()
{
	mJackPotAni = nullptr;
	
	for (int _i = 0; _i < 5; _i++)
	{
		m_HoldemCommunityCard[_i] = nullptr;
		m_HoldemCommunityCardEffect[_i] = nullptr;
		m_HoldemCommunityCardEffectBack[_i] = nullptr;
		m_HoldemCommunityCardSmoke[_i] = nullptr;
	}
	
	_intiPanel();
	_initLabel();
	_initImage();
	//setTouchable(true);

	m_bCenterEffect = false;
	refreshRoomNo();
}

PokerBackgroundPanel::~PokerBackgroundPanel()
{
	if (m_DayPanel)
	{
		m_DayPanel->removeAllChildren();
	}	
	removeAllChildren();	
}

void PokerBackgroundPanel::_intiPanel()
{
	if (GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_HOLDEM)
	{
		construct(getMxmlPath() + "texasholdem_ingame_view.mxml");
	}
	else
	{
	//	construct(getMxmlPath() + "gamescreen.mxml");
		construct(getMxmlPath() + "poker_ingame_view.mxml");		
	}

	mRoomNumberBg = getImage("skel_roomnumber_panel");
	mRoomNumberTitle = getLabel("txt_roomno");
	mRoomNumberSum = getLabel("txt_roomno_sum");	

	mRoomPasswardBg = getImage("skel_secret_panel");
	mRoomPassward = getLabel("txt_secret");
	mRoomPasswardBottom = getLabel("txt_secret_under");

	//주건 필요
	mPokerChip = getSkel("skel_count0");
	mPokerChip->setVisible(false);
	//if (GameDataManager::getSingletonPtr()->m_GameMode == GameMode::MODE_NORMAL && !GameDataManager::getSingletonPtr()->m_IsSelectRoom) {
	//// 게등위 심의 위반, 보너스 칩 지급 제한
	//if (GameDataManager::getSingletonPtr()->m_GameMode == GameMode::MODE_NORMAL) {
	//	mPokerChip->setVisible(true);
	//}

	//시즌, tourmentm 라면 아니고
	//server 가 select 라면 아니다.

	mLimitedIcon = getSkel("skel_limited_icon");
	mLimitedIcon->setVisible(false);

	m_DayPanel = nullptr;
	if (GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_BADUKI)
	{
		m_DayPanel = new Panel();
		if (m_DayPanel)
		{
			m_DayPanel->construct(getMxmlPath() + "dmy_badugiday.mxml");
			m_DayPanel->getSkel("skel_dayimage");
			m_DayPanel->getSkel("skel_afternoon_on")->stopLooping();
			m_DayPanel->getSkel("skel_morning_on")->stopLooping();
			m_DayPanel->getSkel("skel_night_on")->stopLooping();

			m_DayPanel->getSkel("skel_afternoon_on")->setVisible(false);
			m_DayPanel->getSkel("skel_morning_on")->setVisible(false);
			m_DayPanel->getSkel("skel_night_on")->setVisible(false);

			CCPoint _dayPanelPos = getDummy("dmy_badugiday").origin;
			_dayPanelPos.y = -_dayPanelPos.y;
			m_DayPanel->setPosition(_dayPanelPos);

			addChild(m_DayPanel);
			m_DayPanel->release();
		}

	}
	setDiactivateRoomNo();
	initJackPotRewardPanel();
}

void PokerBackgroundPanel::setBadukiDayPanel(int _badukiDayType, bool _visible)
{
	if (m_DayPanel == nullptr)
		return;

	switch (_badukiDayType)
	{
	case DAY_TYPE_MORNING:
		m_DayPanel->getSkel("skel_morning_on")->setVisible(_visible);
		m_DayPanel->getSkel("skel_morning_on")->playAnimation("morning_on_start");
		m_DayPanel->getSkel("skel_morning_on")->appendAnimation("morning_on_stay");
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_dayState = DAY_TYPE_MORNING;
		break;
	case DAY_TYPE_AFTERNOON:
		m_DayPanel->getSkel("skel_morning_on")->playAnimation("morning_on_end");
		m_DayPanel->getSkel("skel_afternoon_on")->setVisible(_visible);
		m_DayPanel->getSkel("skel_afternoon_on")->playAnimation("afternoon_on_start");
		m_DayPanel->getSkel("skel_afternoon_on")->appendAnimation("afternoon_on_stay");
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_dayState = DAY_TYPE_AFTERNOON;
		break;
	case DAY_TYPE_NIGHT:
		m_DayPanel->getSkel("skel_afternoon_on")->playAnimation("afternoon_on_end");
		m_DayPanel->getSkel("skel_night_on")->setVisible(_visible);
		m_DayPanel->getSkel("skel_night_on")->playAnimation("night_on_start");
		m_DayPanel->getSkel("skel_night_on")->appendAnimation("night_on_stay");
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_dayState = DAY_TYPE_NIGHT;
		break;
	case DAY_TYPE_END:
		if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_dayState == DAY_TYPE_MORNING)
			m_DayPanel->getSkel("skel_morning_on")->playAnimation("morning_on_end");
		if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_dayState == DAY_TYPE_AFTERNOON)
			m_DayPanel->getSkel("skel_afternoon_on")->playAnimation("afternoon_on_end");
		if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_dayState == DAY_TYPE_NIGHT)
			m_DayPanel->getSkel("skel_night_on")->playAnimation("night_on_end");

		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_dayState = DAY_TYPE_END;
		break;
	case DAY_TYPE_ALL_CLOSE:
		m_DayPanel->getSkel("skel_morning_on")->setVisible(false);
		m_DayPanel->getSkel("skel_afternoon_on")->setVisible(false);
		m_DayPanel->getSkel("skel_night_on")->setVisible(false);
		break;
	}
}


void PokerBackgroundPanel::setTotalBettingMoney(string bettingMoney)
{
	/*string::iterator itPos = bettingMoney.begin();
	size_t pos = bettingMoney.size();
	while (true)
	{
		if (pos <= 3)
			break;

		itPos = bettingMoney.begin() + pos - 3;
		bettingMoney.insert(itPos, ',');
		pos = bettingMoney.find(",");
	}*/

	mBettingAmount->setString(bettingMoney.c_str());
}

void PokerBackgroundPanel::setCallBettingMoney(string callMoney)
{
	/*string::iterator itPos = callMoney.begin();
	size_t pos = callMoney.size();
	while (true)
	{
		if (pos <= 3)
			break;

		itPos = callMoney.begin() + pos - 3;
		callMoney.insert(itPos, ',');
		pos = callMoney.find(",");
	}*/

	mCallAmount->setString(callMoney.c_str());
}



void PokerBackgroundPanel::_initLabel()
{
	//<mx:Text id = "txt_betcount.r.c.24" styleName = "textStyle" x = "431" y = "297" width = "204" text = "0000억 0000만 골드 " / >
	//<mx:Text id = "txt_callcount.r.c.20" styleName = "textStyle2" x = "429" y = "333" width = "204" text = "0000억 0000만 골드 " / >
	mBettingAmount = getLabel("txt_totalsum");
	mCallAmount = getLabel("txt_callsum");
	getLabel("txt_call")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_total")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	//mBettingAmount->setString(U8("다람쥐"));
}

void PokerBackgroundPanel::_initImage()
{
	//m_Chip = getSkel("skel_getchip");
	//m_Chip->setVisible(false);
	//m_Chip->setListener(this);

	getSkel("skel_background")->setZOrder(-2);
	getSkel("skel_background2")->setZOrder(-2);

	getSkel("skel_finaltable")->setVisible(false);

	m_CenterBoxEffect = getSkel("skel_totalsum_light");
	m_CenterBoxEffect->setVisible(false);
	m_CenterBoxEffect->playAnimation("totalsum_light_start");
	m_CenterBoxEffect->appendAnimation("totalsum_light_stay");
	m_CenterBoxEffect->appendAnimation("totalsum_light_end");

	m_pOptionButton = getButton("sbtn_ingame_option_button");
	m_pOptionButton->setType(Button::NoPressImg);
	m_pOptionButton->setZOrder(1);

	//m_LevelupEffect = getSkel("skel_level_up");
	//m_LevelupEffect->setVisible(false);
	//m_LevelupEffect->playAnimation("level_up", false);

	//m_MadeBonusEffect = getSkel("skel_made_bonus");
	//m_MadeBonusEffect->setVisible(false);
	//m_MadeBonusEffect->playAnimation("made_bonus", false);

	//m_AutoRefillEffect = getSkel("skel_autorefill_start");
	//m_AutoRefillEffect->setVisible(false);
	//m_AutoRefillEffect->playAnimation("autorefill_start", false);

	if (GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_HOLDEM)
	{
		for (int _i = 0; _i < 5; _i++)
		{
			m_HoldemCommunityCard[_i] = getSkel("skel_smallcard_" + StringConverter::toString(_i+1));
			m_HoldemCommunityCard[_i]->setVisible(false);
			m_HoldemCommunityCard[_i]->stopLooping();
			
			m_HoldemCommunityCardEffect[_i] = getSkel("skel_made_appear_front" + StringConverter::toString(_i + 1));
			m_HoldemCommunityCardEffect[_i]->setVisible(false);
			m_HoldemCommunityCardEffect[_i]->stopLooping();
			
			m_HoldemCommunityCardEffectBack[_i] = getSkel("skel_made_appear_back" + StringConverter::toString(_i + 1));
			m_HoldemCommunityCardEffectBack[_i]->setVisible(false);
			m_HoldemCommunityCardEffectBack[_i]->stopLooping();
			
			m_HoldemCommunityCardSmoke[_i] = getSkel("skel_cardsmoke_texas" + StringConverter::toString(_i + 1));
			m_HoldemCommunityCardSmoke[_i]->setVisible(false);
			m_HoldemCommunityCardSmoke[_i]->stopLooping();
		}

		m_HoldemCommunityCardButton = getButton("sbtn_cardtouch");
		m_HoldemCommunityCardButton->setVisible(false);
	}

}


void PokerBackgroundPanel::ShowCenterBoxEffect(float _duration)
{
	if (m_bCenterEffect == true)
		return;

	m_bCenterEffect = true;
	m_CenterBoxEffect->setVisible(true);
	m_CenterBoxEffect->playAnimation("totalsum_light_start");
	m_CenterBoxEffect->appendAnimation("totalsum_light_stay", true);

	runAction(CCSequence::createWithTwoActions(
		CCDelayTime::create(_duration),
		CCCallFunc::create(this, callfunc_selector(PokerBackgroundPanel::EndCenterBoxEffect))
		));
}

void PokerBackgroundPanel::EndCenterBoxEffect()
{
	m_bCenterEffect = false;
	m_CenterBoxEffect->playAnimation("totalsum_light_end");
}

void PokerBackgroundPanel::SetGameKindBoard(int _kind)
{

	//green //orange //pistachio //purple //violet //yellow

	if (_kind == GAMEKIND_7POKER)
	{
		getSkel("skel_tablecolor")->playAnimation("tablecolor_red");
		getSkel("skel_tablecolor2")->playAnimation("tablecolor_red2");
	}
	else if (_kind == GAMEKIND_HIGH_LOW)
	{
		getSkel("skel_tablecolor")->playAnimation("tablecolor_blue");
		getSkel("skel_tablecolor2")->playAnimation("tablecolor_blue2");
	}
	else if (_kind == GAMEKIND_BADUKI)
	{
		getSkel("skel_tablecolor")->playAnimation("tablecolor_green");
		getSkel("skel_tablecolor2")->playAnimation("tablecolor_green2");
	}
	else if (_kind == GAMEKIND_HOLDEM)
	{
		getSkel("skel_tablecolor")->playAnimation("tablecolor_pistachio");
		getSkel("skel_tablecolor2")->playAnimation("tablecolor_pistachio2");
	}
}

void PokerBackgroundPanel::SetLastTableBoard()
{
	getSkel("skel_finaltable")->setVisible(true);
	getSkel("skel_tablecolor")->playAnimation("tablecolor_velvet");
	getSkel("skel_tablecolor2")->playAnimation("tablecolor_velvet2");
}

void PokerBackgroundPanel::MenuItemCallBack(CCObject* sender)
{
	CCMenuItem* menuItem = (CCMenuItem*)sender;
}

void PokerBackgroundPanel::onAnimationEnded(const string& ani)
{
	//if (ani.find("getchip_end") != string::npos)
	//{
	//	m_Chip->setVisible(false);
	//}
}

//void PokerBackgroundPanel::TurnOnGetChip()
//{
//	if (!m_Chip)
//		return;
//
//	m_Chip->playAnimation("getchip_start");
//	m_Chip->appendAnimation("getchip_loop");
//	m_Chip->appendAnimation("getchip_end");
//	m_Chip->setVisible(true);
//}

//void PokerBackgroundPanel::TurnOffGetChip()
//{
//	if (!m_Chip)
//		return;
//
//	m_Chip->setVisible(false);
//}

void PokerBackgroundPanel::setVisibleCenterUI(bool _visible)
{
	mBettingAmount->setVisible(_visible);
	mCallAmount->setVisible(_visible);
	getSkel("skel_totalsum")->setVisible(_visible);
	getLabel("txt_call")->setVisible(_visible);
	getLabel("txt_total")->setVisible(_visible);

}

void PokerBackgroundPanel::setMadeResult(int made)
{
	if (made == -1) {
		mLimitedIcon->setVisible(false);
		return;
	}

	if ((made > HighJokboKind::HIGH_NO && made <= HighJokboKind::HIGH_FOUR_CARD) || (made >= HighJokboKind::HIGH_BADUKI_GOLF && made <= HighJokboKind::HIGH_BADUKI_THIRD)) {
		//현재 적용중이다.
		bool isActivateWindow = GameDataManager::getSingleton().isActivateShopInfo(W_LimitShopData_eLimitType_l_jackpot);
		bool isActive = GameDataManager::getSingleton().isActivateLimitedTime(W_LimitShopData_eLimitType_l_jackpot);
		if (!isActive && isActivateWindow && !GameDataManager::getSingleton().isActivateLimitedBuffer(W_LimitShopData_eLimitType_l_jackpot)) {
			mLimitedIcon->setVisible(true);
			mLimitedIcon->playAnimation("lobby_limited_icon1_ingame");
		}
	}
	else  {
		//made 상품
		bool isActive = GameDataManager::getSingleton().isActivateLimitedTime(W_LimitShopData_eLimitType_l_made);
		bool isActivateWindow = GameDataManager::getSingleton().isActivateShopInfo(W_LimitShopData_eLimitType_l_made);
		if (!isActive && isActivateWindow && !GameDataManager::getSingleton().isActivateLimitedBuffer(W_LimitShopData_eLimitType_l_made)) {
			mLimitedIcon->setVisible(true);
			mLimitedIcon->playAnimation("lobby_limited_icon2_ingame");
		}
	}
}

void PokerBackgroundPanel::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK) {
		HeroApp::getSingleton().exit();
	}
}

void PokerBackgroundPanel::initJackPotRewardPanel()
{
	mJackPotRewardPanel = new Panel();
	addChild(mJackPotRewardPanel);
	mJackPotRewardPanel->release();
	mJackPotRewardPanel->construct(getMxmlPath() + "dmy_jackpot_bonus.mxml");
	CCPoint _dayPanelPos = getDummy("dmy_jackpot_bonus").origin;
	_dayPanelPos.y = -_dayPanelPos.y;
	mJackPotRewardPanel->setPosition(_dayPanelPos);
	CCPoint _RankPos = mJackPotRewardPanel->getDummy("dmy_number_bonus").origin;
	CCSize _RankSize = mJackPotRewardPanel->getDummy("dmy_number_bonus").size;
	_RankPos.x = _RankPos.x + _RankSize.width;
	_RankPos.y = DESIGN_HEIGHT - _RankPos.y - (_RankSize.height / 2);
	mTerm = CCLabelBMFont::create("123", "fonts/number_bonus.fnt");
	mTerm->setContentSize(_RankSize);
	mTerm->setAnchorPoint(ccp(0.0f, 1.0f));
	mTerm->setPosition(_RankPos);
	int gapHeight = (_RankSize.height - mTerm->getContentSize().height) * 0.5f;	
	mTerm->setPositionY(mTerm->getPositionY() + _RankSize.height * 0.5f);

	mJackPotRewardPanel->addChild(mTerm);
	mJackPotRewardPanel->setVisible(false);
	mJackPotAni = mJackPotRewardPanel->getSkel("skel_bonus_back");	
	mJackPotAni->pauseAnimation();
}

void PokerBackgroundPanel::setJackPotRewardPanel(string str)
{
	mJackPotAni->playAnimation("bonus_back");
	mJackPotRewardPanel->setVisible(true);
	mTerm->setString(str.c_str());
}

void PokerBackgroundPanel::setVibieCallBoard(bool visible)
{
	setVisibleCenterUI(visible);
}

void PokerBackgroundPanel::setDiactivateRoomNo()
{
	mRoomNumberBg->setVisible(false);
	mRoomNumberTitle->setVisible(false);
	mRoomNumberSum->setVisible(false);

	mRoomPasswardBg->setVisible(false);
	mRoomPassward->setVisible(false);
	mRoomPasswardBottom->setVisible(false);
}

void PokerBackgroundPanel::setActivateRoomNo(int roomId)
{
	mRoomNumberBg->setVisible(true);
	mRoomNumberTitle->setVisible(true);
	mRoomNumberSum->setVisible(true);

	if (!GameDataManager::getSingleton().getPassward().empty()) {
		mRoomPasswardBg->setVisible(true);
		mRoomPassward->setVisible(true);
		mRoomPasswardBottom->setVisible(true);

		mRoomNumberSum->setString(StringConverter::toString(roomId).c_str());
		mRoomPassward->setString(GameDataManager::getSingleton().getPassward().c_str());
		mRoomPasswardBottom->setString(GameDataManager::getSingleton().getPassward().c_str());
	}
	else {
		mRoomPasswardBg->setVisible(false);
		mRoomPassward->setVisible(false);
		mRoomPasswardBottom->setVisible(false);

		mRoomNumberBg->setVisible(false);
		mRoomNumberTitle->setVisible(false);
		mRoomNumberSum->setVisible(false);
	}
}

void PokerBackgroundPanel::refreshRoomNo()
{
	if (GameDataManager::getSingletonPtr()->m_IsSelectRoom) {
		GameRoomInfo* _pInfo = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr();
		if (_pInfo)
			setActivateRoomNo(_pInfo->GetRoomIdx());
	}
	else {
		setDiactivateRoomNo();
	}
}
void PokerBackgroundPanel::onEnter()
{
	Panel::onEnter();

	setKeypadEnabled(true);
}