#include "pch.h"
#include "PokerPlayerInfoCommonPanel.h"
//#include "Player.h"
#include "HeroUtil.h"
#include "RoomUserData.h"
#include "GameDataManager.h"
#include "socket/TCPService.h"
#include "GameStringDepot.h"

#define ACTION_TAG 255

PokerPlayerInfoCommonPanel::PokerPlayerInfoCommonPanel()
{
	_initData();
}
PokerPlayerInfoCommonPanel::~PokerPlayerInfoCommonPanel()
{
	
}

void PokerPlayerInfoCommonPanel::_initData()
{
	mMyInfo = false;
	mNowGameMoney = 0;

	mParentPanel = nullptr;
	mMainPanel = nullptr;

	mPlayer = nullptr;
	mHighLowImage = nullptr;
	mBettingImage = nullptr;

	mGoldAmount = nullptr;
	mPlayerName = nullptr;
	mBettingAmount = nullptr;

	mCardJokboInfo = nullptr;
	mCardJokboLabel = nullptr;

	m_pWinnerText = nullptr;
	
	mRoomManager = nullptr;

	m_AllInImage = nullptr;
	m_AllBetImage = nullptr;
	m_SideBetImage = nullptr;

	m_WaitImage = nullptr;
	m_EnterImage = nullptr;
	m_pUserInfoPanel = nullptr;

	mCardContainer.clear();
	mBackCardContainer.clear();
	mInitCardContainer.clear();
	mCardNumbers.clear();

	m_AllBetKind = 0;
}

float PokerPlayerInfoCommonPanel::_getPercentage(float currentValue, float maxValue)
{
	return currentValue / maxValue;
}

void PokerPlayerInfoCommonPanel::SetBetting(BettingKind kind, bool isMe, int64 betMoney)
{
	string name;

	switch (kind)
	{
		case CALL:		name = "call"; break;
		case HALF:		name = "half"; break;
		case QUARTER:	name = "quarter"; break;
		case DDADANG:	name = "tadang"; break;
		case BBING:		name = "bing"; break;
		case CHECK:		name = "check"; break;
		case DIE:		name = "die"; break;
		case MAX_BETTING: name = "big"; break;
		case BETTING_NO : 
			if (mBettingImage)
				mBettingImage->setVisible(false);
			return;
	}

	if (mBettingImage)
	{
		mBettingImage->setVisible(true);
		mBettingImage->setPositionX(mMainPanel->getImage("skel_baticon")->getPositionX());
		mBettingImage->setPositionY(mMainPanel->getImage("skel_baticon")->getPositionY());
		//mBettingImage->setPositionX(mMainPanel->getDummy("skel_baticon").getMidX());
		//mBettingImage->setPositionY(mMainPanel->getDummy("skel_baticon").getMidY());
		if (isMe)
		{
			mBettingImage->playAnimation((name + "_start").c_str());
			mBettingImage->appendAnimation((name + "_loop").c_str());
			mBettingImage->appendAnimation((name + "_end").c_str());
			mBettingImage->appendAnimation((name + "_endloop").c_str());
		}
		else
		{
			mBettingImage->playAnimation((name + "_start").c_str());
			mBettingImage->appendAnimation((name + "_loop").c_str());
			mBettingImage->appendAnimation((name + "_end").c_str());
			mBettingImage->appendAnimation((name + "_endloop").c_str());
		}

		if (betMoney >= 0)
		{
			if (kind == BETTING_NO || kind == DIE)
				ClearBettingAmount();
			else
				SetBettingAmount(betMoney);
		}
		else
			ClearBettingAmount();
	}
}

void PokerPlayerInfoCommonPanel::turnOnWaitMark(UserLoadKind kind)
{
	if (kind == UserLoadKind::USER_LOAD_ENTER)
	{
		if (m_EnterImage)
		{
			m_EnterImage->setVisible(true);
			m_EnterImage->playAnimation("mark_join_start");
			m_EnterImage->appendAnimation("mark_join_stay");
		}
	}
	else
	{
		if (m_WaitImage)
		{
			if (m_EnterImage)
			{
				if (m_EnterImage->isVisible())
					m_EnterImage->playAnimation("mark_join_end", false);
			}
			m_WaitImage->setVisible(true);
			m_WaitImage->playAnimation("mark_waiting_start");
			m_WaitImage->appendAnimation("mark_waiting_stay");
		}
	}
}

void PokerPlayerInfoCommonPanel::turnOffWaitMark()
{
	if (m_EnterImage && m_EnterImage->isVisible())
		m_EnterImage->playAnimation("mark_join_end", false);

	if (m_WaitImage && m_WaitImage->isVisible())
		m_WaitImage->playAnimation("mark_waiting_end", false);
}



void PokerPlayerInfoCommonPanel::SetBettingAmount(int64 betMoney)
{
	if (mBettingAmount)
	{
		if (betMoney < 0)
			mBettingAmount->setString("");
		else
			mBettingAmount->setString((GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(betMoney), 2)).c_str());// +GameStringDepot::getSingleton().getString("TXT_GOLD_UNIT")).c_str());
	}
}

void PokerPlayerInfoCommonPanel::ClearBettingAmount()
{
	if (mBettingAmount)
		mBettingAmount->setString("");
}

void PokerPlayerInfoCommonPanel::SetAllBet(AllBetKind kind)
{
	switch (kind)
	{
	case ALL_BET :
		m_AllBetKind = kind;
		ShowAllBet(true);
		//mMainPanel->getSkel("skel_allin2")->setVisible(true);		
		break;
	case MAX_BET:
		m_AllBetKind = kind;
		ShowMaxBet(true);
		break;
	case SIDE_BET :
		ShowSideBet(true);
		//mMainPanel->getSkel("skel_sidebetting")->setVisible(true);
		break;
	case ALLBET_NO :
		if (m_AllBetKind == MAX_BET)
			ShowMaxBet(false);
		else 
			ShowAllBet(false);
		ShowSideBet(false);
		m_AllBetKind = kind;
		//mMainPanel->getSkel("skel_allin2")->setVisible(false);
		//mMainPanel->getSkel("skel_sidebetting")->setVisible(false);
		break;
	}
}

void PokerPlayerInfoCommonPanel::SetAllIn(bool isAllin)
{
	ShowAllIn(isAllin);
	//mMainPanel->getSkel("skel_allin1")->setVisible(isAllin);
}

void PokerPlayerInfoCommonPanel::SetHighLowChoice(HighLowBettingKind betKind, bool isMe)
{
	string name;

	switch (betKind)
	{
		case HIGHLOW_NO_BET:		name = "question"; break;
		case HIGH_BET:				name = "high"; break;
		case LOW_BET:				name = "low"; break;
		case SWING_BET:				name = "swing"; break;
		case SECRET_BET:			name = "exclamation"; break;
	}

	if (mHighLowImage)
	{
		mHighLowImage->setVisible(true);
		
		if (isMe)
		{
			if (mHighLowImage->getCurrentAnimation() != (name + "_loop"))
			{
				mHighLowImage->playAnimation((name + "_start").c_str());
				mHighLowImage->appendAnimation((name + "_loop").c_str());
			}
		}
		else
		{
			if (mHighLowImage->getCurrentAnimation() != (name + "_loop_b"))
			{
				mHighLowImage->playAnimation((name + "_start_b").c_str());
				mHighLowImage->appendAnimation((name + "_loop_b").c_str());
			}
		}
	}
}

void PokerPlayerInfoCommonPanel::TurnOnHighLowChoice()
{
	if (mHighLowImage != nullptr)
		mHighLowImage->setVisible(true);
}

void PokerPlayerInfoCommonPanel::TurnOffHighLowChoice()
{
	if (mHighLowImage != nullptr)
		mHighLowImage->setVisible(false);
}


void PokerPlayerInfoCommonPanel::SetMasterMark(bool isView, bool isMe)
{
	if (mRoomManager != nullptr)
		mRoomManager->setVisible(isView);
}

void PokerPlayerInfoCommonPanel::SetBossMark(bool isView, bool isMe)
{
	
	SkelObject * obj = mMainPanel->getSkel("skel_boss");
	if (obj == nullptr)
		return;

	if (isView)
	{
		if (!obj->isVisible())
		{
			if (isMe)
			{
				obj->playAnimation("boss_start", false);
				obj->appendAnimation("boss_loop", false);
			}
			else
			{
				obj->playAnimation("boss_start", false);
				obj->appendAnimation("boss_loop", false);
			}
		}
	}
	obj->setVisible(isView);
}

void PokerPlayerInfoCommonPanel::SetBasicInfo(PlayerData * data)
{
	SetGoldAmount(data->m_GameMoney);

	if (mPlayerName != nullptr)
	{
		mPlayerName->setVisible(true);
		//mPlayerName->setString(GameDataManager::getSingletonPtr()->GetU8SubStr(data->m_NickName, 6).c_str());
		mPlayerName->setString(data->m_NickName.c_str());

		//mPlayerName->setString(_name.c_str());
	}
	if (mBettingAmount != nullptr)
	{
		mBettingAmount->setVisible(true);
		mBettingAmount->setString("");
	}
}


void PokerPlayerInfoCommonPanel::SetDetailInfo(PlayerData * data)
{

}

void PokerPlayerInfoCommonPanel::TurnOnGameOut(int kind)
{
	if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameMode() != GameMode::MODE_NORMAL)
		return;

	if (!mMainPanel)
		return;

	if (kind == 0)
		mMainPanel->getLabel("txt_gameoutfont")->setString(GameStringDepot::getSingleton().getString("TXT_OUT_RSV").c_str());//U8("나가기 예약"));
	else
		mMainPanel->getLabel("txt_gameoutfont")->setString(GameStringDepot::getSingleton().getString("TXT_PUTOUT_RSV").c_str());//U8("강퇴 예약"));
	mMainPanel->getLabel("txt_gameoutfont")->setVisible(true);
}

void PokerPlayerInfoCommonPanel::TurnOffGameOut()
{
	if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr() == NULL)
		return;

	if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameMode() != GameMode::MODE_NORMAL)
		return;

	if (mMainPanel)
		mMainPanel->getLabel("txt_gameoutfont")->setVisible(false);
}

void PokerPlayerInfoCommonPanel::TurnOnPlayerRank(int _rank, bool _isComplete)
{
	if (!mMainPanel)
		return;

	if (_rank <= 0)
		return;

	string _rankStr = StringConverter::toString(_rank) + GameStringDepot::getSingleton().getString("TXT_RANK");
	if (_isComplete == false)
		_rankStr += "(" + GameStringDepot::getSingleton().getString("TXT_CALCULATING") + ")";
	mMainPanel->getLabel("txt_gameoutfont")->setString(_rankStr.c_str());
	mMainPanel->getLabel("txt_gameoutfont")->setVisible(true);
}

void PokerPlayerInfoCommonPanel::TurnOffPlayerRank()
{
	if (mMainPanel)
		mMainPanel->getLabel("txt_gameoutfont")->setVisible(false);
}

void PokerPlayerInfoCommonPanel::TurnOnPlayerDisconnect(int _leftgame)
{
	if (!mMainPanel)
		return;

	string _msg = GameStringDepot::getSingleton().getString("TXT_DISCONNECT_PLAYER");
	if (_leftgame > 0)
	{
		_msg += "[" + StringConverter::toString(_leftgame) + "]";
	}

	mMainPanel->getLabel("txt_gameoutfont")->setString(_msg.c_str());
	mMainPanel->getLabel("txt_gameoutfont")->setVisible(true);
}

void PokerPlayerInfoCommonPanel::TurnOffPlayerDisconnect()
{
	if (mMainPanel)
		mMainPanel->getLabel("txt_gameoutfont")->setVisible(false);
}


void PokerPlayerInfoCommonPanel::TurnOnJokboInfo(string jokbo)
{
	if (!mMainPanel)
		return;

	mCardJokboLabel->setVisible(true);
	mCardJokboInfo->setVisible(true);
	mCardJokboLabel->setString(jokbo.c_str());
	MoveCardJokboInfoPo(0);
}

void PokerPlayerInfoCommonPanel::TurnOffJokboInfo()
{
	if (!mMainPanel)
		return;
	if (mCardJokboLabel)
		mCardJokboLabel->setVisible(false);
	if (mCardJokboInfo)
		mCardJokboInfo->setVisible(false);

	MoveCardJokboInfoPo(0);
}

void PokerPlayerInfoCommonPanel::MoveCardJokboInfoPo(int kind)
{
	CCPoint target = getPosition() + mMainPanel->getPosition();
	// 초기 위치
	if (kind == 0)
	{
		mCardJokboInfo->setPosition(target + mMainPanel->getImage("skel_cradresultback")->getPosition());
		mCardJokboLabel->setPosition(target + mMainPanel->getImage("skel_cradresultback")->getPosition());
	}
	// 결과 위치
	else
	{
		mCardJokboInfo->setPosition(target + mMainPanel->getImage("skel_cradresultback2")->getPosition());
		mCardJokboLabel->setPosition(target + mMainPanel->getImage("skel_cradresultback2")->getPosition());
	}
}

void PokerPlayerInfoCommonPanel::InitJokboInfo()
{
	mMainPanel->getSkel("skel_cradresultback")->setVisible(false);
	mMainPanel->getLabel("txt_cardresult")->setVisible(false);

	Layer * cardLayer = nullptr;
	if (LayerManager::getSingletonPtr()->hasLayer("CardLayer"))
		cardLayer = LayerManager::getSingletonPtr()->getLayer("CardLayer");

	if (cardLayer == nullptr)
		return;


	CCPoint target = getPosition() + mMainPanel->getPosition();

	mCardJokboInfo = new SkelObject();
	mCardJokboInfo->setPosition(target + mMainPanel->getImage("skel_cradresultback")->getPosition());
	//mCardJokboInfo->setPositionY(mMainPanel->getImage("skel_cradresultback")->getPositionY());
	mCardJokboInfo->setSkelAnim("ui/paneltool_8888.json");
	mCardJokboInfo->playAnimation("cardresult_back", true);

	cardLayer->addChild(mCardJokboInfo, 13);
	//mMainPanel->addChild(mCardJokboInfo, 4);
	mCardJokboInfo->release();
	mCardJokboInfo->setVisible(false);

	mCardJokboLabel = new Nx::Label();
	mCardJokboLabel->initWithString("fsdfasfasf", mMainPanel->getLabel("txt_cardresult")->getSystemFontSize());  //getFontSize // - // setVisible(true)   ??
	//mCardJokboLabel->setPositionX(mMainPanel->getLabel("txt_cardresult")->getPositionX());
	//mCardJokboLabel->setPositionY(mMainPanel->getLabel("txt_cardresult")->getPositionY());
	CCSize test = mMainPanel->getDummy("skel_cradresultback").size;
	mCardJokboLabel->setPosition(target + mMainPanel->getImage("skel_cradresultback")->getPosition());
	mCardJokboLabel->setFont(mMainPanel->getLabel("txt_cardresult")->getTTFConfig().fontFilePath); //getFontName
	mCardJokboLabel->setColor(mMainPanel->getLabel("txt_cardresult")->getColor());
	mCardJokboLabel->setAnchorPoint(ccp(0.5f, 0.5f));
	mCardJokboLabel->setHorizontalAlignment(mMainPanel->getLabel("txt_cardresult")->getHorizontalAlignment());
	mCardJokboLabel->setVerticalAlignment(mMainPanel->getLabel("txt_cardresult")->getVerticalAlignment());
	//mMainPanel->addChild(mCardJokboLabel, 4);
	cardLayer->addChild(mCardJokboLabel, 13);
	mCardJokboLabel->release();
	mCardJokboLabel->setVisible(false);


	/*m_TableCardRect[_i] = _panel->mMainPanel->getDummy(_dmyName + StringConverter::toString(_i + 1));
	CCPoint _pos = _panel->mMainPanel->getImage(_dmyName + StringConverter::toString(_i + 1))->getPosition();
	m_TableCardRect[_i].origin = _panel->getPosition() + _panel->mMainPanel->getPosition() + _pos;*/
}

void PokerPlayerInfoCommonPanel::TurnOffWinnerText()
{
	mWinPanel->setVisible(false);	
}

void PokerPlayerInfoCommonPanel::onAnimationEnded(const string& ani)
{
	if (ani.find("winner_start") != string::npos || ani.find("winner_start_b") != string::npos) {
		//mWinPanel->setVisible(true);
	}
	else if (ani.find("winner_loop") != string::npos || ani.find("winner_loop_b") != string::npos) {
		//mWinPanel->setVisible(false);
	}
	else if (ani.find("winner_end") != string::npos || ani.find("winner_end_b") != string::npos)
		TurnOffWinnerText();
	else if (ani.find("made_end_high") != string::npos)
	{
		mMadeImage->setVisible(false);
	}
	else if (ani.find("made_end_low") != string::npos || ani.find("made_end_swing") != string::npos)
		mMadeImage->setVisible(false);
	else if (ani.find("mark_allin_1_end") != string::npos || ani.find("mark_allin_1_end_b") != string::npos)
		m_AllInImage->setVisible(false);
	else if (ani.find("mark_allin_2_end") != string::npos || ani.find("mark_allin_2_end_b") != string::npos)
		m_AllBetImage->setVisible(false);
	else if (ani.find("mark_sidebetting_end") != string::npos || ani.find("mark_sidebetting_end_b") != string::npos)
		m_SideBetImage->setVisible(false);
	else if (ani.find("mark_join_end") != string::npos)
		m_EnterImage->setVisible(false);
	else if (ani.find("mark_waiting_end") != string::npos)
		m_WaitImage->setVisible(false);
}

void PokerPlayerInfoCommonPanel::SetGoldAmount(int64 gameMoney)
{
	mNowGameMoney = gameMoney;
	if (mGoldAmount != nullptr && mGoldAmount->getActionByTag(ACTION_TAG) == nullptr)
	{
		mGoldAmount->setVisible(true);
		mGoldAmount->setString(GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(gameMoney), 2).c_str());
		if (mMyInfo) {
			int64 _MaxGold = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoneyMax;
			if (gameMoney >= _MaxGold) {
				mGoldAmount->setGrayscale(true);
			}
			else {
				mGoldAmount->setGrayscale(false);
			}
		}
	}
}

void PokerPlayerInfoCommonPanel::InitAllBetImage()
{
	mMainPanel->getSkel("skel_allin1")->setVisible(false);
	mMainPanel->getSkel("skel_allin2")->setVisible(false);
	mMainPanel->getSkel("skel_sidebetting")->setVisible(false);

	Panel* _panel = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetChracterPanel();
	if (_panel == nullptr)
		return;
	CCPoint _pos = ccp(0.f, 0.f);
	if (m_AllInImage == nullptr)
	{
		m_AllInImage = new SkelObject();
		m_AllInImage->setSkelAnim("ui/paneltool_8888.json");
		_pos = mMainPanel->getImage("skel_allin1")->getPosition();
		m_AllInImage->setPosition(_pos + getPosition() + mMainPanel->getPosition());
		_panel->addChild(m_AllInImage, 3);
		m_AllInImage->release();
		m_AllInImage->setVisible(false);
	}
	if (m_AllBetImage == nullptr)
	{
		m_AllBetImage = new SkelObject();
		m_AllBetImage->setSkelAnim("ui/paneltool_8888.json");
		_pos = mMainPanel->getImage("skel_allin2")->getPosition();
		m_AllBetImage->setPosition(_pos + getPosition() + mMainPanel->getPosition());
		_panel->addChild(m_AllBetImage, 3);
		m_AllBetImage->release();
		m_AllBetImage->setVisible(false);
	}
	if (m_SideBetImage == nullptr)
	{
		m_SideBetImage = new SkelObject();
		m_SideBetImage->setSkelAnim("ui/paneltool_8888.json");
		_pos = mMainPanel->getImage("skel_sidebetting")->getPosition();
		m_SideBetImage->setPosition(_pos + getPosition() + mMainPanel->getPosition());
		_panel->addChild(m_SideBetImage, 3);
		m_SideBetImage->release();
		m_SideBetImage->setVisible(false);
	}
}

void PokerPlayerInfoCommonPanel::InitWaitImage()
{
	if (m_WaitImage == nullptr)
	{
		m_WaitImage = new SkelObject();
		m_WaitImage->setSkelAnim("ui/paneltool_8888.json");
		m_WaitImage->setPosition(mMainPanel->getImage("skel_waitingmark")->getPosition());
		mMainPanel->addChild(m_WaitImage);
		m_WaitImage->release();
		m_WaitImage->setVisible(false);
		m_WaitImage->setListener(this);

		m_EnterImage = new SkelObject();
		m_EnterImage->setSkelAnim("ui/paneltool_8888.json");
		m_EnterImage->setPosition(mMainPanel->getImage("skel_join_mark")->getPosition());
		mMainPanel->addChild(m_EnterImage);
		m_EnterImage->release();
		m_EnterImage->setVisible(false);
		m_EnterImage->setListener(this);
	}
}

void PokerPlayerInfoCommonPanel::SetShareEndCard()
{
	if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_isReplayData)
		return;

	runAction(CCSequence::create(
		CCDelayTime::create(0.5f),	//애니메이션 대기 시간.
		CCCallFunc::create(this, callfunc_selector(PokerPlayerInfoCommonPanel::CallBackShareEndCard)),
		NULL));
}

void PokerPlayerInfoCommonPanel::CallBackShareEndCard()
{
	//TODO : ShareEndCard
	cout << "CALL BACK SHARE CARD END.!!!\n\n\n" << endl;
	TCPService::getSingletonPtr()->SendNormalPacket(CSProtocol::C2S_SHARE_CARD_END_RES_IDX);
}


void PokerPlayerInfoCommonPanel::SetMadeJokbo(int kind)
{
	switch (kind)
	{
		case HighJokboKind::HIGH_ROYAL_STRAIGHT_FLUSH :
			mMadeImage->setSkin("royal");
			break;
		case HighJokboKind::HIGH_STRAIGHT_FLUSH:
			mMadeImage->setSkin("straightflush");
			break;
		case HighJokboKind::HIGH_FOUR_CARD:
			mMadeImage->setSkin("four");
			break;
		case HighJokboKind::HIGH_FULL_HOUSE:
			mMadeImage->setSkin("fullhouse");
			break;
		case HighJokboKind::HIGH_FLUSH:
			mMadeImage->setSkin("flush");
			break;
		case HighJokboKind::HIGH_MOUNTAIN:
			mMadeImage->setSkin("mountain");
			break;
		case HighJokboKind::HIGH_BACK_STRAIGHT:
			mMadeImage->setSkin("backstraight");
			break;
		case HighJokboKind::HIGH_STRAIGHT:
			mMadeImage->setSkin("straight");
			break;
		case HighJokboKind::HIGH_TRIPLE:
			mMadeImage->setSkin("three");
			break;
		case LowJokboKind::LOW_EIGHT_TOP:
			mMadeImage->setSkin("8top");
			break;
		case LowJokboKind::LOW_SEVEN_TOP:
			mMadeImage->setSkin("7top");
			break;
		case LowJokboKind::LOW_SIX_TOP:
			mMadeImage->setSkin("6top");
			break;
		case LowJokboKind::BADUKI_GOLF:
			mMadeImage->setSkin("golf");
			break;
		case LowJokboKind::BADUKI_SECOND:
			mMadeImage->setSkin("second");
			break;
		case LowJokboKind::BADUKI_THIRD:
			mMadeImage->setSkin("third");
			break;
		case LowJokboKind::BADUKI_FIVE_TOP:
		case LowJokboKind::BADUKI_SIX_TOP:
		case LowJokboKind::BADUKI_SEVEN_TOP:
		case LowJokboKind::BADUKI_EIGHT_TOP:
		case LowJokboKind::BADUKI_NINE_TOP:
		case LowJokboKind::BADUKI_TEN_TOP:
		case LowJokboKind::BADUKI_J_TOP:
		case LowJokboKind::BADUKI_Q_TOP:
		case LowJokboKind::BADUKI_K_TOP:
			mMadeImage->setSkin("made");
			break;
		default :
			mMadeImage->setSkin("6top");
			break;
	}
}

void PokerPlayerInfoCommonPanel::onEvent(int trackIdx, spEvent* event)
{
	string eventName(event->data->name);
	if (eventName == "start_low")
	{
		SetMadeJokbo(m_MadeKind);
		m_MadeKind = HighJokboKind::HIGH_NO;
	}
}

void PokerPlayerInfoCommonPanel::setMyInfo()
{
	mMyInfo = true;
}

void PokerPlayerInfoCommonPanel::addLimitedError()
{
	int64 _MaxGold = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoneyMax;
	if (mNowGameMoney >= _MaxGold) {
		float fadeoutTime = 0.8f;
		float showTime = 0.2f;
		refreshLimited();
		CCFiniteTimeAction* callbackAction1 = CCCallFunc::create(this, callfunc_selector(PokerPlayerInfoCommonPanel::refreshLimited));
		CCDelayTime* delay1 = CCDelayTime::create(fadeoutTime);
		CCFiniteTimeAction* callbackAction2 = CCCallFunc::create(this, callfunc_selector(PokerPlayerInfoCommonPanel::refreshMyMoney));
		CCDelayTime* delay2 = CCDelayTime::create(fadeoutTime);
		CCFiniteTimeAction* callbackAction3 = CCCallFunc::create(this, callfunc_selector(PokerPlayerInfoCommonPanel::refreshLimited));
		CCDelayTime* delay3 = CCDelayTime::create(fadeoutTime);
		CCFiniteTimeAction* callbackAction4 = CCCallFunc::create(this, callfunc_selector(PokerPlayerInfoCommonPanel::refreshMyMoney));

		CCAction* squenceAction = CCSequence::create(callbackAction1, delay1, CCFadeOut::create(showTime), CCFadeIn::create(0.1f),
									callbackAction2, delay2, CCFadeOut::create(showTime), CCFadeIn::create(0.1f),
									callbackAction3, delay3, CCFadeOut::create(showTime), CCFadeIn::create(0.1f),
									callbackAction4, nullptr);

		squenceAction->setTag(ACTION_TAG);
		mGoldAmount->runAction(squenceAction);
	}	
}

void PokerPlayerInfoCommonPanel::refreshMyMoney()
{
	mGoldAmount->setString(GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(mNowGameMoney), 2).c_str());
}

void PokerPlayerInfoCommonPanel::refreshLimited()
{
	mGoldAmount->setString(GameStringDepot::getSingleton().getString("PokerPlayerInfoCommonPanel_LIMITED_MONEY").c_str());
}

