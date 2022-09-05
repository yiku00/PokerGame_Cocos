#include "pch.h"
#include "PokerPlayerInfoRightPanel.h"
#include "HeroUtil.h"
//#include "Player.h"
#include "RefDefine.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"

#define DMY_CARD_SMALL "dmy_card_small"

PokerPlayerInfoRightPanel::PokerPlayerInfoRightPanel()
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
	_initTimeGauge();
	_initBettingMark();
	_initHighLowImage();
	//TurnOffGameOut();
	//_addCard();
}

PokerPlayerInfoRightPanel::~PokerPlayerInfoRightPanel()
{
	removeFromParentAndCleanup(true);
}

void PokerPlayerInfoRightPanel::setEmptyPlayerInfo()
{
	if (mPlayerName)
		mPlayerName->setVisible(false);
	if (mGoldAmount)
		mGoldAmount->setVisible(false);
	if (mBettingAmount)
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

// 게임 시작시 정보패널 초기화
void PokerPlayerInfoRightPanel::setGameStartPlayerInfo()
{
	ClearBettingAmount();
	mMainPanel->getSkel("skel_allin2")->setVisible(false);
	mMainPanel->getSkel("skel_sidebetting")->setVisible(false);
	mMainPanel->getSkel("skel_allin1")->setVisible(false);
	if (GameDataManager::getSingletonPtr()->getGameKind() != GAMEKIND_HOLDEM)
		mMainPanel->getSkel("skel_highlowicon")->setVisible(false);

	if (m_AllInImage)
		m_AllInImage->setVisible(false);
	if (m_AllBetImage)
		m_AllBetImage->setVisible(false);
	if (m_SideBetImage)
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

void PokerPlayerInfoRightPanel::turnOnUserInfoBack()
{
	if (mMainPanel)
	{
		if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind() == GameKind::GAMEKIND_HOLDEM)
		{
			m_pUserPanelBtn->setSkelAnimation("backcardb_rightback_normal");
		}
		else
		{
			m_pUserPanelBtn->getButtonSkelObject()->playAnimation("rightback_normal");
		}
	}
		
}

void PokerPlayerInfoRightPanel::turnOffUserInfoBack()
{
	if (mMainPanel)
	{
		if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind() == GameKind::GAMEKIND_HOLDEM)
		{
			m_pUserPanelBtn->setSkelAnimation("backcardb_rightback_stay");
		}
		else
		{
			m_pUserPanelBtn->getButtonSkelObject()->playAnimation("rightback_stay");
		}
	}
		
}

void PokerPlayerInfoRightPanel::turnOnTimeGauge(bool _pause)
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
	//GameDataManager::getSingletonPtr()->PlayGameSound(GameEfxKind::EFX_GAME_TIMER);
}

void PokerPlayerInfoRightPanel::turnOffTimeGauge()
{
	mIsTurn = false;
	mMainPanel->getSkel("skel_panel_selectuser")->setVisible(false);
	//GameDataManager::getSingletonPtr()->PlayGameSound(GameEfxKind::EFX_GAME_TIMER, false);
}

void PokerPlayerInfoRightPanel::setWinner(bool isWinner)
{
	mMainPanel->getSkel("skel_winnerimg")->setZOrder(1);
	mMainPanel->getSkel("skel_winnerimg")->setVisible(isWinner);
}

void PokerPlayerInfoRightPanel::setSeed(bool isSeed)
{
	mMainPanel->getSkel("skel_boss")->setVisible(isSeed);
}

void PokerPlayerInfoRightPanel::ShowMade(int gameKind, int highJokbo, int lowJokbo)
{
	assert(mBettingImage);
	if (mBettingImage){
		mBettingImage->playAnimation("mark_made");
		mBettingImage->runAction(CCSequence::create(
			CCJumpBy::create(1.f, ccp(0, 0), 100.f, 1),
			CCDelayTime::create(1.6f),
			CCFadeOut::create(0.4f), NULL)
			);
	}
}

void PokerPlayerInfoRightPanel::refreshCardSet()
{
	/*for (int i = 0; i < mCardContainer.size(); i++)
	{
		
		mCardContainer.at(i)->setPositionX(getDummy(DMY_CARD_SMALL + StringConverter::toString(i + 1)).origin.x);
		mCardContainer.at(i)->setPositionY(getDummy(DMY_CARD_SMALL + StringConverter::toString(i + 1)).origin.y);
		mCardContainer.at(i)->fit(getDummy(DMY_CARD_SMALL + StringConverter::toString(i + 1)).size);
		mCardContainer.at(i)->setContentSize(getDummy(DMY_CARD_SMALL + StringConverter::toString(i + 1)).size);
		addChild(mCardContainer.at(i));
		mCardContainer.at(i)->release();
	}*/
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

void PokerPlayerInfoRightPanel::refreshAllCardSet()
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

void PokerPlayerInfoRightPanel::refreshInitCardSet()
{
	mInitCardContainer.push_back(new PokerCardWidget(mInitCardContainer.size(), 100, PokerCardWidget::PokerCardWidetSmall));
	mInitCardContainer.at(mInitCardContainer.size() - 1)->setPositionX(mMainPanel->getDummy(DMY_CARD_SMALL + StringConverter::toString(mInitCardContainer.size())).origin.x);
	mInitCardContainer.at(mInitCardContainer.size() - 1)->setPositionY(mMainPanel->getDummy(DMY_CARD_SMALL + StringConverter::toString(mInitCardContainer.size())).origin.y);
	mInitCardContainer.at(mInitCardContainer.size() - 1)->fit(mMainPanel->getDummy(DMY_CARD_SMALL + StringConverter::toString(mInitCardContainer.size())).size);
	mInitCardContainer.at(mInitCardContainer.size() - 1)->setContentSize(mMainPanel->getDummy(DMY_CARD_SMALL + StringConverter::toString(mInitCardContainer.size())).size);

	mMainPanel->addChild(mInitCardContainer.at(mInitCardContainer.size() - 1));
	mInitCardContainer.at(mInitCardContainer.size() - 1)->release();
}

void PokerPlayerInfoRightPanel::clearAllCards()
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
void PokerPlayerInfoRightPanel::update(float dt)
{
	if (mIsTurn) {
		mElapsedTime += dt;
		mMainPanel->getImage("sam_timebar")->setScaleX(_getPercentage(GAME_CARD_CHOICE_TIME - mElapsedTime, GAME_CARD_CHOICE_TIME));

		if (mElapsedTime > GAME_CARD_CHOICE_TIME)
		{
			turnOffTimeGauge();
		}
	}
}

void PokerPlayerInfoRightPanel::addCard(int cardId)
{
	mCardNumbers.push_back(cardId);
	mCardContainer.push_back(new PokerCardWidget(mCardContainer.size(), cardId, PokerCardWidget::PokerCardWidetSmall));
	refreshCardSet();
}

void PokerPlayerInfoRightPanel::addInitCard(int cardId)
{
	refreshInitCardSet();
}

void PokerPlayerInfoRightPanel::_initPanel()
{
	mParentPanel = dynamic_cast<Panel*>(LayerManager::getSingletonPtr()->getLayer("Background"));
	if (mParentPanel)
	{
		mMainPanel = new Panel();
		CCSize contentsSize;
		if (GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_BADUKI)
		{
			mMainPanel->construct(getMxmlPath() + "dmy_rightuser_badugipanel.mxml");
			addChild(mMainPanel);
			mMainPanel->release();
			contentsSize = mMainPanel->getDummy("dmy_rightuser_badugipanel").size;
		}
		else if (GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_HOLDEM)
		{
			mMainPanel->construct(getMxmlPath() + "dmy_rightuser_texasholdempanel.mxml");
			addChild(mMainPanel);
			mMainPanel->release();
			contentsSize = mMainPanel->getDummy("dmy_rightuser_texasholdempanel").size;
		}
		else
		{
			mMainPanel->construct(getMxmlPath() + "dmy_rightuser_panel.mxml");
			addChild(mMainPanel);
			mMainPanel->release();
			contentsSize = mMainPanel->getDummy("dmy_rightuser_panel").size;
		}
		mMainPanel->setPositionY(contentsSize.height / 2.f - DESIGN_HEIGHT);
		mMainPanel->setPositionX(-contentsSize.width / 2.f);
		mMainPanel->setContentSize(contentsSize);
		this->setContentSize(contentsSize);
		mMainPanel->getLabel("txt_getgold")->setVisible(false);
	}
}

void PokerPlayerInfoRightPanel::_initText()
{
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

void PokerPlayerInfoRightPanel::_initImage()
{
	mMainPanel->getSkel("skel_allin2")->setVisible(false);
	mMainPanel->getSkel("skel_waitingmark")->setVisible(false);
	mMainPanel->getSkel("skel_join_mark")->setVisible(false);

	mMainPanel->getSkel("skel_sidebetting")->setVisible(false);
	mMainPanel->getSkel("skel_allin1")->setVisible(false);

	mMainPanel->getSkel("skel_panel_selectuser")->setVisible(false);
	mMainPanel->getSkel("skel_roomanager1")->setVisible(false);
	mMainPanel->getSkel("skel_baticon")->setVisible(false);

	//mMainPanel->getSkel("skel_betresult")->setVisible(false);
	mMainPanel->getSkel("skel_boss")->setVisible(false);
	if (GameDataManager::getSingletonPtr()->getGameKind() != GAMEKIND_HOLDEM)
		mMainPanel->getSkel("skel_highlowicon")->setVisible(false);
	
	//mMainPanel->getSkel("skel_choiceresult")->setVisible(false);

	m_pUserPanelBtn = mMainPanel->getButton("sbtn_right_userpanel_board");
	m_pUserPanelBtn->setType(Button::NoPressImg);
	m_pUserPanelBtn->setVisible(true);

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

void PokerPlayerInfoRightPanel::SetBadukiNumber(int _idx, int _num, bool _visible)
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


void PokerPlayerInfoRightPanel::_initTimeGauge()
{
	turnOffTimeGauge();
}

void PokerPlayerInfoRightPanel::_initBettingMark()
{
	//mBettingImage = new SuperObject();
	//mBettingImage->setPositionX(getDummy("sam_lastbet").getMidX());
	//mBettingImage->setPositionY(getDummy("sam_lastbet").getMidY());
	//mBettingImage->setSuperAnim("ui/poker_mark.sam");
	//addChild(mBettingImage);
	mBettingImage = new SkelObject();
	mBettingImage->setPositionX(mMainPanel->getImage("skel_baticon")->getPositionX());
	mBettingImage->setPositionY(mMainPanel->getImage("skel_baticon")->getPositionY());
	mBettingImage->setSkelAnim("ui/panalicons_8888.json");
	mMainPanel->addChild(mBettingImage);
	mBettingImage->release();
	mBettingImage->setVisible(false);
	
}

void PokerPlayerInfoRightPanel::_initHighLowImage()
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


void PokerPlayerInfoRightPanel::_makeTimeGaugeFull()
{
	mMainPanel->getSkel("skel_panel_selectuser")->setVisible(true);
	if (mMainPanel && GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_HOLDEM)
	{
		mMainPanel->getSkel("skel_panel_selectuser")->playAnimation("texasholdem_right_start");
		mMainPanel->getSkel("skel_panel_selectuser")->appendAnimation("texasholdem_right_end", false, false, 0.3f);
	}
	else
	{
		mMainPanel->getSkel("skel_panel_selectuser")->playAnimation("right_start");
		mMainPanel->getSkel("skel_panel_selectuser")->appendAnimation("right_end", false, false, 0.3f);
	}
}


void PokerPlayerInfoRightPanel::SetBetting(BettingKind kind, bool isMe, int64 betMoney)
{
	PokerPlayerInfoCommonPanel::SetBetting(kind, isMe, betMoney);
}

void PokerPlayerInfoRightPanel::SetHighLowChoice(HighLowBettingKind betKind, bool isMe)
{
	PokerPlayerInfoCommonPanel::SetHighLowChoice(betKind, isMe);
	//mHighLowImage->setScale(0.7f);
}

void PokerPlayerInfoRightPanel::InitWinnerText()
{
	//기덕
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

void PokerPlayerInfoRightPanel::SetWinnerText(int64 getMoney)
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

void PokerPlayerInfoRightPanel::InitRoomManager(bool isBig)
{
	mRoomManager = mMainPanel->getSkel("skel_roomanager1");	
}

void PokerPlayerInfoRightPanel::ShowAllBet(bool _show)
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

void PokerPlayerInfoRightPanel::ShowMaxBet(bool _show)
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

void PokerPlayerInfoRightPanel::ShowSideBet(bool _show)
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

void PokerPlayerInfoRightPanel::ShowAllIn(bool _show)
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

void PokerPlayerInfoRightPanel::_makeSelectBox()
{
	mMainPanel->getSkel("skel_panel_selectuser")->setVisible(true);
	if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind() == GameKind::GAMEKIND_HOLDEM)
	{
		mMainPanel->getSkel("skel_panel_selectuser")->playAnimation("texasholdem_right_start");
		mMainPanel->getSkel("skel_panel_selectuser")->appendAnimation("texasholdem_right_loop", true);
	}
	else
	{
		mMainPanel->getSkel("skel_panel_selectuser")->playAnimation("right_start");
		mMainPanel->getSkel("skel_panel_selectuser")->appendAnimation("right_loop", true);
	}
	
}

void PokerPlayerInfoRightPanel::EndWinnerText()
{
	if (mWinPanel->getWinSkel()->isLoopingAnimation()) {
		if (GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_HOLDEM) {
			mWinPanel->getWinSkel()->playAnimation("winner_end_tex");
		}
		else
			mWinPanel->getWinSkel()->playAnimation("winner_end_b");
	}
}
