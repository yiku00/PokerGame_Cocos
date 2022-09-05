#include "pch.h"
#include "PotMoneyPanel.h"
#include "PokerCardWidget.h"
#include "PokerChipWidget.h"
#include "GameDataManager.h"

#define MOVE_POT_MONEY_ANITIME 1.8f

PotMoneyPanel::PotMoneyPanel()
{
	mMainPanel = nullptr;
	Init();
}
PotMoneyPanel::~PotMoneyPanel()
{
	//ClearPotMoney();
	if(mMainPanel)
		mMainPanel->removeAllChildren(); 
	removeAllChildren();

}
void PotMoneyPanel::Init()
{
	mParentPanel = dynamic_cast<Panel*>(LayerManager::getSingletonPtr()->getLayer("Background"));
	if (mParentPanel)
	{
		mMainPanel = new Panel();
		if (GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_HOLDEM)
		{
			mMainPanel->construct(getMxmlPath() + "dmy_texasholdem_chip_position.mxml");
			addChild(mMainPanel);
			mMainPanel->release();
			CCSize contentsSize = mMainPanel->getDummy("dmy_texasholdem_chip_position").size;
			mMainPanel->setPositionY(contentsSize.height / 2.f - DESIGN_HEIGHT);
			mMainPanel->setPositionX(-contentsSize.width / 2.f);
			mMainPanel->setContentSize(contentsSize);
			this->setContentSize(contentsSize);
			this->setPosition(mParentPanel->getImage("dmy_texasholdem_chip_position")->getPosition());
		}
		else
		{
			mMainPanel->construct(getMxmlPath() + "dmy_chip_position.mxml");
			addChild(mMainPanel);
			mMainPanel->release();
			CCSize contentsSize = mMainPanel->getDummy("dmy_chip_position").size;
			mMainPanel->setPositionY(contentsSize.height / 2.f - DESIGN_HEIGHT);
			mMainPanel->setPositionX(-contentsSize.width / 2.f);
			mMainPanel->setContentSize(contentsSize);
			this->setContentSize(contentsSize);
			this->setPosition(mParentPanel->getImage("dmy_chip_position")->getPosition());
		}

		
	}
	m_Money = 0;
}
void PotMoneyPanel::onUpdate(float dt)
{

}
void PotMoneyPanel::SetMoney(int64 _money)
{
	m_Money = _money;
	runAction(CCSequence::create(
		CCDelayTime::create(1.2f),
		CCCallFunc::create(this, callfunc_selector(PotMoneyPanel::SetPotMoneyPosition)),
		NULL));

}
void PotMoneyPanel::ClearPotMoney()
{
	m_Money = 0;
	int _size = m_potChipList.size();
	for (int _i = 0; _i < _size; _i++)
	{
		if (m_potChipList[0] == nullptr)
			return;

		//m_potChipList[0]->cleanup();
		//m_potChipList[0]->removeFromParent();
		m_potChipList[0]->removeFromParentAndCleanup(true);

		vector<SkelObject*>::iterator _itor = m_potChipList.begin();
		m_potChipList.erase(_itor);
	}
	m_potChipList.clear();
}
void PotMoneyPanel::ActionWinnerTakeAll(float _delay)
{
	runAction(CCSequence::create(
		CCDelayTime::create(_delay),
		CCCallFunc::create(this, callfunc_selector(PotMoneyPanel::ClearPotMoney)),
		NULL));
}

void PotMoneyPanel::Action_MovePotMoney(int64 _money, CCPoint _moveTo, float _duration)
{
	//실행 전에 기존의 칩은 제거한 상태에서 실행할 것
	//ex>	ClearPotMoney();
	//		Action_MovePotMoney()
	//		Action_MovePotMoney()
	//		Action_MovePotMoney()
	//		......ActionWinnerTakeAll();

	Layer* _CardLayer = LayerManager::getSingletonPtr()->getLayer("CardLayer");

	int _kind = log10(_money);

	CCPoint _orisin;
	if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind() == GameKind::GAMEKIND_HOLDEM)
	{
		_orisin = mMainPanel->getImage("dmy_chip_size8")->getPosition();
	}
	else
	{
		_orisin = mMainPanel->getImage("dmy_chip_size1")->getPosition();
	}

	CCPoint _moveBy = _moveTo - (_orisin + getPosition() + mMainPanel->getPosition());

	for (int _i = 0; _i < _kind + 1; _i++)
	{
		int _count = 0;
		if (_i == 0)
		{
			_count = _money % 10;
		}
		else
		{
			_count = (_money / (int64)pow(10, _i)) % 10;
		}

		if (_count == 0)
			continue;

		CCPoint _position = mMainPanel->getImage("dmy_chip_size" + StringConverter::toString(_kind + 1 - _i))->getPosition();
		//CCPoint _moveBy = _moveTo - (_position + getPosition() + mMainPanel->getPosition());

		//if (_count == 9)
		//{
		//	SkelObject* _potChip = new SkelObject();
		//	_potChip->setSkelAnim("ui/poker_chip_8888.json");
		//	_potChip->setPosition(_position + getPosition() + mMainPanel->getPosition());
		//	_potChip->playAnimation(GetChipKind(_i, _count));
		//	_CardLayer->addChild(_potChip, 14);
		//	_potChip->release();
		//	m_potChipList.push_back(_potChip);
		//	
		//	_potChip->runAction(CCSequence::create(
		//		CCDelayTime::create(0.2f),
		//		CCMoveBy::create(0.2f, _moveBy),
		//		CCDelayTime::create(0.8f),
		//		CCFadeOut::create(0.4f),
		//		NULL));
		//	_potChip->runAction(CCSequence::create(
		//		CCDelayTime::create(1.2f),
		//		CCMoveBy::create(0.4f, ccp(0,50)),
		//		NULL));
		//}
		//else
		{
			//string _chipName = GetChipKind(_i, _count);
			string _chipName = GetChipKind(_i, 1);
			for (int _cnt = 0; _cnt < _count; _cnt++)
			{
				SkelObject* _potChip = new SkelObject();
				_potChip->setSkelAnim("ui/poker_chip_8888.json");
				_potChip->setPositionX(_position.x + getPositionX() + mMainPanel->getPositionX());
				_potChip->setPositionY(_position.y + getPositionY() + mMainPanel->getPositionY() + (_cnt * 4));
				_potChip->playAnimation(_chipName);
				_CardLayer->addChild(_potChip, 14);
				_potChip->release();
				m_potChipList.push_back(_potChip);

				CCPoint _chipPos = _potChip->getPosition();
				CCPoint _movePos = _moveBy + _chipPos;

				_potChip->runAction(CCSequence::create(
					CCDelayTime::create(0.2f),
					CCMoveTo::create(0.2f, _movePos),
					CCDelayTime::create(0.8f),
					CCFadeOut::create(0.4f),
					NULL));
				_potChip->runAction(CCSequence::create(
					CCDelayTime::create(1.2f),
					CCMoveBy::create(0.4f, ccp(0, 50)),
					NULL));
			}
		}

	}
}

void PotMoneyPanel::SetPotMoneyPosition()
{
	if (LayerManager::getSingletonPtr()->hasLayer("CardLayer") == false)
		return;

	Layer* _CardLayer = LayerManager::getSingletonPtr()->getLayer("CardLayer");
	
	if (_CardLayer == nullptr)
		return;



	int _size = m_potChipList.size();
	for (int _i = 0; _i < _size; _i++)
	{
		if (m_potChipList[0] == nullptr)
			return;

		m_potChipList[0]->cleanup();
		m_potChipList[0]->removeFromParent();

		vector<SkelObject*>::iterator _itor = m_potChipList.begin();
		m_potChipList.erase(_itor);
	}

	int _kind = log10(m_Money);
	int _minKind = 0;

	if (_kind > 13)
	{
		_minKind = _kind - 13;
	}

	for (int _i = _minKind; _i < _kind + 1; _i++)
	{
		int _count = 0;
		if (_i == 0)
		{
			_count = m_Money % 10;
		}
		else
		{
			_count = (m_Money / (int64)pow(10, _i)) % 10;
		}

		if (_count == 0)
			continue;
		else if (_count == 9)
		{
			CCPoint _position = mMainPanel->getImage("dmy_chip_size" + StringConverter::toString(_kind + 1 - _i))->getPosition();
			
			SkelObject* _chipShadow = new SkelObject();
			_chipShadow->setSkelAnim("ui/poker_chip_8888.json");
			//_chipShadow->setPosition(_position);
			_chipShadow->setPosition(_position + getPosition() + mMainPanel->getPosition());
			_chipShadow->playAnimation("chipshadow_9");
			//mMainPanel->addChild(_chipShadow);
			_CardLayer->addChild(_chipShadow, 1);
			_chipShadow->release();
			m_potChipList.push_back(_chipShadow);

			//CCRect _rect = getDummy("dmy_chip_size" + StringConverter::toString(_kind + 1 - _i));
			SkelObject* _potChip = new SkelObject();
			_potChip->setSkelAnim("ui/poker_chip_8888.json");
			//_potChip->setPosition(_position);
			_potChip->setPosition(_position + getPosition() + mMainPanel->getPosition());
			_potChip->playAnimation(GetChipKind(_i, _count));
			//mMainPanel->addChild(_potChip);
			_CardLayer->addChild(_potChip, 1);
			_potChip->release();
			m_potChipList.push_back(_potChip);
		}
		else
		{
			CCPoint _position = mMainPanel->getImage("dmy_chip_size" + StringConverter::toString(_kind + 1 - _i))->getPosition();

			SkelObject* _chipShadow = new SkelObject();
			_chipShadow->setSkelAnim("ui/poker_chip_8888.json");
			//_chipShadow->setPosition(_position);
			_chipShadow->setPosition(_position + getPosition() + mMainPanel->getPosition());
			_chipShadow->playAnimation("chipshadow_" + StringConverter::toString(_count));
			//mMainPanel->addChild(_chipShadow);
			_CardLayer->addChild(_chipShadow, 1);
			_chipShadow->release();
			m_potChipList.push_back(_chipShadow);

			//CCRect _rect = getDummy("dmy_chip_size" + StringConverter::toString(_kind + 1 - _i));
			string _chipName = GetChipKind(_i, _count);
			for (int _cnt = 0; _cnt < _count; _cnt++)
			{
				SkelObject* _potChip = new SkelObject();
				_potChip->setSkelAnim("ui/poker_chip_8888.json");
				//_potChip->setPositionX(_position.x);
				//_potChip->setPositionY(_position.y + (_cnt * 4));
				_potChip->setPositionX(_position.x + getPositionX() + mMainPanel->getPositionX());
				_potChip->setPositionY(_position.y + getPositionY() + mMainPanel->getPositionY() + (_cnt * 4));
				_potChip->playAnimation(_chipName);
				//mMainPanel->addChild(_potChip);
				_CardLayer->addChild(_potChip, 1);
				_potChip->release();
				m_potChipList.push_back(_potChip);
			}
		}
	}
}

string PotMoneyPanel::GetChipKind(int _kind, int _count)
{
	string _FrameName = "";

	int _idx;
	if (_kind == 0)
		_idx = 0;
	else
		_idx = _kind / 4;

	switch (_idx)
	{
	case 0:
		_FrameName = "green_0";
		break;
	case 1:
		_FrameName = "red_0";
		break;
	case 2:
		_FrameName = "blue_0";
		break;
	case 3:
		_FrameName = "yellow_0";
		break;
	case 4:
		_FrameName = "black_0";
		break;
	}

	_idx = _kind % 4;

	if (_count == 9)
	{
		_FrameName += StringConverter::toString(_idx + 5);
	}
	else
	{
		_FrameName += StringConverter::toString(_idx + 1);
	}

	return _FrameName;
}