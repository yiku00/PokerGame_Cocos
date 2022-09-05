#include "pch.h"
#include "InGameOptionPanel.h"

#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "CustomPopupPanel.h"
#include "PokerBackgroundPanel.h"
#include "FightScene.h"
#include "GameStringDepot.h"

InGameOptionPanel::InGameOptionPanel()
{
	InitPanel();
	InitImage();
	initButton();

	//setButtonListener(this);
}

InGameOptionPanel::~InGameOptionPanel()
{
	mMainPanel->removeAllChildren(); 
	removeAllChildren();
}

void InGameOptionPanel::InitPanel()
{
	mParentPanel = dynamic_cast<Panel*>(LayerManager::getSingletonPtr()->getLayer("Background"));
	if (mParentPanel)
	{
		mMainPanel = new Panel();
		mMainPanel->construct(getMxmlPath() + "dmy_ingame_option.mxml");
		addChild(mMainPanel);
		mMainPanel->release();
		CCSize contentsSize = mMainPanel->getDummy("dmy_ingame_option").size;
		mMainPanel->setPositionY(contentsSize.height / 2.f - DESIGN_HEIGHT);
		mMainPanel->setPositionX(-contentsSize.width / 2.f);
		mMainPanel->setContentSize(contentsSize);
		this->setContentSize(contentsSize);

		//음악
		//켜기
		mMainPanel->getLabel("txt_on1")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_ON").c_str());
		//끄기
		mMainPanel->getLabel("txt_off1")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_OFF").c_str());

		//효과음
		//켜기
		mMainPanel->getLabel("txt_on2")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_ON").c_str());
		//끄기
		mMainPanel->getLabel("txt_off2")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_OFF").c_str());

		//목소리
		//켜기
		mMainPanel->getLabel("txt_on3")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_ON").c_str());
		//끄기
		mMainPanel->getLabel("txt_off3")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_OFF").c_str());

		//히든패
		//수동
		mMainPanel->getLabel("txt_on4")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_MENUAL").c_str());
		//자동
		mMainPanel->getLabel("txt_off4")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_AUTO").c_str());

	}

	setPosition(mParentPanel->getImage("dmy_ingame_option")->getPosition());
	setVisible(false);
}

void InGameOptionPanel::InitImage()
{
	m_pOptionCheck[CHECK_MUSIC] = mMainPanel->getSkel("skel_checkframe1");
	m_pOptionCheck[CHECK_EFFECT] = mMainPanel->getSkel("skel_checkframe3"); 
	m_pOptionCheck[CHECK_VOICE] = mMainPanel->getSkel("skel_checkframe5");	
	m_pOptionCheck[CHECK_HIDDEN] = mMainPanel->getSkel("skel_checkframe7");
	
	m_pOptionUnCheck[CHECK_MUSIC] = mMainPanel->getSkel("skel_checkframe2");
	m_pOptionUnCheck[CHECK_EFFECT] = mMainPanel->getSkel("skel_checkframe4"); 
	m_pOptionUnCheck[CHECK_VOICE] = mMainPanel->getSkel("skel_checkframe6");	
	m_pOptionUnCheck[CHECK_HIDDEN] = mMainPanel->getSkel("skel_checkframe8");

	m_pOptionCheck[CHECK_MUSIC]->playAnimation("checkframe_start");
	m_pOptionCheck[CHECK_VOICE]->playAnimation("checkframe_start");
	m_pOptionCheck[CHECK_EFFECT]->playAnimation("checkframe_start");
	m_pOptionCheck[CHECK_HIDDEN]->playAnimation("checkframe_start");
	m_pOptionUnCheck[CHECK_MUSIC]->playAnimation("checkframe_start");
	m_pOptionUnCheck[CHECK_VOICE]->playAnimation("checkframe_start");
	m_pOptionUnCheck[CHECK_EFFECT]->playAnimation("checkframe_start");
	m_pOptionUnCheck[CHECK_HIDDEN]->playAnimation("checkframe_start");

	
	m_pOptionUnCheck[CHECK_MUSIC]->setVisible(false);
	m_pOptionUnCheck[CHECK_VOICE]->setVisible(false);
	m_pOptionUnCheck[CHECK_EFFECT]->setVisible(false);
	m_pOptionUnCheck[CHECK_HIDDEN]->setVisible(false);

	OptionDefineValue* _val = GameDataManager::getSingletonPtr()->m_pOptionValue;
	//음악
	if (_val->m_music)
	{
		m_pOptionCheck[CHECK_MUSIC]->setVisible(true);
		m_pOptionUnCheck[CHECK_MUSIC]->setVisible(false);
	}
	else
	{
		m_pOptionCheck[CHECK_MUSIC]->setVisible(false);
		m_pOptionUnCheck[CHECK_MUSIC]->setVisible(true);
	}

	//효과음
	if (_val->m_effect)
	{
		m_pOptionCheck[CHECK_EFFECT]->setVisible(true);
		m_pOptionUnCheck[CHECK_EFFECT]->setVisible(false);
	}
	else
	{
		m_pOptionCheck[CHECK_EFFECT]->setVisible(false);
		m_pOptionUnCheck[CHECK_EFFECT]->setVisible(true);
	}

	//목소리
	if (_val->m_voice)
	{
		m_pOptionCheck[CHECK_VOICE]->setVisible(true);
		m_pOptionUnCheck[CHECK_VOICE]->setVisible(false);
	}
	else
	{
		m_pOptionCheck[CHECK_VOICE]->setVisible(false);
		m_pOptionUnCheck[CHECK_VOICE]->setVisible(true);
	}
	

	if (_val->m_hiddenCard)
	{
		m_pOptionCheck[CHECK_HIDDEN]->setVisible(true);
		m_pOptionUnCheck[CHECK_HIDDEN]->setVisible(false);
	}
	else
	{
		m_pOptionCheck[CHECK_HIDDEN]->setVisible(false);
		m_pOptionUnCheck[CHECK_HIDDEN]->setVisible(true);
	}
	for (int _i = 1; _i < 5; _i++)
	{
		string _onTxt = "txt_on" + StringConverter::toString(_i);
		string _offTxt = "txt_off" + StringConverter::toString(_i);

		mMainPanel->getLabel(_onTxt)->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		mMainPanel->getLabel(_offTxt)->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	}

	mMainPanel->getLabel("txt_room_number")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mMainPanel->getLabel("txt_roominfo")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mMainPanel->getLabel("txt_potmoney")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mMainPanel->getLabel("txt_roominfo_sum")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mMainPanel->getLabel("txt_potmoney_sum")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mMainPanel->getLabel("str_music")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mMainPanel->getLabel("str_voice")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mMainPanel->getLabel("str_sound")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mMainPanel->getLabel("str_hiddencard")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

	m_RoomNumberText = mMainPanel->getLabel("txt_room_number");
	m_RoomInfoLabel = mMainPanel->getLabel("txt_roominfo");
	m_RoomInfoTextUnder = mMainPanel->getLabel("txt_roominfo_sum_under");
	m_RoomInfoText = mMainPanel->getLabel("txt_roominfo_sum");
	m_PotMoneyLabel = mMainPanel->getLabel("txt_potmoney");	
	m_PotMoneyText = mMainPanel->getLabel("txt_potmoney_sum");
	m_PotMoneyTextUnder = mMainPanel->getLabel("txt_potmoney_sum_under");
	m_OptionLabelMusic = mMainPanel->getLabel("str_music");
	m_OptionLabelVoice = mMainPanel->getLabel("str_voice");
	m_OptionLabelEffect = mMainPanel->getLabel("str_sound");
	m_OptionLabelHidden = mMainPanel->getLabel("str_hiddencard");

	m_RoomInfoLabel->setString(GameStringDepot::getSingletonPtr()->getString("TXT_INGAME_OPTION_ROOM_INFO").c_str());
	m_PotMoneyLabel->setString(GameStringDepot::getSingletonPtr()->getString("TXT_INGAME_OPTION_POTMONEY").c_str());
	m_OptionLabelMusic->setString(GameStringDepot::getSingletonPtr()->getString("TXT_INGAME_OPTION_MUSIC").c_str());
	m_OptionLabelVoice->setString(GameStringDepot::getSingletonPtr()->getString("TXT_INGAME_OPTION_VOICE").c_str());
	m_OptionLabelEffect->setString(GameStringDepot::getSingletonPtr()->getString("TXT_INGAME_OPTION_EFFECT").c_str());
	m_OptionLabelHidden->setString(GameStringDepot::getSingletonPtr()->getString("TXT_INGAME_OPTION_HIDDEN").c_str());

}

void InGameOptionPanel::initButton()
{
	GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetBackgroundPanel()->m_pOptionButton->setListener(this);

	m_pOptionCheckBtn[CHECK_MUSIC] = mMainPanel->getButton("sbtn_checkbox1");
	m_pOptionUnCheckBtn[CHECK_MUSIC] = mMainPanel->getButton("sbtn_checkbox2");
	
	m_pOptionCheckBtn[CHECK_EFFECT] = mMainPanel->getButton("sbtn_checkbox3");
	m_pOptionUnCheckBtn[CHECK_EFFECT] = mMainPanel->getButton("sbtn_checkbox4");

	m_pOptionCheckBtn[CHECK_VOICE] = mMainPanel->getButton("sbtn_checkbox5");
	m_pOptionUnCheckBtn[CHECK_VOICE] = mMainPanel->getButton("sbtn_checkbox6");
	
	m_pOptionCheckBtn[CHECK_HIDDEN] = mMainPanel->getButton("sbtn_checkbox7");
	m_pOptionUnCheckBtn[CHECK_HIDDEN] = mMainPanel->getButton("sbtn_checkbox8");

	m_pOptionCheckBtn[CHECK_MUSIC]->setType(Button::NoPressImg);
	m_pOptionCheckBtn[CHECK_VOICE]->setType(Button::NoPressImg);
	m_pOptionCheckBtn[CHECK_EFFECT]->setType(Button::NoPressImg);
	m_pOptionCheckBtn[CHECK_HIDDEN]->setType(Button::NoPressImg);

	m_pOptionUnCheckBtn[CHECK_MUSIC]->setType(Button::NoPressImg);
	m_pOptionUnCheckBtn[CHECK_VOICE]->setType(Button::NoPressImg);
	m_pOptionUnCheckBtn[CHECK_EFFECT]->setType(Button::NoPressImg);
	m_pOptionUnCheckBtn[CHECK_HIDDEN]->setType(Button::NoPressImg);

	m_pOptionCheckBtn[CHECK_MUSIC]->setListener(this);
	m_pOptionCheckBtn[CHECK_VOICE]->setListener(this);
	m_pOptionCheckBtn[CHECK_EFFECT]->setListener(this);
	m_pOptionCheckBtn[CHECK_HIDDEN]->setListener(this);

	m_pOptionUnCheckBtn[CHECK_MUSIC]->setListener(this);
	m_pOptionUnCheckBtn[CHECK_VOICE]->setListener(this);
	m_pOptionUnCheckBtn[CHECK_EFFECT]->setListener(this);
	m_pOptionUnCheckBtn[CHECK_HIDDEN]->setListener(this);

	//m_pCloseButton->setListener(this);

}


bool InGameOptionPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (isVisible() == false)
		return false;

	CCRect _mainRect = mMainPanel->getDummy("dmy_ingame_option");
	m_bBtnTouch = false;
	//CCRect _collisionRect = CCRectMake(
	//	_mainPos.x,
	//	_mainPos.y,
	//	mMainPanel->getContentSize().width,
	//	mMainPanel->getContentSize().height);

	CCPoint _touchPoint = mMainPanel->convertToWorldSpace(pTouch->getLocation());

	if (_mainRect.containsPoint(_touchPoint) == false)
	{
		setVisible(false);
		setTouchable(false);
	}
	else
	{
		CCPoint _tableTouch = pTouch->getLocation();
		for (int _i = 0; _i < 4; _i++)
		{
			if (m_pOptionCheckBtn[_i]->hasCollided(m_pOptionCheckBtn[_i]->convertToNodeSpace(_tableTouch)))
			{
				m_bBtnTouch = true;
			}

			if (m_pOptionUnCheckBtn[_i]->hasCollided(m_pOptionUnCheckBtn[_i]->convertToNodeSpace(_tableTouch)))
			{
				m_bBtnTouch = true;
			}
		}
		return true;
	}
	return false;
}


void InGameOptionPanel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	
}


void InGameOptionPanel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (m_bBtnTouch == false)
		return;

	CCPoint _tableTouch = pTouch->getLocation();
	for (int _i = 0; _i < 4; _i++)
	{
		if (m_pOptionCheckBtn[_i]->hasCollided(m_pOptionCheckBtn[_i]->convertToNodeSpace(_tableTouch)))
		{
			onClicked(m_pOptionCheckBtn[_i]->getName());
		}

		if (m_pOptionUnCheckBtn[_i]->hasCollided(m_pOptionUnCheckBtn[_i]->convertToNodeSpace(_tableTouch)))
		{
			onClicked(m_pOptionUnCheckBtn[_i]->getName());
		}
	}

	m_bBtnTouch = false;
}

void InGameOptionPanel::resume()
{
}

void InGameOptionPanel::onClicked(const string& name)
{
	if (name == "sbtn_ingame_option_button")
	{
		if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_isReplayData == false)
		{
			if (isVisible() == false)
			{
				GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
				TCPService::getSingletonPtr()->SendPlayRoomInfoReq();
			}
			else
			{
				setVisible(false);
				setTouchable(false);
			}
		}
	}

	if (isVisible() == false)
		return;

	if (name == "sbtn_checkbox1")	//음악켜키
	{
		OptionDefineValue* _val = GameDataManager::getSingletonPtr()->m_pOptionValue;
		if (_val->m_music == false)
		{
			_val->m_music = true;
			m_pOptionCheck[CHECK_MUSIC]->setVisible(true);
			m_pOptionCheck[CHECK_MUSIC]->playAnimation("checkframe_start");
			m_pOptionUnCheck[CHECK_MUSIC]->setVisible(false);
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_CHECK);
		}		
		return;
	}

	if (name == "sbtn_checkbox2")	//음악끄기
	{
		OptionDefineValue* _val = GameDataManager::getSingletonPtr()->m_pOptionValue;
		if (_val->m_music == true)
		{
			_val->m_music = false;
			m_pOptionCheck[CHECK_MUSIC]->setVisible(false);
			m_pOptionUnCheck[CHECK_MUSIC]->setVisible(true);
			m_pOptionUnCheck[CHECK_MUSIC]->playAnimation("checkframe_start");
			if (SoundManager::getSingletonPtr()->isPlayingBGM())
				SoundManager::getSingletonPtr()->stopBGM();
		}
		return;
	}
	if (name == "sbtn_checkbox3")	//효과음
	{
		OptionDefineValue* _val = GameDataManager::getSingletonPtr()->m_pOptionValue;
		if (_val->m_effect == false)
		{
			_val->m_effect = true;
			m_pOptionCheck[CHECK_EFFECT]->setVisible(true);
			m_pOptionCheck[CHECK_EFFECT]->playAnimation("checkframe_start");
			m_pOptionUnCheck[CHECK_EFFECT]->setVisible(false);
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_CHECK);
		}
		return;
	}

	if (name == "sbtn_checkbox4")
	{
		OptionDefineValue* _val = GameDataManager::getSingletonPtr()->m_pOptionValue;
		if (_val->m_effect == true)
		{
			_val->m_effect = false;
			m_pOptionCheck[CHECK_EFFECT]->setVisible(false);
			m_pOptionUnCheck[CHECK_EFFECT]->setVisible(true);
			m_pOptionUnCheck[CHECK_EFFECT]->playAnimation("checkframe_start");
		}
		return;
	}

	if (name == "sbtn_checkbox5")	//목소리
	{
		OptionDefineValue* _val = GameDataManager::getSingletonPtr()->m_pOptionValue;
		if (_val->m_voice == false)
		{
			_val->m_voice = true;
			m_pOptionCheck[CHECK_VOICE]->setVisible(true);
			m_pOptionCheck[CHECK_VOICE]->playAnimation("checkframe_start");
			m_pOptionUnCheck[CHECK_VOICE]->setVisible(false);
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_CHECK);
		}
		return;
	}

	if (name == "sbtn_checkbox6")
	{
		OptionDefineValue* _val = GameDataManager::getSingletonPtr()->m_pOptionValue;
		if (_val->m_voice == true)
		{
			_val->m_voice = false;
			m_pOptionCheck[CHECK_VOICE]->setVisible(false);
			m_pOptionUnCheck[CHECK_VOICE]->setVisible(true);
			m_pOptionUnCheck[CHECK_VOICE]->playAnimation("checkframe_start");
		}
		return;
	}

	
	if (name == "sbtn_checkbox7")
	{
		OptionDefineValue* _val = GameDataManager::getSingletonPtr()->m_pOptionValue;
		if (_val->m_hiddenCard == false)
		{
			_val->m_hiddenCard = true;
			m_pOptionCheck[CHECK_HIDDEN]->setVisible(true);
			m_pOptionCheck[CHECK_HIDDEN]->playAnimation("checkframe_start");
			m_pOptionUnCheck[CHECK_HIDDEN]->setVisible(false);
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_CHECK);
		}
		return;
	}

	if (name == "sbtn_checkbox8")
	{
		OptionDefineValue* _val = GameDataManager::getSingletonPtr()->m_pOptionValue;
		if (_val->m_hiddenCard == true)
		{
			_val->m_hiddenCard = false;
			m_pOptionCheck[CHECK_HIDDEN]->setVisible(false);
			m_pOptionUnCheck[CHECK_HIDDEN]->setVisible(true);
			m_pOptionUnCheck[CHECK_HIDDEN]->playAnimation("checkframe_start");
		}
		return;
	}

	//if (name == "sbtn_ribbon_cancel_yellow")
	//{
	//	setVisible(false);
	//	setTouchable(false);
	//}
}

void InGameOptionPanel::update(float dt)
{
}

bool InGameOptionPanel::handling(STCMD &stCmd)
{
	return false;
}

void InGameOptionPanel::SetOptionValue()
{
	setVisible(true);
	setTouchable(true);

	GameRoomInfo* _pInfo = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr();
	string _infoText = "";
	_infoText = NxGetFormatString(GameStringDepot::getSingletonPtr()->getString("TXT_ROOM_NUMBER"), _pInfo->GetRoomIdx());		
	m_RoomNumberText->setString(_infoText.c_str());
		
	_infoText = "";
	switch (_pInfo->GetGameKind())
	{
	case GameKind::GAMEKIND_7POKER:
		_infoText += GameStringDepot::getSingletonPtr()->getString("TXT_GAME_KIND_7POKER");
		break;
	case GameKind::GAMEKIND_HIGH_LOW:
		_infoText += GameStringDepot::getSingletonPtr()->getString("TXT_GAME_KIND_HIGHLOW");
		break;
	case GameKind::GAMEKIND_BADUKI:
		_infoText += GameStringDepot::getSingletonPtr()->getString("TXT_GAME_KIND_BADUKI");
		break;
	}

	//Rule
	switch (_pInfo->GetBettingRule())
	{
	case BettingRule::RULE_FOUR_CARD:
		_infoText += "/" + GameStringDepot::getSingletonPtr()->getString("TXT_RULE_FOUR_CARD");
		break;
	case BettingRule::RULE_FIVE_CARD:
		_infoText += "/" + GameStringDepot::getSingletonPtr()->getString("TXT_RULE_FIVE_CARD");
		break;
	case BettingRule::RULE_SIX_CARD:
		_infoText += "/" + GameStringDepot::getSingletonPtr()->getString("TXT_RULE_SIX_CARD");
		break;
	}
	//SeedMoney
	_infoText += "/" + GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_pInfo->GetSeedMoney()), 2);
	_infoText += GameStringDepot::getSingletonPtr()->getString("TXT_GOLD_UNIT");
	m_RoomInfoText->setString(_infoText.c_str());
	m_RoomInfoTextUnder->setString(_infoText.c_str());

	//average	
	string _averageMoneyText = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_pInfo->m_avgPotMoney), 2);
	_averageMoneyText += GameStringDepot::getSingletonPtr()->getString("TXT_GOLD_UNIT");
	m_PotMoneyText->setString(_averageMoneyText.c_str());
	m_PotMoneyTextUnder->setString(_averageMoneyText.c_str());
}

void InGameOptionPanel::onEnter()
{
	Panel::onEnter();

	setTouchable(true);
}