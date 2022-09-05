#include "pch.h"
#include "RoomUserData.h"
#include "PokerCardWidget.h"
#include "UserJokboInfo.h"
#include "PokerChipWidget.h"
#include "GameRoomInfo.h"
#include "PokerPlayerInfoPanel.h"
#include "GameStringDepot.h"
#include "SoundHelper.h"
#include "PokerShopHelper.h"

RoomUserData::RoomUserData()
{
	Init();
}

RoomUserData::~RoomUserData()
{
	if (!m_isMe || GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_isReplayData == true)
	{
		if (m_pPlayerData)
		{
			NX_SAFE_DELETE(m_pPlayerData);
			m_pPlayerData = nullptr;
		}		
	}

	if (m_pJokboInfo)
	{
		NX_SAFE_DELETE(m_pJokboInfo);
		m_pJokboInfo = nullptr;
	}
	
	if (m_pCardManager)
	{
		NX_SAFE_DELETE(m_pCardManager);
		m_pCardManager = nullptr;
	}

	if (m_pMyCharater)
	{
		m_pMyCharater = nullptr;
	}

	if (m_pMyCharaterUnder)
	{
		m_pMyCharaterUnder = nullptr;
	}
		
	
	if (m_pMyEmotiBubble)
	{ 
		m_pMyEmotiBubble = nullptr;
	}
}

void RoomUserData::Init()
{
	m_PlayerOutResrvKind = 0;
	m_KickReady = false;
	m_OutReady = false;
	m_bEmotionBlock = false;
	m_isMe = false;
	m_State = PlayerStatus::PLAYER_PREPARE;
	m_BettingKind = BettingKind::BETTING_NO;
	m_AllBetKind = AllBetKind::ALLBET_NO;
	m_BettingMoney = 0;
	m_bBadugiSortWait = false;
	m_BadukiSortDelayTime = 0.f;

	m_pCardManager = new CardManager();
	m_pJokboInfo = new UserJokboInfo();
	m_pJokboInfo->SetCardInfo(&(m_pCardManager->m_CardList));

	m_pMyCharater = nullptr;
	m_pMyCharaterUnder = nullptr;
	m_pMyEmotiBubble = nullptr;
	m_nMyCharacterTime = 0;
	m_PotMoneyUpdateCount = 0; 
	m_ChipAmount = 0;

	m_IsFriendRequest = false;
	m_IsStatcsUpdated = false;

	m_isPlayThinkAni = false;
	m_ThinkAniDelay = 0.f;

	m_bCharacterMoveEnd = false;
	m_fDelayMoveEndTime = 0.f;

}

void RoomUserData::SetMe(bool _isMe)
{
	m_isMe = _isMe;
}

void RoomUserData::Update(float _dt)
{
	if (m_bCharacterMoveEnd == true)
	{
		m_fDelayMoveEndTime -= _dt;
		if (m_fDelayMoveEndTime <= 0.f)
		{
			m_fDelayMoveEndTime = 0.f;
			m_bCharacterMoveEnd = false;
			MoveEndCharacter();
		}
	}

	if (m_bBadugiSortWait == true)
	{
		m_BadukiSortDelayTime -= _dt;
		if (m_BadukiSortDelayTime <= 0.f)
		{
			m_BadukiSortDelayTime = 0.f;
			m_bBadugiSortWait = false;
			BadugiSortCard();
		}
	}

	if (m_pMyCharater != nullptr)
	{
		if (m_pMyCharater->isVisible() == true)
		{
			m_nMyCharacterTime += _dt;
			if (m_nMyCharacterTime >= 35.f)
			{
				if (GetPlayerStatus() == PLAYER_DIE)
				{
					PlayCharacterAnimation(DIE_ACT);
					m_nMyCharacterTime = rand() % 10;
				}
				else
				{
					m_MyCharacterState = (CharacterAniKind)(rand() % 2 + IDLE_ACT1);
					PlayCharacterAnimation(m_MyCharacterState);
					m_nMyCharacterTime = rand() % 10;
				}
				
			}
		}
	}

	if (m_isPlayThinkAni)
	{
		if (m_ThinkAniDelay <= 0.f)
		{
			PlayThink();
		}
		else
		{
			m_ThinkAniDelay -= _dt;
		}
	}

}

void RoomUserData::InitData()
{
	//TODO : 재시작시 호출함.
	m_PotMoneyUpdateCount = 0;
	m_KickReady = false;
	m_OutReady = false;
	m_IsStatcsUpdated = false;
	m_isPlayThinkAni = false;
	m_ThinkAniDelay = 0.f;
	m_bBadugiSortWait = false;
	m_BadukiSortDelayTime = 0.f;
	m_bCharacterMoveEnd = false;
	m_fDelayMoveEndTime = 0.f;

	m_State = PlayerStatus::PLAYER_INIT;

	m_BettingKind = BettingKind::BETTING_NO;
	m_AllBetKind = AllBetKind::ALLBET_NO;
	m_BettingMoney = 0;
	m_HighLowBettingKind = HighLowBettingKind::HIGHLOW_NO_BET;
	
	m_pJokboInfo->Init();
	ClearCardList();
}

void RoomUserData::LastCardCheck(bool _triger)
{
	if (m_State == PlayerStatus::PLAYER_DIE)
		return;

	m_pCardManager->SetLastCardTriger(_triger);
	m_pCardManager->LastCardCheck();
}

void RoomUserData::AddCard(int _number, int _kind, bool _showBack, bool _Action, float _delay)
{
	CCLOG("____________________________________________________n = %d , k = %d , back = %d", _number, _kind, _showBack);
	m_pCardManager->AddCard(_number, _kind, _showBack, _delay);
}

void RoomUserData::BadugiAddCard(int _number, int _kind, bool _showBack, bool _Action, float _delay)
{
	m_pCardManager->BadugiAddCard(_number, _kind, _showBack, _delay);
}


void RoomUserData::EraseCard(int _idx)
{
	m_pCardManager->EraseCard(_idx);
}

void RoomUserData::ChangeCard(int _idx, int _number, int _kind, bool isPaeShow)
{
	m_pCardManager->ChangeCard(_idx, _number, _kind, isPaeShow);
}

void RoomUserData::SelectOffCard(int _idx, bool _cancel)
{
	m_pCardManager->ActionSelectedCard(_idx, _cancel);
}

void RoomUserData::SelectOnCard(int _offCard, int _onCard)
{
	
}

void RoomUserData::ClearCardList()
{
	m_pCardManager->ClearCardList();
}

void RoomUserData::SetGameMoney(int64 gameMoney)
{
	if (m_pPlayerData == nullptr)
		return;

	m_pPlayerData->SetGameMoney(gameMoney);
}

void RoomUserData::SetBetting(BettingRes * res)
{
	PlayThinkAnimation(0.f, false);
	m_BettingKind = res->bettingkind();
	m_BettingMoney = res->bettingmoney();
	SetGameMoney(res->gamemoney());
	m_AllBetKind = res->isallbet();
}

void RoomUserData::ActionBettingChip(int64 _money)
{
	//TODO : Chip 베팅하는 애니메이션
	
}

void RoomUserData::CheckBettingAnimaion(CharacterAniKind _kind)
{
	if (m_pMyCharater == nullptr)
		return;

	string _frameName = m_pMyCharater->getCurrentAnimation();

	if (_frameName == "bet_bbing" || _frameName == "bet_raise" || _frameName == "bet_raise")
	{
		if (m_PotMoneyUpdateCount > 0)
		{
			GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->SetPotMoneyUpdate(PotMoneyState::POT_UPDATE);
			m_PotMoneyUpdateCount--;
		}		
	}

}

void RoomUserData::PlayCharacterAnimation(CharacterAniKind _kind)
{
	m_nMyCharacterTime = 0;

	if (m_pMyCharater == nullptr && m_pMyCharaterUnder == nullptr)
		return;

	m_MyCharacterState = _kind;
	CheckBettingAnimaion(_kind);	//  배팅 에니메이션 씹힐때 처리.
	switch (_kind)
	{
	case RESULT_ALLIN:
		m_pMyCharater->playAnimation("bankrupt_ready");
		m_pMyCharater->appendAnimation("bankrupt_loop", true);
		m_pMyCharaterUnder->playAnimation("bankrupt_ready");
		m_pMyCharaterUnder->appendAnimation("bankrupt_loop", true);
		break;
	case BET_BBING:
		m_pMyCharater->playAnimation("bet_bbing");
		m_pMyCharater->appendAnimation("idle", true);
		m_pMyCharaterUnder->playAnimation("bet_bbing");
		m_pMyCharaterUnder->appendAnimation("idle", true);
		m_PotMoneyUpdateCount++;
		break;
	case BET_BIGFOLD:
		m_pMyCharater->playAnimation("bet_bigfold");
		m_pMyCharater->appendAnimation("die_idle_ready");
		m_pMyCharater->appendAnimation("die_idle_loop", true);
		m_pMyCharaterUnder->playAnimation("bet_bigfold");
		m_pMyCharaterUnder->appendAnimation("die_idle_ready");
		m_pMyCharaterUnder->appendAnimation("die_idle_loop", true);
		break;
	case BET_BIG_RAISE:
		m_pMyCharater->playAnimation("bet_bigraise", false, false, 2.f);
		m_pMyCharater->appendAnimation("idle", true);
		m_pMyCharaterUnder->playAnimation("bet_bigraise", false, false, 2.f);
		m_pMyCharaterUnder->appendAnimation("idle", true);
		m_PotMoneyUpdateCount++;
		break;
	case BET_CHECK:
		m_pMyCharater->playAnimation("bet_check");
		m_pMyCharater->appendAnimation("idle", true);
		m_pMyCharaterUnder->playAnimation("bet_check");
		m_pMyCharaterUnder->appendAnimation("idle", true);
		break;
	case BET_RAISE:
		m_pMyCharater->playAnimation("bet_raise", false, false, 2.f);
		m_pMyCharater->appendAnimation("idle", true);	
		m_pMyCharaterUnder->playAnimation("bet_raise", false, false, 2.f);
		m_pMyCharaterUnder->appendAnimation("idle", true);
		m_PotMoneyUpdateCount++;
		break;
	case DIE_ACT:
		m_pMyCharater->playAnimation("die_act");
		m_pMyCharater->appendAnimation("die_idle_loop", true);
		m_pMyCharaterUnder->playAnimation("die_act");
		m_pMyCharaterUnder->appendAnimation("die_idle_loop", true);
		break;
	case DIE_IDLE:
		m_pMyCharater->playAnimation("die_idle_ready");
		m_pMyCharater->appendAnimation("die_idle_loop", true);
		m_pMyCharaterUnder->playAnimation("die_idle_ready");
		m_pMyCharaterUnder->appendAnimation("die_idle_loop", true);
		break;
	case GESTURE_ANGRY:
		m_pMyCharater->playAnimation("gesture_angry");
		m_pMyCharater->appendAnimation("idle", true);
		m_pMyCharaterUnder->playAnimation("gesture_angry");
		m_pMyCharaterUnder->appendAnimation("idle", true);
		break;
	case GESTURE_CELEBRATE:
		m_pMyCharater->playAnimation("gesture_celebrate");
		m_pMyCharater->appendAnimation("idle", true);
		m_pMyCharaterUnder->playAnimation("gesture_celebrate");
		m_pMyCharaterUnder->appendAnimation("idle", true);
		break;
	case GESTURE_GOOD:
		m_pMyCharater->playAnimation("gesture_good");
		m_pMyCharater->appendAnimation("idle", true);
		m_pMyCharaterUnder->playAnimation("gesture_good");
		m_pMyCharaterUnder->appendAnimation("idle", true);
		break;
	case GESTURE_HURRY:
		m_pMyCharater->playAnimation("gesture_hurry");
		m_pMyCharater->appendAnimation("idle", true);
		m_pMyCharaterUnder->playAnimation("gesture_hurry");
		m_pMyCharaterUnder->appendAnimation("idle", true);
		break;
	case GESTURE_LAUGH:
		m_pMyCharater->playAnimation("gesture_laugh");
		m_pMyCharater->appendAnimation("idle", true);
		m_pMyCharaterUnder->playAnimation("gesture_laugh");
		m_pMyCharaterUnder->appendAnimation("idle", true);
		break;
	case GESTURE_PLEASURE:
		m_pMyCharater->playAnimation("gesture_pleasure");
		m_pMyCharater->appendAnimation("idle", true);
		m_pMyCharaterUnder->playAnimation("gesture_pleasure");
		m_pMyCharaterUnder->appendAnimation("idle", true);
		break;
	case GESTURE_SADNESS:
		m_pMyCharater->playAnimation("gesture_sadness");
		m_pMyCharater->appendAnimation("idle", true);
		m_pMyCharaterUnder->playAnimation("gesture_sadness");
		m_pMyCharaterUnder->appendAnimation("idle", true);
		break;
	case GESTURE_SORRY:
		m_pMyCharater->playAnimation("gesture_sorry");
		m_pMyCharater->appendAnimation("idle", true);
		m_pMyCharaterUnder->playAnimation("gesture_sorry");
		m_pMyCharaterUnder->appendAnimation("idle", true);
		break;
	case GESTURE_SURPRIZE:
		m_pMyCharater->playAnimation("gesture_surprize");
		m_pMyCharater->appendAnimation("idle", true);
		m_pMyCharaterUnder->playAnimation("gesture_surprize");
		m_pMyCharaterUnder->appendAnimation("idle", true);
		break;
	case GESTURE_THANKS:
		m_pMyCharater->playAnimation("gesture_thanks");
		m_pMyCharater->appendAnimation("idle", true);
		m_pMyCharaterUnder->playAnimation("gesture_thanks");
		m_pMyCharaterUnder->appendAnimation("idle", true);
		break;
	case IDLE:
		m_pMyCharater->playAnimation("idle", true);
		m_pMyCharaterUnder->playAnimation("idle", true);
		break;
	case IDLE_ACT1:
		m_pMyCharater->playAnimation("idle1");
		m_pMyCharater->appendAnimation("idle", true);
		m_pMyCharaterUnder->playAnimation("idle1");
		m_pMyCharaterUnder->appendAnimation("idle", true);
		break;
	case IDLE_ACT2:
		m_pMyCharater->playAnimation("idle2");
		m_pMyCharater->appendAnimation("idle", true);
		m_pMyCharaterUnder->playAnimation("idle2");
		m_pMyCharaterUnder->appendAnimation("idle", true);
		break;
	case IDLE_STAND:
		m_pMyCharater->playAnimation("idle_stand", true);
		m_pMyCharaterUnder->playAnimation("idle_stand", true);
		break;
	case IDLE_STAND_ACT1:
		m_pMyCharater->playAnimation("idle1");
		m_pMyCharater->appendAnimation("idle_stand", true);
		m_pMyCharaterUnder->playAnimation("idle1");
		m_pMyCharaterUnder->appendAnimation("idle_stand", true);
		break;
	case IDLE_STAND_ACT2:
		m_pMyCharater->playAnimation("idle2");
		m_pMyCharater->appendAnimation("idle_stand", true);
		m_pMyCharaterUnder->playAnimation("idle2");
		m_pMyCharaterUnder->appendAnimation("idle_stand", true);
		break;
	case LOSE_BIG:
		m_pMyCharater->playAnimation("lose_big_ready");
		m_pMyCharater->appendAnimation("lose_big_loop", true);
		m_pMyCharaterUnder->playAnimation("lose_big_ready");
		m_pMyCharaterUnder->appendAnimation("lose_big_loop", true);
		break;
	case LOSE_SMALL:
		m_pMyCharater->playAnimation("lose_small_ready");
		m_pMyCharater->appendAnimation("lose_small_loop", true);
		m_pMyCharaterUnder->playAnimation("lose_small_ready");
		m_pMyCharaterUnder->appendAnimation("lose_small_loop", true);
		break;
	case REACT_MADE:
		m_pMyCharater->playAnimation("react_made");
		m_pMyCharater->appendAnimation("idle", true);
		m_pMyCharaterUnder->playAnimation("react_made");
		m_pMyCharaterUnder->appendAnimation("idle", true);
		break;
	case THINK1:
		m_pMyCharater->appendAnimation("think1_ready");
		m_pMyCharater->appendAnimation("think1_loop", true);
		m_pMyCharaterUnder->appendAnimation("think1_ready");
		m_pMyCharaterUnder->appendAnimation("think1_loop", true);
		break;
	case THINK2:
		m_pMyCharater->appendAnimation("think2_ready");
		m_pMyCharater->appendAnimation("think2_loop", true);
		m_pMyCharaterUnder->appendAnimation("think2_ready");
		m_pMyCharaterUnder->appendAnimation("think2_loop", true);
		break;
	case WIN_BIG:
		m_pMyCharater->playAnimation("win_big_ready");
		m_pMyCharater->appendAnimation("win_big_loop", true);
		m_pMyCharaterUnder->playAnimation("win_big_ready");
		m_pMyCharaterUnder->appendAnimation("win_big_loop", true);
		break;
	case WIN_SMALL:
		m_pMyCharater->playAnimation("win_small_ready");
		m_pMyCharater->appendAnimation("win_small_loop", true);
		m_pMyCharaterUnder->playAnimation("win_small_ready");
		m_pMyCharaterUnder->appendAnimation("win_small_loop", true);
		break;
	}
}

void RoomUserData::SetCharacterPtr(SkelObject* _ptr, SkelObject* _ptrUnder, Panel* _pBubble)
{
	m_pMyCharater = _ptr;
	m_pMyCharaterUnder = _ptrUnder;
	m_pMyEmotiBubble = _pBubble;
	if (m_pMyEmotiBubble)
		m_pMyEmotiBubble->setTag(m_Po);
	m_pMyCharater->setListener(this);
	m_pMyCharater->addEventListener(this); 
	m_nMyCharacterTime = rand()%10;
	m_MyCharacterState = IDLE;

	m_bEmotionBlock = false;
}

void RoomUserData::SetCharacterPosition(CCPoint _position)
{
	m_pMyCharater->setPosition(_position);
	m_pMyCharaterUnder->setPosition(_position);
}

void RoomUserData::MoveEndCharacter()
{
	//m_pMyCharater->setPosition(m_moveToPosition);
	m_pMyCharater->playAnimation("idle", true);

	//m_pMyCharaterUnder->setPosition(m_moveToPosition);
	m_pMyCharaterUnder->playAnimation("idle", true);


}

void RoomUserData::MoveCharacterPosition(CCPoint _moveTo, float _delay)
{
	m_bCharacterMoveEnd = true;
	m_fDelayMoveEndTime = _delay;
	m_moveToPosition = _moveTo;
	m_pMyCharater->runAction(CCSequence::create(CCMoveTo::create(_delay, _moveTo), CCMoveTo::create(0.f, _moveTo), NULL));
	m_pMyCharaterUnder->runAction(CCSequence::create(CCMoveTo::create(_delay, _moveTo), CCMoveTo::create(0.f, _moveTo), NULL));

	MoveCharacterAnimation();
}

void RoomUserData::MoveCharacterAnimation()
{
	m_pMyCharater->playAnimation("walk_ready");
	m_pMyCharater->appendAnimation("walk_loop", true);
	m_pMyCharaterUnder->playAnimation("walk_ready");
	m_pMyCharaterUnder->appendAnimation("walk_loop", true);
}

void RoomUserData::onAnimationEnded(const string& ani)
{
	//if (ani.find("bet_raise") != string::npos)
	//{
	//	if (m_MyCharacterState == THINK2 || m_MyCharacterState == THINK3)
	//	{
	//		PlayCharacterAnimation(m_MyCharacterState);
	//	}
	//	else
	//	{
	//		PlayCharacterAnimation(IDLE);
	//	}
	//}
}

void RoomUserData::PlayCharacterSound(CharacterEfxKind _kind)
{
	if (GameDataManager::getSingletonPtr()->m_pOptionValue->m_voice == false)
		return;

	string _name = SoundHelper::getCharacterSoundStr(m_pPlayerData->m_CharacterIdx);	
	string efxStr = SoundHelper::getCharacterEfxKind(_kind);
	SoundManager::getSingletonPtr()->playEffect(_name + efxStr);
	CharacterText(_kind);
}

void RoomUserData::CharacterText(CharacterEfxKind _kind)
{
	if (m_pMyEmotiBubble == nullptr)
		return;
	string _emotiText = "TXT_EMOTI_";

	switch (_kind)
	{
	case EFX_ALLIN:
	case EFX_BBING:
	case EFX_CALL:
	case EFX_CHECK:
	case EFX_DDADANG:
	case EFX_QUARTER:
	case EFX_HALF:
	case EFX_DIE:
	case EFX_HIGH:
	case EFX_LOW:
	case EFX_SWING:
	case EFX_MADE:
	case EFX_THINK1:
	case EFX_THINK2:
	case EFX_BOX:
	case EFX_ENTER1:
	case EFX_ENTER2:
	case EFX_LOSEBIG:
	case EFX_LOSESMALL:
	case EFX_ONECARD:
	case EFX_PASS:
	case EFX_PR1:
	case EFX_PR2:
	case EFX_THREECARD:
	case EFX_TWOCARD:
	case EFX_WINBIG:
	case EFX_WINSMALL:
		return;
		break;
	case EFX_ANGRY:
		_emotiText += "ANGRY";
		break;
	case EFX_CHEER:
		_emotiText += "CELEBRATE";
		break;
	case EFX_GOOD:
		_emotiText += "GOOD";
		break;
	case EFX_HURRY:
		_emotiText += "HURRY";
		break;
	case EFX_LAUGH:
		_emotiText += "LAUGH";
		break;
	case EFX_PLEASURE:
		_emotiText += "PLEASURE";
		break;
	case EFX_SADNESS:
		_emotiText += "SADNESS";
		break;
	case EFX_SORRY:
		_emotiText += "SORRY";
		break;
	case EFX_SURPRIZE:
		_emotiText += "SURPRIZE";
		break;
	case EFX_THANKS:
		_emotiText += "THANK";
		break;
	}

	const W_CharacterData characterData = PokerShopHelper::getCharacterData(m_pPlayerData->m_CharacterIdx);
	string _name = "_" + characterData.image();
	_name = nxReplace(_name, "santiagov", "santiago");
	_name = nxReplace(_name, "christinav", "christina");
	_name = nxReplace(_name, "boxer", "alexander");
	_name = nxReplace(_name, "alexanderv", "alexander");
	_name = nxReplace(_name, "blackrosev", "blackrose");
	_name = nxReplace(_name, "jenniferv", "jennifer");
	_name = nxReplace(_name, "martinv", "martin");
	string _text = GameStringDepot::getSingletonPtr()->getString(_emotiText + _name);

	m_pMyEmotiBubble->stopAllActions();
	m_pMyEmotiBubble->setVisible(true);
	m_pMyEmotiBubble->getSkel("skel_emoticon_bubblel")->playAnimation("emoticon_bubblel_start");
	m_pMyEmotiBubble->getSkel("skel_emoticon_bubblel")->appendAnimation("emoticon_bubblel_stay");

	m_pMyEmotiBubble->getLabel("txt_emoticon_dialogue")->setOpacity(0);
	m_pMyEmotiBubble->getLabel("txt_emoticon_dialogue")->setString(_text.c_str());

	m_pMyEmotiBubble->getLabel("txt_emoticon_dialogue")->runAction(CCSequence::create(
		CCDelayTime::create(0.1f),
		CCFadeIn::create(0.1f),
		NULL));

	PokerPlayerInfoPanel* _pPanel = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetPlayerInfoPanel();
	_pPanel->HideTextBubblePanel(m_Po);

}

void RoomUserData::HideTextBubble()
{
	
}

void RoomUserData::onEvent(int trackIdx, spEvent* event)
{
	string _EventName = event->data->name;
	
	if (_EventName == "bet_bbing_chip")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BET);
		PokerChipWidget::create(GetBettingMoney(), (UserTablePosition)GetUserTablePosition());
		m_ChipAmount = 0;
		if (m_PotMoneyUpdateCount > 0)
		{
			GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->SetPotMoneyUpdate(PotMoneyState::POT_UPDATE);
			m_PotMoneyUpdateCount--;
		}
	}
	
	if (_EventName == "bet_bbing_voice")
	{
		if (m_BettingKind == CALL)
			PlayCharacterSound(EFX_CALL);
		else
			PlayCharacterSound(EFX_BBING);
	}
	
	if (_EventName == "bet_check_voice")
	{
		if (m_BettingKind == CALL)
			PlayCharacterSound(EFX_CALL);
		else
			PlayCharacterSound(EFX_CHECK);
		
	}

	if (_EventName == "bet_raise_chip")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BET);
		PokerChipWidget::create(GetBettingMoney(), (UserTablePosition)GetUserTablePosition());
		m_ChipAmount = 0;
		if (m_PotMoneyUpdateCount > 0)
		{
			GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->SetPotMoneyUpdate(PotMoneyState::POT_UPDATE);
			m_PotMoneyUpdateCount--;
		}
	}

	if (_EventName == "bet_bigraise_chip")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BIGBET);
		PokerChipWidget::create(GetBettingMoney(), (UserTablePosition)GetUserTablePosition());
		m_ChipAmount = 0;
		if (m_PotMoneyUpdateCount > 0)
		{
			GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->SetPotMoneyUpdate(PotMoneyState::POT_UPDATE);
			m_PotMoneyUpdateCount--;
		}
	}
	
	if (_EventName == "bet_raise_voice")
	{
		m_pMyCharater->setAnimationSpeed(1.f);
		m_pMyCharaterUnder->setAnimationSpeed(1.f);
		if (m_AllBetKind == ALL_BET)
		{
			PlayCharacterSound(EFX_ALLIN);
		}
		else 
		{
			if (m_BettingKind == CALL)
				PlayCharacterSound(EFX_CALL);
			if (m_BettingKind == HALF)
				PlayCharacterSound(EFX_HALF);
			if (m_BettingKind == QUARTER)
				PlayCharacterSound(EFX_QUARTER);
			if (m_BettingKind == DDADANG)
				PlayCharacterSound(EFX_DDADANG);
		}
	}
	
	if (_EventName == "bet_bigraise_voice")
	{
		m_pMyCharater->setAnimationSpeed(1.f);
		m_pMyCharaterUnder->setAnimationSpeed(1.f);
		if (m_AllBetKind == ALL_BET)
		{
			PlayCharacterSound(EFX_ALLIN);
		}
		else
		{
			if (m_BettingKind == CALL)
				PlayCharacterSound(EFX_CALL);
			if (m_BettingKind == HALF)
				PlayCharacterSound(EFX_HALF);
			if (m_BettingKind == QUARTER)
				PlayCharacterSound(EFX_QUARTER);
			if (m_BettingKind == DDADANG)
				PlayCharacterSound(EFX_DDADANG);
		}
	
	}

	if (_EventName == "die_idle_voice") { PlayCharacterSound(EFX_DIE); }
	// : 메이드
	if (_EventName == "react_made_voice") { PlayCharacterSound(EFX_MADE); }
	// : 고민1
	if (_EventName == "think1_voice") 
	{
		if (m_isMe == true) PlayCharacterSound(EFX_THINK1); 
	}
	// : 고민2
	if (_EventName == "think2_voice") 
	{ 
		if (m_isMe == true) PlayCharacterSound(EFX_THINK2);
	}

	//: 화남 목소리
	if (_EventName == "gesture_angry_voice") { PlayCharacterSound(EFX_ANGRY); }
	// : 축하 목소리
	if (_EventName == "gesture_celebrate_voice") { PlayCharacterSound(EFX_CHEER); }
	// : 굿 목소리
	if (_EventName == "gesture_good_voice") { PlayCharacterSound(EFX_GOOD); }
	// : 빨리 목소리
	if (_EventName == "gesture_hurry_voice") { PlayCharacterSound(EFX_HURRY); }
	// : ㅋㅋㅋ 목소리
	if (_EventName == "gesture_laugh_voice") { PlayCharacterSound(EFX_LAUGH); }
	// : 기쁨 목소리
	if (_EventName == "gesture_pleasure_voice") { PlayCharacterSound(EFX_PLEASURE); }
	// : 슬픔 목소리
	if (_EventName == "gesture_sadness_voice") { PlayCharacterSound(EFX_SADNESS); }
	// : 미안 목소리
	if (_EventName == "gesture_sorry_voice") { PlayCharacterSound(EFX_SORRY); }
	// : 헐 목소리
	if (_EventName == "gesture_surprize_voice") { PlayCharacterSound(EFX_SURPRIZE); }
	// : 감사 목소리
	if (_EventName == "gesture_thanks_voice") { PlayCharacterSound(EFX_THANKS); }

}

void RoomUserData::SetPlayerStatus(PlayerStatus status)
{
	m_State = status;

	GameRoomInfo* _pRoomInfo = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr();

	if (_pRoomInfo == nullptr)
		return;
	
	PokerPlayerInfoCommonPanel * _panel = _pRoomInfo->GetPlayerCommonPanel(m_Po);
	if (_panel == nullptr)
		return;

	if (m_State == PlayerStatus::PLAYER_SEE)
		_panel->turnOnWaitMark(PokerPlayerInfoCommonPanel::UserLoadKind::USER_LOAD_WAIT);
	else if (m_State == PlayerStatus::PLAYER_PREPARE)
		_panel->turnOnWaitMark(PokerPlayerInfoCommonPanel::UserLoadKind::USER_LOAD_ENTER);
	else
		_panel->turnOffWaitMark();
}

//void RoomUserData::ShowHighJokboEffect()
//{
//	if (!m_isMe)
//		return;
//
//	m_pJokboInfo->HighJokboCheck();
//
//	for (CardData* _CardData : m_pJokboInfo->GetHighJokboCardList())
//	{
//		_CardData->m_pCard->PlayCardEffect(CARD_EFFECT_MADE);
//	}
//
//
//	m_pJokboInfo->LowJokboCheck();
//}

void RoomUserData::ShowHoldemJokboCheck()
{
	//기덕 수정 여기서 체크 한다.
	m_pJokboInfo->HoldemJokboCheck();

	HighJokboKind _kind = m_pJokboInfo->GetHighJokboKind();
	switch (_kind)
	{
	case HIGH_ROYAL_STRAIGHT_FLUSH:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_ROYALFLUSH);
		break;
	case HIGH_STRAIGHT_FLUSH:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_STRAIGHTFLUSH);
		break;
	case HIGH_FOUR_CARD:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_FOURCARD);
		break;
	case HIGH_FULL_HOUSE:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_FULLHOUSE);
		break;
	case HIGH_FLUSH:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_FLUSH);
		break;
	case HIGH_MOUNTAIN:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_MOUNTAIN);
		break;
	case HIGH_BACK_STRAIGHT:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_BACKSTRAIGHT);
		break;
	case HIGH_STRAIGHT:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_STRAIGHT);
		break;
	case HIGH_TRIPLE:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_TRIPLE);
		break;
	case HIGH_TWO_PAIR:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_TWOPAIR);
		break;
	case HIGH_ONE_PAIR:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_ONEPAIR);
		break;
	case HIGH_TOP:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_TOP);
		break;
	}

	if (_kind <= HighJokboKind::HIGH_TRIPLE)
	{
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerAnimation(DEALER_REACT_MADE);
	}
	else if (_kind >= HighJokboKind::HIGH_ONE_PAIR)
	{
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerAnimation(DEALER_REACT_SMALLOPEN);
	}

	//PresetJokboCard();
	//for (CardData* _CardData : m_pJokboInfo->GetHighJokboCardList())
	//{
	//	if (m_isMe)
	//		_CardData->m_pCard->GetCardSkelObj()->playAnimation("cardfront");
	//	else
	//		_CardData->m_pCard->GetCardSkelObj()->playAnimation("cardfront_b");
	//}

	//GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetPlayerInfoPanel()->ClearAllPanelAction();

	PokerPlayerInfoCommonPanel*  _panel = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetPlayerCommonPanel(m_Po);
	if (_panel != nullptr)
	{
		//_panel->ClearBettingAmount();
		_panel->TurnOnJokboInfo(m_pJokboInfo->GetHighJokboString());
		//_panel->turnOnTimeGauge(true);

		if (m_isMe)
			_panel->MoveCardJokboInfoPo(1);
	}

}

void RoomUserData::ShowBadugiJokboCheck()
{
	m_pJokboInfo->BadukiJokboCheck();
	LowJokboKind _kind = m_pJokboInfo->GetLowJokboKind();
	switch (_kind)
	{
	case LOW_NO:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_NOTHING);
		break;
	case BADUKI_GOLF:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_GOLF);
		break;
	case BADUKI_SECOND:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_SECOND);
		break;
	case BADUKI_THIRD:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_THIRD);
		break;
	case BADUKI_FIVE_TOP:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_5TOP);
		break;
	case BADUKI_SIX_TOP:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_6TOP);
		break;
	case BADUKI_SEVEN_TOP:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_7TOP);
		break;
	case BADUKI_EIGHT_TOP:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_8TOP);
		break;
	case BADUKI_NINE_TOP:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_9TOP);
		break;
	case BADUKI_TEN_TOP:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_10TOP);
		break;
	case BADUKI_J_TOP:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_JTOP);
		break;
	case BADUKI_Q_TOP:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_QTOP);
		break;
	case BADUKI_K_TOP:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_KTOP);
		break;
	case BADUKI_BASE:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_BASE);
		break;
	case BADUKI_TWO_BASE:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_TWOBASE);
		break;
	case BADUKI_TWO_BASE_DOWN:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_NOTHING);
		break;
	default:
		break;
	}

	if (_kind <= LowJokboKind::BADUKI_K_TOP)
	{
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerAnimation(DEALER_REACT_MADE);
	}
	else if (_kind >= LowJokboKind::BADUKI_TWO_BASE)
	{
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerAnimation(DEALER_REACT_SMALLOPEN);
	}

	BadugiSortCard();

	for (int _i = 0; _i < 4; _i++)
	{
		m_pCardManager->m_CardList[_i]->m_pCard->setTag(100);
	}
	for (CardData* _pCardData : m_pJokboInfo->GetLowJokboRepCardList())
	{
		_pCardData->m_pCard->setTag(0);
	}
	
	for (int _i = 0; _i < 4; _i++)
	{
		int _idx = m_pCardManager->m_CardList[_i]->m_idx;
		m_pCardManager->m_CardList[_i]->m_pCard->Action_BadugiFlipOpen(0.02f * _idx);
	}

	//GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetPlayerInfoPanel()->ClearAllPanelAction();
	PokerPlayerInfoCommonPanel*  _panel = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetPlayerCommonPanel(m_Po);
	if (_panel != nullptr)
	{
		//_panel->ClearBettingAmount();
		_panel->TurnOnJokboInfo(m_pJokboInfo->GetBadukiJokboString());
		//_panel->turnOnTimeGauge(true);

		if (m_isMe)
			_panel->MoveCardJokboInfoPo(1);
	}
}

void RoomUserData::ShowHighJokboCheck()
{
	m_pJokboInfo->HighJokboCheck();

	HighJokboKind _kind = m_pJokboInfo->GetHighJokboKind();
	switch (_kind)
	{
	case HIGH_ROYAL_STRAIGHT_FLUSH:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_ROYALFLUSH);
		break;
	case HIGH_STRAIGHT_FLUSH:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_STRAIGHTFLUSH);
		break;
	case HIGH_FOUR_CARD:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_FOURCARD);
		break;
	case HIGH_FULL_HOUSE:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_FULLHOUSE);
		break;
	case HIGH_FLUSH:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_FLUSH);
		break;
	case HIGH_MOUNTAIN:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_MOUNTAIN);
		break;
	case HIGH_BACK_STRAIGHT:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_BACKSTRAIGHT);
		break;
	case HIGH_STRAIGHT:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_STRAIGHT);
		break;
	case HIGH_TRIPLE:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_TRIPLE);
		break;
	case HIGH_TWO_PAIR:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_TWOPAIR);
		break;
	case HIGH_ONE_PAIR:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_ONEPAIR);
		break;
	case HIGH_TOP:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_TOP);
		break;
	}

	if (_kind <= HighJokboKind::HIGH_TRIPLE)
	{
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerAnimation(DEALER_REACT_MADE);
		//ActionPointer::createLastPaeHighLowEvent(DealerAniKind::DEALER_REACT_MADE, EFX_DEALER_NOVOICE, 1.f);
	}
	else if (_kind >= HighJokboKind::HIGH_ONE_PAIR)
	{
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerAnimation(DEALER_REACT_SMALLOPEN);
		//ActionPointer::createLastPaeHighLowEvent(DealerAniKind::DEALER_REACT_SMALLOPEN, EFX_DEALER_NOVOICE, 1.f);
	}
	

	PresetJokboCard();

	for (CardData* _CardData : m_pJokboInfo->GetHighJokboCardList())
	{
		if (m_isMe)
			_CardData->m_pCard->GetCardSkelObj()->playAnimation("cardfront");
		else
			_CardData->m_pCard->GetCardSkelObj()->playAnimation("cardfront_b");
		//_CardData->m_pCard->GetCardSkelObj()->runAction(CCSequence::create(
		//	CCScaleTo::create(0.05f, 1.3f),
		//	CCDelayTime::create(0.5f),
		//	CCScaleTo::create(0.05f, 1.f),
		//	NULL));
	}

	//GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetPlayerInfoPanel()->ClearAllPanelAction();

	PokerPlayerInfoCommonPanel*  _panel = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetPlayerCommonPanel(m_Po);
	if (_panel != nullptr)
	{
		//_panel->ClearBettingAmount();
		_panel->TurnOnJokboInfo(m_pJokboInfo->GetFullJokboString());
		//_panel->turnOnTimeGauge(true);

		if (m_isMe)
			_panel->MoveCardJokboInfoPo(1);
	}
}

void RoomUserData::ShowSwingJokboCheck()
{
	PresetJokboCard();

	//GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetPlayerInfoPanel()->ClearAllPanelAction();
	PokerPlayerInfoCommonPanel* _panel = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetPlayerCommonPanel(m_Po);
	//if (_panel) _panel->turnOnTimeGauge(true);
	//_panel->ClearBettingAmount();

	switch (m_HighLowBettingKind)
	{
	case HIGH_BET:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_HIGH);
		for (CardData* _CardData : m_pJokboInfo->GetHighJokboCardList())
		{
			if (m_isMe)
				_CardData->m_pCard->GetCardSkelObj()->playAnimation("cardfront");
			else
				_CardData->m_pCard->GetCardSkelObj()->playAnimation("cardfront_b");
		}

		_panel->TurnOnJokboInfo(m_pJokboInfo->GetHighJokboString());
		break;
	case LOW_BET:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_LOW);
		for (CardData* _CardData : m_pJokboInfo->GetLowJokboCardList())
		{
			if (m_isMe)
				_CardData->m_pCard->GetCardSkelObj()->playAnimation("cardfront");
			else
				_CardData->m_pCard->GetCardSkelObj()->playAnimation("cardfront_b");
		}
		
		_panel->TurnOnJokboInfo(m_pJokboInfo->GetLowJokboString());
		break;
	case SWING_BET:
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_SWING);
		for (CardData* _CardData : m_pJokboInfo->GetHighJokboCardList())
		{
			if (m_isMe)
				_CardData->m_pCard->GetCardSkelObj()->playAnimation("cardfront");
			else
				_CardData->m_pCard->GetCardSkelObj()->playAnimation("cardfront_b");
		}

		for (CardData* _CardData : m_pJokboInfo->GetLowJokboCardList())
		{
			if (m_isMe)
				_CardData->m_pCard->GetCardSkelObj()->playAnimation("cardfront");
			else
				_CardData->m_pCard->GetCardSkelObj()->playAnimation("cardfront_b");
		}

		if (m_pJokboInfo->GetLowJokboKind() >= LowJokboKind::LOW_SIX_TOP)
		{
			string jokboStr = "";
			jokboStr = m_pJokboInfo->GetHighJokboString();
			jokboStr.append("/");
			jokboStr.append((m_pJokboInfo->GetLowJokboString()).c_str());
			_panel->TurnOnJokboInfo(jokboStr);
		}
		break;
	}
	if (m_isMe)
		_panel->MoveCardJokboInfoPo(1);

}

void RoomUserData::PresetJokboCard()
{
	//모두 흑백으로
	int _CardSize = GetCardManager()->m_CardList.size();

	for (int _i = 0; _i < _CardSize; _i++)
	{
		if (m_isMe)
			GetCardManager()->m_CardList[_i]->m_pCard->GetCardSkelObj()->playAnimation("frontdie");
		else
			GetCardManager()->m_CardList[_i]->m_pCard->GetCardSkelObj()->playAnimation("frontdie_b");
	}
}

void RoomUserData::PlayThinkAnimation(float _delay, bool _play)
{
	m_isPlayThinkAni = _play;
	m_ThinkAniDelay = (_play ? _delay : 0.f);
}

void RoomUserData::PlayThink()
{
	if (m_isPlayThinkAni == false)
	{
		m_ThinkAniDelay = 0.f;
		return;
	}

	m_isPlayThinkAni = false;
	m_ThinkAniDelay = 0.f;

	int _randValue = CharacterAniKind::THINK1 + ( rand() % 2 );
	PlayCharacterAnimation((CharacterAniKind)_randValue);
}

void RoomUserData::BadugiSortCard(float _delay)
{
	if (m_pJokboInfo == nullptr)
		return;

	if (_delay != 0)
	{
		m_bBadugiSortWait = true;
		m_BadukiSortDelayTime = _delay;
		return;
	}

	m_pJokboInfo->BadukiJokboCheck();

	//카드 소트 위치 저장 //add to chiuki
	vector<CardData*>	sortCardContainer;
	m_pJokboInfo->SortCard(sortCardContainer, SortKind::CARD_SORT_LOW);
	int _size = sortCardContainer.size();

	for (int _i = 0; _i < _size; _i++)
	{
		CardData* _pData = sortCardContainer[_i];
		CCPoint _movePos = GetCardManager()->GetTableCardRect(_i).origin;
		_pData->m_pCard->Action_MoveToCard(_movePos);
		_pData->m_pCard->setZOrder(_i);
		_pData->m_idx = _i;

		if (m_isMe == true)
		{
			_pData->m_pCard->CardEffectSelectBoxOff();
			GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[_i] = false;
		}
			
	}
}

void RoomUserData::SetBadugiSelectedCardEffect(float _delay)
{
	if (GetCardManager()->m_CardList.size() == 0)
		return;

	for (int _i = 0; _i < 4; _i++)
	{
		int _idx = GetCardManager()->m_CardList[_i]->m_idx;
		bool _isSelected = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[_idx];

		if (_isSelected == true)
		{
			GetCardManager()->m_CardList[_i]->m_pCard->Action_BadugiCardEffectSelectBox(_delay, _isSelected);
		}
		else
		{
			GetCardManager()->m_CardList[_i]->m_pCard->Action_BadugiCardEffectSelectBox(0.f, _isSelected);
		}

		//CCPoint _cardPos = GetCardManager()->GetTableCardRect(_idx).origin;
		//if (_isSelected == true)
		//{
		//	GetCardManager()->m_CardList[_i]->m_pCard->Action_MoveToCard(_cardPos + ccp(0.f, 15.f), _delay);
		//	GetCardManager()->m_CardList[_i]->m_pCard->CardEffectSelectBoxOn();
		//	
		//}
		//else
		//{
		//	GetCardManager()->m_CardList[_i]->m_pCard->Action_MoveToCard(_cardPos, _delay);
		//	GetCardManager()->m_CardList[_i]->m_pCard->CardEffectSelectBoxOff();
		//}


	}
}

void RoomUserData::SelectBadugiRecommendCard()
{
	for (int _i = 0; _i < 4; _i++)
	{
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[_i] = true;
	}

	for (CardData* _pCard : m_pJokboInfo->GetLowJokboRepCardList())
	{
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[_pCard->m_idx] = false;
	}

}

void RoomUserData::PlaySoundBadugiSelectChangeCard(int _count)
{
	switch (_count)
	{
	case 1:
		PlayCharacterSound(EFX_ONECARD);
		break;
	case 2:
		PlayCharacterSound(EFX_TWOCARD);
		break;
	case 3:
		PlayCharacterSound(EFX_THREECARD);
		break;
	case 4:
		PlayCharacterSound(EFX_BOX);
		break;
	}
}

void RoomUserData::setMyCharacterVisible(bool visible)
{
	if (visible) {
		m_pMyCharater->setVisible(visible);
		m_pMyCharaterUnder->setVisible(visible);
	}
	else {
		m_pMyCharater->setVisible(visible);
		m_pMyCharaterUnder->setVisible(visible);
	}
}

void RoomUserData::setActionSpeed()
{
	m_pCardManager->setActionSpeed();
}

bool RoomUserData::isLastCardOpen()
{
	if (GetCardManager()->IsLastCard()) {
		if (GameDataManager::getSingletonPtr()->m_pOptionValue->m_hiddenCard == false) {
			return true;
		}
	}
	return false;
}
