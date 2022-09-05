                                                                                                                                                             #include "pch.h"
#include "ChannelCell.h"

#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "CustomPopupPanel.h"
#include "GameStringDepot.h"

ChannelCell::ChannelCell()
{
	m_CellInfo = nullptr;

	InitPanel();
	InitImage();
	initButton();

	setTouchable(false);
	setButtonListener(this);
}

ChannelCell::~ChannelCell()
{
	//destruct();
}

void ChannelCell::InitPanel()
{
	construct(getMxmlPath() + "dmy_channel_button.mxml");
}

void ChannelCell::InitImage()
{
	m_labelUserCount = getLabel("txt_channel_usernumber");
	m_labelSeedmoney = getLabel("txt_seed_money");
	m_labelTitle = getLabel("txt_channel_title");

	m_labelTitle->setAnchorPoint(ccp(0.f, LABEL_ANCHOR_OFFSET));
	m_labelSeedmoney->setAnchorPoint(ccp(0.f, LABEL_ANCHOR_OFFSET));
	m_labelUserCount->setAnchorPoint(ccp(0.f, LABEL_ANCHOR_OFFSET));
}

void ChannelCell::initButton()
{
	m_btnChannel = getButton("sbtn_channel_button");
	m_btnChannel->setType(Button::NoPressImg);
	m_btnChannel->setPaused(true);
}


bool ChannelCell::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	
	return false;
}


void ChannelCell::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	
}


void ChannelCell::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	
}

void ChannelCell::resume()
{
}

void ChannelCell::onClicked(const string& name)
{
	if (name == "sbtn_channel_button")
	{
		return;
	}
}

void ChannelCell::update(float dt)
{
}

bool ChannelCell::handling(STCMD &stCmd)
{
	return false;
}

void ChannelCell::SetCellData(W_ChannelInfo* _pInfo)
{
	m_CellInfo = _pInfo;
	m_labelTitle->setString(m_CellInfo->name().c_str());
	//m_labelTitleUnder->setString(m_CellInfo->name().c_str());

	string _seedMoney = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(m_CellInfo->seedmoney()));
	m_labelSeedmoney->setString(_seedMoney.c_str());

	string _userCount = StringConverter::toString(m_CellInfo->usercount()) + GameStringDepot::getSingletonPtr()->getString("TXT_PEOPLE_COUNT");
	m_labelUserCount->setString(_userCount.c_str());

	if (m_CellInfo->overmoney() == 0)
	{
		if (m_CellInfo->undermoney() > GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney)
		{
			m_btnChannel->setEnable(false);

		}
		else
		{
			m_btnChannel->setEnable(true);
		}

	}
	else if (m_CellInfo->undermoney() > GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney
		|| m_CellInfo->overmoney() < GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney)
	{
		m_btnChannel->setEnable(false);
	}
	else
	{
		m_btnChannel->setEnable(true);
	}

	string _frameName1 = "";
	string _frameName2 = "";


	ccColor3B unlockTabColor;
	ccColor3B lockTabColor = { 109, 109, 109 };	//잠겨있는거 선택시
	ccColor3B unlockTitleColor;	//오픈될을때 타이틀 색깔 마카오 라스베가스등
	ccColor3B lockTitleColor = { 151,151,151 };	//잠겨있는거 선택시
	

	switch (m_CellInfo->gamekind())
	{
	case GameKind::GAMEKIND_7POKER:
		unlockTabColor = { 235, 122, 122 };
		unlockTitleColor = { 255,241,233 };
		_frameName1 = "seven_";
		_frameName2 = "lock_saven";
		break;
	case GameKind::GAMEKIND_HIGH_LOW:
		unlockTabColor = { 111, 151, 224 };
		unlockTitleColor = { 233,246,255 };
		_frameName1 = "highlow_";
		_frameName2 = "lock_highlow";
		break;
	case GameKind::GAMEKIND_BADUKI:
		unlockTabColor = { 128, 228, 114 };
		unlockTitleColor = { 243,255,233 };
		_frameName1 = "badugi_";
		_frameName2 = "lock_badugi";
		break;
	case GameKind::GAMEKIND_HOLDEM:
		unlockTabColor = { 105, 228, 212 };
		unlockTitleColor = { 233,255,255 };
		_frameName1 = "texas_";
		_frameName2 = "lock_texas";
		break;
	}

	if (m_btnChannel->isEnabled())
	{
		getSkel("skel_lock")->setVisible(false);
		_frameName1 += "stay";

		m_labelSeedmoney->setColor(unlockTabColor);
		m_labelUserCount->setColor(unlockTabColor);
		m_labelTitle->setColor(unlockTitleColor);
	}
	else
	{
		getSkel("skel_lock")->setVisible(true);
		_frameName1 += "stayoff";
		m_labelSeedmoney->setColor(lockTabColor);
		m_labelUserCount->setColor(lockTabColor);
		m_labelTitle->setColor(lockTitleColor);
	}

	m_btnChannel->getButtonSkelObject()->playAnimation(_frameName1, true);
	getSkel("skel_lock")->playAnimation(_frameName2);
	//if (m_btnChannel->isEnabled() == false)
	//{
	//	m_btnChannel->getButtonSkelObject()->setSkin("channel_off");
	//}
	//else if (m_CellInfo->gamekind() == GAMEKIND_7POKER)
	//{
	//	m_btnChannel->getButtonSkelObject()->setSkin("seven_poker");
	//}
	//else if(m_CellInfo->gamekind() == GAMEKIND_HIGH_LOW)
	//{
	//	m_btnChannel->getButtonSkelObject()->setSkin("highlow");
	//}
	//else if (m_CellInfo->gamekind() == GAMEKIND_BADUKI)
	//{
	//	m_btnChannel->getButtonSkelObject()->setSkin("badugi");
	//}
	//else if (m_CellInfo->gamekind() == GAMEKIND_HOLDEM)
	//{
	//	m_btnChannel->getButtonSkelObject()->setSkin("texasholdem");
	//}

	//int _ChanelGrade = m_CellInfo->grade() % 20;

	//if (m_btnChannel->isEnabled() == false)
	//{
	//	m_btnChannel->getButtonSkelObject()->playAnimation("channel_off_stay");
	//}
	//else if (_ChanelGrade == 8 || _ChanelGrade == 9 )
	//{
	//	m_btnChannel->getButtonSkelObject()->playAnimation("channel_silver_stay");
	//}
	//else if (_ChanelGrade == 10 )
	//{
	//	m_btnChannel->getButtonSkelObject()->playAnimation("channel_gold_stay");
	//}
	//else if (_ChanelGrade == 18 || _ChanelGrade == 19)
	//{
	//	m_btnChannel->getButtonSkelObject()->playAnimation("channel_free_stay");
	//}
	//else
	//{
	//	m_btnChannel->getButtonSkelObject()->playAnimation("channel_normal_stay");
	//}

	//string _landmark = "landmark_cruise";
	//switch (_ChanelGrade)
	//{
	//case 0:
	//	_landmark = "landmark_cruise";
	//	break;
	//case 1:
	//	_landmark = "landmark_Kangwon";
	//	break;
	//case 2:
	//case 3:
	//	_landmark = "landmark_Sydney";
	//	break;
	//case 4:
	//case 5:
	//	_landmark = "landmark_Atlantic";
	//	break;
	//case 6:
	//case 7:
	//	_landmark = "landmark_Paris";
	//	break;
	//case 8:
	//case 9:
	//	_landmark = "landmark_Macao";
	//	break;
	//case 10:
	//	_landmark = "landmark_lasvegas";
	//	break;
	//case 18:
	//case 19:
	//	_landmark = "landmark_cruise";
	//	break;
	//}

	//
	//if (m_btnChannel->isEnabled() == false)
	//{
	//	_landmark += "_off";
	//}

	//m_Landmark->playAnimation(_landmark);

}