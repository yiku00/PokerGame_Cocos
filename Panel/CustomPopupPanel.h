/********************************************************************
	file name:	CustomPopupPanel.h
	
	purpose:	각자의 mxml 데이터를 가지고 알아서 만드는 판넬
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "W_LetterInfo.pb.h"
#include "ChannelRoomMainPanel.h"
//#include "TypeDefine.pb.h"

class CustomPopupPanel : public Panel, public Button::Listener, public SkelObject::Listener, public TextField::Listener
{
public:
	enum CustomPopupType{
		WEEKLY_REWOARD_TYPE,		//
		POINT_WEEKLY_REWARD_TYPE,
		REPLAY_INFO_TYPE,
		USER_REPLAY_BOX_TYPE,
		//USER_BANK_PANL_TYPE,
		CHAR_INFO_TYPE,
		CHAR_INFO_INVEN_TYPE,
		FRIEND_INFO_TYPE,
		//CHANNEL_LIST_TYPE,
		CHANNEL_ROOM_LIST_TYPE,
		MAKE_CHANNEL_ROOM_TYPE,
		ENTER_CHANNEL_ROOM_TYPE,
		RANKING_TUTORIAL_TYPE,
		REPLAY_TUTORIAL_TYPE,

		WEB_VIEW_TYPE,
	};

	enum CharaterHoldType
	{
		TYPE_HOLD_ITEM,
		TYPE_NONE_ITEM,
		TYPE_EXPIRED_ITEM
	};

public:
	CustomPopupPanel(CustomPopupType type, int param1 = 0, int param2 = 0, int param3 = 0, string param4 = "");
	~CustomPopupPanel();

	// Button::Listener
	virtual void onClicked(const string& name);
	virtual void onAnimationEnded(const string& ani);
	// TextField::Listener
	virtual void onDetached();
	virtual void onRefresh();

	void setGeneralListener(CCObject* target, ObjectListener listener) { mTarget = target; mGeneralListener = listener; }
	//void UpdateChannelListPanel();
	void UpdateChannelUiPanel();
	void ShowPanel(bool isVisible);
	void SetHoldItem(int _type);

public:
	virtual bool handling(STCMD &stCmd);

public:
	void clearThisPanel();

private:
	void initPanel();
	void MakeWeeklyRewardPanel();
	
	
	void ExeEvent();
	void MakePointWeeklyRewardPanel();
	void MakeUserReplayBoxPanel();
	void MakeUserBankPanel();

	void MakeReplayInfoPanel();
	void MakeCharacterInfoPanel();
	void SetCharacterInfoPanel(int _characterId);
	void MakeFriendInfoPanel();

	//void MakeChannelListPanel();

	void MakeChannelRoomPanel();
	void MakeChannelRoomMakePannel();
	void MakeEnterChannelRoomPanel();
	void ChannelListOnClicked(const string& name);
	void ChannelRoomOnClicked(const string& name);
	void ChannelRoomListOnClicked(const string& name);
	void FriendInfoOnClicked(const string& name);
	void WebViewOnClicked(const string& name);
	void CharacterInfoOnClicked(const string& name);
	void MakeWebViewPanel();

	void MakeRankingTutorialPanel();
	void RankingOnClick(const string& name);
	void MakeReplayTutorialPanel();
	void ReplayOnClick(const string& name);
	void ClosePanel();

	void TouchCharacter();

	bool isCorrectPassward();

	void initPasswardData();
	void initPassward();
	void backPassward();
	void pushPassward(int passwardNumber);
	void refreshPassward();


private:
	Panel* m_OkButtonPanel;

	CustomPopupType mType;

	CCObject* mTarget;
	ObjectListener mGeneralListener;
	string	mEventName;

	CCPoint m_ButtonStartPosition;

	int mParam1;
	int mParam2;
	int mParam3;

	string mParam4;
	string m_Password;

	SkelObject* m_UpSkel;
	SkelObject* m_DownSkel;
	ChannelRoomMainPanel* mChannelRoomMainPanel;

	Button* mMakeRoomBtn;

	int mPasswardPos;
	string mPassward_1;
	string mPassward_2;
	string mPassward_3;
	string mPassward_4;

	Button* mNum1Btn;
	Button* mNum2Btn;
	Button* mNum3Btn;
	Button* mNum4Btn;
	Button* mNum5Btn;
	Button* mNum6Btn;
	Button* mNum7Btn;
	Button* mNum8Btn;
	Button* mNum9Btn;
	Button* mNum0Btn;
	Button* mBackBtn;
	Button* mInitNumBtn;

	Nx::Label* mFocusBottom1;
	Nx::Label* mFocusBottom2;
	Nx::Label* mFocusBottom3;
	Nx::Label* mFocusBottom4;

public:
	bool m_isSearching;
	int m_searchIdx;

};
