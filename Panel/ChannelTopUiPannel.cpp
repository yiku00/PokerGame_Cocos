#include "pch.h"
#include "ChannelTopUiPannel.h"

#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "CustomPopupPanel.h"

ChannelTopUiPannel::ChannelTopUiPannel()
{
	m_bProcessing = false;

	InitPanel();
	InitImage();
	initButton();

	setTouchable(false);
	setButtonListener(this);
}

ChannelTopUiPannel::~ChannelTopUiPannel()
{
	//destruct();
}

void ChannelTopUiPannel::InitPanel()
{
	construct(getMxmlPath() + "dmy_channel_top.mxml");
}

void ChannelTopUiPannel::InitImage()
{
	//m_TopEfx[0] = getSkel("skel_rubby_light");
	//m_TopEfx[1] = getSkel("skel_chip_light");
	//m_TopEfx[2] = getSkel("skel_gold_light");
	//m_LeftEfx[0] = getSkel("skel_emphasis1");
	//m_LeftEfx[1] = getSkel("skel_emphasis2");
	//m_LeftEfx[2] = getSkel("skel_emphasis3");

	//m_TopEfx[0]->playAnimation("rubby_light");
	//m_TopEfx[1]->playAnimation("gold_light");
	//m_TopEfx[2]->playAnimation("gold_light");

	//m_LeftEfx[0]->playAnimation("emphasis_end");
	//m_LeftEfx[1]->playAnimation("emphasis_end");
	//m_LeftEfx[2]->playAnimation("emphasis_end");

	//m_gold = getLabel("txt_gold");
	//m_chip = getLabel("txt_chip");
	//m_rubby = getLabel("txt_rubby");

	//m_gold->setAnchorPoint(ccp(0.f, LABEL_ANCHOR_OFFSET));
	//m_chip->setAnchorPoint(ccp(0.f, LABEL_ANCHOR_OFFSET));
	//m_rubby->setAnchorPoint(ccp(0.f, LABEL_ANCHOR_OFFSET));

	int64 _money = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney;
	string _gameMoney = StringConverter::toString(_money);
	//m_gold->setString(GameDataManager::getSingletonPtr()->GetKoreanLiteral(_gameMoney, 3).c_str());

	int64 _chip = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Chip;
	string _gameChip = StringConverter::toString(_chip);
	//m_chip->setString(_gameChip.c_str());

	int64 _ruby = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Cash;
	string _gameCash = StringConverter::toString(_ruby);
	//m_rubby->setString(_gameCash.c_str());

	//if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_7POKER)
	//{
	//	getSkel("skel_game_title")->playAnimation("c_sevenpoker");
	//}
	//else if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_HIGH_LOW)
	//{
	//	getSkel("skel_game_title")->playAnimation("c_highlow");
	//}
	//else if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_BADUKI)
	//{
	//	getSkel("skel_game_title")->playAnimation("c_badugi");
	//}
	//else if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_HOLDEM)
	//{
	//	getSkel("skel_game_title")->playAnimation("c_texasholdem");
	//}

}

void ChannelTopUiPannel::UpdatePlayerInfo()
{
	int64 _money = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney;
	string _gameMoney = StringConverter::toString(_money);
	//m_gold->setString(GameDataManager::getSingletonPtr()->GetKoreanLiteral(_gameMoney, 3).c_str());

	int64 _chip = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Chip;
	string _gameChip = StringConverter::toString(_chip);
	//m_chip->setString(_gameChip.c_str());

	int64 _ruby = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Cash;
	string _gameCash = StringConverter::toString(_ruby);
	//m_rubby->setString(_gameCash.c_str());
}

void ChannelTopUiPannel::initButton()
{
	//m_btnBank = getButton("sbtn_bank_button");
	//m_btnRubyShop = getButton("sbtn_rubby_button");
	//m_btnOption = getButton("sbtn_option_button");
	//m_btnLetterBox = getButton("sbtn_lobbyleft_button1");
	//m_btnMission = getButton("sbtn_lobbyleft_button2");
	//m_btnShop = getButton("sbtn_lobbyleft_button3");

	//m_btnLetterBox->setType(Button::NoPressImg);
	//m_btnMission->setType(Button::NoPressImg);
	//m_btnShop->setType(Button::NoPressImg);
	//m_btnBank->setType(Button::NoPressImg);
	//m_btnRubyShop->setType(Button::NoPressImg);
	//m_btnOption->setType(Button::NoPressImg);

	//m_btnOption->getButtonSkelObject()->playAnimation("cancel_stay");
	//m_btnLetterBox->getButtonSkelObject()->setSkin("letter");
	//m_btnMission->getButtonSkelObject()->setSkin("mission");
	//m_btnShop->getButtonSkelObject()->setSkin("shop");
}


bool ChannelTopUiPannel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return false;
}


void ChannelTopUiPannel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	
}


void ChannelTopUiPannel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	
}

void ChannelTopUiPannel::resume()
{
}

void ChannelTopUiPannel::onClicked(const string& name)
{
	if (m_bProcessing)
		return;

	
}

void ChannelTopUiPannel::update(float dt)
{
}

bool ChannelTopUiPannel::handling(STCMD &stCmd)
{
	return false;
}