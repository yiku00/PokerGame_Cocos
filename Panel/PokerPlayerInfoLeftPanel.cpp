#include "pch.h"
#include "PokerPlayerInfoLeftPanel.h"
#include "HeroUtil.h"
//#include "Player.h"
#include "RefDefine.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"

#define DMY_CARD_SMALL		"dmy_card_small"

PokerPlayerInfoLeftPanel::PokerPlayerInfoLeftPanel()
{
	mHighLowImage = nullptr;
	mBettingImage = nullptr;
	mWinPanel = nullptr;
	mIsTurn = false;
	mElapsedTime = 0.0f;
	mMainPanel = nullptr;

	_initPanel();
	_initText();
	_initImage();
	_initGageBar();
	_initBettingMark();
	_initHighLowImage();
	//TurnOffGameOut();
	//_addCard();
}

PokerPlayerInfoLeftPanel::~PokerPlayerInfoLeftPanel()
{
	removeFromParentAndCleanup(true);
}

// 플레이어 정보를 비우는 함수
// 이미 판넬을 생성하고 난 다음 유저가 나갈때 쓰는 함수
void PokerPlayerInfoLeftPanel::setEmptyPlayerInfo()
{
	mPlayerName->setVisible(false);
	mGoldAmount->setVisible(false);
	mBettingAmount->setVisible(false);

	mRoomManager->setVisible(false);
	mMainPanel->getSkel("skel_allin2")->setVisible(false);

	mMainPanel->getSkel("skel_panel_selectuser")->setVisible(false);
	mMainPanel->getSkel("skel_sidebetting")->setVisible(false);
	mMainPanel->getSkel("skel_allin1")->setVisible(false);

	mMainPanel->getSkel("skel_boss")->setVisible(false);

	if (GameDataManager::getSingletonPtr()->getGameKind() != GAMEKIND_HOLDEM)
		mMainPanel->getSkel("skel_highlowicon")->setVisible(false);

	mBettingImage->setVisible(false);

	m_AllInImage->setVisible(false);
	m_AllBetImage->setVisible(false);
	m_SideBetImage->setVisible(false);

	turnOffUserInfoBack();
	TurnOffGameOut();
	TurnOffWinnerText();
	turnOffWaitMark();
	TurnOffJokboInfo();
	TurnOffHighLowChoice();

	if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind() == GameKind::GAMEKIND_BADUKI)
	{
		SetBadukiNumber(DAY_TYPE_MORNING, -1, false);
		SetBadukiNumber(DAY_TYPE_AFTERNOON, -1, false);
		SetBadukiNumber(DAY_TYPE_NIGHT, -1, false);
	}
}

void PokerPlayerInfoLeftPanel::setGameStartPlayerInfo()
{
	ClearBettingAmount();
	mMainPanel->getSkel("skel_allin2")->setVisible(false);
	mMainPanel->getSkel("skel_sidebetting")->setVisible(false);
	mMainPanel->getSkel("skel_allin1")->setVisible(false);

	if (GameDataManager::getSingletonPtr()->getGameKind() != GAMEKIND_HOLDEM)
		mMainPanel->getSkel("skel_highlowicon")->setVisible(false);

	m_AllInImage->setVisible(false);
	m_AllBetImage->setVisible(false);
	m_SideBetImage->setVisible(false);


	TurnOffJokboInfo();
	TurnOffGameOut();
	TurnOffWinnerText();
	turnOffWaitMark();
	TurnOffHighLowChoice();

	if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind() == GameKind::GAMEKIND_BADUKI)
	{
		SetBadukiNumber(DAY_TYPE_MORNING, -1, false);
		SetBadukiNumber(DAY_TYPE_AFTERNOON, -1, false);
		SetBadukiNumber(DAY_TYPE_NIGHT, -1, false);
	}
}

void PokerPlayerInfoLeftPanel::turnOnUserInfoBack()
{
	if (mMainPanel)
	{
		if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind() == GameKind::GAMEKIND_HOLDEM)
		{
			m_pUserPanelBtn->setSkelAnimation("backcardb_leftback_normal", false);
		}
		else
		{
			m_pUserPanelBtn->setSkelAnimation("leftback_normal", false);
		}
	}
}

void PokerPlayerInfoLeftPanel::turnOffUserInfoBack()
{
	if (mMainPanel)
	{
		if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind() == GameKind::GAMEKIND_HOLDEM)
		{
			m_pUserPanelBtn->setSkelAnimation("backcardb_leftback_stay", false);
		}
		else
		{
			m_pUserPanelBtn->setSkelAnimation("leftback_stay", false);
		}
	}
		
}

void PokerPlayerInfoLeftPanel::turnOnTimeGauge(bool _pause)
{
	
	if (_pause == true)
	{
		_makeSelectBox();
	}
	else
	{
		mIsTurn = true;
		mElapsedTime = 0.0f;
		_makeTimeGaugeFull();
	}
	mMainPanel->getSkel("skel_panel_selectuser")->setVisible(true);
	//GameDataManager::getSingletonPtr()->PlayGameSound(GameEfxKind::EFX_GAME_TIMER, true, true);
}

void PokerPlayerInfoLeftPanel::turnOffTimeGauge()
{
	mIsTurn = false; 
	mMainPanel->getSkel("skel_panel_selectuser")->setVisible(false);
	//GameDataManager::getSingletonPtr()->PlayGameSound(GameEfxKind::EFX_GAME_TIMER, false);
}

void PokerPlayerInfoLeftPanel::setWinner(bool isWinner)
{
	mMainPanel->getSkel("skel_winnerimg")->setZOrder(1);
	mMainPanel->getSkel("skel_winnerimg")->setVisible(isWinner);
}

void PokerPlayerInfoLeftPanel::setSeed(bool isSeed)
{
	mMainPanel->getSkel("skel_bossmark")->setVisible(isSeed);
}

void PokerPlayerInfoLeftPanel::ShowMade(int gameKind, int highJokbo, int lowJokbo)
{
	assert(mBettingImage);
	if (mBettingImage){
		/*mBettingImage->playAnimation("mark_made");
		mBettingImage->runAction(CCSequence::create(
			CCJumpBy::create(1.f, ccp(0, 0), 100.f, 1),
			CCDelayTime::create(1.6f),
			CCFadeOut::create(0.4f), NULL)
		);*/
	}
}

void PokerPlayerInfoLeftPanel::refreshCardSet()
{
#ifdef SHOW_ALL_CARD_DEBUG
	mCardContainer.at(mCardContainer.size() - 1)->setPositionX(getDummy(DMY_CARD_SMALL + StringConverter::toString(mCardContainer.size())).origin.x);
	mCardContainer.at(mCardContainer.size() - 1)->setPositionY(getDummy(DMY_CARD_SMALL + StringConverter::toString(mCardContainer.size())).origin.y);
	mCardContainer.at(mCardContainer.size() - 1)->fit(getDummy(DMY_CARD_SMALL + StringConverter::toString(mCardContainer.size())).size);
	mCardContainer.at(mCardContainer.size() - 1)->setContentSize(getDummy(DMY_CARD_SMALL + StringConverter::toString(mCardContainer.size())).size);
	addChild(mCardContainer.at(mCardContainer.size() - 1));
	mCardContainer.at(mCardContainer.size() - 1)->release();
#else

	if (mCardContainer.size() < 3) {
		mBackCardContainer.push_back(new PokerCardWidget(mBackCardContainer.size(), 100, PokerCardWidget::PokerCardWidetSmall));
		mBackCardContainer.at(mBackCardContainer.size() - 1)->setPositionX(mMainPanel->getDummy(DMY_CARD_SMALL + StringConverter::toString(mCardContainer.size())).origin.x);
		mBackCardContainer.at(mBackCardContainer.size() - 1)->setPositionY(mMainPanel->getDummy(DMY_CARD_SMALL + StringConverter::toString(mCardContainer.size())).origin.y);
		mBackCardContainer.at(mBackCardContainer.size() - 1)->fit(mMainPanel->getDummy(DMY_CARD_SMALL + StringConverter::toString(mCardContainer.size())).size);
		mBackCardContainer.at(mBackCardContainer.size() - 1)->setContentSize(mMainPanel->getDummy(DMY_CARD_SMALL + StringConverter::toString(mCardContainer.size())).size);

		mMainPanel->addChild(mBackCardContainer.at(mBackCardContainer.size() - 1));
		mBackCardContainer.at(mBackCardContainer.size() - 1)->release();
	}
	else if (mCardContainer.size() == 7) {
		mBackCardContainer.push_back(new PokerCardWidget(mBackCardContainer.size(), 100, PokerCardWidget::PokerCardWidetSmall));
		mBackCardContainer.at(mBackCardContainer.size() - 1)->setPositionX(mMainPanel->getDummy(DMY_CARD_SMALL + StringConverter::toString(mCardContainer.size())).origin.x);
		mBackCardContainer.at(mBackCardContainer.size() - 1)->setPositionY(mMainPanel->getDummy(DMY_CARD_SMALL + StringConverter::toString(mCardContainer.size())).origin.y);
		mBackCardContainer.at(mBackCardContainer.size() - 1)->fit(mMainPanel->getDummy(DMY_CARD_SMALL + StringConverter::toString(mCardContainer.size())).size);
		mBackCardContainer.at(mBackCardContainer.size() - 1)->setContentSize(mMainPanel->getDummy(DMY_CARD_SMALL + StringConverter::toString(mCardContainer.size())).size);

		mMainPanel->addChild(mBackCardContainer.at(mBackCardContainer.size() - 1));
		mBackCardContainer.at(mBackCardContainer.size() - 1)->release();
	}
	else {
		mCardContainer.at(mCardContainer.size() - 1)->setPositionX(mMainPanel->getDummy(DMY_CARD_SMALL + StringConverter::toString(mCardContainer.size())).origin.x);
		mCardContainer.at(mCardContainer.size() - 1)->setPositionY(mMainPanel->getDummy(DMY_CARD_SMALL + StringConverter::toString(mCardContainer.size())).origin.y);
		mCardContainer.at(mCardContainer.size() - 1)->fit(mMainPanel->getDummy(DMY_CARD_SMALL + StringConverter::toString(mCardContainer.size())).size);
		mCardContainer.at(mCardContainer.size() - 1)->setContentSize(mMainPanel->getDummy(DMY_CARD_SMALL + StringConverter::toString(mCardContainer.size())).size);
		mMainPanel->addChild(mCardContainer.at(mCardContainer.size() - 1));
		mCardContainer.at(mCardContainer.size() - 1)->release();
	}
#endif
}

void PokerPlayerInfoLeftPanel::refreshAllCardSet()
{
	for (unsigned int i = 0; i < mCardContainer.size(); i++) {
		mMainPanel->removeChild(mCardContainer.at(i), true);
	}

	for (unsigned int i = 0; i < mBackCardContainer.size(); i++) {
		mMainPanel->removeChild(mBackCardContainer.at(i), true);
	}

	mBackCardContainer.clear();
	mCardContainer.clear();

	for (unsigned int i = 0; i < mCardNumbers.size(); i++)
	{
		mCardContainer.push_back(new PokerCardWidget(mCardContainer.size(), mCardNumbers.at(i), PokerCardWidget::PokerCardWidetSmall));

		mCardContainer.at(mCardContainer.size() - 1)->setPositionX(mMainPanel->getDummy(DMY_CARD_SMALL + StringConverter::toString(mCardContainer.size())).origin.x);
		mCardContainer.at(mCardContainer.size() - 1)->setPositionY(mMainPanel->getDummy(DMY_CARD_SMALL + StringConverter::toString(mCardContainer.size())).origin.y);
		mCardContainer.at(mCardContainer.size() - 1)->fit(mMainPanel->getDummy(DMY_CARD_SMALL + StringConverter::toString(mCardContainer.size())).size);
		mCardContainer.at(mCardContainer.size() - 1)->setContentSize(mMainPanel->getDummy(DMY_CARD_SMALL + StringConverter::toString(mCardContainer.size())).size);
		mMainPanel->addChild(mCardContainer.at(mCardContainer.size() - 1));
		mCardContainer.at(mCardContainer.size() - 1)->release();
	}
}

void PokerPlayerInfoLeftPanel::refreshInitCardSet()
{
	mInitCardContainer.push_back(new PokerCardWidget(mInitCardContainer.size(), 100, PokerCardWidget::PokerCardWidetSmall));
	mInitCardContainer.at(mInitCardContainer.size() - 1)->setPositionX(mMainPanel->getDummy(DMY_CARD_SMALL + StringConverter::toString(mInitCardContainer.size())).origin.x);
	mInitCardContainer.at(mInitCardContainer.size() - 1)->setPositionY(mMainPanel->getDummy(DMY_CARD_SMALL + StringConverter::toString(mInitCardContainer.size())).origin.y);
	mInitCardContainer.at(mInitCardContainer.size() - 1)->fit(mMainPanel->getDummy(DMY_CARD_SMALL + StringConverter::toString(mInitCardContainer.size())).size);
	mInitCardContainer.at(mInitCardContainer.size() - 1)->setContentSize(mMainPanel->getDummy(DMY_CARD_SMALL + StringConverter::toString(mInitCardContainer.size())).size);

	mMainPanel->addChild(mInitCardContainer.at(mInitCardContainer.size() - 1));
	mInitCardContainer.at(mInitCardContainer.size() - 1)->release();
}

void PokerPlayerInfoLeftPanel::clearAllCards()
{
	for (unsigned int i = 0; i < mCardContainer.size(); i++) {
		mMainPanel->removeChild(mCardContainer.at(i), true);
	}

	for (unsigned int i = 0; i < mBackCardContainer.size(); i++) {
		mMainPanel->removeChild(mBackCardContainer.at(i), true);
	}

	for (unsigned int i = 0; i < mInitCardContainer.size(); i++) {
		mMainPanel->removeChild(mInitCardContainer.at(i), true);
	}

	mCardContainer.clear();
	mBackCardContainer.clear();
	mInitCardContainer.clear();
}

void PokerPlayerInfoLeftPanel::update(float dt)
{
	if (mIsTurn) {
		mElapsedTime += dt;
		if (mElapsedTime > GAME_CARD_CHOICE_TIME)
		{
			turnOffTimeGauge();
		}
	}
	
}

void PokerPlayerInfoLeftPanel::addCard(int cardId)
{
	mCardNumbers.push_back(cardId);
	mCardContainer.push_back(new PokerCardWidget(mCardContainer.size(), cardId, PokerCardWidget::PokerCardWidetSmall));
	refreshCardSet();
}

void PokerPlayerInfoLeftPanel::addInitCard(int cardId)
{
	refreshInitCardSet();
}

void PokerPlayerInfoLeftPanel::_initPanel()
{
	mParentPanel = dynamic_cast<Panel*>(LayerManager::getSingletonPtr()->getLayer("Background"));
	if (mParentPanel)
	{
		mMainPanel = new Panel();
		CCSize contentsSize;
		if (GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_BADUKI)
		{
			mMainPanel->construct(getMxmlPath() + "dmy_leftuser_badugipanel.mxml");
			addChild(mMainPanel);
			mMainPanel->release();
			contentsSize = mMainPanel->getDummy("dmy_leftuser_badugipanel").size;
			
		}
		else if (GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_HOLDEM)
		{
			mMainPanel->construct(getMxmlPath() + "dmy_leftuser_texasholdempanel.mxml");
			addChild(mMainPanel);
			mMainPanel->release();
			contentsSize = mMainPanel->getDummy("dmy_leftuser_texasholdempanel").size;
		}
		else
		{
			mMainPanel->construct(getMxmlPath() + "dmy_leftuser_panel.mxml");
			addChild(mMainPanel);
			mMainPanel->release();
			contentsSize = mMainPanel->getDummy("dmy_leftuser_panel").size;
		}

		mMainPanel->setPositionY(contentsSize.height / 2.f - DESIGN_HEIGHT);
		mMainPanel->setPositionX(-contentsSize.width / 2.f);
		mMainPanel->setContentSize(contentsSize);
		this->setContentSize(contentsSize);
		mMainPanel->getLabel("txt_getgold")->setVisible(false);
	}
}

void PokerPlayerInfoLeftPanel::_initText()
{
	//<mx:Text id = "txt_bettingcount.r.c.18" styleName = "textStyle" x = "146" y = "37" width = "174" text = "9999조9999억9999만골드" / >
	//<mx:Text id = "txt_username.c.c.18" styleName = "textStyle2" x = "41" y = "134" width = "94" text = "플레이어네임" / >
	//<mx:Text id = "txt_goldcounter.r.c.17" styleName = "textStyle3" x = "14" y = "154" width = "114" text = "3000조9999억 " / >

	mBettingAmount = mMainPanel->getLabel("txt_battingsum1");
	mBettingAmount->setOpacity(90);

	mPlayerName = mMainPanel->getLabel("txt_bname");
	mPlayerName->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mPlayerName->setOpacity(135);
	mGoldAmount = mMainPanel->getLabel("txt_bgold");
	mGoldAmount->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mGoldAmount->setOpacity(204);

	mBettingAmount->setVisible(false);
	mPlayerName->setVisible(false);
	mGoldAmount->setVisible(false);

	mMainPanel->getLabel("txt_noob_or_ribal")->setVisible(false);
}
void PokerPlayerInfoLeftPanel::_initImage()
{
	/*
	<mx:Image id = "sam_left_userpanel_board.bigworld_poker_8888.card_panel_leftuser" source = "sam_left_userpanel_board.bigworld_poker_8888.card_panel_leftuser.png" x = "8" y = "33" width = "320" height = "144" / >
	<mx:Image id = "sam_lastbet.poker_mark.mark_die_small" source = "sam_lastbet.poker_mark.mark_die_small.png" x = "329" y = "31" width = "41" height = "41" / >
	<mx:Image id = "sam_waitingmark.poker_mark.mark_waiting" source = "sam_waitingmark.poker_mark.mark_waiting.png" x = "191" y = "97" width = "80" height = "30" / >
	<mx:Image id = "sam_character.poker_character.minsang_user_01" source = "sam_character.poker_character.minsang_user_01.png" x = "58" y = "44" width = "60" height = "78" / >

	<mx:Image id = "sam_roomanager.poker_mark.mark_room_manager" source = "sam_roomanager.poker_mark.mark_room_manager.png" x = "0" y = "25" width = "42" height = "42" / >
	<mx:Image id = "sam_usergrade.poker_mark.mark_grade1" source = "sam_usergrade.poker_mark.mark_grade1.png" x = "15" y = "122" width = "25" height = "29" / >
	<mx:Image id = "sam_allin2.poker_mark.mark_allin_2.mark_allin_2end" source = "sam_allin2.poker_mark.mark_allin_2.mark_allin_2end.png" x = "267" y = "48" width = "64" height = "64" / >
	<mx:Image id = "sam_timebarbg.bigworld_poker_8888.choice_timebarbg_user" source = "sam_timebarbg.bigworld_poker_8888.choice_timebarbg_user.png" x = "137" y = "38" width = "184" height = "16" / >

	<mx:Image id = "sam_timebar.bigworld_poker_8888.choice_timebar_user" source = "sam_timebar.bigworld_poker_8888.choice_timebar_user.png" x = "139" y = "40" width = "180" height = "12" / >
	<mx:Image id = "sam_panel_selectuser.bigworld_poker_8888.panel_select_user" source = "sam_panel_selectuser.bigworld_poker_8888.panel_select_user.png" x = "8" y = "33" width = "320" height = "144" / >
	<mx:Image id = "sam_sidebetting.poker_mark.mark_sidebetting" source = "sam_sidebetting.poker_mark.mark_sidebetting.png" x = "134" y = "132" width = "88" height = "38" / >
	<mx:Image id = "sam_allin1.poker_mark.mark_allin_1" source = "sam_allin1.poker_mark.mark_allin_1.png" x = "155" y = "77" width = "157" height = "67" / >

	<mx:Image id = "sam_balloon.bigworld_poker_8888.speech_balloon1.speech_balloon1end" source = "sam_balloon.bigworld_poker_8888.speech_balloon1.speech_balloon1end.png" x = "93" y = "3" width = "118" height = "69" / >
	<mx:Image id = "sam_bossmark.poker_mark.mark_boss" source = "sam_bossmark.poker_mark.mark_boss.png" x = "329" y = "130" width = "41" height = "41" / >
	<mx:Image id = "sam_betresult.poker_mark.mark_die_big.mark_die_bigend" source = "sam_betresult.poker_mark.mark_die_big.mark_die_bigend.png" x = "322" y = "15" width = "64" height = "64" / >
	<mx:Image id = "sam_choicewaiting.poker_mark.mark_exclamation" source = "sam_choicewaiting.poker_mark.mark_exclamation.png" x = "342" y = "23" width = "15" height = "47" / >

	<mx:Image id = "sam_choiceresult.poker_mark.arrow_swing_big.arrow_swing_bigend" source = "sam_choiceresult.poker_mark.arrow_swing_big.arrow_swing_bigend.png" x = "333" y = "21" width = "34" height = "54" / >
	<mx:Image id = "sam_winnerimg.bigworld_poker_8888.winner_img" source = "sam_winnerimg.bigworld_poker_8888.winner_img.png" x = "159" y = "69" width = "145" height = "37" / >
	*/
	mMainPanel->getSkel("skel_baticon")->setVisible(false);
	mMainPanel->getSkel("skel_waitingmark")->setVisible(false);
	mMainPanel->getSkel("skel_join_mark")->setVisible(false);

	mMainPanel->getSkel("skel_roomanager1")->setVisible(false);
	mMainPanel->getSkel("skel_allin2")->setVisible(false);

	mMainPanel->getSkel("skel_panel_selectuser")->setVisible(false);
	mMainPanel->getSkel("skel_sidebetting")->setVisible(false);
	mMainPanel->getSkel("skel_allin1")->setVisible(false);

	mMainPanel->getSkel("skel_boss")->setVisible(false);
	//mMainPanel->getSkel("skel_betresult")->setVisible(false);

	if (GameDataManager::getSingletonPtr()->getGameKind() != GAMEKIND_HOLDEM)
		mMainPanel->getSkel("skel_highlowicon")->setVisible(false);

	m_pUserPanelBtn = mMainPanel->getButton("sbtn_left_userpanel_board");
	m_pUserPanelBtn->setType(Button::NoPressImg);
	m_pUserPanelBtn->setVisible(true);

	//mMainPanel->getSkel("skel_winnerimg")->setVisible(false);
	//mMainPanel->getLabel("txt_getgold")->setVisible(false);

	mMainPanel->getSkel("skel_cradresultback3")->setVisible(false);

	mMainPanel->getSkel("skel_mark_noob_or_rival")->setVisible(false);

	if (GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_BADUKI)
	{
		mMainPanel->getSkel("skel_number_b1")->setVisible(false);
		mMainPanel->getSkel("skel_number_b2")->setVisible(false);
		mMainPanel->getSkel("skel_number_b3")->setVisible(false);

		mMainPanel->getSkel("skel_number_b1")->stopLooping();
		mMainPanel->getSkel("skel_number_b2")->stopLooping();
		mMainPanel->getSkel("skel_number_b3")->stopLooping();
	}

	mMainPanel->getLabel("txt_gameoutfont")->setVisible(false);
}


void PokerPlayerInfoLeftPanel::SetBadukiNumber(int _idx, int _num, bool _visible)
{
	if (_idx < 0 || _idx > 2)
		return;

	string _skelName = "skel_number_b" + StringConverter::toString(_idx + 1);
	SkelObject* _obj = mMainPanel->getSkel(_skelName);

	if (!_obj)
		return;

	_obj->setVisible(_visible);

	if (_visible == false)
		return;

	if (_num <= -1)
	{
		_obj->playAnimation("number_b_end");
	}
	else if (_num < 5)
	{
		string _skinName = "number_" + StringConverter::toString(_num);
		_obj->setSkin(_skinName);
		_obj->playAnimation("number_b_start");
		_obj->appendAnimation("number_b_stay");
	}
	else
	{
		return;
	}
}

void PokerPlayerInfoLeftPanel::_initGageBar()
{
	turnOffTimeGauge();
}

void PokerPlayerInfoLeftPanel::_initBettingMark()
{

	mBettingImage = new SkelObject();
	mBettingImage->setPositionX(mMainPanel->getImage("skel_baticon")->getPositionX());
	mBettingImage->setPositionY(mMainPanel->getImage("skel_baticon")->getPositionY());
	mBettingImage->setSkelAnim("ui/panalicons_8888.json");
	mMainPanel->addChild(mBettingImage);
	mBettingImage->release();
	mBettingImage->setVisible(false);
	
	//mBettingImage = 
	//mCardImage->setPositionX(rect.getMidX());
	//mCardImage->setPositionY(rect.getMidY());
	//mCardImage->setSuperAnim("ui/poker_card.sam");
	//if (mPokerCardWidgetType == PokerCardWidetBig) {
	//	mCardImage->playAnimation(findIter->second);
	//}
	//else if (mPokerCardWidgetType == PokerCardWidetSmall) {
	//	mCardImage->playAnimation(nxReplace(findIter->second, "my", "user"));
	//}
}

void PokerPlayerInfoLeftPanel::_initHighLowImage()
{
	if (mMainPanel && GameDataManager::getSingletonPtr()->getGameKind() != GAMEKIND_HOLDEM)
	{
		mHighLowImage = new SkelObject();
		mHighLowImage->setPositionX(mMainPanel->getImage("skel_highlowicon")->getPositionX());
		mHighLowImage->setPositionY(mMainPanel->getImage("skel_highlowicon")->getPositionY());
		mHighLowImage->setSkelAnim("ui/panalicons_8888.json");
		mMainPanel->addChild(mHighLowImage);
		mHighLowImage->release();
		mHighLowImage->setVisible(false);
	}
}

void PokerPlayerInfoLeftPanel::_makeTimeGaugeFull()
{
	mMainPanel->getSkel("skel_panel_selectuser")->setVisible(true);
	if (mMainPanel && GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_HOLDEM)
	{
		mMainPanel->getSkel("skel_panel_selectuser")->playAnimation("texasholdem_left_start");
		mMainPanel->getSkel("skel_panel_selectuser")->appendAnimation("texasholdem_left_end", false, false, 0.3f);
	}
	else
	{
		mMainPanel->getSkel("skel_panel_selectuser")->playAnimation("left_start");
		mMainPanel->getSkel("skel_panel_selectuser")->appendAnimation("left_end", false, false, 0.3f);
	}
}

void PokerPlayerInfoLeftPanel::SetBetting(BettingKind kind, bool isMe, int64 betMoney)
{
	PokerPlayerInfoCommonPanel::SetBetting(kind, isMe, betMoney);
}

void PokerPlayerInfoLeftPanel::SetHighLowChoice(HighLowBettingKind betKind)
{
	//PokerPlayerInfoCommonPanel::SetHighLowChoice(betKind);
	//mHighLowImage->setScale(0.7f);
}

void PokerPlayerInfoLeftPanel::InitWinnerText()
{
	mMainPanel->getSkel("skel_winnerimg")->setVisible(false);
	mMainPanel->getLabel("txt_getgold")->setVisible(false);
	Layer * cardLayer = nullptr;
	if (LayerManager::getSingletonPtr()->hasLayer("CardLayer"))
		cardLayer = LayerManager::getSingletonPtr()->getLayer("CardLayer");

	if (cardLayer == nullptr)
		return;

	CCPoint target = getPosition() + mMainPanel->getPosition();
	m_pWinnerText = mMainPanel->getSkel("skel_winnerimg");
	if (mWinPanel == nullptr)
	{
		if (GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_HOLDEM)
			mWinPanel = new GameWinPanel(GameWinPanel::PANEL_ENEMY_HOLDEM_RESULT);
		else
			mWinPanel = new GameWinPanel(GameWinPanel::PANEL_ENEMY_RESULT);
		mWinPanel->setPosition(target + mMainPanel->getImage("skel_winnerimg")->getPosition());
		cardLayer->addChild(mWinPanel, 13);
		mWinPanel->release();
		mWinPanel->getWinSkel()->setListener(this);
		mWinPanel->setPosition(target + mMainPanel->getImage("skel_winnerimg")->getPosition());
	}
	if (mWinPanel)
		mWinPanel->setVisible(false);

	if (m_pWinnerText)
		m_pWinnerText->setVisible(false);
}

void PokerPlayerInfoLeftPanel::SetWinnerText(int64 getMoney)
{
	if (mWinPanel == nullptr)
		return;

	//기덕 수정

	mWinPanel->setVisible(true);
	if (GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_HOLDEM) {
		mWinPanel->getWinSkel()->playAnimation("winner_start_tex");
		mWinPanel->getWinSkel()->appendAnimation("winner_loop_tex", true);
	}
	else {
		mWinPanel->getWinSkel()->playAnimation("winner_start_b");
		mWinPanel->getWinSkel()->appendAnimation("winner_loop_b", true);
	}
	
	
	string plusStr = "+" + GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(getMoney), 2);	
	mWinPanel->setResult(plusStr);
}

void PokerPlayerInfoLeftPanel::InitRoomManager(bool isBig)
{
	mRoomManager = mMainPanel->getSkel("skel_roomanager1");	
}

void PokerPlayerInfoLeftPanel::ShowAllBet(bool _show)
{
	if (_show)
	{
		if (m_AllBetImage->isVisible())
			return;
		m_AllBetImage->setVisible(true);
		m_AllBetImage->playAnimation("mark_allin_2_start_b");
		m_AllBetImage->appendAnimation("mark_allin_2_stay_b");
	}
	else
	{
		m_AllBetImage->playAnimation("mark_allin_2_end_b");

	}
}

void PokerPlayerInfoLeftPanel::ShowMaxBet(bool _show)
{
	if (_show)
	{
		if (m_AllBetImage->isVisible())
			return;
		m_AllBetImage->setVisible(true);
		m_AllBetImage->playAnimation("mark_maxbetting_start_b");
		m_AllBetImage->appendAnimation("mark_maxbetting_stay_b");
	}
	else
	{
		m_AllBetImage->playAnimation("mark_maxbetting_end_b");

	}
}

void PokerPlayerInfoLeftPanel::ShowSideBet(bool _show)
{
	if (_show)
	{
		if (m_SideBetImage->isVisible())
			return;
		m_SideBetImage->setVisible(true);
		m_SideBetImage->playAnimation("mark_sidebetting_start_b");
		m_SideBetImage->appendAnimation("mark_sidebetting_stay_b");
	}
	else
	{
		m_SideBetImage->playAnimation("mark_sidebetting_end_b");

	}
}

void PokerPlayerInfoLeftPanel::ShowAllIn(bool _show)
{
	if (_show)
	{
		if (m_AllInImage->isVisible())
			return;
		m_AllInImage->setVisible(true);
		m_AllInImage->playAnimation("mark_allin_1_start_b");
		m_AllInImage->appendAnimation("mark_allin_1_stay_b");
	}
	else
	{
		m_AllInImage->playAnimation("mark_allin_1_end_b");

	}
}

void PokerPlayerInfoLeftPanel::_makeSelectBox()
{
	mMainPanel->getSkel("skel_panel_selectuser")->setVisible(true);
	if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind() == GameKind::GAMEKIND_HOLDEM)
	{
		mMainPanel->getSkel("skel_panel_selectuser")->playAnimation("texasholdem_left_start");
		mMainPanel->getSkel("skel_panel_selectuser")->appendAnimation("texasholdem_left_loop", true);
	}
	else
	{
		mMainPanel->getSkel("skel_panel_selectuser")->playAnimation("left_start");
		mMainPanel->getSkel("skel_panel_selectuser")->appendAnimation("left_loop", true);
	}
}

void PokerPlayerInfoLeftPanel::EndWinnerText()
{
	if (mWinPanel->getWinSkel()->isLoopingAnimation()) {

		if (GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_HOLDEM) {
			mWinPanel->getWinSkel()->playAnimation("winner_end_tex");
		}
		else
			mWinPanel->getWinSkel()->playAnimation("winner_end_b");
	}
}
