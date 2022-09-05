#include "pch.h"
#include "PokerPlayerInfoMyPanel.h"
#include "HeroUtil.h"
#include "RefDefine.h"
//#include "Player.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"
#include "BadugiSelectCardPanel.h"

#define DMY_CARD_BIG	"dmy_card_big"

PokerPlayerInfoMyPanel::PokerPlayerInfoMyPanel()
{
	setMyInfo();
	mElapsedTime = 0.f;
	mIsTurn = false;
	mBettingImage = nullptr;
	mMadeImage = nullptr;
	mHighLowImage = nullptr;
	m_AllInImage = nullptr;
	m_AllBetImage = nullptr;
	m_SideBetImage = nullptr;
	m_TimeSound = false;
	mWinPanel = nullptr;

	_initPanel();

	_initText();
	_initImage();
	_initTimegauge();
	_initBettingMark();
	_initHighLowImage();
	//TurnOffGameOut();
}

PokerPlayerInfoMyPanel::~PokerPlayerInfoMyPanel()
{
	removeFromParentAndCleanup(true);
}

// 유저 나갈때 정보패널 초기화
void PokerPlayerInfoMyPanel::setEmptyPlayerInfo()
{
	mPlayerName->setVisible(false);
	mGoldAmount->setVisible(false);
	if (mBettingAmount)
		mBettingAmount->setVisible(false);

	if (mRoomManager)
		mRoomManager->setVisible(false);
	mMainPanel->getSkel("skel_allin2")->setVisible(false);

	mMainPanel->getSkel("skel_panel_select")->setVisible(false);
	mMainPanel->getSkel("skel_sidebetting")->setVisible(false);
	mMainPanel->getSkel("skel_allin1")->setVisible(false);

	mMainPanel->getSkel("skel_boss")->setVisible(false);
	mMainPanel->getSkel("skel_highlowicon")->setVisible(false);
	mMainPanel->getLabel("txt_gameoutfont")->setVisible(false);

	mBettingImage->setVisible(false);
	
	m_AllInImage->setVisible(false);
	m_AllBetImage->setVisible(false);
	m_SideBetImage->setVisible(false);

	turnOffWaitMark();
	TurnOffJokboInfo();

	turnOnUserInfoBack();
	TurnOffWinnerText();
	TurnOffHighLowChoice();

	if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind() == GameKind::GAMEKIND_BADUKI)
	{
		SetBadukiNumber(DAY_TYPE_MORNING, -1, false);
		SetBadukiNumber(DAY_TYPE_AFTERNOON, -1, false);
		SetBadukiNumber(DAY_TYPE_NIGHT, -1, false);
	}
}

// 게임 시작시 정보패널 초기화
void PokerPlayerInfoMyPanel::setGameStartPlayerInfo()
{
	ClearBettingAmount();
	mMainPanel->getSkel("skel_allin2")->setVisible(false);
	mMainPanel->getSkel("skel_sidebetting")->setVisible(false);
	mMainPanel->getSkel("skel_allin1")->setVisible(false);
	mMainPanel->getSkel("skel_highlowicon")->setVisible(false);
	m_AllInImage->setVisible(false);
	m_AllBetImage->setVisible(false);
	m_SideBetImage->setVisible(false);
	TurnOffHighLowChoice();
	TurnOffJokboInfo();
	TurnOffWinnerText();
	turnOffWaitMark();

	if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind() == GameKind::GAMEKIND_BADUKI)
	{
		SetBadukiNumber(DAY_TYPE_MORNING, -1, false);
		SetBadukiNumber(DAY_TYPE_AFTERNOON, -1, false);
		SetBadukiNumber(DAY_TYPE_NIGHT, -1, false);
	}

}

void PokerPlayerInfoMyPanel::turnOnUserInfoBack()
{
}

void PokerPlayerInfoMyPanel::turnOffUserInfoBack()
{
}

bool PokerPlayerInfoMyPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	//if (pTouch->getLocation().x < DESIGN_HEIGHT / 2) {
	//	
	//}
	//else {
	//	
	//}
	return false;
}

void PokerPlayerInfoMyPanel::turnOnTimeGauge(bool _pause)
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
	mMainPanel->getSkel("skel_panel_select")->setVisible(true);

	//
	runAction(CCSequence::create(
		CCDelayTime::create(5.f),
		CCCallFunc::create(this, callfunc_selector(PokerPlayerInfoMyPanel::PlayTimeSound)),
		NULL));
}

void PokerPlayerInfoMyPanel::turnOffTimeGauge()
{
	//mBettingPanel->setVisible(false);
	if (m_TimeSound == true)
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(GameEfxKind::EFX_GAME_TIMER, false);
	}

	stopAllActions();
	mIsTurn = false;
	mMainPanel->getSkel("skel_panel_select")->setVisible(false);
	
}

void PokerPlayerInfoMyPanel::PlayTimeSound()
{
	if (mIsTurn == true)
	{
		m_TimeSound = true;
		GameDataManager::getSingletonPtr()->PlayGameSound(GameEfxKind::EFX_GAME_TIMER, true, true);
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_TURN);
	}
}

void PokerPlayerInfoMyPanel::setWinner(bool isWinner)
{
	mMainPanel->getSkel("skel_winnerimg")->setZOrder(1);
	mMainPanel->getSkel("skel_winnerimg")->setVisible(isWinner);	
}

void PokerPlayerInfoMyPanel::setSeed(bool isSeed)
{
	mMainPanel->getSkel("skel_bossmark")->setVisible(isSeed);
}


/*
void PokerPlayerInfoMyPanel::setCall()
{
	//playAnimation("");
	assert(mBettingImage);
	if (mBettingImage){
		mBettingImage->playAnimation("mark_call_big");
		mBettingImage->appendAnimation("mark_call_bigend");
		mBettingImage->appendAnimation("mark_call_small");
	}
}

void PokerPlayerInfoMyPanel::setHalf()
{
	assert(mBettingImage);
	if (mBettingImage){
		mBettingImage->playAnimation("mark_half_big");
		mBettingImage->appendAnimation("mark_half_bigend");
		mBettingImage->appendAnimation("mark_half_small");
	}
}

void PokerPlayerInfoMyPanel::setDie()
{
	assert(mBettingImage);
	if (mBettingImage){
		mBettingImage->playAnimation("mark_die_big");
		mBettingImage->appendAnimation("mark_die_bigend");
		mBettingImage->appendAnimation("mark_die_small");
	}
}
*/

void PokerPlayerInfoMyPanel::SetBetting(BettingKind kind, bool isMe, int64 betMoney)
{
	PokerPlayerInfoCommonPanel::SetBetting(kind, isMe, betMoney);
}

void PokerPlayerInfoMyPanel::ShowMade(int gameKind, int highJokbo, int lowJokbo)
{
	assert(mMadeImage);
	if (mMadeImage)
	{
		GameKind gameKind = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind();

		m_MadeKind = LowJokboKind::LOW_NO;

		if (gameKind == GameKind::GAMEKIND_HIGH_LOW)
		{
			// 스윙
			if (highJokbo != HighJokboKind::HIGH_NO && highJokbo <= HighJokboKind::HIGH_FOUR_CARD)
			{
				mMadeImage->playAnimation("made_start_swing");
				mMadeImage->appendAnimation("made_loop_swing");
				mMadeImage->appendAnimation("made_end_swing");
				SetMadeJokbo(highJokbo);
			}
			else
			{
				if (highJokbo != HighJokboKind::HIGH_NO && lowJokbo != LowJokboKind::LOW_NO)
				{
					mMadeImage->playAnimation("made_start_high");
					mMadeImage->appendAnimation("made_loop_highlow");
					mMadeImage->appendAnimation("made_end_low");
					SetMadeJokbo(highJokbo);
					m_MadeKind = lowJokbo;
				}
				else if (highJokbo != HighJokboKind::HIGH_NO)
				{
					mMadeImage->playAnimation("made_start_high");
					mMadeImage->appendAnimation("made_loop_high");
					mMadeImage->appendAnimation("made_end_high");
					SetMadeJokbo(highJokbo);
				}
				else
				{
					mMadeImage->playAnimation("made_start_low");
					mMadeImage->appendAnimation("made_loop_low");
					mMadeImage->appendAnimation("made_end_low");
					SetMadeJokbo(lowJokbo);
				}
			}

		}
		else if (gameKind == GameKind::GAMEKIND_7POKER || gameKind == GameKind::GAMEKIND_HOLDEM)
		{
			mMadeImage->playAnimation("made_start_swing");
			mMadeImage->appendAnimation("made_loop_swing");
			mMadeImage->appendAnimation("made_end_swing");

			SetMadeJokbo(highJokbo);
		}
		else if (gameKind == GameKind::GAMEKIND_BADUKI)
		{
			SetMadeJokbo(lowJokbo);

			mMadeImage->playAnimation("made_start_swing");
			mMadeImage->appendAnimation("made_loop_swing");
			mMadeImage->appendAnimation("made_end_swing");
		}

		mMadeImage->setVisible(true);
	}
}

void PokerPlayerInfoMyPanel::refreshCardSet()
{
	mCardContainer.at(mCardContainer.size() - 1)->setPositionX(getDummy(DMY_CARD_BIG + StringConverter::toString(mCardContainer.size())).origin.x);
	mCardContainer.at(mCardContainer.size() - 1)->setPositionY(getDummy(DMY_CARD_BIG + StringConverter::toString(mCardContainer.size())).origin.y);
	mCardContainer.at(mCardContainer.size() - 1)->fit(getDummy(DMY_CARD_BIG + StringConverter::toString(mCardContainer.size())).size);
	mCardContainer.at(mCardContainer.size() - 1)->setContentSize(getDummy(DMY_CARD_BIG + StringConverter::toString(mCardContainer.size())).size);
	addChild(mCardContainer.at(mCardContainer.size() - 1));
	mCardContainer.at(mCardContainer.size() - 1)->release();
}

void PokerPlayerInfoMyPanel::refreshAllCardSet()
{
	for (unsigned int i = 0; i < mCardContainer.size(); i++) {
		removeChild(mCardContainer.at(i), true);
	}

	for (unsigned int i = 0; i < mBackCardContainer.size(); i++) {
		removeChild(mBackCardContainer.at(i), true);
	}

	mBackCardContainer.clear();
	mCardContainer.clear();

	for (unsigned int i = 0; i < mCardNumbers.size(); i++)
	{
		mCardContainer.push_back(new PokerCardWidget(mCardContainer.size(), mCardNumbers.at(i), PokerCardWidget::PokerCardWidetBig));

		mCardContainer.at(mCardContainer.size() - 1)->setPositionX(getDummy(DMY_CARD_BIG + StringConverter::toString(mCardContainer.size())).origin.x);
		mCardContainer.at(mCardContainer.size() - 1)->setPositionY(getDummy(DMY_CARD_BIG + StringConverter::toString(mCardContainer.size())).origin.y);
		mCardContainer.at(mCardContainer.size() - 1)->fit(getDummy(DMY_CARD_BIG + StringConverter::toString(mCardContainer.size())).size);
		mCardContainer.at(mCardContainer.size() - 1)->setContentSize(getDummy(DMY_CARD_BIG + StringConverter::toString(mCardContainer.size())).size);
		addChild(mCardContainer.at(mCardContainer.size() - 1));
		mCardContainer.at(mCardContainer.size() - 1)->release();
	}
}

void PokerPlayerInfoMyPanel::refreshInitCardSet()
{
	mInitCardContainer.push_back(new PokerCardWidget(mInitCardContainer.size(), 100, PokerCardWidget::PokerCardWidetBig));
	mInitCardContainer.at(mInitCardContainer.size() - 1)->setPositionX(getDummy(DMY_CARD_BIG + StringConverter::toString(mInitCardContainer.size())).origin.x);
	mInitCardContainer.at(mInitCardContainer.size() - 1)->setPositionY(getDummy(DMY_CARD_BIG + StringConverter::toString(mInitCardContainer.size())).origin.y);
	mInitCardContainer.at(mInitCardContainer.size() - 1)->fit(getDummy(DMY_CARD_BIG + StringConverter::toString(mInitCardContainer.size())).size);
	mInitCardContainer.at(mInitCardContainer.size() - 1)->setContentSize(getDummy(DMY_CARD_BIG + StringConverter::toString(mInitCardContainer.size())).size);
	addChild(mInitCardContainer.at(mInitCardContainer.size() - 1));
	mInitCardContainer.at(mInitCardContainer.size() - 1)->release();
}

void PokerPlayerInfoMyPanel::clearAllCards()
{
	for (unsigned int i = 0; i < mCardContainer.size(); i++) {
		removeChild(mCardContainer.at(i), true);
	}

	for (unsigned int i = 0; i < mBackCardContainer.size(); i++) {
		removeChild(mBackCardContainer.at(i), true);
	}

	for (unsigned int i = 0; i < mInitCardContainer.size(); i++) {
		removeChild(mInitCardContainer.at(i), true);
	}

	mCardContainer.clear();
	mBackCardContainer.clear();
	mInitCardContainer.clear();
}

void PokerPlayerInfoMyPanel::update(float dt)
{
	if (mIsTurn) {
		mElapsedTime += dt;
		if (mElapsedTime > GAME_CARD_CHOICE_TIME)
		{
			turnOffTimeGauge();

			GameDataManager::getSingleton().GetGameRoomInfoPtr()->InitCanBettingPanel();			
			//다이 호출.
			//GameDataManager::getSingleton().GetGameRoomInfoPtr()->BettingChoice(BettingKind::DIE);
		}
	}
}

void PokerPlayerInfoMyPanel::addCard(int cardId)
{
	mCardNumbers.push_back(cardId);
	mCardContainer.push_back(new PokerCardWidget(mCardContainer.size(), cardId, PokerCardWidget::PokerCardWidetBig));
	refreshCardSet();
}

void PokerPlayerInfoMyPanel::addInitCard(int cardId)
{
	refreshInitCardSet();
}


void PokerPlayerInfoMyPanel::setBettingPanel()
{
	mBettingPanel = dynamic_cast<Panel*>(LayerManager::getSingleton().getLayer("BettingPanel"));
	if (mBettingPanel) {
		mBettingPanel->setVisible(false);
	}
}

void PokerPlayerInfoMyPanel::_initPanel()
{
	mParentPanel = dynamic_cast<Panel*>(LayerManager::getSingletonPtr()->getLayer("Background"));
	if (mParentPanel)
	{
		mMainPanel = new Panel();
		CCSize contentsSize;
		if (GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_BADUKI)
		{
			mMainPanel->construct(getMxmlPath() + "dmy_my_badugipanel.mxml");
			addChild(mMainPanel);
			mMainPanel->release();
			contentsSize = mMainPanel->getDummy("dmy_my_badugipanel").size;
		}
		else if(GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_HOLDEM)
		{
			mMainPanel->construct(getMxmlPath() + "dmy_my_texasholdempanel.mxml");
			addChild(mMainPanel);
			mMainPanel->release();
			contentsSize = mMainPanel->getDummy("dmy_my_texasholdempanel").size; 
		}
		else
		{
			mMainPanel->construct(getMxmlPath() + "dmy_my_panel.mxml");
			addChild(mMainPanel);
			mMainPanel->release();
			contentsSize = mMainPanel->getDummy("dmy_my_panel").size;
		}

		mMainPanel->setPositionY(contentsSize.height / 2.f - DESIGN_HEIGHT);
		mMainPanel->setPositionX(-contentsSize.width / 2.f);
		mMainPanel->setContentSize(contentsSize);
		this->setContentSize(contentsSize);
		mMainPanel->getLabel("txt_getgold")->setVisible(false);
	}
}

void PokerPlayerInfoMyPanel::_initText()
{
	//<mx:Text id = "txt_cardresult.c.c.19" styleName = "textStyle" x = "136" y = "221" width = "164" text = "로열 스트레이트 플러시" / >
	//<mx:Text id = "txt_username.c.c.18" styleName = "textStyle2" x = "57" y = "173" width = "94" text = "플레이어네임" / >
	//<mx:Text id = "txt_goldcounter.c.c.18" styleName = "textStyle2" x = "37" y = "192" width = "134" text = "3000조9999억 " / >

	mCardHandOrder = mMainPanel->getLabel("txt_cardresult");
	mPlayerName = mMainPanel->getLabel("txt_bname");
	mPlayerName->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mPlayerName->setOpacity(135);
	mGoldAmount = mMainPanel->getLabel("txt_bgold");
	mGoldAmount->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mGoldAmount->setOpacity(204);
	mGoldAmount->setGrayColor(StringConverter::parseColor3B("f73030"));
	mMainPanel->getLabel("txt_battingsum1")->setVisible(false);
	mBettingAmount = mMainPanel->getLabel("txt_battingsum1");
	mBettingAmount->setOpacity(90);

	mCardHandOrder->setVisible(false);
	mPlayerName->setVisible(false);
	mGoldAmount->setVisible(false);
	mBettingAmount->setVisible(false);
}

void PokerPlayerInfoMyPanel::_initImage()
{
	mMainPanel->getSkel("skel_panel_select")->setVisible(false);
	mMainPanel->getSkel("skel_boss")->setVisible(false);
	mMainPanel->getSkel("skel_made")->setVisible(false);
	mMainPanel->getSkel("skel_roomanager")->setVisible(false);
	mMainPanel->getSkel("skel_sidebetting")->setVisible(false);
	mMainPanel->getSkel("skel_baticon")->setVisible(false);
	mMainPanel->getSkel("skel_highlowicon")->setVisible(false);
	mMainPanel->getSkel("skel_winnerimg")->setVisible(false);
	mMainPanel->getSkel("skel_allin2")->setVisible(false);
	mMainPanel->getSkel("skel_allin1")->setVisible(false);
	mMainPanel->getSkel("skel_waitingmark")->setVisible(false);
	mMainPanel->getSkel("skel_join_mark")->setVisible(false);
	mMainPanel->getSkel("skel_cradresultback2")->setVisible(false);
	mMainPanel->getLabel("txt_cardresult2")->setVisible(false);
	mMainPanel->getSkel("skel_cradresultback3")->setVisible(false);
	
	m_pUserPanelBtn = mMainPanel->getButton("sbtn_card_panel");
	m_pUserPanelBtn->setType(Button::NoPressImg);
	m_pUserPanelBtn->setName("MyPlayerInfo_Btn");
	m_pUserPanelBtn->setPaused(true);

	if (GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_BADUKI)
	{
		mMainPanel->getSkel("skel_number1")->setVisible(false);
		mMainPanel->getSkel("skel_number2")->setVisible(false);
		mMainPanel->getSkel("skel_number3")->setVisible(false);

		mMainPanel->getSkel("skel_number1")->stopLooping();
		mMainPanel->getSkel("skel_number2")->stopLooping();
		mMainPanel->getSkel("skel_number3")->stopLooping();

		mMainPanel->getButton("sbtn_touch_1")->setVisible(false);
		mMainPanel->getButton("sbtn_touch_1")->setPaused(true);
		mMainPanel->getButton("sbtn_touch_2")->setVisible(false);
		mMainPanel->getButton("sbtn_touch_2")->setPaused(true);
		mMainPanel->getButton("sbtn_touch_3")->setVisible(false);
		mMainPanel->getButton("sbtn_touch_3")->setPaused(true);
		mMainPanel->getButton("sbtn_touch_4")->setVisible(false);
		mMainPanel->getButton("sbtn_touch_4")->setPaused(true);
	}

	mMainPanel->getLabel("txt_gameoutfont")->setVisible(false);
}

void PokerPlayerInfoMyPanel::SetBadukiNumber(int _idx, int _num, bool _visible)
{
	if (_idx < 0 || _idx > 2)
		return;

	string _skelName = "skel_number" + StringConverter::toString(_idx + 1);
	SkelObject* _obj = mMainPanel->getSkel(_skelName);

	if (!_obj)
		return;

	_obj->setVisible(_visible);

	if (_visible == false)
		return;

	if (_num <= -1)
	{
		_obj->playAnimation("number_end");
	}
	else if(_num < 5)
	{
		string _skinName = "number_" + StringConverter::toString(_num);
		_obj->setSkin(_skinName);
		_obj->playAnimation("number_start");
		_obj->appendAnimation("number_stay");
	}
	else
	{
		return;
	}

}

void PokerPlayerInfoMyPanel::_initTimegauge()
{
	turnOffTimeGauge();
}

void PokerPlayerInfoMyPanel::_initBettingMark()
{
	if (mMainPanel)
	{
		mBettingImage = new SkelObject();
		mBettingImage->setPositionX(mMainPanel->getImage("skel_baticon")->getPositionX());
		mBettingImage->setPositionY(mMainPanel->getImage("skel_baticon")->getPositionY());
		mBettingImage->setSkelAnim("ui/panalicons_8888.json");
		mMainPanel->addChild(mBettingImage);
		mBettingImage->release();
		mBettingImage->setVisible(false);
	}
}

void PokerPlayerInfoMyPanel::_initHighLowImage()
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

void PokerPlayerInfoMyPanel::InitMadeImage()
{
	if (!mMainPanel)
		return;

	mMainPanel->getSkel("skel_cradresultback")->setVisible(false);
	mMainPanel->getLabel("txt_cardresult")->setVisible(false);

	Panel* _panel = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetChracterPanel();
	if (_panel == nullptr)
		return;

	CCPoint target = getPosition() + mMainPanel->getPosition();

	mMadeImage = new SkelObject();
	mMadeImage->setPosition(target + mMainPanel->getImage("skel_made")->getPosition());
	mMadeImage->setSkelAnim("ui/made_mark_8888.json");

	_panel->addChild(mMadeImage, 4);
	mMadeImage->release();
	mMadeImage->setVisible(false);
	mMadeImage->setListener(this);
	mMadeImage->addEventListener(this);
}



void PokerPlayerInfoMyPanel::_makeTimeGaugeFull()
{
	mMainPanel->getSkel("skel_panel_select")->setVisible(true);
	mMainPanel->getSkel("skel_panel_select")->playAnimation("front_start");
	mMainPanel->getSkel("skel_panel_select")->appendAnimation("front_end", false, false, 0.3f);

}

void PokerPlayerInfoMyPanel::addCards()
{
	return;
}

void PokerPlayerInfoMyPanel::SetHighLowChoice(HighLowBettingKind betKind, bool isMe)
{
	PokerPlayerInfoCommonPanel::SetHighLowChoice(betKind, isMe);
	//mHighLowImage->setScale(1.0f);
}

void PokerPlayerInfoMyPanel::InitWinnerText()
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
		mWinPanel = new GameWinPanel(GameWinPanel::PANEL_MY_RESULT);
		mWinPanel->setPosition(target + mMainPanel->getImage("skel_winnerimg")->getPosition());		
		cardLayer->addChild(mWinPanel, 13);
		mWinPanel->release();
		mWinPanel->getWinSkel()->setListener(this);		
	}
	if (mWinPanel)
		mWinPanel->setVisible(false);	
}

void PokerPlayerInfoMyPanel::SetWinnerText(int64 getMoney)
{
	if (mWinPanel == nullptr)
		return;

	//기덕 수정
	mWinPanel->setVisible(true);
	mWinPanel->getWinSkel()->playAnimation("winner_start");
	mWinPanel->getWinSkel()->appendAnimation("winner_loop", true);	
	string plusStr = "+" + GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(getMoney), 2);
	mWinPanel->setResult(plusStr);	
	addLimitedError();
}

void PokerPlayerInfoMyPanel::InitRoomManager(bool isBig)
{
	mRoomManager = mMainPanel->getSkel("skel_roomanager");
}

void PokerPlayerInfoMyPanel::ShowAllBet(bool _show)
{
	if (_show)
	{
		if (m_AllBetImage->isVisible())
			return;
		m_AllBetImage->setVisible(true);
		m_AllBetImage->playAnimation("mark_allin_2_start");
		m_AllBetImage->appendAnimation("mark_allin_2_stay");
	}
	else
	{
		m_AllBetImage->playAnimation("mark_allin_2_end");

	}
}

void PokerPlayerInfoMyPanel::ShowMaxBet(bool _show)
{
	if (_show)
	{
		if (m_AllBetImage->isVisible())
			return;
		m_AllBetImage->setVisible(true);
		m_AllBetImage->playAnimation("mark_maxbetting_start");
		m_AllBetImage->appendAnimation("mark_maxbetting_stay");
	}
	else
	{
		m_AllBetImage->playAnimation("mark_maxbetting_end");

	}
}

void PokerPlayerInfoMyPanel::ShowSideBet(bool _show)
{
	if (_show)
	{
		if (m_SideBetImage->isVisible())
			return;
		m_SideBetImage->setVisible(true);
		m_SideBetImage->playAnimation("mark_sidebetting_start");
		m_SideBetImage->appendAnimation("mark_sidebetting_stay");
	}
	else
	{
		m_SideBetImage->playAnimation("mark_sidebetting_end");

	}
}

void PokerPlayerInfoMyPanel::ShowAllIn(bool _show)
{
	if (_show)
	{
		if (m_AllInImage->isVisible())
			return;
		m_AllInImage->setVisible(true);
		m_AllInImage->playAnimation("mark_allin_1_start");
		m_AllInImage->appendAnimation("mark_allin_1_stay");
	}
	else
	{
		m_AllInImage->playAnimation("mark_allin_1_end");

	}
}

void PokerPlayerInfoMyPanel::_makeSelectBox()
{
	mMainPanel->getSkel("skel_panel_select")->setVisible(true);
	mMainPanel->getSkel("skel_panel_select")->playAnimation("front_start");
	mMainPanel->getSkel("skel_panel_select")->appendAnimation("front_loop", true);
}

void PokerPlayerInfoMyPanel::EndWinnerText()
{
	if (mWinPanel->getWinSkel()->isLoopingAnimation())
		mWinPanel->getWinSkel()->playAnimation("winner_end");
	
	//골드표시가 없었다는건 플레이어가 우승하여 딜러수수료를 표시했다는 뜻
	if (mPlayerName->getOpacity() == 255) {
		mGoldAmount->setString(GameDataManager::getSingleton().GetKoreanLiteral(StringConverter::toString(mNowGameMoney),2).c_str());
		mGoldAmount->setOpacity(204);
		mPlayerName->setString(GameDataManager::getSingleton().GetPlayerDataPtr()->m_NickName.c_str());
		mPlayerName->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		mPlayerName->setOpacity(135);
	}
		


}

bool PokerPlayerInfoMyPanel::TouchBadugiCardCheck(CCPoint _touchPosint)
{
	if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_PlayStatus != PLAY_CHANGE_CARD)
		return false;

	if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind() != GameKind::GAMEKIND_BADUKI)
		return false;

	GameRoomInfo* _pInfo = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr();
	if (_pInfo == nullptr)
		return false;

	if (_pInfo->m_bSendChanageRequest == true || _pInfo->m_bSendPassRequest == true)
		return false;

	RoomUserData* _User = _pInfo->GetUserDataPtr(_pInfo->m_MyPo);
	if (_User == nullptr)
		return false;

	if (_User->GetPlayerStatus() == PlayerStatus::PLAYER_DIE)
		return false;

	//if (LayerManager::getSingletonPtr()->hasLayer("BadugiSelectCardPanel"))
	//{
	//	BadugiSelectCardPanel* _pSelectCardPanel = dynamic_cast<BadugiSelectCardPanel*>(LayerManager::getSingletonPtr()->getLayer("BadugiSelectCardPanel"));
	//	if (_pSelectCardPanel->isVisible() == false)
	//		return false;
	//}

	Button* _card[4];
	_card[0] = mMainPanel->getButton("sbtn_touch_1");
	_card[1] = mMainPanel->getButton("sbtn_touch_2");
	_card[2] = mMainPanel->getButton("sbtn_touch_3");
	_card[3] = mMainPanel->getButton("sbtn_touch_4");

	for (int _i = 0; _i < 4; _i++)
	{
		if (_card[_i]->hasCollided(_card[_i]->convertToNodeSpace(_touchPosint)) == true)
		{
			return true;
		}
	}

	return false;
}

void PokerPlayerInfoMyPanel::TouchBadugiCard(CCPoint _touchPosint)
{
	if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_PlayStatus == PLAY_SHARE_CARD)
		return;

	if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind() != GameKind::GAMEKIND_BADUKI)
		return;

	GameRoomInfo* _pInfo = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr();
	if (_pInfo == nullptr)
		return;

	if (_pInfo->m_isReplayData == true)
		return;

	RoomUserData* _User = _pInfo->GetUserDataPtr(_pInfo->m_MyPo);
	if (_User == nullptr)
		return;

	Button* _card[4];
	_card[0] = mMainPanel->getButton("sbtn_touch_1");
	_card[1] = mMainPanel->getButton("sbtn_touch_2");
	_card[2] = mMainPanel->getButton("sbtn_touch_3");
	_card[3] = mMainPanel->getButton("sbtn_touch_4");

	if (LayerManager::getSingletonPtr()->hasLayer("BadugiSelectCardPanel"))
	{
		BadugiSelectCardPanel* _pSelectCardPanel = dynamic_cast<BadugiSelectCardPanel*>(LayerManager::getSingletonPtr()->getLayer("BadugiSelectCardPanel"));

		for (int _i = 0; _i < 4; _i++)
		{
			if (_card[_i]->hasCollided(_card[_i]->convertToNodeSpace(_touchPosint)) == true)
			{
				bool _touch = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[_i];
				GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[_i] = !_touch;
				_pSelectCardPanel->SetSeletBtn(_i, !_touch);
			}
		}
		_User->SetBadugiSelectedCardEffect();
		_pSelectCardPanel->ApplyChangeButtonState();
	}
}

