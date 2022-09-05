#include "pch.h"
#include "JackpotPanel.h"
#include "PokerCardWidget.h"
#include "GameDataManager.h"
#include "PokerChipWidget.h"

#define MOVE_POT_MONEY_ANITIME 1.8f

JackpotPanel::JackpotPanel()
{
	Init();
}
JackpotPanel::~JackpotPanel()
{
	m_pJackpotTop->subEventListener(this);
	m_pJackpotBottom->subEventListener(this);
	mMainPanel->removeAllChildren();

	removeAllChildren();
}
void JackpotPanel::Init()
{
	mParentPanel = dynamic_cast<Panel*>(LayerManager::getSingletonPtr()->getLayer("Background"));
	if (mParentPanel)
	{
		mMainPanel = new Panel();
		mMainPanel->construct(getMxmlPath() + "dmy_jackpot.mxml");
		addChild(mMainPanel, 10);
		mMainPanel->release();
		CCSize contentsSize = mMainPanel->getDummy("dmy_jackpot").size;
		mMainPanel->setPositionY(contentsSize.height / 2.f - DESIGN_HEIGHT);
		mMainPanel->setPositionX(-contentsSize.width / 2.f);
		mMainPanel->setContentSize(contentsSize);
		this->setContentSize(contentsSize);
		this->setPosition(mParentPanel->getImage("dmy_jackpot")->getPosition());
	}

	m_pJackpotBottom = mMainPanel->getSkel("skel_jackpot_bottom");
	m_pJackpotBottom->pauseAnimation();
	m_pJackpotBottom->addEventListener(this);

	m_pJackpotTop = mMainPanel->getSkel("skel_jackpot_top");
	m_pJackpotTop->pauseAnimation();
	m_pJackpotTop->addEventListener(this);

	for (int _i = 0; _i < 5; _i++)
	{
		m_pCard[_i] = mMainPanel->getSkel("skel_card" + StringConverter::toString(_i + 1));
		m_pCard[_i]->pauseAnimation();
	}

	InitImage();

	m_dTime = 0.f;
	m_bMakeGoldChip = false;
}

void JackpotPanel::InitImage()
{
	//init Image
	m_pJackpotBottom->setVisible(false);
	m_pJackpotTop->setVisible(false);

	for (int _i = 0; _i < 5; _i++)
	{
		m_pCard[_i]->setVisible(false);
	}
}


void JackpotPanel::OnUpdate(float _dt)
{
	if (!m_bMakeGoldChip)
		return;

	m_dTime += _dt;
	if (m_dTime >= 0.02f)
	{
		PokerChipWidget::createGoldChip(1, 0.1f);
		m_dTime = 0.f;
	}
}


void JackpotPanel::StartJackpotAnimation(int _kind)
{
	m_JokboKind = _kind;
	int _cardCount = 0;
	switch (_kind)
	{
	case HighJokboKind::HIGH_ROYAL_STRAIGHT_FLUSH:
		m_pJackpotTop->playAnimation("royalstraight_start");
		m_pJackpotTop->appendAnimation("royalstraight_loop");
		m_pJackpotTop->appendAnimation("royalstraight_end");

		m_pJackpotBottom->playAnimation("royalstraight_start");
		m_pJackpotBottom->appendAnimation("royalstraight_loop");
		m_pJackpotBottom->appendAnimation("royalstraight_end");
		break;
	case HighJokboKind::HIGH_STRAIGHT_FLUSH:
		m_pJackpotTop->playAnimation("straight_start");
		m_pJackpotTop->appendAnimation("straight_loop");
		m_pJackpotTop->appendAnimation("straight_end");

		m_pJackpotBottom->playAnimation("straight_start");
		m_pJackpotBottom->appendAnimation("straight_loop");
		m_pJackpotBottom->appendAnimation("straight_end");
		break;
	case HighJokboKind::HIGH_FOUR_CARD:
		m_pJackpotTop->playAnimation("four_start");
		m_pJackpotTop->appendAnimation("four_loop");
		m_pJackpotTop->appendAnimation("four_end");

		m_pJackpotBottom->playAnimation("four_start");
		m_pJackpotBottom->appendAnimation("four_loop");
		m_pJackpotBottom->appendAnimation("four_end");

		_cardCount = 1;
		break;
	case LowJokboKind::BADUKI_GOLF:
		m_pJackpotTop->playAnimation("golf_start");
		m_pJackpotTop->appendAnimation("golf_loop");
		m_pJackpotTop->appendAnimation("golf_end");

		m_pJackpotBottom->playAnimation("golf_start");
		m_pJackpotBottom->appendAnimation("golf_loop");
		m_pJackpotBottom->appendAnimation("golf_end");
		_cardCount = 1;
		break;
	case LowJokboKind::BADUKI_SECOND:
		m_pJackpotTop->playAnimation("second_start");
		m_pJackpotTop->appendAnimation("second_loop");
		m_pJackpotTop->appendAnimation("second_end");

		m_pJackpotBottom->playAnimation("second_start");
		m_pJackpotBottom->appendAnimation("second_loop");
		m_pJackpotBottom->appendAnimation("second_end");
		_cardCount = 1;
		break;
	case LowJokboKind::BADUKI_THIRD:
		m_pJackpotTop->playAnimation("third_start");
		m_pJackpotTop->appendAnimation("third_loop");
		m_pJackpotTop->appendAnimation("third_end");

		m_pJackpotBottom->playAnimation("third_start");
		m_pJackpotBottom->appendAnimation("third_loop");
		m_pJackpotBottom->appendAnimation("third_end");
		_cardCount = 1;
		break;
	}

	m_pJackpotBottom->setVisible(true);
	m_pJackpotTop->setVisible(true);

	for (int _i = _cardCount; _i < 5; _i++)
	{
		m_pCard[_i]->setVisible(true);
	}

	setVisible(true);
	
}


void JackpotPanel::onEvent(int trackIdx, spEvent* event)
{
	string _EventName = event->data->name;
	if (_EventName == "card_summon")
	{
		for (int _i = 0; _i < 5; _i++)
		{
			m_pCard[_i]->playAnimation("jackpot_"+ StringConverter::toString(_i+1) +"_start");
		}
	}
	else if (_EventName == "card_end")
	{
		for (int _i = 0; _i < 5; _i++)
		{
			m_pCard[_i]->playAnimation("jackpot_" + StringConverter::toString(_i+1) + "_end");
		}
	}
	else if (_EventName == "gold_summon")
	{
		m_bMakeGoldChip = true;
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_SLOTCOIN, true, true);
	}
	else if (_EventName == "gold_end")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_SLOTCOIN, false);
		m_bMakeGoldChip = false;
		m_dTime = 0.f;
	}
	else if (_EventName == "bonus_summon") {
		GameDataManager::getSingleton().m_GameRoomInfo->playJackpotBonusPanel();
	}
}

void JackpotPanel::SetCard(int _idx, const string _skinName)
{
	if (_idx < 0 && _idx >= 5)
		return;

	m_pCard[_idx]->setSkin(_skinName);
	m_pCard[_idx]->setVisible(false);
}
