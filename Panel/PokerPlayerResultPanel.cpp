#include "pch.h"
#include "PokerResultPanel.h"
#include "GameDataManager.h"
#include "RefDefine.h"
#include "HeroUtil.h"
#include "NxUtil.h"
#include "NxDefine.h"
#include "GameStringDepot.h"

PokerPlayerResultPanel::PokerPlayerResultPanel()
{
	m_IsDataInit = false;
	mParentPanel = nullptr;
	//initPanel();
}

PokerPlayerResultPanel::~PokerPlayerResultPanel()
{
	mMainPanel->destruct();
}

void PokerPlayerResultPanel::initPanel(Panel * mParent)
{
	mParentPanel = mParent;
	initPanel();
}

void PokerPlayerResultPanel::initPanel()
{
	if (mParentPanel == nullptr)
		return;

	mMainPanel = new Panel();
	mMainPanel->construct(getMxmlPath() + "dmy_result_board_slot.mxml");

	CCSize contentsSize = mMainPanel->getDummy("dmy_result_board_slot").size;
	mMainPanel->setPositionY(contentsSize.height - DESIGN_HEIGHT - contentsSize.height / 2.f);
	mMainPanel->setPositionX(-contentsSize.width / 2.f);
	mMainPanel->setContentSize(contentsSize);
	this->setContentSize(contentsSize);

	addChild(mMainPanel);
	mMainPanel->release();

	mMyBar = mMainPanel->getSkel("skel_my_lightback");
	mJokbo = mMainPanel->getLabel("txt_result");
	mGold = mMainPanel->getLabel("txt_gold");
	mPlayerName = mMainPanel->getLabel("txt_username");
}

void PokerPlayerResultPanel::InitData()
{
	m_IsDataInit = false;
}

void PokerPlayerResultPanel::HidePanel()
{
	setVisible(false);
}

void PokerPlayerResultPanel::ShowPanel()
{
	if (m_IsDataInit)
		setVisible(true);
}

void PokerPlayerResultPanel::SetData(GameKind gameKind, WinKind winKind, string& nickname, bool isMine, int highJokboKind, int lowJokboKind, int64 inoutGameMoney)
{
	SetWin(gameKind, winKind);

	mMyBar->setVisible(isMine);
	SetJokbo(winKind, highJokboKind, lowJokboKind, gameKind);
	SetMoney(inoutGameMoney);
	mPlayerName->setString(nickname.c_str());
	m_IsDataInit = true;

	if (isMine)
	{
		mJokbo->setColor(ccc3(55, 22, 7));
		mGold->setColor(ccc3(55, 22, 7));
		mPlayerName->setColor(ccc3(55, 22, 7));
	}
	else
	{
		mJokbo->setColor(ccc3(250, 183, 96));
		mGold->setColor(ccc3(250, 183, 96));
		mPlayerName->setColor(ccc3(250, 183, 96));
	}
	//ShowPanel();

}

void PokerPlayerResultPanel::SetWin(GameKind gameKind, WinKind winKind)
{
	if (winKind <= WinKind::NORMAL_LOSE)
	{
		mMainPanel->getSkel("skel_mark_win")->setVisible(false);
		return;
	}

	mMainPanel->getSkel("skel_mark_win")->setVisible(true);
	switch (gameKind)
	{
		case GAMEKIND_HIGH_LOW :
			if (winKind == WinKind::HIGH_WIN)
				mMainPanel->getSkel("skel_mark_win")->playAnimation("mark_highwin");
			else if (winKind == WinKind::LOW_WIN)
				mMainPanel->getSkel("skel_mark_win")->playAnimation("mark_lowwin");
			else if (winKind == WinKind::SWING_WIN)
				mMainPanel->getSkel("skel_mark_win")->playAnimation("mark_swingwin");
			else if (winKind == WinKind::GIVEUP_WIN)
				mMainPanel->getSkel("skel_mark_win")->playAnimation("mark_win");
			break;
		case GAMEKIND_7POKER :
			mMainPanel->getSkel("skel_mark_win")->playAnimation("mark_win");
			break;
	}
}

void PokerPlayerResultPanel::SetJokbo(WinKind winKind, int highJokboKind, int lowJokboKind, int _gamekind)
{
	string highStr, lowStr;
	string resultStr;
	if (winKind == WinKind::GIVEUP_LOSE)
		mJokbo->setString(GameStringDepot::getSingleton().getString("TXT_MINUS").c_str());
	else if (winKind == WinKind::GIVEUP_WIN)
		mJokbo->setString(GameStringDepot::getSingleton().getString("TXT_GIVEUP_WIN").c_str());
	else if (_gamekind == GameKind::GAMEKIND_BADUKI)
	{
		resultStr = GameDataManager::getSingletonPtr()->GetBadugiJokboStr(lowJokboKind);
		mJokbo->setString(resultStr.c_str());
	}
	else
	{
		highStr = GameDataManager::getSingletonPtr()->GetJokboStr(highJokboKind);
		lowStr = GameDataManager::getSingletonPtr()->GetJokboStr(lowJokboKind);

		switch (winKind)
		{
			case WinKind::LOW_WIN :
			case WinKind::LOW_LOSE:
				resultStr = lowStr;
				break;
			case WinKind::SWING_WIN :
			case WinKind::SWING_LOSE:
			{
				if (highJokboKind != HighJokboKind::HIGH_NO && highJokboKind <= HighJokboKind::HIGH_FOUR_CARD)
				{
					resultStr = highStr;
				}
				else
				{
					string shortStr = GameDataManager::getSingletonPtr()->GetU8SubStr(highStr, 4);
					if (shortStr.length() < highStr.length())
						shortStr = GameDataManager::getSingletonPtr()->GetU8SubStr(highStr, 3) + "..";
					resultStr.append(shortStr);
					resultStr.append("/");

					shortStr = GameDataManager::getSingletonPtr()->GetU8SubStr(lowStr, 4);
					if (shortStr.length() < lowStr.length())
						shortStr = GameDataManager::getSingletonPtr()->GetU8SubStr(lowStr, 3) + "..";
					resultStr.append(shortStr);
				}

				break;
			}
			default :
				resultStr = highStr;
				break;
		}

		mJokbo->setString(resultStr.c_str());
	}
}

void PokerPlayerResultPanel::SetMoney(int64 inoutGameMoney)
{
	string moneyStr = StringConverter::toString(inoutGameMoney);
	if (inoutGameMoney > 0)
		moneyStr = "+" + GameDataManager::getSingletonPtr()->GetKoreanLiteral(moneyStr, 2);
	else
		moneyStr = GameDataManager::getSingletonPtr()->GetKoreanLiteral(moneyStr, 2);

	mGold->setString(moneyStr.c_str());
}


