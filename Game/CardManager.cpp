#include "pch.h"
#include "CardManager.h"
#include "NxDefine.h"
#include "PokerPlayerInfoPanel.h"
#include "GameDataManager.h"
#include "NxLayerManager.h"
#include "NxPanel.h"
#include "BettingCardOnOffPanel.h"
#include "PokerChipWidget.h"


CardManager::CardManager()
{
	m_UserIdx = -1;
	m_UserPo = -1;
	m_pCardPanel = nullptr;
	
}

CardManager::~CardManager()
{
	ClearCardList();
	m_bLastCardTriger = false;
}

void CardManager::SetData()
{
	if (m_UserIdx == -1)
		return;

	PokerPlayerInfoCommonPanel* _panel = nullptr;
	string _dmyName;
	switch (m_UserIdx)
	{
	case 0:
		_dmyName = "dmy_card_big";
		break;
	case 1:
	case 2:
	case 3:
	case 4:
		_dmyName = "dmy_card_small";
		break;
	default:
		break;
	}

	PokerPlayerInfoPanel* _pPlayerInfoPanel = dynamic_cast<PokerPlayerInfoPanel*>(LayerManager::getSingleton().getLayer("PlayerInfo"));
	_panel = _pPlayerInfoPanel->GetPlayerCommonPanel(m_UserPo);

	int _size = 7;
	if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind() == GAMEKIND_BADUKI)
		_size = 4;
	else if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind() == GAMEKIND_HOLDEM)
		_size = 2;

	for (int _i = 0; _i < _size; _i++)
	{
		m_TableCardRect[_i] = _panel->mMainPanel->getDummy(_dmyName + StringConverter::toString(_i + 1));
		CCPoint _pos = _panel->mMainPanel->getImage(_dmyName + StringConverter::toString(_i + 1))->getPosition();
		m_TableCardRect[_i].origin = _panel->getPosition() + _panel->mMainPanel->getPosition() + _pos;
	}

	cout << "Set [" << m_UserIdx << "]User CardPosition Complete!" << endl;
}

bool CardManager::IsLastCard()
{
	if (m_CardList.size() == 7)
		return true;
	else
		return false;
}

void CardManager::LastCardCheck()
{
	// 라스트 카드이면 자동 플립
	if (m_CardList.size() == 7)
	{
		if (m_bLastCardTriger)
		{
			GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->SetHiddenCheck(true);
		}
		else
		{
			ActionFlipCard(6, true, 0);
		}
	}
		
}

void CardManager::BadugiAddCard(int _number, int _kind, bool _showBack, float _delay)
{
	int _cardIdx = (_number * 4) + _kind;

	if (_number == 100 && _kind == -1)
	{
		_showBack = true;
		_cardIdx = 0;
	}

	if (_cardIdx < 52)
	{
		CardData* _pCardData = new CardData();

		_pCardData->m_Number = _number;
		_pCardData->m_Kind = _kind;
		_pCardData->m_idx = m_CardList.size();
		
		if (m_UserIdx == 0)
		{
			_pCardData->m_pCard = new PokerCardWidget(m_CardList.size(), _cardIdx, PokerCardWidget::PokerCardWidetBig);
		}
		else
		{
			_pCardData->m_pCard = new PokerCardWidget(m_CardList.size(), _cardIdx, PokerCardWidget::PokerCardWidetSmall);
		}

		_pCardData->m_pCard->setZOrder(_pCardData->m_idx + 2);

		

		if (_showBack == true)
		{
			_pCardData->m_pCard->PlayCardEffect(CARD_EFFECT_DUST, 0.2f + _delay);
			_pCardData->m_pCard->SetBack(false);
		}
		else
		{
			_pCardData->m_pCard->PlayCardEffect(CARD_EFFECT_DUST, 0.2f + _delay);
			_pCardData->m_pCard->SetBack(false);
			_pCardData->m_pCard->Action_BadugiFlipOpen(0.5f + _delay);
		}

		m_CardList.push_back(_pCardData);

		if (m_pCardPanel == nullptr)
		{
			m_pCardPanel = dynamic_cast<Panel*>(LayerManager::getSingleton().getLayer("CardLayer"));
		}

		if (m_pCardPanel)
		{
			_pCardData->m_pCard->setPosition(m_TableCardRect[m_CardList.size() - 1].origin);
			m_pCardPanel->addChild(_pCardData->m_pCard);
			_pCardData->m_pCard->release();
		}
	}
}


void CardManager::AddCard(int _number, int _kind, bool _showBack, float _delay)
{
	int _cardIdx = (_number * 4) + _kind;

	if (_number == 100 && _kind == -1)
	{
		_showBack = true;
		_cardIdx = 0;
	}
	
	if (_cardIdx < 52)
	{
		CardData* _pCardData = new CardData();

		_pCardData->m_Number = _number;
		_pCardData->m_Kind = _kind;
		_pCardData->m_idx = m_CardList.size();
				
		if (m_UserIdx == 0)
		{
			_pCardData->m_pCard = new PokerCardWidget(m_CardList.size(), _cardIdx, PokerCardWidget::PokerCardWidetBig);
		}
		else
		{
			_pCardData->m_pCard = new PokerCardWidget(m_CardList.size(), _cardIdx, PokerCardWidget::PokerCardWidetSmall);
		}

		_pCardData->m_pCard->setZOrder(_pCardData->m_idx + 2);

		if (_showBack == true)
		{
			if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetIsCardSelected() && m_CardList.size() <= 2)
			{
				_pCardData->m_pCard->SetBack(false);
			}
			else
			{
				//last card
				_pCardData->m_pCard->PlayCardEffect(CARD_EFFECT_DUST, 0.2f + _delay);
				_pCardData->m_pCard->SetBack(false);
			}
		}
		else
		{
			if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetIsCardSelected() && m_CardList.size() > 2)
			{
				//3~6 card
				_pCardData->m_pCard->PlayCardEffect(CARD_EFFECT_DUST, 0.2f + _delay);
				_pCardData->m_pCard->SetBack(false);
				_pCardData->m_pCard->Action_FlipOpen(0.5f + _delay);
			}
			else
			{
				//select card
				_pCardData->m_pCard->SetFront();
			}
		}

		m_CardList.push_back(_pCardData);

		if (m_pCardPanel == nullptr)
		{
			m_pCardPanel = dynamic_cast<Panel*>(LayerManager::getSingleton().getLayer("CardLayer"));
		}

		if (m_pCardPanel)
		{
			_pCardData->m_pCard->setPosition(m_TableCardRect[m_CardList.size()-1].origin);
			//_pCardData->m_pCard->setPositionY(m_TableCardRect[m_CardList.size() - 1].origin.y);
			//_pCardData->m_pCard->fit(m_TableCardRect[m_CardList.size() - 1].size);
			//_pCardData->m_pCard->setContentSize(m_TableCardRect[m_CardList.size() - 1].size);
			m_pCardPanel->addChild(_pCardData->m_pCard);
			_pCardData->m_pCard->release();
		}		
	}
}

void CardManager::EraseCard(int _idx)
{
	CardData* _data;
	if (m_CardList.size() >= (unsigned int)_idx + 1)
	{
		if (m_CardList[_idx] != nullptr)
		{
			_data = m_CardList[_idx];
			//_data->m_pCard->CardClear();
			m_CardList.erase(m_CardList.begin() + _idx);
			NX_SAFE_DELETE(_data);
		}
	}
}

void CardManager::ChangeCard(int _idx, int _number, int _kind, bool isPaeShow)
{
	if (m_CardList.size() <= _idx)
		return;

	if (m_CardList.size() == 0 || m_CardList[_idx] == nullptr)
	{
		return;
	}
	if (m_CardList[_idx]->m_pCard == nullptr)
	{
		return;
	}

	CCPoint _cardPos = GetTableCardRect(m_CardList[_idx]->m_idx).origin;

	if (_kind == -1 || _number == 100)
	{
		//move only
		if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind() == GAMEKIND_BADUKI)
		{
			m_CardList[_idx]->m_pCard->Action_BadugiChangeCard(0.2f, false, _cardPos);
		}
		return;
	}
	else
	{
		m_CardList[_idx]->m_Kind = _kind;
		m_CardList[_idx]->m_Number = _number;
		int _cardIdx = (_number * 4) + _kind;
		m_CardList[_idx]->m_pCard->ChangeCard(_cardIdx);

		int _gamekind = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind();
		if (_gamekind == GAMEKIND_BADUKI)
		{
			if (isPaeShow == false)
			{
				if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_isReplayData == true)
				{
					m_CardList[_idx]->m_pCard->Action_BadugiChangeCard(0.2f, true, _cardPos);
				}
				else
				{
					m_CardList[_idx]->m_pCard->Action_BadugiChangeCard(0.2f, true, _cardPos);
				}
			}
			
		}
		else if (_gamekind == GAMEKIND_HOLDEM)
		{
			if (m_UserIdx == 0)
			{
				if (isPaeShow)
					m_CardList[_idx]->m_pCard->SetOpen();
				else
					m_CardList[_idx]->m_pCard->SetFront();
			}
			else
			{
				m_CardList[_idx]->m_pCard->FilpCardFront();
			}
			
		}
		else if (isPaeShow)
			m_CardList[_idx]->m_pCard->SetOpen();
		else
			m_CardList[_idx]->m_pCard->SetFront();
	}
	
	//GameDataManager::getSingletonPtr()->PlayGameSound(GameEfxKind::EFX_GAME_CARDFLOP);
}

void CardManager::ClearCardList()
{
	CardData* _data;
	while (!m_CardList.empty())
	{
		_data = m_CardList[0];
		//_data->m_pCard->CardClear();
		m_CardList.erase(m_CardList.begin());
		NX_SAFE_DELETE(_data);
	}
	m_CardList.clear();
}

void CardManager::ActionMoveCard(unsigned int _idx, CCPoint _moveTo, float _duration, float _scale, float _delay)
{
	if (m_CardList.size() <= _idx)
		return;	


	if (_scale != 1.0f)
	{
		m_CardList[_idx]->m_pCard->runAction(CCScaleTo::create(_duration, _scale));
	}


	CCLOG("____________________________________________________m_CardList[_idx]->m_pCard->getRotation() = %f", m_CardList[_idx]->m_pCard->getRotation());

	if (m_CardList[_idx]->m_pCard->getRotation() != 0.f)
	{
		m_CardList[_idx]->m_pCard->runAction(CCSequence::create(
			CCDelayTime::create(_delay),
			CCMoveTo::create(_duration, _moveTo), NULL));
		m_CardList[_idx]->m_pCard->runAction(CCSequence::create(
			CCDelayTime::create(_delay),
			CCRotateTo::create(_duration, 0.f),			
			NULL));
	}
	else
	{
		m_CardList[_idx]->m_pCard->runAction(CCSequence::create(
			CCDelayTime::create(_delay),
			CCMoveTo::create(_duration, _moveTo), NULL));
	}
	
}

void CardManager::ActionFadeToCard(int _idx, unsigned int _opacity)
{
	m_CardList[_idx]->m_pCard->runAction(CCFadeTo::create(0.5f, _opacity));
}

void CardManager::ActionSelectedCard(int _idx, bool _cancel)
{

	string _frame1Name = "cardfront_s" + StringConverter::toString(_idx + 1) + "select";

	if (_cancel == false)
	{
		string _frame2Name = "cardfront_s";
		_frame2Name += StringConverter::toString(_idx + 1) + "unselect";

		m_CardList[_idx]->m_pCard->GetCardSkelObj()->playAnimation(_frame1Name);
		m_CardList[_idx]->m_pCard->GetCardSkelObj()->appendAnimation(_frame2Name);
		

		if (LayerManager::getSingletonPtr()->hasLayer("CardOnOffPanel"))
		{
			BettingCardOnOffPanel* _pBettingPanel = dynamic_cast<BettingCardOnOffPanel*>(LayerManager::getSingleton().getLayer("CardOnOffPanel"));
			_pBettingPanel->ShowCancelBtn(_idx, true);

			m_CardList[_idx]->m_pCard->GetCardSkelObj()->runAction(CCFadeTo::create(0.1f, 180));
		}
	}
	else
	{
		m_CardList[_idx]->m_pCard->GetCardSkelObj()->playAnimation(_frame1Name);

		if (LayerManager::getSingletonPtr()->hasLayer("CardOnOffPanel"))
		{
			BettingCardOnOffPanel* _pBettingPanel = dynamic_cast<BettingCardOnOffPanel*>(LayerManager::getSingleton().getLayer("CardOnOffPanel"));
			_pBettingPanel->ShowCancelBtn(_idx, false);
			m_CardList[_idx]->m_pCard->GetCardSkelObj()->runAction(CCFadeTo::create(0.1f, 255));
		}
	}
}

void CardManager::ActionShareMoveCard(int _idx, CCPoint _moveto, bool _rand, float _delay)
{
	ccBezierConfig _bezierConfig;
	_bezierConfig.controlPoint_1 = ccp(512, 350);
	_bezierConfig.controlPoint_2 = ccp(512, 300);
	_bezierConfig.endPosition = _moveto;

	if (LayerManager::getSingletonPtr()->hasLayer("Background"))
	{
		Panel* _prepanel = dynamic_cast<Panel*>(LayerManager::getSingletonPtr()->getLayer("Background"));
		CCPoint _pos = _prepanel->getImage("dmy_dealer")->getPosition();
		_pos.y += 25.f;
		m_CardList[_idx]->m_pCard->setPosition(_pos);
	}
	CCAction* _action = CCSequence::createWithTwoActions(CCDelayTime::create(_delay), CCBezierTo::create(0.3f, _bezierConfig));
	m_CardList[_idx]->m_pCard->runAction(_action);

	m_CardList[_idx]->m_pCard->GetCardSkelObj()->setScale(0.3f);

	m_CardList[_idx]->m_pCard->setVisible(false);
	m_CardList[_idx]->m_pCard->runAction(CCSequence::createWithTwoActions(
		CCDelayTime::create(_delay),
		CCCallFunc::create(m_CardList[_idx]->m_pCard, callfunc_selector(PokerCardWidget::MoveStart))
		));

	if(m_CardList[_idx]->m_pCard->mPokerCardWidgetType == PokerCardWidget::PokerCardWidetSmall && GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind() == GameKind::GAMEKIND_HOLDEM)
	{
		m_CardList[_idx]->m_pCard->GetCardSkelObj()->runAction(CCSequence::create(
			CCDelayTime::create(_delay),
			CCScaleTo::create(0.3f, 0.6f),
			CCScaleTo::create(0.1f, 0.7f),
			NULL));
	}
	else
	{
		m_CardList[_idx]->m_pCard->GetCardSkelObj()->runAction(CCSequence::create(
			CCDelayTime::create(_delay),
			CCScaleTo::create(0.3f, 0.9f),
			CCScaleTo::create(0.1f, 1.f),
			NULL));
	}
	

	//m_CardList[_idx]->m_pCard->SetBack(false);
	if (_rand == true)
	{
		
		float _moveAngle = -15.f + (rand() % 30);
		m_CardList[_idx]->m_pCard->GetCardSkelObj()->setRotation(180);

		if (_idx == 3 && m_UserPo == GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_MyPo)
		{
			auto func = CallFunc::create(CC_CALLBACK_0(CardManager::CallBackCardMoveEnd, this));
			func->setTargetCallback(m_CardList[_idx]->m_pCard->GetCardSkelObj());
			
			m_CardList[_idx]->m_pCard->GetCardSkelObj()->runAction(CCSequence::create(
				CCDelayTime::create(_delay),
				CCRotateTo::create(0.3f, _moveAngle),
				CCDelayTime::create(0.1f),
				func,
				nullptr));
		}
		else
		{
			m_CardList[_idx]->m_pCard->GetCardSkelObj()->runAction(CCSequence::createWithTwoActions(
				CCDelayTime::create(_delay),
				CCRotateTo::create(0.3f, _moveAngle)));
		}		
	}
	else
	{
		m_CardList[_idx]->m_pCard->GetCardSkelObj()->setRotation(180);
		m_CardList[_idx]->m_pCard->GetCardSkelObj()->runAction(CCSequence::createWithTwoActions(
			CCDelayTime::create(_delay),
			CCRotateTo::create(0.3f, 0)));
	}
	

	//m_CardList[_idx]->m_pCard->setScale(0.f);
	//m_CardList[_idx]->m_pCard->runAction(CCScaleTo::create(0.2f, 1.f));
}

void CardManager::CallBackCardMoveEnd()
{
	int _userPo = GameDataManager::getSingletonPtr()->ClientToServerIndex(0);
	GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetPlayerCommonPanel(_userPo)->SetShareEndCard();
}

void CardManager::ActionCardSort()
{
	for (CardData* _card : m_CardList)
	{
		_card->m_pCard->GetCardSkelObj()->runAction(CCRotateTo::create(0.2f, 0.f));
	}
}

void CardManager::ActionFlipCard(int _idx, bool _open, float _delay)
{
	if (_open ==  true)
		m_CardList[_idx]->m_pCard->Action_FlipOpen(_delay);
	else
		m_CardList[_idx]->m_pCard->Action_FlipBack(_delay);
}

void CardManager::ActionAllCloseCard(bool isPlayerOut)
{
	GameDataManager::getSingletonPtr()->PlayGameSound(GameEfxKind::EFX_GAME_CARDFLOP);
	int _size = m_CardList.size();

	for (int _i = _size - 1; _i >= 0; _i--)
	{
		float _delay = 0.1f + (0.05f*(_size-1-_i));
		m_CardList[_i]->m_pCard->stopAllActions();

		CCPoint _cardPos = GetTableCardRect(0).origin;
		_cardPos.x = _cardPos.x + (_i * 15.f);
		m_CardList[_i]->m_pCard->runAction(CCSequence::createWithTwoActions(
			CCDelayTime::create(_delay), CCMoveTo::create(0.2f, _cardPos)));
		m_CardList[_i]->m_pCard->setZOrder(_i);

		GameKind _gameKind = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind();

		if (m_UserIdx > 0 && (_gameKind == GameKind::GAMEKIND_BADUKI || _gameKind == GameKind::GAMEKIND_HOLDEM) 
			&& GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_isReplayData == false)
		{
			m_CardList[_i]->m_pCard->Action_DieCard(_delay);
		}
		else
		{
			m_CardList[_i]->m_pCard->Action_FlipDie(_delay);
		}

		m_CardList[_i]->m_pCard->CardEffectNo();

		if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind() == GameKind::GAMEKIND_BADUKI)
		{
			m_CardList[_i]->m_pCard->CardEffectSelectBoxOff();
		}
	}

	if (isPlayerOut)
		ActionPointer::createDieGameOutEvent(3.f);
}

void CardManager::setActionSpeed()
{
	for (int i = 0; i < m_CardList.size(); i++)
	{
		m_CardList[i]->m_pCard->setVisible(true);			
		m_CardList[i]->m_pCard->setPosition(m_TableCardRect[i].origin);
	}
}

void CardManager::setVisibleCard(bool visible)
{
	for (int i = 0; i < m_CardList.size(); i++)
	{
		m_CardList[i]->m_pCard->setVisible(visible);
	}
}
