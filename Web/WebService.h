/********************************************************************
	file name:	TCPService.h
	
	purpose:	
*********************************************************************/
#pragma once

#include "NxFramework.h"
#include "NxSingleton.h"
#include "NxThread.h"

#include "W_PreLoginReq.pb.h"
#include "W_PreLoginRes.pb.h"
#include "W_LoginReq.pb.h"
#include "W_LoginRes.pb.h"
#include "W_UserInfoReq.pb.h"
#include "W_UserInfoRes.pb.h"
#include "W_GameDataReq.pb.h"
#include "W_GameDataRes.pb.h"
#include "W_GameData.pb.h"
#include "W_LoginReq.pb.h"
#include "W_ChannelReq.pb.h"
#include "W_ChannelRes.pb.h"

#include "W_LetterUpdateReq.pb.h"
#include "W_LetterUpdateRes.pb.h"
#include "W_QuestUpdateReq.pb.h"
#include "W_QuestUpdateRes.pb.h"

#include "W_SlotMachineReq.pb.h"
#include "W_SlotMachineRes.pb.h"

#include "W_QuestInfo.pb.h"
#include "W_CashBuyReq.pb.h"
#include "W_CashBuyRes.pb.h"
#include "W_MonthlyClassBuyReq.pb.h"
#include "W_MonthlyClassBuyRes.pb.h"
#include "W_PlayerNameReq.pb.h"
#include "W_PlayerNameRes.pb.h"

#include "W_BankInReq.pb.h"
#include "W_BankInRes.pb.h"
#include "W_BankOutReq.pb.h"
#include "W_BankOutRes.pb.h"

#include "NxHttpManager.h"
#include "HeroUtil.h"
#include "HeroApp.h"
#include "TItlePanel.h"
#include "W_RankInfoReq.pb.h"

#define LOGIN_REQ_KEY "frAQBc8Wsa1xVPfv"

using google::protobuf::Message;

enum WCSProtocol
{
	W_S2C_CHANNEL_LIST_RES,
	W_S2C_FRIEND_LIST_RES,
	W_S2C_ADD_FRIEND_LIST_RES,
	W_S2C_UPDATE_FRIEND_LIST_RES,
	W_S2C_UPDATE_RECOMMEND_FRIEND_LIST_RES,
	W_S2C_UPDATE_RECOMMEND_FRIEND_DATA_RES,
	W_S2C_OPEN_QUEST_LIST_RES,
	W_S2C_UPDATE_QUEST_LIST_RES,
	W_S2C_SHOW_LETTER_LIST_RES,
	W_S2C_UPDATE_LETTER_LIST_RES,
	W_S2C_UPDATE_PLAYER_INFO_RES,
	W_S2C_UPDATE_SLOTMACHINE_INFO_RES,
	W_S2C_UPDATE_REPLAY_INFO_RES,
	W_S2C_UPDATE_RANK_INFO_RES,
	W_S2C_POPUP_REPLAYBOX_LIST_RES,
	W_S2C_SELECT_CHARACTER_RES,
	W_S2C_EVENT_LIST_RES,
	W_S2C_EVENT_UPDATE_RES,
	W_S2C_FRIEND_SEARCH_RES,
	W_S2C_PLAYER_NAME_RES,
	W_S2C_FreeRefillRes,
	W_S2C_RefreshRes,
	W_S2C_BUY_CHARACTER_RES,
	W_S2C_TOURNAMENT_REPLAY_RES,
	W_S2C_TOURNAMENT_REWARD_RES,
	W_S2C_TOURNAMENT_REFREASH_RES,
	W_S2C_DEATHMATCH_REPLAY_RES,
	W_S2C_DEATHMATCH_CANCEL_RES,
	W_S2C_DEATHMATCH_REFREASH_RES,
	W_S2C_BANK_IN_RES,
	W_S2C_BANK_OUT_RES,
	ERROR_MASSGE_WAITING_OVER
};

class WebService : public Singleton<WebService>, public Panel, public Nx::Layer::Listener
{
public:
	WebService();
	~WebService();

public:
	virtual void update(float _dt);
	virtual void onLayerMessage(const string& msg);

	void _sendFacebookLoginReq(std::string _id, std::string _photoUrl);
	void sendGoogleLoginReq(std::string _id, std::string _photoUrl);

	void _sendPreloginReq();
	void _recvPreloginRes(HttpMessage* _msg);
	void _sendGuestLoginReq();
	void _recvGuestLoginRes(HttpMessage* msg);
	void _sendGameDataReq();
	void _recvGameDataRes(HttpMessage* msg);
	void _sendUserDataReq();
	void _recvUserDataRes(HttpMessage* msg);
	void _sendChannelReq();
	void _recvChannelRes(HttpMessage* msg);

	void _sendBankInReq(int64 gamemoney);
	void _recvBankInRes(HttpMessage* msg);
	void _sendBankOutReq(int64 gamemoney);
	void _recvBankOutRes(HttpMessage* msg);

	void _sendLetterListReq();
	void _recvLetterListRes(HttpMessage* msg);
	void _sendLetterUpdateReq(int64 seq);
	void _recvLetterUpdateRes(HttpMessage* msg);
	void _sendLetterAllGetReq(vector<int64>& _seqList);
	void _recvLetterAllGetRes(HttpMessage* msg);

	void _sendQuestListUpdateReq();
	void _recvQuestListUpdateRes(HttpMessage* msg);
	void _sendQuestUpdateReq(int64 seq,int _type);
	void _recvQuestUpdateRes(HttpMessage* msg);
	
	void _sendSlotMachineReq(W_SlotMachineReq_eSlotMachineResourceType type);
	void _recvSlotMachineRes(HttpMessage* msg);
	void _sendCashBuyReq(int32 id);
	void _recvCashBuyRes(HttpMessage* msg);
	void _sendMonthlyClassBuyReq(int32 id);
	void _recvMonthlyClassBuyRes(HttpMessage* msg);
	void _sendPlayerNameReq(string name);
	void _recvPlayerNameRes(HttpMessage* msg);

	void SendChannelListReq();
	void RecvChannelListRes(HttpMessage* msg);

	void SendUserInfoReq();
	void RecvUserInfoRes(HttpMessage* msg);

	void _sendFriendAddReq(vector<int64>& _uidList);
	void _recvFriendAddRes(HttpMessage* msg);
	void _sendFriendGiftReceiveReq(vector<int64>& _uidList);
	void _recvFriendGiftReceiveRes(HttpMessage* msg);
	
	void _sendFriendGiftSendReq(vector<int64>& _uidList);
	void _recvFriendGiftSendRes(HttpMessage* msg);

	//facebook 친구 선물
	void _sendFaceFriendGiftSendReq(vector<int64>& _uidList);
	void _recvFaceFriendGiftSendRes(HttpMessage* msg);
	void _sendFaceFriendGiftReceiveReq(vector<int64>& _uidList);
	void _recvFaceFriendGiftReceiveRes(HttpMessage* msg);


	void _sendFriendOfInfoReq();
	void _recvFriendOfInfoRes(HttpMessage* msg);
	void _sendFriendReCommendReq();
	void _recvFriendReCommendRes(HttpMessage* msg);
	void _sendFriendRejectReq(vector<int64>& _uidList);
	void _recvFriendRejectdRes(HttpMessage* msg);
	void _sendFriendRemoveReq(int64 _uid);
	void _recvFriendRemoveRes(HttpMessage* msg);
	
	void _sendFriendRequestListReq();
	void _recvFriendRequestListRes(HttpMessage* msg);
	void _sendFacebookRequestListReq();
	void _recvFacebookRequestListRes(HttpMessage* msg);

	
	void _sendFriendRequestReq(vector<int64>& _uidList);	//친구 요청
	void _recvFriendRequestRes(HttpMessage* msg);			//request

	void _sendFriendInviteReq(int invited_uid, int inviting_roomid);
	void recvFriendInviteRes(HttpMessage* msg);

	void _sendReplayListReq(int64 _uid);
	void _recvReplayListRes(HttpMessage* msg);
	
	//리플레이 관련
	void _sendReplaySeasonReq();						//시즌 
	void _recvReplaySeasonRes(HttpMessage* msg);
	void _sendReplayDeathMatchReq();
	void _recvReplayDeathMatchRes(HttpMessage* msg);


	void SendReplayListBoxReq(int64 _uid);
	void RecvReplayListBoxRes(HttpMessage* msg);

	void _sendReplayModifyReq(int64 seq, string _name);
	void _recvReplayModifyRes(HttpMessage* msg);
	void _sendReplayDeleteReq(int64 seq);
	void _recvReplayDeleteRes(HttpMessage* msg);
	void _sendReplayStartReq(eReplayType _type, int64 _seq);
	void _recvReplayStartRes(HttpMessage* msg);

	void _sendRankInfoReq(W_RankInfoReq_eRankType _type);
	void _recvRankInfoRes(HttpMessage* msg);

	void _sendCharacterBuyReq(int32 id);
	void _recvCharacterBuyRes(HttpMessage* msg);

	void _sendSkinBuyReq(int32 id);
	void _recvSkinBuyRes(HttpMessage* msg);

	void _sendPlayerInfoReq(string _name, int32 _characterID, eGenderType _genderType = Man);
	void _recvPlayerInfoRes(HttpMessage* msg);

	void _sendCharacterSelectReq(int32 _id);
	void _recvCharacterSelectRes(HttpMessage* msg);

	void _sendSkinSelectReq(int32 _id);
	void _recvSkinSelectRes(HttpMessage* msg);

	void _sendReplayCommentReq(eReplayType _type, int64 _seq, int32 _time, string _comment);
	void _recvReplayCommentRes(HttpMessage* msg);
	void _sendReplayLikeReq(eReplayType _type, int64 _seq);
	void _recvReplayLikeRes(HttpMessage* msg);
	
	void _sendEventListReq();
	void _recvEventListRes(HttpMessage* msg);
	void _sendEventListUpdateReq(int32 _id);
	void _recvEventListUpdateRes(HttpMessage* msg);

	void _sendFriendFindReq(string _name);
	void _recvFriendFindRes(HttpMessage* msg);

	void _sendFreeRefillReq();
	void _recvFreeRefillRes(HttpMessage* msg);

	void _sendAttendDailyRewardReq();
	void _recvAttendDailyRewardRes(HttpMessage* msg);

	void SendModelPicBuyReq(int id);
	void RecvModelPicBuyRes(HttpMessage* msg);
	void SendBuySlotReq(int tId);
	void RecvBuySlotRes(HttpMessage* msg);
	void SendBuyTapReq(int tId);
	void RecvBuyTapRes(HttpMessage* msg);
	void SendPing();
	void RecvPing(HttpMessage* msg);

	void setLobbyIp(string _ip) { m_LobbyIp = _ip; }
	void setLobbyPort(int16 _port) { m_LobbyPort = _port; }
	string getCurIp() { return m_LobbyIp; }
	int16 getCurPort() { return m_LobbyPort; }
	void ShowLetterGetPopup(W_RewardInfo& _pInfo);
	void GotoRubyShopPopup(int32 _value);

	void ParsingErrorCode(string _errorCode);
	void SendChannelListUpdateReq();
	void RecvChannelListUpdateRes(HttpMessage* msg);
	void LoginEnterLobby();
	void SendRefreshReq();
	void SendRefreshRes(HttpMessage* msg);

	void TournamentInfoReq();
	void TournamentInfoRes(HttpMessage* msg);
	void TournamentEnterReq();
	void TournamentEnterRes(HttpMessage* msg);
	void TournamentRefreshReq();
	void TournamentRefreshRes(HttpMessage* msg);
	void TournamentIdReq(int32 _tourId);
	void TournamentIdRes(HttpMessage* msg);
	void TournamentReplayListReq(int64 _uid, int64 _gamekey);
	void TournamentReplayListRes(HttpMessage* msg);
	void TournamentReplayReq(int64 _seq);
	void TournamentReplayRes(HttpMessage* msg);
	void TournamentRewardReq(int32 _tourId);
	void TournamentRewardRes(HttpMessage* msg);

	void SurvivalInfoReq();
	void SurvivalInfoRes(HttpMessage* msg);
	void SurvivalMatchRegistReq(int32 _matchId);
	void SurvivalMatchRegistRes(HttpMessage* msg);
	void SurvivalMatchRegistCancelReq(int32 _matchId);
	void SurvivalMatchRegistCancelRes(HttpMessage* msg);
	void SurvivalEnterReq(int32 _matchId);
	void SurvivalEnterRes(HttpMessage* msg);
	void SurvivalRefreshReq(int32 _matchId);
	void SurvivalRefreshRes(HttpMessage* msg);
	void SurvivalMatchIdReq(int32 _matchId);
	void SurvivalMatchIdRes(HttpMessage* msg);
	void SurvivalRankReq();
	void SurvivalRankRes(HttpMessage* msg);
	void SurvivalReplayListReq(int _matchId);
	void SurvivalReplayListRes(HttpMessage* msg);
	void SurvivalReplayReq(int64 _seq);
	void SurvivalReplayRes(HttpMessage* msg);

	void TournamentGameReq(int64 _seq);
	void TournamentGameRes(HttpMessage* msg);
	void SurvivalGameReq(int64 _seq);
	void SurvivalGameRes(HttpMessage* msg);

	void SetMsgWait(float _time);
	void EndWait();

	void DirectTournamentSelectReq();
	void DirectTournamentSelectRes(HttpMessage* msg);
	void DirectTournamentSelectNextRes(HttpMessage* msg);

	void DirectSurvivalSelectReq();
	void DirectSurvivalSelectRes(HttpMessage* msg);
	void DirectSurvivalSelectNextRes(HttpMessage* msg);
	void SurvivalMatchUpdateReq(int32 _matchId);
	void SurvivalMatchUpdateRes(HttpMessage* msg);

	void VersionReq();
	void VersionRes(HttpMessage* msg);

	void sendGooglePlatFormReq();	// guest 에서 googleFlatForm
	void recvGooglePlatFormRes(HttpMessage* msg);

	void sendFacebookPlatFormReq();
	void recvFacebookPlatFormRes(HttpMessage* msg);

	void sendPlatoformOutReq(eLoginType type);
	void recvPlatoformOutRes(HttpMessage* msg);

	void sendReputeRankReq(int index);
	void recvTotalReputeRankRes(HttpMessage* msg);
	void recvFriendReputeRankRes(HttpMessage* msg);

	//refillmovie
	void sendFreeChargeReq();
	void recvFreeChargeRes(HttpMessage* msg);

	//grand reward
	void sendW_GranChanceNormalReq();
	void sendW_GranChanceRandomReq();
	void recvW_GranChanceRes(HttpMessage* msg);
	void recvW_GranChanceRandomRes(HttpMessage* msg);

	void sendLimitedReq(vector<W_LimitShopData_eLimitType> types);
	void recvLimitedRes(HttpMessage* msg);

	void sendNoticeinfoReq();
	void recvNoticeinfoRes(HttpMessage* msg);
private:
	//eLoginType m_LoginType;
	string mInitialVector;
	string m_LobbyIp;
	int16 m_LobbyPort;
	int64 LastSendNotiTime = 0;
	eReplayType m_ReplayType;

	bool m_bMsgWait;
	float m_fMsgWaitTime;
	string m_UpdateUrl;
	string LocalIp;
	int mCharacterBuyId;
	int mMemberShipBuyId;
	private:
		bool CheckNotiSend();
		void CheckAndRedirectIP(W_ChannelInfo* _param); //For Local Machine
};
