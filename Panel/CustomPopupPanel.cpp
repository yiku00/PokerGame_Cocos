#include "pch.h"
#include "CustomPopupPanel.h"
#include "HeroUtil.h"
#include "GameStringDepot.h"
#include "GameDataManager.h"
#include "PopupUserReplayPanel.h"
#include "PopupUserBankPanel.h"
#include "SelectCharacterPanel.h"
#include "ChannelRoomMainPanel.h"
#include "LobbyScene.h"
#include "SceneUtil.h"
#include "ChannelMainPannel.h"
#include "LobbyUIPanel.h"
#include "RankingTutorialPanel.h"
#include "ReplayTutorialPanel.h"
#include "ReplayGameManager.h"
#include "SoundHelper.h"
#include "PokerResourceHelper.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "android/AndroidUtilManager.h"
#endif
#include "PokerShopHelper.h"

static const string DEFAULT_PASSWARD_STR = "-";
#define REPEAT_TAG 255

CustomPopupPanel::CustomPopupPanel(CustomPopupType type, int param1, int param2, int param3, string param4) : Panel("PopupPanel")
{
	mChannelRoomMainPanel = nullptr;
	mMakeRoomBtn = nullptr;
	mType = type;
	mTarget = NULL;
	mGeneralListener = NULL;
	mParam1 = param1;
	mParam2 = param2;
	mParam3 = param3;
	mParam4 = param4;
	m_Password = "";
	m_searchIdx = -1;
	m_isSearching = false;
	initPanel();	
	ShowPanel(true);
}

CustomPopupPanel::~CustomPopupPanel()
{
	CCLOG("~CustomPopupPanel");
}

void CustomPopupPanel::onClicked(const string& name)
{
	//SoundManager::getSingleton().playEffect(BTN_CLICK);

	mEventName = name;
	if (mType != CHAR_INFO_TYPE)
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);

	switch (mType)
	{
	case CHAR_INFO_TYPE:
	case CHAR_INFO_INVEN_TYPE:
	{
		CharacterInfoOnClicked(name);
		return;
	}
	//case CHANNEL_LIST_TYPE:
	//{
	//	ChannelListOnClicked(name);
	//	return;
	//}
	case MAKE_CHANNEL_ROOM_TYPE:
	case ENTER_CHANNEL_ROOM_TYPE:
		ChannelRoomOnClicked(name);
		return;
	case CHANNEL_ROOM_LIST_TYPE:
		ChannelRoomListOnClicked(name);
		return;
	case FRIEND_INFO_TYPE :
		FriendInfoOnClicked(name);
		return;
	case WEB_VIEW_TYPE:
		WebViewOnClicked(name);
		return;
	case RANKING_TUTORIAL_TYPE:
		RankingOnClick(name);
		return;
	case REPLAY_TUTORIAL_TYPE:
		ReplayOnClick(name);
		return;
	}
		

	if (name == "sbtn_cancel")
	{
		ShowPanel(false);
	}
	else if (name == "sbtn_bank_button")
	{
		ShowPanel(false);
	}
	else if (name == "sbtn_bank_check")
	{
		ShowPanel(false);
	}
	else if (name == "sbtn_small_button_4r_stay")
	{
		if (mType == REPLAY_INFO_TYPE)
		{
			int _index = mParam1;
			if (GameDataManager::getSingletonPtr()->m_ReplaySaveList[_index]->has_seq())
			{
				int64 _seq = GameDataManager::getSingletonPtr()->m_ReplaySaveList[_index]->seq();
				WebService::getSingletonPtr()->_sendReplayDeleteReq(_seq);
				ShowPanel(false);
			}
		}
	}
	else if (name == "sbtn_small_button_4_stay")
	{
		if (mType == REPLAY_INFO_TYPE)
		{
			int _index = mParam1;
			if (GameDataManager::getSingletonPtr()->m_ReplaySaveList[_index]->has_seq())
			{
				int64 _seq = GameDataManager::getSingletonPtr()->m_ReplaySaveList[_index]->seq();
				bool _isLike = GameDataManager::getSingletonPtr()->m_ReplaySaveList[_index]->islike();
				ReplayGameManager::getSingletonPtr()->SetIsLike(_isLike);
				eReplayType _type = (eReplayType)mParam3;

				WebService::getSingletonPtr()->_sendReplayStartReq(_type, _seq);
				ShowPanel(false);
			}
		}
		else
		{
			ShowPanel(false);
		}
	}

	
}

void CustomPopupPanel::ChannelListOnClicked(const string& name)
{
	if (name == "sbtn_bank_button")
	{
		LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
		if (_pScene == nullptr)
			return;

		if (_pScene->m_LobbyUIPanel == nullptr)
			return;

		_pScene->m_LobbyUIPanel->ShowBankPanel();
	}
	if (name == "sbtn_rubby_button")
	{
		LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
		if (_pScene == nullptr)
			return;

		if (_pScene->m_LobbyUIPanel == nullptr)
			return;

		int state = GameDataManager::getSingletonPtr()->GetUiState();

		_pScene->m_LobbyUIPanel->mUiProcess = true;
		_pScene->m_LobbyUIPanel->SetShopUi(2);
		GameDataManager::getSingletonPtr()->m_pChannelListPanel = nullptr;
		ShowPanel(false);

		GameDataManager::getSingletonPtr()->SetUiState(state);
		
	}
	if (name == "sbtn_option_button")
	{
		if (GameDataManager::getSingletonPtr()->m_pOptionValue->m_music == true)
			SoundManager::getSingletonPtr()->playBGM("BGM_Lobby");

		GameDataManager::getSingletonPtr()->m_pChannelListPanel = nullptr;
		ShowPanel(false);
	}
	if (name == "sbtn_lobbyleft_button1")
	{
		LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
		if (_pScene == nullptr)
			return;
		if (_pScene->m_LobbyUIPanel == nullptr)
			return;

		int state = GameDataManager::getSingletonPtr()->GetUiState();

		_pScene->m_LobbyUIPanel->mUiProcess = true;
		WebService::getSingletonPtr()->_sendLetterListReq();
		GameDataManager::getSingletonPtr()->m_pChannelListPanel = nullptr;
		ShowPanel(false);

		GameDataManager::getSingletonPtr()->SetUiState(state);
		
	}
	if (name == "sbtn_lobbyleft_button2")
	{
		LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
		if (_pScene == nullptr)
			return;
		if (_pScene->m_LobbyUIPanel == nullptr)
			return;

		int state = GameDataManager::getSingletonPtr()->GetUiState();

		_pScene->m_LobbyUIPanel->mUiProcess = true;
		WebService::getSingletonPtr()->_sendQuestListUpdateReq();
		GameDataManager::getSingletonPtr()->m_pChannelListPanel = nullptr;
		ShowPanel(false);

		GameDataManager::getSingletonPtr()->SetUiState(state);
	}
	if (name == "sbtn_lobbyleft_button3")
	{
		LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
		if (_pScene == nullptr)
			return;
		if (_pScene->m_LobbyUIPanel == nullptr)
			return;

		int state = GameDataManager::getSingletonPtr()->GetUiState();

		_pScene->m_LobbyUIPanel->mUiProcess = true;
		_pScene->m_LobbyUIPanel->SetShopUi();
		GameDataManager::getSingletonPtr()->m_pChannelListPanel = nullptr;
		ShowPanel(false);

		GameDataManager::getSingletonPtr()->SetUiState(state);
	}
}

void CustomPopupPanel::ChannelRoomOnClicked(const string& name)
{
	if (name == getButtonName(mMakeRoomBtn))
	{
		if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
		{
			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
			if (mType == ENTER_CHANNEL_ROOM_TYPE)
			{
				if (!isCorrectPassward())
				{
					LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, GameStringDepot::getSingleton().getString("TXT_INPUT_PASSWORD2")), DYNAMIC_PUSH_LAYER);
					return;
				}
				string passwardStr = mPassward_1 + mPassward_2 + mPassward_3 + mPassward_4;
				_pScene->EnterGameRoom(mParam1, passwardStr);
				GameDataManager::getSingleton().setPassward(passwardStr);
			}
			else if (mType == MAKE_CHANNEL_ROOM_TYPE)
			{
				string passwardStr = mPassward_1 + mPassward_2 + mPassward_3 + mPassward_4;
				if (isCorrectPassward()) {
					_pScene->MakeGameRoom(passwardStr);
					GameDataManager::getSingleton().setPassward(passwardStr);
				}
				else if (mPasswardPos == 0) {
					_pScene->MakeGameRoom("");
					GameDataManager::getSingleton().setPassward("");
				}
				else {
					LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, GameStringDepot::getSingleton().getString("TXT_MAKE_PASSWORD")), DYNAMIC_PUSH_LAYER);
				}
			}
			else if(mType == CHAR_INFO_TYPE)
			{

			}
			ShowPanel(false);
		}
	}
	else if (name == "sbtn_cancel")
	{
		m_Password = "";
		ShowPanel(false);
	}
	else if (name == getButtonName(mNum0Btn)) {
		pushPassward(0);
	}
	else if (name == getButtonName(mNum1Btn)) {
		pushPassward(1);
	}
	else if (name == getButtonName(mNum2Btn)) {
		pushPassward(2);
	}
	else if (name == getButtonName(mNum3Btn)) {
		pushPassward(3);
	}
	else if (name == getButtonName(mNum4Btn)) {
		pushPassward(4);
	}
	else if (name == getButtonName(mNum5Btn)) {
		pushPassward(5);
	}
	else if (name == getButtonName(mNum6Btn)) {
		pushPassward(6);
	}
	else if (name == getButtonName(mNum7Btn)) {
		pushPassward(7);
	}
	else if (name == getButtonName(mNum8Btn)) {
		pushPassward(8);
	}
	else if (name == getButtonName(mNum9Btn)) {
		pushPassward(9);
	}
	else if (name == getButtonName(mBackBtn)) {
		backPassward();
	}
	else if (name == getButtonName(mInitNumBtn)) {
		initPassward();
	}	

}

void CustomPopupPanel::ChannelRoomListOnClicked(const string& name)
{
	if (mChannelRoomMainPanel == nullptr)
		return;

	if (name == "sbtn_option_button")
	{
		ShowPanel(false);
	}
	if (name == getButtonName(mMakeRoomBtn))
	{
		CustomPopupPanel* _panel = new CustomPopupPanel(CustomPopupPanel::CustomPopupType::MAKE_CHANNEL_ROOM_TYPE);
		if (_panel)
		{
			LayerManager::getSingleton().pushDynamicLayer(_panel, DYNAMIC_PUSH_LAYER);
		}
	}
	if (name == getButtonName(mChannelRoomMainPanel->m_pRoomJoinBtn))
	{
		if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
		{
			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
			_pScene->EnterGameRoom();			
			ShowPanel(false);

		}
	}
	if (name == getButtonName(mChannelRoomMainPanel->m_pRoomInputBtn))
	{
		//기덕수정
		if (mChannelRoomMainPanel) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			GameDataManager::getSingletonPtr()->m_bEditTextField = false;
			GameDataManager::getSingletonPtr()->m_onFocusTextFeild = mChannelRoomMainPanel->getTextField("fld_room_search");
			std::string _fieldText = mChannelRoomMainPanel->getTextField("fld_room_search")->getString();
			//AndroidUtilManager::getSingletonPtr()->ReleaseCustomEditTextField();
			AndroidUtilManager::getSingletonPtr()->InitCustomEditTextField();
			AndroidUtilManager::getSingletonPtr()->ShowCustomEditTextField(_fieldText);
#else
			mChannelRoomMainPanel->getTextField("fld_room_search")->attachWithIME();
#endif
		}			
	}
	if (name == getButtonName(mChannelRoomMainPanel->m_pSearchBtn))
	{
		if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
		{
			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
			GameDataManager::getSingletonPtr()->ReomveChannelRoomInfoList();

			// 이미 검색한 상태에서 아무것도 넣지 않은 경우
			if (m_isSearching && m_searchIdx == -1)
			{
				_pScene->RoomList(GameDataManager::getSingletonPtr()->m_curPage, ROOM_LIST_COUNT);
			}
			else if (m_searchIdx > 0)
			{
				_pScene->SerchRoom(m_searchIdx);
			}
			//기덕수정
			if (mChannelRoomMainPanel)
				mChannelRoomMainPanel->m_searchField->setString("");
		}
	}
}

void CustomPopupPanel::FriendInfoOnClicked(const string& name)
{
	if (name == "FriendInfo_Replay")
	{
		int _idx = mParam1;
		W_FriendInfo* _info = GameDataManager::getSingletonPtr()->m_FriendDataList[_idx];
		if (_info)
		{
			if (_info->has_uid())
			{
				WebService::getSingletonPtr()->SendReplayListBoxReq(_info->uid());
			}
		}
		ShowPanel(false);
	}
	if (name == "FriendInfo_RemoveFriend")
	{
		int _idx = mParam1;
		W_FriendInfo* _info = GameDataManager::getSingletonPtr()->m_FriendDataList[_idx];
		if (_info)
		{
			if (_info->has_uid())
				WebService::getSingletonPtr()->_sendFriendRemoveReq(_info->uid());
		}
		ShowPanel(false);
	}
	if (name == "FriendInfo_Close")
	{
		ShowPanel(false);
	}
}

void CustomPopupPanel::WebViewOnClicked(const string& name)
{
	if (name == "sbtn_webview_cancel")
	{
		ShowPanel(false);
	}
}

void CustomPopupPanel::CharacterInfoOnClicked(const string& name)
{
	if (name == "sbtn_cancel")
	{
		ShowPanel(false);
	}
	if (name == "sbtn_Ok_btn")
	{
		ShowPanel(false);
		if (mType == CHAR_INFO_TYPE) {
			if (LayerManager::getSingleton().hasLayerType<LobbyShopPanel>()) {
				LobbyShopPanel* pLobbyShoPanel = dynamic_cast<LobbyShopPanel*>(LayerManager::getSingleton().getLayerType<LobbyShopPanel>());
				pLobbyShoPanel->setCharacterBuy(mParam1);
			}
		}
		else if (mType == CHAR_INFO_INVEN_TYPE) {
			if (LayerManager::getSingleton().hasLayerType<LobbyInventoryPanel>()) {
				LobbyInventoryPanel* pLobbyShoPanel = dynamic_cast<LobbyInventoryPanel*>(LayerManager::getSingleton().getLayerType<LobbyInventoryPanel>());
				pLobbyShoPanel->setCharacterSelect(mParam1);
			}
		}
	}
	if (name == "btn_Touch")
	{
		TouchCharacter();
	}
}

void CustomPopupPanel::TouchCharacter()
{
	int _kind = rand() % 4;
	string _aniName = "";
	string soundStr = "";

	switch (GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_CharacterIdx)
	{
	case SANTIAGO:
	case SANTIAGO2:
		if (_kind == 0) {
			_aniName = "gesture_thanks";
			soundStr = "thanks";
		}
		else if (_kind == 1) {
			_aniName = "gesture_sadness";
			soundStr = "sad";
		}
		else if (_kind == 2) {
			_aniName = "gesture_hurry";
			soundStr = "quick";
		}
		else if (_kind == 3) {
			_aniName = "gesture_good";
			soundStr = "good";
		}
		break;
	case CHRISTINA:
	case CHRISTINA2:
		if (_kind == 0) {
			_aniName = "gesture_good";
			soundStr = "good";
		}
		else if (_kind == 1) {
			_aniName = "gesture_surprize";
			soundStr = "omg";
		}
		else if (_kind == 2) {
			_aniName = "gesture_hurry";
			soundStr = "quick";
		}
		else if (_kind == 3) {
			_aniName = "gesture_thanks";
			soundStr = "thanks";
		}
		break;
	case ALEXANDER:
	case ALEXANDER2:
		if (_kind == 0) {
			_aniName = "idle2";
			soundStr = "think1";
		}
		else if (_kind == 1) {
			_aniName = "gesture_pleasure";
			soundStr = "omg";
		}
		else if (_kind == 2) {
			_aniName = "gesture_hurry";
			soundStr = "quick";
		}
		else if (_kind == 3) {
			_aniName = "gesture_surprize";
			soundStr = "omg";
		}
		break;
	case BLACKROSE:
	case BLACKROSE2:
		if (_kind == 0) {
			_aniName = "gesture_laugh";
			soundStr = "lol";
		}
		else if (_kind == 1) {
			_aniName = "react_made";
			soundStr = "made";
		}
		else if (_kind == 2) {
			_aniName = "gesture_hurry";
			soundStr = "quick";
		}
		else if (_kind == 3) {
			_aniName = "gesture_thanks";
			soundStr = "thanks";
		}
		break;
	case JENIPER:
	case JENIPER2:
		if (_kind == 0) {
			_aniName = "gesture_angry";
			soundStr = "anger";
		}
		else if (_kind == 1) {
			_aniName = "gesture_sadness";
			soundStr = "sad";
		}
		else if (_kind == 2) {
			_aniName = "gesture_hurry";
			soundStr = "quick";
		}
		else if (_kind == 3) {
			_aniName = "gesture_surprize";
			soundStr = "omg";
		}
		break;
	case MARTIN:
	case MARTIN2:
		if (_kind == 0) {
			_aniName = "gesture_pleasure";
			soundStr = "glad";
		}
		else if (_kind == 1) {
			_aniName = "gesture_surprize";
			soundStr = "omg";
		}
		else if (_kind == 2) {
			_aniName = "gesture_hurry";
			soundStr = "quick";
		}
		else if (_kind == 3) {
			_aniName = "gesture_thanks";
			soundStr = "thanks";
		}
		break;
	default:
		if (_kind == 0) {
			_aniName = "gesture_thanks";
			soundStr = "thanks";
		}
		else if (_kind == 1) {
			_aniName = "gesture_sadness";
			soundStr = "sad";
		}
		else if (_kind == 2) {
			_aniName = "gesture_hurry";
			soundStr = "quick";
		}
		else if (_kind == 3) {
			_aniName = "gesture_good";
			soundStr = "good";
		}
		break;
	}

	m_UpSkel->playAnimation(_aniName);
	m_UpSkel->appendAnimation("idle_stand", true);
	m_DownSkel->playAnimation(_aniName);
	m_DownSkel->appendAnimation("idle_stand", true);

	string _name = SoundHelper::getCharacterSoundStr(mParam1);
	SoundManager::getSingleton().stopEffects();
	SoundManager::getSingletonPtr()->playEffect(_name + soundStr);
}

void CustomPopupPanel::ShowPanel(bool isVisible)
{
	if (isVisible)
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_POPUPOPEN);

	if (!isVisible)
	{
		clearThisPanel();		
	}
		
}

void CustomPopupPanel::SetHoldItem(int _type)
{
	if (mType == CHAR_INFO_TYPE || mType == CHAR_INFO_INVEN_TYPE)
	{
		switch (_type)
		{
		case TYPE_HOLD_ITEM:
			getLabel("txt_limit")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_HOLD_ITEM").c_str());
			break;
		case TYPE_NONE_ITEM:
			getLabel("txt_limit")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_NONE_ITEM").c_str());
			break;
		case TYPE_EXPIRED_ITEM:
			getLabel("txt_limit")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_EXPIRATION_ITEM").c_str());
			break;
		}
	}
}

void CustomPopupPanel::initPanel()
{
	if (mType == RANKING_TUTORIAL_TYPE || mType == REPLAY_TUTORIAL_TYPE)
	{
		addMouseBlockPanel(this, true);
	}
	else if (mType == CHANNEL_ROOM_LIST_TYPE) {
		//안한다.
	}
	else
	{
		addMouseBlockPanel(this,true);
	}
	
	mPasswardPos = 0;
	mNum1Btn = nullptr;
	mNum2Btn = nullptr;
	mNum3Btn = nullptr;
	mNum4Btn = nullptr;
	mNum5Btn = nullptr;
	mNum6Btn = nullptr;
	mNum7Btn = nullptr;
	mNum8Btn = nullptr;
	mNum9Btn = nullptr;
	mNum0Btn = nullptr;
	mBackBtn = nullptr;
	mInitNumBtn = nullptr;

	mFocusBottom1 = nullptr;
	mFocusBottom2 = nullptr;
	mFocusBottom3 = nullptr;
	mFocusBottom4 = nullptr;


	switch (mType)
	{
		case WEEKLY_REWOARD_TYPE :
			MakeWeeklyRewardPanel();
			break;
		case POINT_WEEKLY_REWARD_TYPE :
			MakePointWeeklyRewardPanel();
			break;
		case USER_REPLAY_BOX_TYPE:
			MakeUserReplayBoxPanel();
			break;
		//case USER_BANK_PANL_TYPE:
		//	MakeUserBankPanel();
		//	break;
		case REPLAY_INFO_TYPE :
			MakeReplayInfoPanel();
			break;
		case CHAR_INFO_TYPE :
		case CHAR_INFO_INVEN_TYPE :
			MakeCharacterInfoPanel();
			break;
		case FRIEND_INFO_TYPE:
			MakeFriendInfoPanel();
			break;
		//case CHANNEL_LIST_TYPE:
		//	MakeChannelListPanel();
		//	break;
		case CHANNEL_ROOM_LIST_TYPE:
			MakeChannelRoomPanel();
			break;
		case MAKE_CHANNEL_ROOM_TYPE:
			MakeChannelRoomMakePannel();
			break;
		case ENTER_CHANNEL_ROOM_TYPE:
			MakeEnterChannelRoomPanel();
			break;
		case RANKING_TUTORIAL_TYPE:
			MakeRankingTutorialPanel();
			break;
		case REPLAY_TUTORIAL_TYPE:
			MakeReplayTutorialPanel();
			break;
		case WEB_VIEW_TYPE :
			MakeWebViewPanel();
			break;
	}
}

void CustomPopupPanel::MakeWebViewPanel()
{
    GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_POPUP);

    construct(getMxmlPath() + "dmy_webview_bar.mxml");
    Button* m_WeekGiftBtn = getButton("sbtn_webview_cancel");
    m_WeekGiftBtn->setListener(this);
    m_WeekGiftBtn->setTouchable(true, 0, false);

    CCSize _contentSize = getDummy("dmy_webview_bar").size;
    CCPoint _pos = getDummy("dmy_webview_bar").origin;
    GameDataManager::getSingletonPtr()->OpenUrl(mParam4);
}

void CustomPopupPanel::MakeWeeklyRewardPanel()
{
	GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_POPUP);

	construct(getMxmlPath() + "dmy_weekplaygift.mxml");
	Button * m_WeekGiftBtn = getButton("sbtn_cancel");
	m_WeekGiftBtn->setListener(this);
	m_WeekGiftBtn->setTouchable(true, 0, false);
	m_WeekGiftBtn->getButtonSkelObject()->setSkin("mark_cancel");

	Nx::Label* _bonusGuideText = getLabel("txt_guide");
	Nx::Label* _bottomText = getLabel("txt_bottommessage");

	W_GameData* _pData = GameDataManager::getSingletonPtr()->GetGameDataPtr();

	int _size = _pData->replayweeklyrankdata_size();
	if (_size != 6)
		return;

	for (int _i = 0; _i < 6; _i++)
	{
		W_ReplayWeeklyRankData _pReplayRank = _pData->replayweeklyrankdata(_i);

		string dmyStr = "dmy_weekplay_table" + StringConverter::toString(_i + 1);
		CCPoint pos = getImage(dmyStr)->getPosition();
		Panel* contentsPanel = new Panel();
		contentsPanel->construct(getMxmlPath() + "dmy_weekplay_table.mxml");
		addChild(contentsPanel);
		contentsPanel->release();
		contentsPanel->setPosition(ccpSub(pos, ccp(contentsPanel->getContentSize().width * 0.5f, DESIGN_HEIGHT - contentsPanel->getContentSize().height * 0.5f)));
		
		string _bonusNumberText = "";

		if (_pReplayRank.has_minrank() && _pReplayRank.has_maxrank())
		{
			if (_pReplayRank.maxrank() == _pReplayRank.minrank())
			{
				_bonusNumberText = StringConverter::toString(_pReplayRank.maxrank()) + GameStringDepot::getSingleton().getString("TXT_RANK");
			}
			else
			{
				_bonusNumberText = StringConverter::toString(_pReplayRank.minrank()) + GameStringDepot::getSingleton().getString("TXT_RANK") + " ~ " + StringConverter::toString(_pReplayRank.maxrank()) + GameStringDepot::getSingleton().getString("TXT_RANK");
			}
		}


		SkelObject* rankIcon = contentsPanel->getSkel("skel_rank");
		Nx::Label* classNumterUnder = contentsPanel->getLabel("str_classnumber_under");
		Nx::Label* classNumter = contentsPanel->getLabel("str_classnumber");

		Nx::Label* bonusUnder = contentsPanel->getLabel("str_bonus_under");
		Nx::Label* bonus = contentsPanel->getLabel("str_bonus");

		rankIcon->setVisible(false);
		classNumterUnder->setVisible(false);
		classNumter->setVisible(false);

		if (_i < 3) {	//0 1, 2
			rankIcon->setVisible(true);
			string rankIconLabel = "rank_" + StringConverter::toString( _i + 1) + "_s";
			rankIcon->playAnimation(rankIconLabel);
		}
		else {			
			classNumterUnder->setVisible(true);
			classNumter->setVisible(true);
			classNumterUnder->setString(_bonusNumberText.c_str());
			classNumter->setString(_bonusNumberText.c_str());
		}

		//SkelObject* _bonusIcon = getSkel("skel_icon_bonus" + StringConverter::toString(_i + 1));

		if (_pReplayRank.has_rewardinfo())
		{
			int _size = _pReplayRank.rewardinfo().rewardset_size();
			string moneyData = "";
			for (int _count = 0; _count < _size; _count++)
			{
				eResourceType _type = _pReplayRank.rewardinfo().rewardset(_count).type();
				int64 _amount = _pReplayRank.rewardinfo().rewardset(_count).amount();

				switch (_type)
				{
				case  CASH:
					//_bonusIcon->playAnimation("icon_rubby");
					bonus->setString(StringConverter::toString(_amount).c_str());
					bonusUnder->setString(StringConverter::toString(_amount).c_str());
					break;
				case GAMEMONEY:
					//_bonusIcon->playAnimation("icon_gold");
					moneyData = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_amount));
					bonus->setString(moneyData.c_str());
					bonusUnder->setString(moneyData.c_str());
					break;
				case CHIP:
					//_bonusIcon->playAnimation("icon_chip");
					bonus->setString(StringConverter::toString(_amount).c_str());
					bonusUnder->setString(StringConverter::toString(_amount).c_str());
					break;
				case CHARACTER:
					break;
				}
			}
		}
	}
	setVisible(true);
}

void CustomPopupPanel::MakePointWeeklyRewardPanel()
{
	GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_POPUP);

	construct(getMxmlPath() + "dmy_week_rank.mxml");
	Button * m_WeekGiftBtn = getButton("sbtn_cancel");
	m_WeekGiftBtn->setListener(this);
	m_WeekGiftBtn->setTouchable(true, 0, false);
	m_WeekGiftBtn->getButtonSkelObject()->setSkin("mark_cancel");

	CCSize _contentSize = getDummy("dmy_week_rank").size;
	CCPoint _pos = getDummy("dmy_week_rank").origin;

	
	getSkel("skel_small_title")->setSkin("title_weekpalyrankgift");

	getLabel("txt_timelimit_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_timelimit")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

	getLabel("txt_bottommessage")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_bonus_under1")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_bonus1")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_classnumber_under2")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_classnumber2")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_bonus_under2")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_bonus2")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_classnumber_under3")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_classnumber3")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_bonus_under3")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_bonus3")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	
	for (int i = 4; i < 16; i++)
	{
		getLabel("txt_classnumber" + StringConverter::toString(i))->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		getLabel("txt_bonus_under" + StringConverter::toString(i))->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		getLabel("txt_bonus" + StringConverter::toString(i))->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	}
	
	Nx::Label* _bonusGuideText = getLabel("txt_guide");
	Nx::Label* _bottomText = getLabel("txt_bottommessage");


	string _TimeLeft = GameDataManager::getSingletonPtr()->GetRemainWeeklyBonusTime(SHOW_TIME_DAY);
	getLabel("txt_timelimit_under")->setString(_TimeLeft.c_str());
	getLabel("txt_timelimit")->setString(_TimeLeft.c_str());

	W_GameData* _pData = GameDataManager::getSingletonPtr()->GetGameDataPtr();

	int _size = _pData->pointweeklyrankdata_size();

	for (int _i = 0; _i < 16; _i++)
	{
		W_PointWeeklyRankData _pReplayRank = _pData->pointweeklyrankdata(_i);

		string _bonusNumberText = "";

		if (_pReplayRank.has_minrank() && _pReplayRank.has_maxrank())
		{
			if (_pReplayRank.maxrank() == _pReplayRank.minrank())
			{
				_bonusNumberText = StringConverter::toString(_pReplayRank.maxrank()) + GameStringDepot::getSingleton().getString("TXT_RANK");
			}
			else
			{
				_bonusNumberText = StringConverter::toString(_pReplayRank.minrank()) + "~" + StringConverter::toString(_pReplayRank.maxrank());
				if (_pReplayRank.ranktype() ==  W_PointWeeklyRankData_eWeeklyRankType_AbsRank)
					_bonusNumberText += GameStringDepot::getSingleton().getString("TXT_RANK");
				else
					_bonusNumberText += GameStringDepot::getSingleton().getString("TXT_PERCENT");
			}
		}

		//보너스 설정.
		if (_i == 1 || _i == 2)
		{
			string _number = "txt_classnumber" + StringConverter::toString(_i + 1);
			string _numberShadow = "txt_classnumber_under" + StringConverter::toString(_i + 1);
			Nx::Label* _classNumber = getLabel(_number);
			Nx::Label* _classNumberShadow = getLabel(_numberShadow);

			_classNumber->setString(_bonusNumberText.c_str());
			_classNumberShadow->setString(_bonusNumberText.c_str());

		}
		else if (_i > 2)
		{
			string _number = "txt_classnumber" + StringConverter::toString(_i + 1);
			Nx::Label* _classNumber = getLabel(_number);

			_classNumber->setString(_bonusNumberText.c_str());
		}

		string LabelName1 = "txt_bonus" + StringConverter::toString(_i + 1);
		string LabelName2 = "txt_bonus_under" + StringConverter::toString(_i + 1);

		Nx::Label* _BounusText = getLabel(LabelName1);
		Nx::Label* _BounusShadow = getLabel(LabelName2);

		string _skelName = "skel_gift_";
		if (_i < 9)
		{
			_skelName += "0" + StringConverter::toString(_i + 1);
		}
		else
		{
			_skelName += StringConverter::toString(_i + 1);
		}
		

		SkelObject* _bonusIcon = getSkel(_skelName);

		if (_pReplayRank.has_rewardinfo())
		{
			int _size = _pReplayRank.rewardinfo().rewardset_size();
			string moneyData = "";
			for (int _count = 0; _count < _size; _count++)
			{
				eResourceType _type = _pReplayRank.rewardinfo().rewardset(_count).type();
				int64 _amount = _pReplayRank.rewardinfo().rewardset(_count).amount();

				switch (_type)
				{
				case  CASH:
					if (_i > 2)
					{
						_bonusIcon->playAnimation("gift_ruby01");
					}
					_BounusText->setString(StringConverter::toString(_amount).c_str());
					_BounusShadow->setString(StringConverter::toString(_amount).c_str());
					break;
				case GAMEMONEY:
					_bonusIcon->playAnimation("gift_gold01");
					moneyData = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_amount));
					_BounusText->setString(moneyData.c_str());
					_BounusShadow->setString(moneyData.c_str());
					break;
				case CHIP:
					_bonusIcon->playAnimation("gift_chip01");
					_BounusText->setString(StringConverter::toString(_amount).c_str());
					_BounusShadow->setString(StringConverter::toString(_amount).c_str());
					break;
				case CHARACTER:
					break;
				}
			}
		}
	}
	setVisible(true);
}

void CustomPopupPanel::MakeReplayInfoPanel()
{
	GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_POPUP);

	construct(getMxmlPath() + "dmy_replayinfo.mxml");
	Button * m_WeekGiftBtn = getButton("sbtn_cancel");
	m_WeekGiftBtn->setListener(this);
	m_WeekGiftBtn->setTouchable(true);
	m_WeekGiftBtn->getButtonSkelObject()->setSkin("mark_cancel");

	W_ReplaySaveInfo* _pInfo = GameDataManager::getSingletonPtr()->m_ReplaySaveList[mParam1];

	if (_pInfo == NULL)
		return;

	GamePlaySummaryData summaryData = _pInfo->gamesummarydata();
	if (_pInfo->title().length() == 0)
	{
		int count = 0;
		GamePlaySummaryData summaryData = _pInfo->gamesummarydata();

		string titleStr = GameDataManager::getSingletonPtr()->GetChannelGradeName(_pInfo->channelid());

		if (titleStr.length() > 0)
		{
			titleStr = "[" + titleStr + "] ";
		}

		UserSummaryInfo userInfo;
		for (int i = 0, j = summaryData.usersummaryinfo_size(); i < j; i++)
		{
			userInfo = summaryData.usersummaryinfo(i);
			if (userInfo.winkind() >= WinKind::GIVEUP_WIN)
			{
				if (count > 0)
					titleStr += ",";
				titleStr += userInfo.nickname();
				count++;
			}
		}

		if (count >= 1) {
			titleStr = NxGetFormatString(GameStringDepot::getSingleton().getString("TXT_OF_REPLAY"), titleStr);
		}
	}	
	string path;

	int infosize = summaryData.usersummaryinfo_size();
	int * index = new int[infosize];
	int64 * money = new int64[infosize];

	for (int i = 0; i < infosize; i++)
	{
		index[i] = i;
		money[i] = 0;
	}

	for (int i = 0; i < infosize; i++)
	{
		index[i] = i;
		money[i] = summaryData.usersummaryinfo(i).potmoney();
	}

	// 획득 머니에 따라 소팅 시작.
	int max, tmp;
	int64 data1, data2;
	for (int i = 0; i < infosize - 1; i++)
	{
		max = i;
		for (int j = i + 1; j < infosize; j++)
		{
			data1 = money[index[max]];
			data2 = money[index[j]];

			if (data1 < data2)
				max = j;
		}

		if (i != max)
		{
			tmp = index[i];
			index[i] = index[max];
			index[max] = tmp;
		}
	}

	UserSummaryInfo userInfo;
	for (int i = 0; i < infosize; i++)
	{
		userInfo = summaryData.usersummaryinfo(index[i]);
		PokerPlayerResultPanel * mPlayerResultPanel = new PokerPlayerResultPanel();
		path = "dmy_result_board_slot";
		path += StringConverter::toString(i + 1);

		//mPlayerResultPanel[i]->setPositionX(getImage(path.c_str())->getPositionX() - getDummy(path.c_str()).size.width / 2.0f + 1);
		//mPlayerResultPanel[i]->setPositionY(getImage(path.c_str())->getPositionY() - getDummy(path.c_str()).size.height / 2.0f);

		mPlayerResultPanel->setPosition(getImage(path.c_str())->getPosition());
		mPlayerResultPanel->initPanel(this);
		addChild(mPlayerResultPanel);
		mPlayerResultPanel->release();
		//mPlayerResultPanel[i]->HidePanel();
		mPlayerResultPanel->setVisible(true);

		string nickname = userInfo.nickname();
		mPlayerResultPanel->SetData(summaryData.gamekind(), 
									userInfo.winkind(), 
									nickname,
									userInfo.dbidx() == GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->GetDid(), 
									userInfo.highjokbokind(), 
									userInfo.lowjokbokind(), 
									userInfo.potmoney());
	}

	//title 이름
	getLabel("txt_replaytitle")->setString(_pInfo->title().c_str());
	//게임 사진
	getSkel("skel_symbol")->playAnimation(PokerResourceHelper::getGameKindIcon(summaryData.gamekind()));
	//ok 버튼
	CCPoint _BtnPos = getDummy("dmy_button_small").origin;
	m_OkButtonPanel = new Panel;
	m_OkButtonPanel->construct(getMxmlPath() + "dmy_button_small.mxml");
	m_OkButtonPanel->getLabel("txt_button_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_OkButtonPanel->getLabel("txt_button")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_OkButtonPanel->getButton("sbtn_button")->setSkelAnimation("button_smiddle_y");
	string buttonStr = GameStringDepot::getSingletonPtr()->getString("TXT_REPLAY_PLAY_BUTTON");	
	m_OkButtonPanel->getLabel("txt_button_under")->setString(buttonStr.c_str());
	m_OkButtonPanel->getLabel("txt_button")->setString(buttonStr.c_str());
	m_OkButtonPanel->setPositionX(_BtnPos.x);
	m_OkButtonPanel->setPositionY(-_BtnPos.y);
	addChild(m_OkButtonPanel);
	m_OkButtonPanel->release();
	m_OkButtonPanel->getButton("sbtn_button")->setListener(this);
	m_OkButtonPanel->getButton("sbtn_button")->setName("sbtn_small_button_4_stay");



	CCPoint _ScorePos = getDummy("dmy_number_score").origin;
	CCSize _ScoreSize = getDummy("dmy_number_score").size;
	_ScorePos.y = DESIGN_HEIGHT - _ScorePos.y - (_ScoreSize.height / 2);
	CCLabelBMFont* m_ScoreLabel = CCLabelBMFont::create("", "fonts/number_score.fnt");
	m_ScoreLabel->setContentSize(_ScoreSize);
	m_ScoreLabel->retain();
	m_ScoreLabel->setAnchorPoint(ccp(0.f, 0.5f));
	m_ScoreLabel->setScale(1.f);
	m_ScoreLabel->setPosition(_ScorePos);
	addChild(m_ScoreLabel);
	m_ScoreLabel->release();
	m_ScoreLabel->setString(StringConverter::toString(_pInfo->point()).c_str());

}

void CustomPopupPanel::clearThisPanel()
{
	if(this->isDynamic())
		LayerManager::getSingleton().popLayer(this);

	if (mType == WEB_VIEW_TYPE)
	{
		GameDataManager::getSingletonPtr()->CloseUrl();
		GameDataManager::getSingletonPtr()->m_WebViewPanel = nullptr;
	}
}

void CustomPopupPanel::onRefresh()
{
	setVisible( true );

}


void CustomPopupPanel::onAnimationEnded(const string& ani)
{
	if (!isVisible())
		return;
}

void CustomPopupPanel::ExeEvent()
{
	clearThisPanel();
	/*
	if (mEventName == mMiddleOkBtn->getName())
	{
		clearThisPanel();
		if (mGeneralListener)
			(mTarget->*mGeneralListener)(mOkEventMsg);
		else
			fireMessage(mOkEventMsg);
	}
	else if (mEventName == mOkBtn->getName())
	{
		clearThisPanel();
		if (mGeneralListener)
			(mTarget->*mGeneralListener)(mOkEventMsg);
		else
			fireMessage(mOkEventMsg);
	}
	else if (mEventName == mCancelBtn->getName())
	{
		clearThisPanel();
		if (mGeneralListener)
			(mTarget->*mGeneralListener)(mCancelEventMsg);
		else
			fireMessage(mCancelEventMsg);
	}
	else if (mEventName == mExitBtn->getName())
	{
		clearThisPanel();
		if (mGeneralListener)
			(mTarget->*mGeneralListener)(mExitEventMsg);
		else
			fireMessage(mExitEventMsg);
	}
	*/
}

void CustomPopupPanel::MakeUserReplayBoxPanel()
{
	GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_POPUP);

	PopupUserReplayPanel* pPanel = new PopupUserReplayPanel();
	pPanel->getButton("sbtn_cancel")->setListener(this);
	addChild(pPanel, 15);
	pPanel->release();
	pPanel->SetReplayList();	
	pPanel->SetUserReplyBoxTitle(GameDataManager::getSingletonPtr()->m_ReplayUserName.c_str());
	pPanel->setVisible(true);
}

void CustomPopupPanel::MakeUserBankPanel()
{
	GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_POPUP);

	PopupUserBankPanel* pPanel = new PopupUserBankPanel();
	addChild(pPanel, 15);
	pPanel->release();
	pPanel->setVisible(true);
}

void CustomPopupPanel::MakeCharacterInfoPanel()
{
	GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_POPUP);

	construct(getMxmlPath() + "dmy_characterinfo.mxml");
	Button * m_WeekGiftBtn = getButton("sbtn_cancel");
	m_WeekGiftBtn->setListener(this);

	CCSize _contentSize = getDummy("dmy_characterinfo").size;
	CCPoint _pos = getDummy("dmy_characterinfo").origin;

	//setPosition(ccp(_pos.x, _contentSize.height + _pos.y - DESIGN_HEIGHT));// _contentSize.width / -2.f, _contentSize.height / -2.f));

	

	Button* _CharacterTouch = new Button("btn_Touch", Button::NoPressImg);
	_CharacterTouch->setSkel("ui/alluse_board_8888", "toastbar1_loop", _contentSize);
	_CharacterTouch->setVisible(false);
	_CharacterTouch->setPosition(ccp(0, 0));
	addChild(_CharacterTouch);
	_CharacterTouch->release();
	_CharacterTouch->setListener(this);

	getLabel("txt_title")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_limit")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_character_name")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_gender")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_gender_sum")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_age")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_age_sum")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_job")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_job_sum")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

	getLabel("txt_title")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_CHARATER_INFO").c_str());
	getLabel("txt_title_under")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_CHARATER_INFO").c_str());

	getLabel("txt_gender")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_CHARATER_GENDER").c_str());
	getLabel("txt_age")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_CHARATER_AGE").c_str());
	getLabel("txt_job")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_CHARATER_JOB").c_str());

	getButton("sbtn_cancel")->setListener(this);

	CCPoint _BtnPos = getDummy("dmy_button_smiddle").origin;

	m_OkButtonPanel = new Panel;
	m_OkButtonPanel->construct(getMxmlPath() + "dmy_button_smiddle.mxml");
	m_OkButtonPanel->getLabel("txt_button_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_OkButtonPanel->getLabel("txt_button")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_OkButtonPanel->getLabel("txt_button_under2")->setVisible(false);
	m_OkButtonPanel->getLabel("txt_button2")->setVisible(false);
	m_OkButtonPanel->getSkel("skel_icon_gold2")->setVisible(false);
	m_OkButtonPanel->getButton("sbtn_button")->setSkelAnimation("button_smiddle_y");

	string buttonStr = GameStringDepot::getSingletonPtr()->getString("MEMBER_BTN_BUY");
	if (mType == CHAR_INFO_INVEN_TYPE) {
		//만약 선택됐다면 
		if (GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_CharacterIdx == mParam1) {
			buttonStr = GameStringDepot::getSingletonPtr()->getString("TXT_SELECTED_UNIT");
			m_OkButtonPanel->getLabel("txt_button")->setColor(StringConverter::parseColor3B("ffd042"));
			m_OkButtonPanel->getButton("sbtn_button")->setEnable(false);
			m_OkButtonPanel->getButton("sbtn_button")->setSkelAnimation("button_smiddle_use");
		}
		else 
			buttonStr = GameStringDepot::getSingletonPtr()->getString("CHARACTER_INFO_INVEN_BTN_TXT");
	}
	m_OkButtonPanel->getLabel("txt_button_under")->setString(buttonStr.c_str());
	m_OkButtonPanel->getLabel("txt_button")->setString(buttonStr.c_str());

	m_OkButtonPanel->setPositionX(_BtnPos.x);
	m_OkButtonPanel->setPositionY(-_BtnPos.y);
	addChild(m_OkButtonPanel);
	m_OkButtonPanel->release();
	
	m_OkButtonPanel->getButton("sbtn_button")->setListener(this);
	m_OkButtonPanel->getButton("sbtn_button")->setName("sbtn_Ok_btn");

	int count = GameDataManager::getSingletonPtr()->GetGameDataPtr()->characterdata_size();
	for (int i = 0; i < count; i++)
	{
		W_CharacterData characterData = GameDataManager::getSingletonPtr()->GetGameDataPtr()->characterdata(i);
		if (characterData.id() == mParam1)
		{
			getLabel("txt_story_content")->setString(characterData.desc().c_str());
			getLabel("txt_character_name")->setString(characterData.name().c_str());
			getLabel("txt_gender_sum")->setString(characterData.gender().c_str());
			getLabel("txt_age_sum")->setString(characterData.age().c_str());
			getLabel("txt_job_sum")->setString(characterData.job().c_str());

			string _sDesc = "";
			int _size = characterData.effect_size();
			int realEffectSize = 0;
			for (int _i = 0; _i < _size; _i++)
			{
				W_CharacterData_CharacterEffect _dataEff = characterData.effect(_i);
				if (_dataEff.type() != W_CharacterData_eEffectType_None) {
					if (realEffectSize != 0)
						_sDesc += "\n";
					_sDesc += _dataEff.desc();
					realEffectSize++;
				}
			}

			getLabel("str_spec")->setString(_sDesc.c_str());

			//getLabel("str_gold_goods_top")->

			getLabel("str_gold_goods_top")->setVisible(false);
			getLabel("str_gold_goods_center")->setVisible(false);
			getLabel("str_gold_goods_bottom")->setVisible(false);
			if (mType == CHAR_INFO_TYPE) {
				
				int shopIdx = PokerShopHelper::getShopDataIndex(characterData.id());
				W_CharacterShopData _ShopInfo = GameDataManager::getSingletonPtr()->GetGameDataPtr()->charactershopdata(shopIdx);
				string _rewardText = "";
				if (_ShopInfo.has_rewardinfo())
				{
					int _rewardSize = _ShopInfo.rewardinfo().rewardset_size();

					for (int _j = 0; _j < _rewardSize; _j++)
					{
						W_RewardInfo_RewardSet _set = _ShopInfo.rewardinfo().rewardset(_j);


						//if (_set.has_id());

						if (_set.has_amount())
						{
							_rewardText += GameStringDepot::getSingleton().getString("TXT_IMMEDIATELY");
							_rewardText += " " + GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_set.amount()));
							_rewardText += " " + GameStringDepot::getSingleton().getString("TXT_GET_UNIT");
						}
					}
				}
				if (realEffectSize == 2) {
					getLabel("str_gold_goods_top")->setVisible(true);
					getLabel("str_gold_goods_top")->setString(_rewardText.c_str());
				}
				else if (realEffectSize == 1) {
					getLabel("str_gold_goods_center")->setVisible(true);
					getLabel("str_gold_goods_center")->setString(_rewardText.c_str());
				}
				else if (realEffectSize == 0) {
					getLabel("str_gold_goods_bottom")->setVisible(true);
					getLabel("str_gold_goods_bottom")->setString(_rewardText.c_str());
				}
			}
			SetCharacterInfoPanel(mParam1);
			break;
		}
	}
	
	//능력치 뿌려준다.

	setVisible(true);
}

void CustomPopupPanel::SetCharacterInfoPanel(int _characterId)
{
	m_UpSkel = new SkelObject();
	m_DownSkel = new SkelObject();
	m_UpSkel->setSkelAnim(PokerResourceHelper::getCharacterOverSpineName(_characterId));
	m_DownSkel->setSkelAnim(PokerResourceHelper::getCharacterUnderSpineName(_characterId));	
	getImage("dmy_character1")->addChild(m_DownSkel);
	getImage("dmy_character1")->addChild(m_UpSkel);
	m_UpSkel->release();
	m_DownSkel->release();
	m_UpSkel->playAnimation("idle_stand", true);
	m_DownSkel->playAnimation("idle_stand", true);
}

void CustomPopupPanel::MakeFriendInfoPanel()
{
	GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_POPUP);

	construct(getMxmlPath() + "dmy_friendinfo.mxml");
	
	//Image
	getSkel("skel_panel_line_box1")->setVisible(false);
	getSkel("skel_panel_line_box2")->setVisible(false);
	getSkel("skel_panel_line_box3")->setVisible(false);
	getSkel("skel_panel_line_box4")->setVisible(false);

	//BUtton
	Button* _pReplayBtn = getButton("sbtn_small_button_4r_stay");
	Button* _pRemoveBtn = getButton("sbtn_small_button_4_stay");
	Button* _pExitBtn = getButton("sbtn_cancel");

	_pReplayBtn->getButtonSkelObject()->setSkin("txt_storage_tray");
	_pRemoveBtn->getButtonSkelObject()->setSkin("txt_frienddel");
	_pExitBtn->getButtonSkelObject()->setSkin("mark_cancel");

	getSkel("skel_small_title")->setSkin("title_friendinfo");

	_pReplayBtn->setName("FriendInfo_Replay");
	_pRemoveBtn->setName("FriendInfo_RemoveFriend");
	_pExitBtn->setName("FriendInfo_Close");

	_pReplayBtn->setListener(this);
	_pRemoveBtn->setListener(this);
	_pExitBtn->setListener(this);

	_pReplayBtn->setType(Button::NoPressImg);
	_pRemoveBtn->setType(Button::NoPressImg);
	_pExitBtn->setType(Button::NoPressImg);


	getLabel("txt_trophy")->setString("");
	getLabel("txt_record")->setString("");
	getLabel("txt_lastday")->setString("");



	W_FriendInfo* _info = nullptr;
	
	switch (mParam2)
	{
	case 1:
		_info = GameDataManager::getSingletonPtr()->m_SnsDataList[mParam1];
		break;
	case 2:
		_info = GameDataManager::getSingletonPtr()->m_FriendDataList[mParam1];
		break;
	case 3:
		break;
	case 4:
		break;
	}

	if (_info == nullptr)
		return;

	if (_info->has_name())
	{
		getLabel("txt_username")->setString(_info->name().c_str());
	}

	if (_info->has_connecttime())
	{
		getLabel("txt_lastday")->setString(_info->connecttime().c_str());
	}

	if (_info->has_characterid())
	{
// 		string _name = PokerResourceHelper::getCharacterImgName(_info->characterid());
// 		getSkel("skel_cha_thumbnail")->setSkin(_name);
	}

	if (_info->has_lose() && _info->has_win())
	{
		string _totalGame = StringConverter::toString(_info->win() + _info->lose()) + GameStringDepot::getSingletonPtr()->getString("TXT_TOTAL_GAME");
		string _winLose = "[" + StringConverter::toString(_info->win()) + GameStringDepot::getSingletonPtr()->getString("TXT_TOTAL_WIN") + " / " + StringConverter::toString(_info->lose()) + GameStringDepot::getSingletonPtr()->getString("TXT_TOTAL_LOSE") + "]";
		getLabel("txt_totalplay")->setString(_totalGame.c_str());
		getLabel("txt_winandlose")->setString(_winLose.c_str());
	}
	CCSize originSize = getDummy("skel_rankicon").size;
	CCSize iconSize = getDummy("dmy_rankicon").size;
	getSkel("skel_rankicon")->setScale(getScaleFit(originSize, iconSize));

	setVisible(true);
	getLabel("txt_title")->setString(GameStringDepot::getSingletonPtr()->getString("dmy_friendinfo_TITLE").c_str());
	getLabel("txt_title_under")->setString(GameStringDepot::getSingletonPtr()->getString("dmy_friendinfo_TITLE").c_str());

}

//void CustomPopupPanel::MakeChannelListPanel()
//{
//	if (mMainPanel != nullptr)
//		return;
//	
//	if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_7POKER)
//	{
//		GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_7POKER);
//	}
//	else if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_HIGH_LOW)
//	{
//		GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_HIGHLOW);
//	}
//	else if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_BADUKI)
//	{
//		GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_BADUKI);
//	}
//	else if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_HOLDEM)
//	{
//		GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_HOLDEM);
//	}
//
//	if (GameDataManager::getSingletonPtr()->m_pOptionValue->m_music == true)
//		SoundManager::getSingletonPtr()->playBGM("BGM_CHANNEL");
//
//
//	mMainPanel = new ChannelMainPannel();
//	addChild(mMainPanel, 15);
//	mMainPanel->release();
//	mMainPanel->setVisible(true);
//
//	//dynamic_cast<ChannelMainPannel*>(mMainPanel)->m_LeftUi->getButton("sbtn_lobbyleft_button1")->setListener(this);
//	//dynamic_cast<ChannelMainPannel*>(mMainPanel)->m_LeftUi->getButton("sbtn_lobbyleft_button2")->setListener(this);
//	//dynamic_cast<ChannelMainPannel*>(mMainPanel)->m_LeftUi->getButton("sbtn_lobbyleft_button3")->setListener(this);
//	//dynamic_cast<ChannelMainPannel*>(mMainPanel)->m_TopUi->getButton("sbtn_bank_button")->setListener(this);
//	//dynamic_cast<ChannelMainPannel*>(mMainPanel)->m_TopUi->getButton("sbtn_rubby_button")->setListener(this);
//	//dynamic_cast<ChannelMainPannel*>(mMainPanel)->m_TopUi->getButton("sbtn_option_button")->setListener(this);
//
//	GameDataManager::getSingletonPtr()->m_pChannelListPanel = this;
//
//	//LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
//	//if (_pScene == nullptr)
//	//	return;
//	//_pScene->LobbyVisible(false);
//}

void CustomPopupPanel::MakeChannelRoomPanel()
{

	construct(getMxmlPath() + "dmy_room_list_top.mxml");
	GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_CHANNELROOM);
	mChannelRoomMainPanel = new ChannelRoomMainPanel();
	mChannelRoomMainPanel->m_pRoomMakeBtn->setListener(this);
	mChannelRoomMainPanel->m_pRoomJoinBtn->setListener(this);
	mChannelRoomMainPanel->m_pRoomInputBtn->setListener(this);
	mChannelRoomMainPanel->m_pSearchBtn->setListener(this);
	mChannelRoomMainPanel->m_searchField->setListener(this);
	addChild(mChannelRoomMainPanel, 15);
	mChannelRoomMainPanel->release();
	mChannelRoomMainPanel->setVisible(true);
	CCPoint roomPos = getDummy("dmy_room_list_under").origin;		
	mChannelRoomMainPanel->setPositionX(roomPos.x);
	mChannelRoomMainPanel->setPositionY(-roomPos.y);
}

void CustomPopupPanel::UpdateChannelUiPanel()
{
	NXASSERT(false, "CHECK no Use here");
	if (mType != CHANNEL_ROOM_LIST_TYPE)
		return;
	if (mChannelRoomMainPanel)
		mChannelRoomMainPanel->m_pChannelRoomUi->UpdateChannelPage();
	return;
}

void CustomPopupPanel::MakeChannelRoomMakePannel()
{
	GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_POPUP);
	construct(getMxmlPath() + "dmy_make_room.mxml");
	setButtonListener(this);
	initPasswardData();

	Button * m_WeekGiftBtn = getButton("sbtn_cancel");	
	m_WeekGiftBtn->setTouchable(true, 0, false);
	mMakeRoomBtn = getButton("sbtn_button_enter"); 
	getLabel("str_secret_room_guide")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_CREATE_CHANNELROOM").c_str());
	getLabel("txt_title")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_MAKE_ROOM_UNIT").c_str());
	getLabel("txt_title_under")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_MAKE_ROOM_UNIT").c_str());
	string windowGameType = "";
	string buttonGameKind = "";
	if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_7POKER) {
		windowGameType = "panel_room_make_sevenpoker";
		buttonGameKind = "button_seven";
	}
	else if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_HIGH_LOW) {
		windowGameType = "panel_room_make_highlow";
		buttonGameKind = "button_highlow";
	}
	else if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_BADUKI) {
		windowGameType = "panel_room_make_badugi";
		buttonGameKind = "button_badugi";
	}
	else if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_HOLDEM) {
		windowGameType = "panel_room_make_texasholdem";
		buttonGameKind = "button_texas";
	}

	getSkel("skel_panel")->playAnimation(windowGameType);
	mMakeRoomBtn->setSkelAnimation(buttonGameKind);

	//초기화
	getLabel("txt_reset_under")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_INIT_UNIT").c_str());
	getLabel("txt_reset")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_INIT_UNIT").c_str());
	//자유방
	getLabel("txt_enter_under")->setString(GameStringDepot::getSingletonPtr()->getString("MAKE_BTN_NORMAL").c_str());
	getLabel("txt_enter")->setString(GameStringDepot::getSingletonPtr()->getString("MAKE_BTN_NORMAL").c_str());
	setVisible(true);
}

void CustomPopupPanel::MakeEnterChannelRoomPanel()
{
	GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_POPUP);
	construct(getMxmlPath() + "dmy_make_room.mxml");
	initPasswardData();
	setButtonListener(this);
	Button * m_WeekGiftBtn = getButton("sbtn_cancel");
	m_WeekGiftBtn->setTouchable(true, 0, false);
	mMakeRoomBtn = getButton("sbtn_button_enter"); 
	getLabel("str_secret_room_guide")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_ENTER_SECRETROOM").c_str());
	getLabel("txt_title")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_ENTER_ROOM_UNIT").c_str());
	getLabel("txt_title_under")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_ENTER_ROOM_UNIT").c_str());
	string windowGameType = "";
	string buttonGameKind = "";
	if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_7POKER) {
		windowGameType = "panel_room_make_sevenpoker";
		buttonGameKind = "button_seven";
	}
	else if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_HIGH_LOW) {
		windowGameType = "panel_room_make_highlow";
		buttonGameKind = "button_highlow";
	}
	else if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_BADUKI) {
		windowGameType = "panel_room_make_badugi";
		buttonGameKind = "button_badugi";
	}
	else if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_HOLDEM) {
		windowGameType = "panel_room_make_texasholdem";
		buttonGameKind = "button_texas";
	}

	getSkel("skel_panel")->playAnimation(windowGameType);
	mMakeRoomBtn->setSkelAnimation(buttonGameKind);
	//초기화
	getLabel("txt_reset_under")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_INIT_UNIT").c_str());
	getLabel("txt_reset")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_INIT_UNIT").c_str());
	//입장
	getLabel("txt_enter_under")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_WAITTING_LABEL").c_str());
	getLabel("txt_enter")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_WAITTING_LABEL").c_str());
	setVisible(true);
}

void CustomPopupPanel::onDetached()
{
	CCLog("CustomPopupPanel::onDetached()");
	if (mType == CHANNEL_ROOM_LIST_TYPE)
	{
		string _searchTxt = mChannelRoomMainPanel->getTextField("fld_room_search")->getString();
		if (_searchTxt == "")
		{
			m_searchIdx = -1;
		}
		else
		{
			m_searchIdx = StringConverter::parseInt(_searchTxt);
		}
		
	}

	if (mType == MAKE_CHANNEL_ROOM_TYPE)
	{
		
		return;
	}
	
	if (mType == ENTER_CHANNEL_ROOM_TYPE)
	{
		
		return;
	}
}

void CustomPopupPanel::MakeRankingTutorialPanel()
{
	GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_TUTORIAL);
	RankingTutorialPanel* pPanel = new RankingTutorialPanel();
	pPanel->getButton("sbtn_touch_size")->setListener(this);
	addChild(pPanel, 15);
	pPanel->release();
	pPanel->setVisible(true);
}

void CustomPopupPanel::MakeReplayTutorialPanel()
{
	GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_TUTORIAL);
	ReplayTutorialPanel* pPanel = new ReplayTutorialPanel();
	pPanel->getButton("sbtn_touch_size")->setListener(this);
	addChild(pPanel, 15);
	pPanel->release();
	pPanel->setVisible(true);
}

void CustomPopupPanel::RankingOnClick(const string& name)
{
	if (name == "sbtn_touch_size")
	{
		NXASSERT(false, "NO CHECK HERE");
// 		if (dynamic_cast<RankingTutorialPanel*>(mMainPanel)->m_TutorialStep == 3)
// 		{
// 			int _page = dynamic_cast<RankingTutorialPanel*>(mMainPanel)->m_pageIndex;
// 			if (_page == 4)
// 			{
// 				dynamic_cast<RankingTutorialPanel*>(mMainPanel)->m_TutorialStep = 4;
// 				GameDataManager::getSingletonPtr()->SaveRankingTutorialComplate();
// 				runAction(CCSequence::create(
// 					CCDelayTime::create(0.6f),
// 					CCCallFunc::create(this, callfunc_selector(CustomPopupPanel::ClosePanel)),
// 					NULL));
// 				return;
// 			}
// 			dynamic_cast<RankingTutorialPanel*>(mMainPanel)->ShowText(_page);
// 			dynamic_cast<RankingTutorialPanel*>(mMainPanel)->ShowPage(_page);
// 			dynamic_cast<RankingTutorialPanel*>(mMainPanel)->m_pageIndex++;
// 		}		
	}
}

void CustomPopupPanel::ReplayOnClick(const string& name)
{
	if (name == "sbtn_touch_size")
	{
		NXASSERT(false, "NO CHECK HERE");
// 		if (dynamic_cast<ReplayTutorialPanel*>(mMainPanel)->m_TutorialStep == 3)
// 		{
// 			int _page = dynamic_cast<ReplayTutorialPanel*>(mMainPanel)->m_pageIndex;
// 			if (_page == 4)
// 			{
// 				dynamic_cast<ReplayTutorialPanel*>(mMainPanel)->m_TutorialStep = 4;
// 				GameDataManager::getSingletonPtr()->SaveReplayTutorialComplate();
// 
// 				runAction(CCSequence::create(
// 					CCDelayTime::create(0.6f),
// 					CCCallFunc::create(this, callfunc_selector(CustomPopupPanel::ClosePanel)),
// 					NULL));
// 
// 				return;
// 			}
// 			dynamic_cast<ReplayTutorialPanel*>(mMainPanel)->ShowText(_page);
// 			dynamic_cast<ReplayTutorialPanel*>(mMainPanel)->ShowPage(_page);
// 			dynamic_cast<ReplayTutorialPanel*>(mMainPanel)->m_pageIndex++;
// 		}		
	}
}

void CustomPopupPanel::ClosePanel()
{
	ShowPanel(false);
}

bool CustomPopupPanel::handling(STCMD &stCmd)
{
	return false;
}

bool CustomPopupPanel::isCorrectPassward()
{
	return mPasswardPos == 4;
}

void CustomPopupPanel::initPassward()
{
	mPasswardPos = 0;
	mPassward_1 = DEFAULT_PASSWARD_STR;
	mPassward_2 = DEFAULT_PASSWARD_STR;
	mPassward_3 = DEFAULT_PASSWARD_STR;
	mPassward_4 = DEFAULT_PASSWARD_STR;
	refreshPassward();
}

void CustomPopupPanel::backPassward()
{
	if (mPasswardPos > 0) {
		mPasswardPos--;
	
		if (mPasswardPos < 1)
			mPassward_1 = DEFAULT_PASSWARD_STR;

		if (mPasswardPos < 2)
			mPassward_2 = DEFAULT_PASSWARD_STR;

		if (mPasswardPos < 3)
			mPassward_3 = DEFAULT_PASSWARD_STR;

		if (mPasswardPos < 4)
			mPassward_4 = DEFAULT_PASSWARD_STR;
	}	

	refreshPassward();
}

void CustomPopupPanel::pushPassward(int passwardNumber)
{
	if (mPasswardPos < 4) {
		mPasswardPos++;
		if (mPasswardPos == 1)
			mPassward_1 = StringConverter::toString(passwardNumber);

		if (mPasswardPos == 2)
			mPassward_2 = StringConverter::toString(passwardNumber);

		if (mPasswardPos == 3)
			mPassward_3 = StringConverter::toString(passwardNumber);

		if (mPasswardPos == 4)
			mPassward_4 = StringConverter::toString(passwardNumber);
	}
	refreshPassward();
}

void CustomPopupPanel::initPasswardData()
{
	mNum1Btn = getButton("sbtn_button_number1");
	mNum2Btn = getButton("sbtn_button_number2");
	mNum3Btn = getButton("sbtn_button_number3");
	mNum4Btn = getButton("sbtn_button_number4");
	mNum5Btn = getButton("sbtn_button_number5");
	mNum6Btn = getButton("sbtn_button_number6");
	mNum7Btn = getButton("sbtn_button_number7");
	mNum8Btn = getButton("sbtn_button_number8");
	mNum9Btn = getButton("sbtn_button_number9");
	mNum0Btn = getButton("sbtn_button_number0");
	mBackBtn = getButton("sbtn_button_backs");
	mInitNumBtn = getButton("sbtn_button_reset");

	mFocusBottom1 = getLabel("txt_secret_number1");
	mFocusBottom2 = getLabel("txt_secret_number2");
	mFocusBottom3 = getLabel("txt_secret_number3");
	mFocusBottom4 = getLabel("txt_secret_number4");
	initPassward();	
}

void CustomPopupPanel::refreshPassward()
{
	mFocusBottom1->setString(mPassward_1.c_str());
	mFocusBottom2->setString(mPassward_2.c_str());
	mFocusBottom3->setString(mPassward_3.c_str());
	mFocusBottom4->setString(mPassward_4.c_str());

	
	if (mFocusBottom1->getActionByTag(REPEAT_TAG) != nullptr && mPasswardPos != 0) {
		mFocusBottom1->stopAllActions();
		mFocusBottom1->runAction(PokerResourceHelper::getRestoreTwinkle());
	}
	if (mFocusBottom2->getActionByTag(REPEAT_TAG) != nullptr && mPasswardPos != 1) {
		mFocusBottom2->stopAllActions();
		mFocusBottom2->runAction(PokerResourceHelper::getRestoreTwinkle());
	}

	if (mFocusBottom3->getActionByTag(REPEAT_TAG) != nullptr && mPasswardPos != 2) {
		mFocusBottom3->stopAllActions();
		mFocusBottom3->runAction(PokerResourceHelper::getRestoreTwinkle());
	}

	if (mFocusBottom4->getActionByTag(REPEAT_TAG) != nullptr && mPasswardPos != 3) {
		mFocusBottom4->stopAllActions();
		mFocusBottom4->runAction(PokerResourceHelper::getRestoreTwinkle());
	}

	if (mPasswardPos == 0) {
		if (mFocusBottom1->getActionByTag(REPEAT_TAG) == nullptr) {
			CCAction* repeatAction = PokerResourceHelper::getRepeatTwinkle();
			repeatAction->setTag(REPEAT_TAG);
			mFocusBottom1->runAction(repeatAction);
		}
	}
	else if (mPasswardPos == 1) {
		if (mFocusBottom2->getActionByTag(REPEAT_TAG) == nullptr) {
			CCAction* repeatAction = PokerResourceHelper::getRepeatTwinkle();
			repeatAction->setTag(REPEAT_TAG);
			mFocusBottom2->runAction(repeatAction);
		}
	}
	else if (mPasswardPos == 2) {
		if (mFocusBottom3->getActionByTag(REPEAT_TAG) == nullptr) {
			CCAction* repeatAction = PokerResourceHelper::getRepeatTwinkle();
			repeatAction->setTag(REPEAT_TAG);
			mFocusBottom3->runAction(repeatAction);
		}
	}
	else if (mPasswardPos == 3) {
		if (mFocusBottom4->getActionByTag(REPEAT_TAG) == nullptr) {
			CCAction* repeatAction = PokerResourceHelper::getRepeatTwinkle();
			repeatAction->setTag(REPEAT_TAG);
			mFocusBottom4->runAction(repeatAction);
		}
	}	

	if (mMakeRoomBtn) {
		if (mPasswardPos == 0 || mPasswardPos == 4) {
			mMakeRoomBtn->setEnable(true);
			mMakeRoomBtn->setGrayscale(false);
		}
		else {
			mMakeRoomBtn->setEnable(false);
			mMakeRoomBtn->setGrayscale(true);
		}
	}

	if (mPasswardPos == 0) {
		//자유방
		getLabel("txt_enter_under")->setString(GameStringDepot::getSingletonPtr()->getString("MAKE_BTN_NORMAL").c_str());
		getLabel("txt_enter")->setString(GameStringDepot::getSingletonPtr()->getString("MAKE_BTN_NORMAL").c_str());
	}
	else {
		//비밀방
		getLabel("txt_enter_under")->setString(GameStringDepot::getSingletonPtr()->getString("MAKE_BTN_SCRIT").c_str());
		getLabel("txt_enter")->setString(GameStringDepot::getSingletonPtr()->getString("MAKE_BTN_SCRIT").c_str());
	}
}
