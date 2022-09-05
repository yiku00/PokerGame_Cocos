#include "pch.h"
#include "JokboList.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"


JokboList::JokboList()
{
	m_pJokboBox = nullptr;

	m_pHighJokboView = nullptr;
	m_pLowJokboView = nullptr;

	m_HighJokboLabelContainer = nullptr;
	m_LowJokboLabelContainer = nullptr;

	mMainPanel = nullptr;
	mParentPanel = nullptr;

}

JokboList::~JokboList()
{
	removeAllChildren();
}

void JokboList::Init()
{
	//CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	mParentPanel = dynamic_cast<Panel*>(LayerManager::getSingletonPtr()->getLayer("Background"));
	if (mParentPanel)
	{
		if (mMainPanel == nullptr)
		{
			mMainPanel = new Panel();
			mMainPanel->construct(getMxmlPath() + "dmy_record_board.mxml");
			addChild(mMainPanel);
			mMainPanel->release();
			CCSize contentsSize = mMainPanel->getDummy("dmy_record_board").size;
			mMainPanel->setPositionY(contentsSize.height / 2.f - DESIGN_HEIGHT);
			mMainPanel->setPositionX(-contentsSize.width / 2.f);
			mMainPanel->setContentSize(contentsSize);
			this->setContentSize(contentsSize);
			this->setPosition(mParentPanel->getImage("dmy_record_board")->getPosition());

			m_JokboBoardRect = mMainPanel->getDummy("dmy_record_board");

			//족보
			mPokerHandLabel = mMainPanel->getLabel("txt_title1");
			mPokerHand_under_Label = mMainPanel->getLabel("txt_title1_under");
			mPokerHandLabel->setString(GameStringDepot::getSingletonPtr()->getString("JokboList_TITLE").c_str());
			mPokerHand_under_Label->setString(GameStringDepot::getSingletonPtr()->getString("JokboList_TITLE").c_str());
			//하이
			mHighPokerHandLabel = mMainPanel->getLabel("txt_title2");
			mHighPokerHand_under_Label = mMainPanel->getLabel("txt_title2_under");
			mHighPokerHandLabel->setString(GameStringDepot::getSingletonPtr()->getString("JokboList_HI").c_str());
			mHighPokerHand_under_Label->setString(GameStringDepot::getSingletonPtr()->getString("JokboList_HI").c_str());
			//로우
			mLowPokerHandLabel = mMainPanel->getLabel("txt_title3");
			mLowPokerHand_under_Label = mMainPanel->getLabel("txt_title3_under");
			mLowPokerHandLabel->setString(GameStringDepot::getSingletonPtr()->getString("JokboList_LOW").c_str());
			mLowPokerHand_under_Label->setString(GameStringDepot::getSingletonPtr()->getString("JokboList_LOW").c_str());
		}		
	}
	refreshPokerHandsTitle();
	//CCRect _JokboRect = mPokerBackgroundPanel->getDummy("dmy_record_board");
	GameKind _gameKind = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind();
	if (_gameKind == GameKind::GAMEKIND_HIGH_LOW)
	{
		mMainPanel->getSkel("skel_highlow_board")->setVisible(true);
		mMainPanel->getSkel("skel_poker_board")->setVisible(false);
	}
	else
	{
		mMainPanel->getSkel("skel_highlow_board")->setVisible(false);
		mMainPanel->getSkel("skel_poker_board")->setVisible(true);
	}
	
	mMainPanel->getLabel("txt_record1")->setVisible(false);
	mMainPanel->getLabel("txt_record2")->setVisible(false);
	mMainPanel->getLabel("txt_record3")->setVisible(false);
	mMainPanel->getLabel("txt_record4")->setVisible(false);
	mMainPanel->getLabel("txt_record5")->setVisible(false);
	mMainPanel->getLabel("txt_record6")->setVisible(false);
	mMainPanel->getLabel("txt_record7")->setVisible(false);
	mMainPanel->getLabel("txt_record8")->setVisible(false);
	mMainPanel->getLabel("txt_record9")->setVisible(false);
	mMainPanel->getLabel("txt_record10")->setVisible(false);

	if (_gameKind == GameKind::GAMEKIND_BADUKI)
	{
		InitBabukiJokbo();
	}
	else
	{
		InitHighJokbo();
		InitLowJokbo();
	}
	
}

void JokboList::InitBabukiJokbo()
{
	if (m_HighJokboLabelContainer != nullptr)
	{
		if (m_pHighJokboView != nullptr)
		{
			m_pHighJokboView->removeFromParentAndCleanup(true);
		}
		m_pHighJokboView = nullptr;
	}

	m_HighJokboLabelContainer = CCLayer::create();
	CCSize contentsSize = mMainPanel->getDummy("dmy_record_board").size;

	for (int _i = 0; _i < BADUKI_JOKBO_SIZE; _i++)
	{
		m_pBadugiJokboLabel[_i] = new SkelObject();
		m_pBadugiJokboLabel[_i]->setSkelAnim("ui/record_board_8888.json");
		string _frameName = GameDataManager::getSingletonPtr()->GetBadukiJokboFrameName(_i+41, false);
		if (_frameName == "")
		{
			m_pBadugiJokboLabel[_i]->setVisible(false);
		}
		else
		{
			m_pBadugiJokboLabel[_i]->playAnimation(_frameName);
			m_pBadugiJokboLabel[_i]->setVisible(true);
		}

		float _x, _y;

		_x = 40.f + 30.f;
		_y = JOKBO_FONT_HIGHT * BADUKI_JOKBO_SIZE - (JOKBO_FONT_HIGHT*(_i)) - 9.f;
		m_pBadugiJokboLabel[_i]->setPosition(ccp(_x, _y));

		m_HighJokboLabelContainer->addChild(m_pBadugiJokboLabel[_i]);
		m_pBadugiJokboLabel[_i]->release();
	}

	m_HighJokboLabelContainer->setContentSize(CCSizeMake(m_JokboBoardRect.size.width, JOKBO_FONT_HIGHT*BADUKI_JOKBO_SIZE));

	// Setup scroll view
	m_pHighJokboView = CCScrollView::create(CCSizeMake(m_JokboBoardRect.size.width / 2, m_JokboBoardRect.size.height - 22), m_HighJokboLabelContainer);
	m_pHighJokboView->setDirection(ScrollView::Direction::VERTICAL);

	// Scroll to bottom
	m_pHighJokboView->setBounceable(true);

	//스크롤 위치 지정(위치, 3초 애니)
	m_pHighJokboView->setContentOffset(CCPointZero, false);

	m_pHighJokboView->setPositionX(m_JokboBoardRect.origin.x - contentsSize.width / 2.f);
	m_pHighJokboView->setPositionY(m_JokboBoardRect.origin.y - contentsSize.height / 2.f);

	addChild(m_pHighJokboView);
	//m_pHighJokboView->release();
}

void JokboList::InitHighJokbo()
{
	if (m_HighJokboLabelContainer != nullptr)
	{
		if (m_pHighJokboView != nullptr)
		{
			m_pHighJokboView->removeFromParentAndCleanup(true);
		}
		m_pHighJokboView = nullptr;
	}

	m_HighJokboLabelContainer = CCLayer::create();

	//string _fontName = mMainPanel->getLabel("txt_record1")->getFontName();
	//int _fontSize = mMainPanel->getLabel("txt_record1")->getFontSize();

	CCSize contentsSize = mMainPanel->getDummy("dmy_record_board").size;

	for (int _i = 0; _i < HIGH_JOKBO_SIZE; _i++)
	{
		m_pHighJokboLabel[_i] = new SkelObject();
		m_pHighJokboLabel[_i]->setSkelAnim("ui/record_board_8888.json");
		string _frameName = GameDataManager::getSingletonPtr()->GetJokboFrameName((HighJokboKind)_i, false);
		if (_frameName == "")
		{
			m_pHighJokboLabel[_i]->setVisible(false);
		}
		else
		{
			m_pHighJokboLabel[_i]->playAnimation(_frameName);
			m_pHighJokboLabel[_i]->setVisible(true);
		}	

		float _x, _y;

		_x = 40.f + 30.f;
		_y = JOKBO_FONT_HIGHT * HIGH_JOKBO_SIZE - (JOKBO_FONT_HIGHT*(_i)) - 9.f;
		m_pHighJokboLabel[_i]->setPosition(ccp(_x, _y));

		m_HighJokboLabelContainer->addChild(m_pHighJokboLabel[_i]);
		m_pHighJokboLabel[_i]->release();
	}

	m_HighJokboLabelContainer->setContentSize(CCSizeMake(m_JokboBoardRect.size.width, JOKBO_FONT_HIGHT*HIGH_JOKBO_SIZE));

	// Setup scroll view
	m_pHighJokboView = CCScrollView::create(CCSizeMake(m_JokboBoardRect.size.width / 2, m_JokboBoardRect.size.height - 22), m_HighJokboLabelContainer);
	m_pHighJokboView->setDirection(ScrollView::Direction::VERTICAL);
	
	// Scroll to bottom
	m_pHighJokboView->setBounceable(true);

	//스크롤 위치 지정(위치, 3초 애니)
	m_pHighJokboView->setContentOffset(CCPointZero, false);

	m_pHighJokboView->setPositionX(m_JokboBoardRect.origin.x - contentsSize.width / 2.f);
	m_pHighJokboView->setPositionY(m_JokboBoardRect.origin.y - contentsSize.height / 2.f);

	addChild(m_pHighJokboView);
	//m_pHighJokboView->release();

}

void JokboList::InitLowJokbo()
{
	if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind() != GameKind::GAMEKIND_HIGH_LOW)
		return;

	if (m_LowJokboLabelContainer != nullptr)
	{
		if (m_pLowJokboView != nullptr)
		{
			m_pLowJokboView->removeFromParentAndCleanup(true);
		}

		m_pLowJokboView = nullptr;
	}

	m_LowJokboLabelContainer = CCLayer::create();

	// 일단 주석을 달아줍니다.... 안쓰는 것 같아서!
	//string _fontName = mMainPanel->getLabel("txt_record1")->getFontName();
	//int _fontSize = mMainPanel->getLabel("txt_record1")->getFontSize();

	CCSize contentsSize = mMainPanel->getDummy("dmy_record_board").size;

	for (int _i = 0; _i < LOW_JOKBO_SIZE; _i++)
	{
		m_pLowJokboLabel[_i] = new SkelObject();
		m_pLowJokboLabel[_i]->setSkelAnim("ui/record_board_8888.json");
		string _frameName;
		if (_i > 2)
		{
			_frameName = GameDataManager::getSingletonPtr()->GetJokboFrameName((LowJokboKind)_i + 18, false);
		}
		else
		{
			_frameName = GameDataManager::getSingletonPtr()->GetJokboFrameName((LowJokboKind)_i, false);
		}

		if (_frameName == "")
		{
			m_pLowJokboLabel[_i]->setVisible(false);
		}
		else
		{
			m_pLowJokboLabel[_i]->playAnimation(_frameName);
			m_pLowJokboLabel[_i]->setVisible(true);
		}
		m_pLowJokboLabel[_i]->setAnchorPoint(ccp(0.f, 0.5f));

		float _x, _y;

		_x = 40.f + 30.f;
		_y = JOKBO_FONT_HIGHT * LOW_JOKBO_SIZE - (JOKBO_FONT_HIGHT*(_i)) - 9.f;
		m_pLowJokboLabel[_i]->setPosition(ccp(_x, _y));

		m_pLowJokboLabel[_i]->setTag(1);
		m_LowJokboLabelContainer->addChild(m_pLowJokboLabel[_i]);
		m_pLowJokboLabel[_i]->setVisible(true);
		m_pLowJokboLabel[_i]->autorelease();
	}

	m_LowJokboLabelContainer->setContentSize(CCSizeMake(m_JokboBoardRect.size.width, JOKBO_FONT_HIGHT*LOW_JOKBO_SIZE));

	// Setup scroll view
	m_pLowJokboView = CCScrollView::create(CCSizeMake(m_JokboBoardRect.size.width / 2, m_JokboBoardRect.size.height - 22), m_LowJokboLabelContainer);
	m_pLowJokboView->setDirection(ScrollView::Direction::VERTICAL);
	// Scroll to bottom
	m_pLowJokboView->setBounceable(true);

	//스크롤 위치 지정(위치, 3초 애니)
	m_pLowJokboView->setContentOffset(CCPointZero, false);

	m_pLowJokboView->setPositionX(m_JokboBoardRect.origin.x - contentsSize.width / 2.f + (m_JokboBoardRect.size.width / 2.f));
	m_pLowJokboView->setPositionY(m_JokboBoardRect.origin.y - contentsSize.height / 2.f);

	addChild(m_pLowJokboView);
}

void JokboList::ShowBadugiLabel(int _index)
{
	if (_index == -1)
	{
		m_pHighJokboView->setContentOffset(CCPointZero, false);
		string _frameName;
		for (int _i = 0; _i < BADUKI_JOKBO_SIZE; _i++)
		{
			_frameName = GameDataManager::getSingletonPtr()->GetBadukiJokboFrameName(_i + 41, false);
			if (_frameName == "")
			{
				m_pBadugiJokboLabel[_i]->setVisible(false);
			}
			else
			{
				m_pBadugiJokboLabel[_i]->playAnimation(_frameName);
				m_pBadugiJokboLabel[_i]->setVisible(true);
			}
		}
		return;
	}

	string _frameName;
	for (int _i = 0; _i < BADUKI_JOKBO_SIZE; _i++)
	{
		bool _show = (_index - 41 == _i);
		_frameName = GameDataManager::getSingletonPtr()->GetBadukiJokboFrameName(_i + 41, _show);
		if (_frameName == "")
		{
			m_pBadugiJokboLabel[_i]->setVisible(false);
		}
		else
		{
			m_pBadugiJokboLabel[_i]->playAnimation(_frameName);
			m_pBadugiJokboLabel[_i]->setVisible(true);
		}
	}

	int _value = _index - 41 - BADUKI_JOKBO_SIZE + 3;

	if (_value > 0)
	{
		_value = 0;
	}

	if (_value < 5 - BADUKI_JOKBO_SIZE)
	{
		_value = 5 - BADUKI_JOKBO_SIZE;
	}
	float _y;

	_y = JOKBO_FONT_HIGHT * _value;

	m_pHighJokboView->setContentOffset(ccp(0.f, _y), true);


}

void JokboList::ShowHighLabel(int _index)
{
	if (_index == -1)
	{
		m_pHighJokboView->setContentOffset(CCPointZero, false);
		string _frameName;
		for (int _i = 0; _i < HIGH_JOKBO_SIZE; _i++)
		{
			_frameName = GameDataManager::getSingletonPtr()->GetJokboFrameName((HighJokboKind)_i, false);
			if (_frameName == "")
			{
				m_pHighJokboLabel[_i]->setVisible(false);
			}
			else
			{
				m_pHighJokboLabel[_i]->playAnimation(_frameName);
				m_pHighJokboLabel[_i]->setVisible(true);
			}
		}
		return;
	}
	
	string _frameName;
	for (int _i = 0; _i < HIGH_JOKBO_SIZE; _i++)
	{
		bool _show = (_index == _i);
		_frameName = GameDataManager::getSingletonPtr()->GetJokboFrameName((HighJokboKind)_i, _show);
		if (_frameName == "")
		{
			m_pHighJokboLabel[_i]->setVisible(false);
		}
		else
		{
			m_pHighJokboLabel[_i]->playAnimation(_frameName);
			m_pHighJokboLabel[_i]->setVisible(true);
		}
	}

	int _value = _index - HIGH_JOKBO_SIZE + 3;

	if (_value > 0)
	{
		_value = 0;
	}

	if (_value < 5 - HIGH_JOKBO_SIZE)
	{
		_value = 5 - HIGH_JOKBO_SIZE;
	}
	float _y;

	_y = JOKBO_FONT_HIGHT * _value;

	m_pHighJokboView->setContentOffset(ccp(0.f, _y), true);
	

}
void JokboList::ShowLowLabel(int _index)
{
	if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind() != GameKind::GAMEKIND_HIGH_LOW)
		return;

	if (_index == -1)
	{
		m_pLowJokboView->setContentOffset(CCPointZero, false);

		string _frameName;
		for (int _i = 0; _i < LOW_JOKBO_SIZE; _i++)
		{
			if (_i > 2)
			{
				_frameName = GameDataManager::getSingletonPtr()->GetJokboFrameName((LowJokboKind)_i + 18, false);
			}
			else
			{
				_frameName = GameDataManager::getSingletonPtr()->GetJokboFrameName((LowJokboKind)_i, false);
			}

			if (_frameName == "")
			{
				m_pLowJokboLabel[_i]->setVisible(false);
			}
			else
			{
				m_pLowJokboLabel[_i]->playAnimation(_frameName);
				m_pLowJokboLabel[_i]->setVisible(true);
			}
		}
		return;
	}

	int _idx = _index;
	if (_idx > 30)
	{
		_idx = 31;
	}

	string _frameName;
	for (int _i = 0; _i < LOW_JOKBO_SIZE; _i++)
	{
		bool _show;
		if (_i > 2)
		{
			_show = (_idx == _i + 18);
			_frameName = GameDataManager::getSingletonPtr()->GetJokboFrameName((LowJokboKind)_i + 18, _show);
		}
		else
		{
			_show = (_idx == _i);
			_frameName = GameDataManager::getSingletonPtr()->GetJokboFrameName((LowJokboKind)_i, _show);
		}

		if (_frameName == "")
		{
			m_pLowJokboLabel[_i]->setVisible(false);
		}
		else
		{
			m_pLowJokboLabel[_i]->playAnimation(_frameName);
			m_pLowJokboLabel[_i]->setVisible(true);
		}
	}

	if (_idx > 2)
	{
		_idx -= 18;
	}

	int _value = _idx - LOW_JOKBO_SIZE + 3;

	if (_value > 0)
	{
		_value = 0;
	}

	if (_value < 5 - LOW_JOKBO_SIZE)
	{
		_value = 5 - LOW_JOKBO_SIZE;
	}

	float _y;

	_y = JOKBO_FONT_HIGHT * _value;

	m_pLowJokboView->setContentOffset(ccp(0.f, _y), true);

}

void JokboList::refreshPokerHandsTitle()
{
	mHighPokerHandLabel->setVisible(false);
	mHighPokerHand_under_Label->setVisible(false);
	mLowPokerHandLabel->setVisible(false);
	mLowPokerHand_under_Label->setVisible(false);
	mPokerHandLabel->setVisible(false);
	mPokerHand_under_Label->setVisible(false);
	GameKind _gameKind = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind();
	if (_gameKind == GameKind::GAMEKIND_HIGH_LOW) {
		mHighPokerHandLabel->setVisible(true);
		mHighPokerHand_under_Label->setVisible(true);
		mLowPokerHandLabel->setVisible(true);
		mLowPokerHand_under_Label->setVisible(true);
	}
	else {
		mPokerHandLabel->setVisible(true);
		mPokerHand_under_Label->setVisible(true);
	}
}
