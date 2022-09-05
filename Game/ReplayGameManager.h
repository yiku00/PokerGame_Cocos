#pragma once

#include "NxFramework.h"
#include "NxSingleton.h"
#include "NxDefine.h"
#include "GamePlayData.pb.h"
#include "GameRoomInfo.h"
#include "CustomTextView.h"

#define CHAT_BOARD_SIZE CCSize(310.f, 500.f)
#define CHAT_CELL_SIZE CCSize(310.f, 21.f)

enum 
{
	COMMENT_NAME = 0,
	COMMENT_TEXT = 1,
	COMMENT_COLOR = 2,
};

class UserCommentData : public Panel
{
public:
	UserCommentData();
	UserCommentData(int64 _time, int _id, string _nick, string _text, ccColor4B _color4b = ccc4(ccWHITE.r, ccWHITE.g, ccWHITE.b, 0xFF));
	~UserCommentData();
	void ShowUserComment();
	void CloseUserComment();
	void RemoveUserComment();

	void SetTextBubble(int _size);

public:
	int64 m_Time;
	int m_UID;
	string m_UserNickname;
	string m_Comment;
	ccColor4B m_Color;
	
	CCNode* m_BubbleNode;
	SkelObject* m_Background[3];
	//SkelObject* m_Icon;
	Nx::Label* m_IdLabel;
	Nx::Label* m_TextLabel;
};

class ReplayGameManager : public Singleton < ReplayGameManager >, public Nx::Layer::Listener
{
public:
	ReplayGameManager();
	~ReplayGameManager();
	
	virtual void onLayerMessage(const string& msg);//Layer::Listener

	bool initialize(const GamePlayData& _data);

	void MakeReplayRoom();
	void Update(float _dt);
	void UpdateUserComment(int64 _time);
	void ReplayReset();
	void ReplayPause();
	void ReplayEnd();
	void CloseReplay();
	void PlayData();
	bool IsReplayDataReady() { return m_ReplayDataReady; }
	void ParsingLogData(int _idx);

	void ResetUserComment();
	void RemoveCommentData();

	int getCommentIndex() { return m_UserCommentIndex; }
	
	void AddUserCommentData(int64 _time, int _id, string _nick, string _text);
	void InsertUserCommentData(int64 _time, int _id, string _nick, string _text, int _index);
	void StartReplay();
	void ClickBoardSetButton();

	void MakeChatRistScrollPanel();
	void ClearChatListScroll();
	
	int GetNowCommentIndex() { return m_UserCommentIndex; }

	void InputChat();
	void SendCommentData();
	void SetReplaySeq(int64 _seq) { m_ReplaySeq = _seq; }
	int64 GetReplaySeq() { return m_ReplaySeq; }
	int64 GetGameTime() { return m_GameTime; }

	string GetCommentData(int _idx, int _type);
	int GetCommentDataSize() { return m_UserCommetList.size(); }
	ccColor4B GetCommentColor(int _idx);
	
	void ResetTextField();
	void SetType(eReplayType _type) { m_ReplayType = _type; }
	eReplayType GetType() { return m_ReplayType; }
	void SetIsLike(bool _like) { m_isLike = _like; }
	bool GetIsLike()	{ return m_isLike; }

	void ReplayResume();

	void SetIsPublish(bool _publish) { m_isPublish = _publish; }
	bool GetIsPublish() { return m_isPublish; }
public:
	int64 m_ReplaySeq;
	CustomTextView* m_pChatTableView;
		
	Panel* m_pReplayPanel;
	Panel* m_pChatPanel;

	CCPoint m_ChatBoardHidePos;
	CCPoint m_ChatBoardShowPos;

	Button* m_pPlayButton;
	Button* m_pResetButton;
	Button* m_pChattButton;
	Button* m_pRecommendButton;
	SkelObject* m_pButtonBack;

	Button* m_pChatBoardButton;
	bool m_bChatBoardShow;

	TextField* m_pChatTextField;

	eReplayType m_ReplayType;
	bool m_isLike;
private:
	GamePlayData* m_pRePlayGameData;
	bool m_IsReplayEnable;
	bool m_ReplayDataReady;
	bool m_isPublish;

	bool m_isPause;

	int m_ReplayIndex;
	int m_ReplayIndexMax;

	int m_UserCommentIndex;
	int m_UserCommentIndexMax;
	vector<UserCommentData*> m_UserCommetList;

	int64 m_GameTime;
	int64 m_MaxTime;

	GameRoomInfo* m_GameRoomInfo;

	bool m_isTurnLight;
	bool m_isTextInput;
	
};