#include "pch.h"
#include "LobbyTopUiPanel.h"

#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "CustomPopupPanel.h"
#include "LobbyUIPanel.h"
#include "CmdList.h"
#include "GameStringDepot.h"
#include "PokerRankHelper.h"
#include "BankPopupPanel.h"
#include "LobbyOptionPanel.h"
#include "PanelHelper.h"
#include "FriendHelper.h"
#include "PokerResourceHelper.h"
#include "GlobalDefine.h"

#define INT_ACTION_TAG 256
#define RESOURCE_TAG 255

LobbyTopUiPanel::LobbyTopUiPanel()
{
	mLoginProcess = false;
	m_isUseProfilePhoto = false;

	InitPanel();
	InitImage();
	initButton();
	InitMyPhoto();
	initNotiWidget();
	//setTouchable(true);
	setButtonListener(this);
}

LobbyTopUiPanel::~LobbyTopUiPanel()
{
	//if (!m_isUseProfilePhoto)
	//	NX_SAFE_DELETE(mMyProfilePhoto);
}

void LobbyTopUiPanel::InitPanel()
{
	construct(getMxmlPath() + "dmy_top_panel.mxml");
	mVipIcon = getSkel("skel_vip");
	mMemberIcon = getSkel("skel_class_gold");
	mAddRubyIcon = getImage("skel_rubyp");
	mLvTitle = getLabel("txt_lv");
	mVipAmount = getLabel("txt_vip");
	mUserPhoto = getImage("dmy_photo");
	mMyHomeAni = getImage("skel_light_myroom");
	getLabel("txt_gold")->setGrayColor(StringConverter::parseColor3B("f73030"));	
}

void LobbyTopUiPanel::InitImage()
{
	//getSkel("skel_toppanal");
	//getSkel("skel_sumbox_gold");
	//getSkel("skel_sumbox_chip");
	//getSkel("skel_sumbox_rubby");
	getSkel("skel_rubby_light")->playAnimation("rubby_light");
	getSkel("skel_chip_light")->playAnimation("gold_light");
	getSkel("skel_gold_light")->playAnimation("gold_light");
	//getSkel("skel_class_gold");
	//getSkel("skel_top_crack");
	m_ExpStartPos = getSkel("skel_expbar_center")->getPosition();
	getSkel("skel_menu_mark")->setVisible(false);
	//getSkel("skel_menu_title")->setVisible(false);
	//getSkel("skel_game_title")->setVisible(false);
	getSkel("skel_titlelight")->setVisible(false);

	getLabel("txt_gold")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_chip")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_rubby")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_usernameshadow")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_username")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("str_userlevel")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));	
	getLabel("txt_menu_title")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	mBankEffect = getImage("skel_beffect2");
	mBankEffect->setVisible(false);
	getLabel("txt_menu_title")->setVisible(false);


	//getLabel("txt_gold")->setAnchorPoint(ccp(0.5f, 0.5f));
	//getLabel("txt_rubby")->setAnchorPoint(ccp(0.5f, 0.5f));
	//getLabel("txt_chip")->setAnchorPoint(ccp(0.5f,0.5f));

}

void LobbyTopUiPanel::SetTopTitle(int _kind)
{
	if (_kind == LOBBY_UI_MAIN)
	{
		getSkel("skel_toppanal")->playAnimation("toppanal_menu");		
	}
	else
	{
		getSkel("skel_toppanal")->playAnimation("toppanal");		
	}

	//기본적으로 false 하고 true 해야 할 것들	
	getSkel("skel_menu_mark")->setVisible(true);
	getSkel("skel_titlelight")->setVisible(true);
	getLabel("txt_menu_title")->setVisible(true);
	switch (_kind)
	{
	case LOBBY_UI_MYHOME:		
		getSkel("skel_menu_mark")->playAnimation("my_room_mark");		
		getLabel("txt_menu_title")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_MYROOM_BUTTON").c_str());
		break;
	case LOBBY_UI_LETTER:
		getSkel("skel_menu_mark")->playAnimation("letter_mark");		
		getLabel("txt_menu_title")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_LETTERBOX_BUTTON").c_str());
		break;
	case LOBBY_UI_FRIEND:
		getSkel("skel_menu_mark")->playAnimation("friend_mark");
		getLabel("txt_menu_title")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_FRIEND_BUTTON").c_str());
		break;
	case LOBBY_UI_MISSION:
		getSkel("skel_menu_mark")->playAnimation("mission_mark");
		getLabel("txt_menu_title")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_MISSION_BUTTON").c_str());
		break;
	case LOBBY_UI_SHOP:
		getSkel("skel_menu_mark")->playAnimation("shop_mark");
		getLabel("txt_menu_title")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_SHOP_BUTTON").c_str());
		break;
	case LOBBY_UI_DAYCHECK:
		getSkel("skel_menu_mark")->playAnimation("friend_mark");
		getLabel("txt_menu_title")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_DAILY_ATTEND").c_str());
		break;
	case LOBBY_UI_RANKING:
	case LOBBY_UI_RANKING_PROCESS:
		getSkel("skel_menu_mark")->playAnimation("rank_mark");		
		getLabel("txt_menu_title")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_RANKING_UNIT").c_str());
		break;
	case LOBBY_UI_REPLAY:
	case LOBBY_UI_REPLAY_PROCESS:
		getSkel("skel_menu_mark")->playAnimation("replay_mark");		
		getLabel("txt_menu_title")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_REPLAY_UNIT").c_str());
		break;
	case LOBBY_SLOTMACHINE:
		break;
	case LOBBY_UI_BANK:
		break;
	case LOBBY_UI_OPTION:
		getSkel("skel_menu_mark")->playAnimation("option_mark");
		getLabel("txt_menu_title")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_OPTION_UNIT").c_str());
		break;
// 	case LOBBY_UI_CHARACTER_SHOP:
// 		getSkel("skel_menu_mark")->playAnimation("mark_character");
// 		getLabel("txt_menu_title")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_CHARACTER_SHOP").c_str());
// 		break;
	case LOBBY_UI_INVEN:
		getSkel("skel_menu_mark")->playAnimation("shop_mark");
		getLabel("txt_menu_title")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_GO_INVEN").c_str());
		break;

	case LOBBY_UI_RECORD:
		getSkel("skel_menu_mark")->playAnimation("record_mark");
		getLabel("txt_menu_title")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_RECORD").c_str());
		break;
	default:
		SetVisiebleUserInfo(true);
		
		getSkel("skel_menu_mark")->setVisible(false);
		getSkel("skel_titlelight")->setVisible(false);
		getLabel("txt_menu_title")->setVisible(false);
		return;
		break;
	}

	SetVisiebleUserInfo(false);
}

void LobbyTopUiPanel::SetVisiebleUserInfo(bool _visible)
{
	getLabel("txt_usernameshadow")->setVisible(_visible);
	getLabel("txt_username")->setVisible(_visible);
	getLabel("str_userlevel")->setVisible(_visible);
	
	getSkel("skel_expbar_center")->setVisible(_visible);
	getImage("skel_photoline")->setVisible(_visible);
	getSkel("skel_userpanal")->setVisible(_visible);

	mUserPhoto->setVisible(_visible);
	mMyHomeAni->setVisible(_visible);
	
	if (_visible == true && LayerManager::getSingletonPtr()->hasLayer("LobbyUI"))
	{
		LobbyUIPanel* _pLobbyUiPanel = dynamic_cast<LobbyUIPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyUI"));
		_pLobbyUiPanel->UpdateUserVip();
	}
	else
	{
		getSkel("skel_class_gold")->setVisible(false);
	}

	//vip 대신 현재 등급등을 표시
	setvisibleRank(_visible);
}

void LobbyTopUiPanel::initButton()
{
	setButtonListener(this);
	mCloseBtn = getButton("sbtn_option_button");
	mMyRoomBtn = getButton("sbtn_myroom");
	mBankBtn = getButton("sbtn_bank_button");
	mRubyBtn = getButton("sbtn_rubby_button");	
	mCloseBtn->setTouchable(true, 10);
	mMyRoomBtn->setTouchable(true, 10);
	mBankBtn->setTouchable(true, 10);
	mRubyBtn->setTouchable(true, 10);
}


bool LobbyTopUiPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	int _uiState = GameDataManager::getSingletonPtr()->GetUiState();

	if (_uiState == LOBBY_UI_LETTER)
	{
		if (LayerManager::getSingletonPtr()->hasLayer("LobbyLetter"))
		{
			LobbyLetterBoxPanel* _pPanel = dynamic_cast<LobbyLetterBoxPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyLetter"));
			if (_pPanel)
			{
				return _pPanel->ccTouchBegan(pTouch, pEvent);
			}
		}
	}
	else if (_uiState == LOBBY_UI_CHANNELLIST)
	{
		if (LayerManager::getSingletonPtr()->hasLayer("LobbyChannel"))
		{
			ChannelMainPannel* _pPanel = dynamic_cast<ChannelMainPannel*>(LayerManager::getSingletonPtr()->getLayer("LobbyChannel"));
			if (_pPanel)
			{
				return _pPanel->ccTouchBegan(pTouch, pEvent);
			}
		}
	}
	else if(_uiState == LOBBY_UI_TOURNAMENT)
	{
		if (LayerManager::getSingletonPtr()->hasLayer("LobbyTournamet"))
		{
			LobbyTournamentMain* _pPanel = dynamic_cast<LobbyTournamentMain*>(LayerManager::getSingletonPtr()->getLayer("LobbyTournamet"));
			if (_pPanel)
			{
				return _pPanel->ccTouchBegan(pTouch, pEvent);
			}
		}
	}
	else if (_uiState == LOBBY_UI_TOURNAMENT_SELECT)
	{
		if (LayerManager::getSingletonPtr()->hasLayer("TournamentSelect"))
		{
			LobbyTourSelectPanel* _pPanel = dynamic_cast<LobbyTourSelectPanel*>(LayerManager::getSingletonPtr()->getLayer("TournamentSelect"));
			if (_pPanel)
			{
				return _pPanel->ccTouchBegan(pTouch, pEvent);
			}
		}
	}
	else if (_uiState == LOBBY_UI_SURVIVAL)
	{
		if (LayerManager::getSingletonPtr()->hasLayer("LobbySurvival"))
		{
			LobbySurvivalMain* _pPanel = dynamic_cast<LobbySurvivalMain*>(LayerManager::getSingletonPtr()->getLayer("LobbySurvival"));
			if (_pPanel)
			{
				return _pPanel->ccTouchBegan(pTouch, pEvent);
			}
		}
	}
	else if (_uiState == LOBBY_UI_SURVIVAL_SELECT)
	{
		if (LayerManager::getSingletonPtr()->hasLayer("SurvivalSelect"))
		{
			LobbySurvivalWindowMain* _pPanel = dynamic_cast<LobbySurvivalWindowMain*>(LayerManager::getSingletonPtr()->getLayer("SurvivalSelect"));
			if (_pPanel)
			{
				return _pPanel->ccTouchBegan(pTouch, pEvent);
			}
		}
	}
	else if (_uiState == LOBBY_UI_RANKER_GAME_POPUP)
	{
		return true;
	}
	else if (_uiState == LOBBY_UI_SHOP)
	{
		if (LayerManager::getSingletonPtr()->hasLayer("LobbyShop"))
		{
			LobbyShopPanel* _pPanel = dynamic_cast<LobbyShopPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyShop"));
			if (_pPanel)
			{
				return _pPanel->ccTouchBegan(pTouch, pEvent);
			}
		}
	}
// 	else if (_uiState == LOBBY_UI_CHARACTER_SHOP)
// 	{
// 		if (LayerManager::getSingletonPtr()->hasLayer("LobbyCharacterShop"))
// 		{
// 			LobbyCharacterShopPanel* _pPanel = dynamic_cast<LobbyCharacterShopPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyCharacterShop"));
// 			if (_pPanel)
// 			{
// 				return _pPanel->ccTouchBegan(pTouch, pEvent);
// 			}
// 		}
// 	}
	return false;
}


void LobbyTopUiPanel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	int _uiState = GameDataManager::getSingletonPtr()->GetUiState();

	if (_uiState == LOBBY_UI_LETTER)
	{
		if (LayerManager::getSingletonPtr()->hasLayer("LobbyLetter"))
		{
			LobbyLetterBoxPanel* _pPanel = dynamic_cast<LobbyLetterBoxPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyLetter"));
			if (_pPanel)
			{
				_pPanel->ccTouchMoved(pTouch, pEvent);
				return;
			}
		}
	}
	else if(_uiState == LOBBY_UI_CHANNELLIST)
	{
		if (LayerManager::getSingletonPtr()->hasLayer("LobbyChannel"))
		{
			ChannelMainPannel* _pPanel = dynamic_cast<ChannelMainPannel*>(LayerManager::getSingletonPtr()->getLayer("LobbyChannel"));
			if (_pPanel)
			{
				_pPanel->ccTouchMoved(pTouch, pEvent);
				return;
			}
		}
	}
	else if (_uiState == LOBBY_UI_TOURNAMENT)
	{
		if (LayerManager::getSingletonPtr()->hasLayer("LobbyTournamet"))
		{
			LobbyTournamentMain* _pPanel = dynamic_cast<LobbyTournamentMain*>(LayerManager::getSingletonPtr()->getLayer("LobbyTournamet"));
			if (_pPanel)
			{
				_pPanel->ccTouchMoved(pTouch, pEvent);
				return;
			}
		}
	}
	else if (_uiState == LOBBY_UI_TOURNAMENT_SELECT)
	{
		if (LayerManager::getSingletonPtr()->hasLayer("TournamentSelect"))
		{
			LobbyTourSelectPanel* _pPanel = dynamic_cast<LobbyTourSelectPanel*>(LayerManager::getSingletonPtr()->getLayer("TournamentSelect"));
			if (_pPanel)
			{
				_pPanel->ccTouchMoved(pTouch, pEvent);
				return;
			}
		}
	}
	else if (_uiState == LOBBY_UI_SURVIVAL)
	{
		if (LayerManager::getSingletonPtr()->hasLayer("LobbySurvival"))
		{
			LobbySurvivalMain* _pPanel = dynamic_cast<LobbySurvivalMain*>(LayerManager::getSingletonPtr()->getLayer("LobbySurvival"));
			if (_pPanel)
			{
				_pPanel->ccTouchMoved(pTouch, pEvent);
				return;
			}
		}
	}
	else if (_uiState == LOBBY_UI_SURVIVAL_SELECT)
	{
		if (LayerManager::getSingletonPtr()->hasLayer("SurvivalSelect"))
		{
			LobbySurvivalWindowMain* _pPanel = dynamic_cast<LobbySurvivalWindowMain*>(LayerManager::getSingletonPtr()->getLayer("SurvivalSelect"));
			if (_pPanel)
			{
				_pPanel->ccTouchMoved(pTouch, pEvent);
				return;
			}
		}
	}
	else if (_uiState == LOBBY_UI_SHOP)
	{
		if (LayerManager::getSingletonPtr()->hasLayer("LobbyShop"))
		{
			LobbyShopPanel* _pPanel = dynamic_cast<LobbyShopPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyShop"));
			if (_pPanel)
			{
				_pPanel->ccTouchMoved(pTouch, pEvent);
				return;
			}
		}
	}
// 	else if (_uiState == LOBBY_UI_CHARACTER_SHOP)
// 	{
// 		if (LayerManager::getSingletonPtr()->hasLayer("LobbyCharacterShop"))
// 		{
// 			LobbyCharacterShopPanel* _pPanel = dynamic_cast<LobbyCharacterShopPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyCharacterShop"));
// 			if (_pPanel)
// 			{
// 				_pPanel->ccTouchMoved(pTouch, pEvent);
// 				return;
// 			}
// 		}
// 	}
}


void LobbyTopUiPanel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	int _uiState = GameDataManager::getSingletonPtr()->GetUiState();

	if (_uiState == LOBBY_UI_LETTER)
	{
		if (LayerManager::getSingletonPtr()->hasLayer("LobbyLetter"))
		{
			LobbyLetterBoxPanel* _pPanel = dynamic_cast<LobbyLetterBoxPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyLetter"));
			if (_pPanel)
			{
				_pPanel->ccTouchEnded(pTouch, pEvent);
				return;
			}
		}
	}
	else if (_uiState == LOBBY_UI_CHANNELLIST)
	{
		if (LayerManager::getSingletonPtr()->hasLayer("LobbyChannel"))
		{
			ChannelMainPannel* _pPanel = dynamic_cast<ChannelMainPannel*>(LayerManager::getSingletonPtr()->getLayer("LobbyChannel"));
			if (_pPanel)
			{
				_pPanel->ccTouchEnded(pTouch, pEvent);
				return;
			}
		}
	}
	else if (_uiState == LOBBY_UI_TOURNAMENT)
	{
		if (LayerManager::getSingletonPtr()->hasLayer("LobbyTournamet"))
		{
			LobbyTournamentMain* _pPanel = dynamic_cast<LobbyTournamentMain*>(LayerManager::getSingletonPtr()->getLayer("LobbyTournamet"));
			if (_pPanel)
			{
				_pPanel->ccTouchEnded(pTouch, pEvent);
				return;
			}
		}
	}
	else if (_uiState == LOBBY_UI_TOURNAMENT_SELECT)
	{
		if (LayerManager::getSingletonPtr()->hasLayer("TournamentSelect"))
		{
			LobbyTourSelectPanel* _pPanel = dynamic_cast<LobbyTourSelectPanel*>(LayerManager::getSingletonPtr()->getLayer("TournamentSelect"));
			if (_pPanel)
			{
				 _pPanel->ccTouchEnded(pTouch, pEvent);
				 return;
			}
		}
	}
	else if(_uiState == LOBBY_UI_SURVIVAL)
	{
		if (LayerManager::getSingletonPtr()->hasLayer("LobbySurvival"))
		{
			LobbySurvivalMain* _pPanel = dynamic_cast<LobbySurvivalMain*>(LayerManager::getSingletonPtr()->getLayer("LobbySurvival"));
			if (_pPanel)
			{
				_pPanel->ccTouchEnded(pTouch, pEvent);
				return;
			}
		}
	}
	else if (_uiState == LOBBY_UI_SURVIVAL_SELECT)
	{
		if (LayerManager::getSingletonPtr()->hasLayer("SurvivalSelect"))
		{
			LobbySurvivalWindowMain* _pPanel = dynamic_cast<LobbySurvivalWindowMain*>(LayerManager::getSingletonPtr()->getLayer("SurvivalSelect"));
			if (_pPanel)
			{
				_pPanel->ccTouchEnded(pTouch, pEvent);
				return;
			}
		}
	}
	else if (_uiState == LOBBY_UI_SHOP)
	{
		if (LayerManager::getSingletonPtr()->hasLayer("LobbyShop"))
		{
			LobbyShopPanel* _pPanel = dynamic_cast<LobbyShopPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyShop"));
			if (_pPanel)
			{
				_pPanel->ccTouchEnded(pTouch, pEvent);
				return;
			}
		}
	}
// 	else if (_uiState == LOBBY_UI_CHARACTER_SHOP)
// 	{
// 		if (LayerManager::getSingletonPtr()->hasLayer("LobbyCharacterShop"))
// 		{
// 			LobbyCharacterShopPanel* _pPanel = dynamic_cast<LobbyCharacterShopPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyCharacterShop"));
// 			if (_pPanel)
// 			{
// 				_pPanel->ccTouchEnded(pTouch, pEvent);
// 				return;
// 			}
// 		}
// 	}

}

void LobbyTopUiPanel::resume()
{
}

void LobbyTopUiPanel::onClicked(const string& name)
{
	if (mLoginProcess)
		return;

	if (GameDataManager::getSingletonPtr()->GetUiState() == LOBBY_UI_RANKER_GAME_POPUP)
		return;
	
	LobbyUIPanel* _pLobbyUiPanel = dynamic_cast<LobbyUIPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyUI"));
	if (name == getButtonName(mMyRoomBtn))
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		PanelHelper::pushMyHomePanel();
	}
	else if (name == getButtonName(mBankBtn))
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		PlayerData * _playerData = GameDataManager::getSingletonPtr()->GetPlayerDataPtr();
		
		if (isBankOpen()) {
			PanelHelper::pushBankPanel();
			GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_BANK);
		}
		else {
			if (_playerData->m_MonthlyClassID == 0)
			{
				PanelHelper::pushBuyMemberNoticePanel();
			}
		}		
	}
	else if (name == getButtonName(mRubyBtn))
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		//현재창이 샵창이라면 바꾸고 아니라면 push 한다.
		LobbyShopPanel* lobbyShopPanel = dynamic_cast<LobbyShopPanel*>(LayerManager::getSingleton().getCurrentLayer());
		if (lobbyShopPanel) {
			//바꾸고
			lobbyShopPanel->ShowShopPanel();
			lobbyShopPanel->SetTapIdx(TAB_RUBY);			
		}
		else {
			PanelHelper::pushRubyShopPanel();			
		}
		pushUiPanel(LOBBY_UI_SHOP);		
	}
	else if (name == getButtonName(mCloseBtn))
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		if (isCloseBtn()) {
			if (LayerManager::getSingleton().getCurrentLayer()->isDynamic()) {
				//현재창이 ccnallist 나 season 일대는
				if (LayerManager::getSingleton().isCurrentLayerType<ChannelMainPannel>()){
					if (GameDataManager::getSingletonPtr()->m_pOptionValue->m_music == true)
						SoundManager::getSingletonPtr()->playBGM("BGM_Lobby");
				}
				else if (LayerManager::getSingleton().isCurrentLayerType<LobbyTournamentMain>()){
					if (GameDataManager::getSingletonPtr()->m_pOptionValue->m_music == true)
						SoundManager::getSingletonPtr()->playBGM("BGM_Lobby");
				}
			
				bool shouldrefreshAdminText = false;
				if (LayerManager::getSingleton().getCurrentLayer()->getName().find("Toast") != string::npos) {
					LayerManager::getSingleton().popLayer();
					shouldrefreshAdminText = true;
				}

				LayerManager::getSingleton().popLayer();
				GameDataManager::getSingletonPtr()->PopUiState();

				if (LayerManager::getSingleton().getCurrentLayer()->getName().find("Toast") != string::npos) {
					LayerManager::getSingleton().popLayer();
					shouldrefreshAdminText = true;
				}

				//if( LayerManager::getSingleton().getCurrentLayer() == ChannelMainPannel())
				Layer* temp = dynamic_cast<ChannelMainPannel*>(LayerManager::getSingleton().getCurrentLayer());
				if (temp != nullptr) {
					LayerManager::getSingleton().popLayer();
					//GameDataManager::getSingletonPtr()->PopUiState();
				}
				
				if (!LayerManager::getSingleton().getCurrentLayer()->isDynamic()) {
					if (mCloseBtn->getButtonSkelObject()->getCurrentAnimation() == "cancel_stay") {
						mCloseBtn->getButtonSkelObject()->playAnimation("option_change");
						mCloseBtn->getButtonSkelObject()->appendAnimation("option_stay");
						pushUiPanel(LOBBY_UI_MAIN);
					}
				}
				else {
					int uiState = PanelHelper::getUiState();
					pushUiPanel(uiState);
				}

				if (shouldrefreshAdminText)
					WebService::getSingleton().sendNoticeinfoReq();
			}
		}
		else {
			LayerManager::getSingleton().pushDynamicLayer(new LobbyOptionPanel());
			pushUiPanel(LOBBY_UI_OPTION);
		}
	}
}

void LobbyTopUiPanel::update(float dt)
{
	updateNotiWidget();
}

bool LobbyTopUiPanel::handling(STCMD &stCmd)
{
	if (auto *pstIt = castCMD<STCMD_CURL_DOWNLOAD_SOCIAL_PROFILE_ACK>(&stCmd))
	{
		STCMD_CURL_DOWNLOAD_SOCIAL_PROFILE_ACK res = *pstIt;

		if (res.param != MY_PHOTO)
			return false;
		
		if (!res.imagePath.empty())
		{
			InitMyPhoto(false);
		}
		return true;
	}

	return false;
}


void LobbyTopUiPanel::UpdatePlayerInfo()
{
	int64 _money = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney;
	int64 _MaxGold = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoneyMax;

	string _gameMoney = StringConverter::toString(_money);
	string originStr = getLabel("txt_gold")->getString();
	getLabel("txt_gold")->setString(GameDataManager::getSingletonPtr()->GetKoreanLiteral(_gameMoney, 3).c_str());
// 	if (originStr != getLabel("txt_gold")->getString()) {
// 		if (getLabel("txt_gold")->getActionByTag(RESOURCE_TAG) == nullptr) {
// 			CCAction* action = PokerResourceHelper::getUiNoticeAction();
// 			action->setTag(RESOURCE_TAG);
// 			getLabel("txt_gold")->runAction(action);
// 		}
// 	}

	if (_money >= _MaxGold) {
		getLabel("txt_gold")->setGrayscale(true);
	}
	else {
		getLabel("txt_gold")->setGrayscale(false);
	}

	int64 _chip = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Chip;
	string _gameChip = StringConverter::toString(_chip);
	string originChipStr = getLabel("txt_chip")->getString();
	getLabel("txt_chip")->setString(_gameChip.c_str());
// 	if (originChipStr != getLabel("txt_chip")->getString()) {
// 		if (getLabel("txt_chip")->getActionByTag(RESOURCE_TAG) == nullptr) {
// 			CCAction* action = PokerResourceHelper::getUiNoticeAction();
// 			action->setTag(RESOURCE_TAG);
// 			getLabel("txt_chip")->runAction(action);
// 		}
// 	}

	int64 _ruby = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Cash;
	string _gameCash = StringConverter::toString(_ruby);
	string originRubyStr = getLabel("txt_rubby")->getString();
	getLabel("txt_rubby")->setString(_gameCash.c_str());
// 	if (originRubyStr != getLabel("txt_rubby")->getString()) {
// 		if (getLabel("txt_rubby")->getActionByTag(RESOURCE_TAG) == nullptr) {
// 			CCAction* action = PokerResourceHelper::getUiNoticeAction();
// 			action->setTag(RESOURCE_TAG);
// 			getLabel("txt_rubby")->runAction(action);
// 		}
// 	}

	CCLog("UpdatePlayerInfo...");
}

void LobbyTopUiPanel::updateVip()
{
	//Rank 아이콘
	//Rank 에 따른 표시
	int rank = PokerRankHelper::getRank();	
	//Vip 표시
	int _vipLevel = PokerRankHelper::getVip();
	if (_vipLevel == 0) {
		mVipIcon->playAnimation("mark_vip_off");
	}
	else {
		mVipIcon->playAnimation("mark_vip");
	}
	mVipAmount->setString(StringConverter::toString(_vipLevel).c_str());
	mAddRubyIcon->setVisible(false);	
	//맴버쉽
	if (!isCloseBtn()) {
		int _monthlyClass = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_MonthlyClassID;
		switch (_monthlyClass)
		{
		case 0:
			mMemberIcon->setVisible(false);
			break;
		case 1:
			mMemberIcon->setVisible(true);
			mMemberIcon->playAnimation("class_silver");
			break;
		case 2:
			mMemberIcon->setVisible(true);
			mMemberIcon->playAnimation("class_gold");
			break;
		}
		//표시	
		mAddRubyIcon->setVisible(PokerRankHelper::hasRubyPlus());
	}
}

void LobbyTopUiPanel::setvisibleRank(bool vislble)
{
	mVipIcon->setVisible(vislble);
	mMemberIcon->setVisible(vislble);
	if (vislble) {
		int _monthlyClass = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_MonthlyClassID;
		switch (_monthlyClass)
		{
		case 0:
			mMemberIcon->setVisible(false);
			break;
		case 1:
			mMemberIcon->setVisible(true);
			mMemberIcon->playAnimation("class_silver");
			break;
		case 2:
			mMemberIcon->setVisible(true);
			mMemberIcon->playAnimation("class_gold");
			break;
		}
	}

	mAddRubyIcon->setVisible(vislble);
	if (vislble) {		
		mAddRubyIcon->setVisible(PokerRankHelper::hasRubyPlus());
	}
	mVipAmount->setVisible(vislble);
	mLvTitle->setVisible(vislble);
	mMyRoomBtn->setEnable(vislble);
	mMyRoomBtn->setVisible(vislble);
}

void LobbyTopUiPanel::pushUiPanel(int status)
{
	//x 로 바꿔준다.
	SetTopTitle(status);
	if (mCloseBtn->getButtonSkelObject()->getCurrentAnimation() == "option_stay") {
		mCloseBtn->getButtonSkelObject()->playAnimation("cancel_change");
		mCloseBtn->getButtonSkelObject()->appendAnimation("cancel_stay");
	}
}

bool LobbyTopUiPanel::isCloseBtn()
{
	return mCloseBtn->getButtonSkelObject()->getCurrentAnimation() == "cancel_stay";
}

void LobbyTopUiPanel::onLayerMessage(const string& msg)
{
	LobbyUIPanel* _pLobbyUiPanel = dynamic_cast<LobbyUIPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyUI"));
	_pLobbyUiPanel->onLayerMessage(msg);
}


void LobbyTopUiPanel::addRewardRuby(int64 ruby)
{
	int64 _ruby = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Cash;
	CCLog("addRewardRuby _ruby = %d , ruby = %d", _ruby, ruby);
	getLabel("txt_rubby")->setInt(_ruby);
	getLabel("txt_rubby")->setIntAction(_ruby + ruby);
	CCDelayTime* delay = CCDelayTime::create(1.1f);
	CCFiniteTimeAction* completeFunc = CCCallFunc::create(this, callfunc_selector(LobbyTopUiPanel::_completeIntAction));
	CCAction* action = CCSequence::create(delay, completeFunc, nullptr);
}

void LobbyTopUiPanel::addRewardInfo(W_RewardInfo rewardInfo)
{
	int64 _money = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney;
	int64 _chip = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Chip;
	int64 _ruby = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Cash;	
	//애니메이션
	for (int i = 0; i < rewardInfo.rewardset_size(); i++)
	{
		W_RewardInfo_RewardSet rewardSet = rewardInfo.rewardset(i);
		eResourceType type = rewardSet.type();
		switch (type)
		{
		case CASH:
		{
			getLabel("txt_rubby")->setInt(_ruby - rewardSet.amount());
			getLabel("txt_rubby")->setIntAction(_ruby);
			CCLog("addRewardInfo _ruby = %d , rewardSet.amount() = %d", _ruby, rewardSet.amount());
			CCDelayTime* delay = CCDelayTime::create(1.1f);
			CCFiniteTimeAction* completeFunc = CCCallFunc::create(this, callfunc_selector(LobbyTopUiPanel::_completeIntAction));
			CCAction* action = CCSequence::create(delay, completeFunc, nullptr);
			runAction(action);
		}
			break;
		case GAMEMONEY:
		{
			float ups = 10.f;
			float duration = 1.f;
			mRewardGameMoneyInit = _money - rewardSet.amount();
			mRewardResultGameMoney = _money;
			mRewardAddGameMoney = (mRewardResultGameMoney - mRewardGameMoneyInit) / ups;
			stopActionByTag(INT_ACTION_TAG);
			CCDelayTime* delay = CCDelayTime::create(duration / ups);
			CCFiniteTimeAction* updateFunc = CCCallFunc::create(this, callfunc_selector(LobbyTopUiPanel::_updateIntAction));
			CCFiniteTimeAction* completeFunc = CCCallFunc::create(this, callfunc_selector(LobbyTopUiPanel::_completeIntAction));
			CCRepeat* repeat = CCRepeat::create(CCSequence::create(delay, updateFunc, nullptr), duration*ups);
			CCAction* action = CCSequence::create(repeat, completeFunc, nullptr);
			action->setTag(INT_ACTION_TAG);
			runAction(action);
		}
			break;
		case CHIP:
		{
			//	getLabel("txt_chip")->setString(_gameChip.c_str());
			getLabel("txt_chip")->setInt(_chip - rewardSet.amount());
			getLabel("txt_chip")->setIntAction(_chip);
			CCDelayTime* delay = CCDelayTime::create(1.1f);
			CCFiniteTimeAction* completeFunc = CCCallFunc::create(this, callfunc_selector(LobbyTopUiPanel::_completeIntAction));
			CCAction* action = CCSequence::create(delay, completeFunc, nullptr);
			runAction(action);
		}
			break;
		}
	}
}

void LobbyTopUiPanel::_updateIntAction()
{
	mRewardGameMoneyInit += mRewardAddGameMoney;
	string _gameMoney = StringConverter::toString(mRewardGameMoneyInit);
	getLabel("txt_gold")->setString(GameDataManager::getSingletonPtr()->GetKoreanLiteral(_gameMoney, 3).c_str());
}

void LobbyTopUiPanel::_completeIntAction()
{
	mRewardGameMoneyInit = mRewardResultGameMoney;
	string _gameMoney = StringConverter::toString(mRewardGameMoneyInit);	
	getLabel("txt_gold")->setString(GameDataManager::getSingletonPtr()->GetKoreanLiteral(_gameMoney, 3).c_str());
	//
	UpdatePlayerInfo();
}

void LobbyTopUiPanel::refreshUserPhoto()
{
	InitMyPhoto(false);
}

void LobbyTopUiPanel::InitMyPhoto(bool isDownload /*= true*/)
{
	CCRect rect = getDummy("dmy_photo");
	bool _ret;
	//디폴트 이미지로 설정
	mUserPhoto->setSpriteFrameWithFile(FriendHelper::getDefaultImg());
	if (GameDataManager::getSingletonPtr()->m_FacebookUserId != "")
	{
		_ret = GameDataManager::getSingletonPtr()->LoadFileImage(
			GameDataManager::getSingletonPtr()->m_FacebookUserId,
			GameDataManager::getSingletonPtr()->m_FacebookUserPhotoUrl,
			DOWNLOAD_FILE_TYPE::MY_PHOTO,
			mUserPhoto,
			isDownload,
			STATIC_PHOTO_FOLDER
			);

		// 로딩되었으면 이미지를 교체한다.
		if (_ret)
		{			
			mUserPhoto->fit(CCSize(rect.getMaxX() - rect.getMinX(), rect.getMaxY() - rect.getMinY()));			
			m_isUseProfilePhoto = true;
		}
	}
	else if (GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_thumbnailUrl != "")
	{
		_ret = GameDataManager::getSingletonPtr()->LoadFileImage(
			GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_NickName,
			GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_thumbnailUrl,
			DOWNLOAD_FILE_TYPE::MY_PHOTO,
			mUserPhoto,
			isDownload,
			STATIC_PHOTO_FOLDER
			);

		// 로딩되었으면 이미지를 교체한다.
		if (_ret)
		{			
			mUserPhoto->fit(CCSize(rect.getMaxX() - rect.getMinX(), rect.getMaxY() - rect.getMinY()));			
			m_isUseProfilePhoto = true;
		}
	}
	else
	{
		mUserPhoto->setSpriteFrameWithFile(FriendHelper::getMycharacterImg());		
		mUserPhoto->fit(CCSize(rect.getMaxX() - rect.getMinX(), rect.getMaxY() - rect.getMinY()));
		m_isUseProfilePhoto = true;		
	}	
}

void LobbyTopUiPanel::refreshBank()
{
	if (isBankOpen()) {
		//mBankEffect->setVisible(true);
		mBankBtn->setSkelAnimation("bank_stay");
	}
	else {
		//mBankEffect->setVisible(false);
		mBankBtn->setSkelAnimation("bank_off_stay");
	}
}

bool LobbyTopUiPanel::isBankOpen()
{
	return GameDataManager::getSingleton().getPlayerInfo().bankbax() != 0;
}

#include "NotiDataManager.h"

void LobbyTopUiPanel::initNotiWidget()
{
	NotiDataManager::getSingletonPtr()->setNoticeNoti(
		CCUserDefault::sharedUserDefault()->getBoolForKey(NSGameConfig::keyNotiNotification.c_str())
	);
    // 공지
    {
        NotiWidget* notiWidget = new NotiWidget(NotiWidget::NOTI_LOBBY_OPTION);
        addChild(notiWidget);
        notiWidget->release();
        notiWidget->setPosition(getImage("dmy_notification_icon")->getPosition());
        mNotiWidgets.push_back(notiWidget);
    }
}

void LobbyTopUiPanel::updateNotiWidget()
{
    for (int i = 0; i < mNotiWidgets.size(); i++)
    {
        mNotiWidgets[i]->refresh();
    }
}

void LobbyTopUiPanel::onEnter()
{
	Panel::onEnter();
	scheduleUpdate();
}