#pragma once
#include "NxFramework.h"
#include "TypeDefine.pb.h"
#include "NxDefine.h"
#include "NewUserRes.pb.h"
#include "RoomPlayerInfo.pb.h"
#include "UserPlayerInfo.pb.h"
#include "W_PlayerInfo.pb.h"

#define CHARACTER_NOT_READY		0

class PlayerData
{
public:

	int64	m_UID;

	int32	m_DId;
	int32	m_DGroup;

	string	m_NickName;
	int32	m_Level;
	int32	m_Exp;
	int32	m_SafeID;
	string	m_thumbnailUrl;

	int32	m_Rating;
	int32	m_Repute;

	uint64	m_GameMoney;
	uint64	m_GameMoneyBank;
	uint64	m_GameMoneySafe;
	uint64	m_GameMoneyLoss;

	uint64	m_Chip;
	int32	m_Cash;
	int32	m_Vip;
	int32	m_CashPayment;

	uint64	m_GameMoneyMax;
	uint64	m_BankMax;
	uint64	m_ChipMax;

	int32	m_CharacterIdx;
	int32	m_FreeRefillCount;
	int32	m_MonthlyClassID;
	double	m_MonthlyClassDay;
	int32	m_MonthlyCashID;
	double	m_MonthlyCashDay;
	int32	m_DailyAttendDay;
	int32	m_SlotMachineCount;
	bool	m_isNameChange;
	int32	m_BaseCharacter;
	double	m_WeeklyRankExpireTime;
	double	m_GoneTime;
	float	m_fUpdateTime;

	int		m_WinCount[5];
	int		m_LoseCount[5];
	UserKind m_UserKind;
public:
	PlayerData();
	void SetData(const W_PlayerInfo* _pPlayerInfo);
	void SetData(int _uId, string _nickname, int _wincount, int _losecount, 
				 int _charIdx, int64 _gamemoney, int _level, int _exp, 
				 PlayerStatus _state, string thumbnail);
	void SetData(NewUserRes * userRes);
	void SetData(RoomPlayerInfo * playerInfo);
	void SetDetailData(UserPlayerInfo * res);
	void SetGameMoney(int64 gameMoney);
	int64 GetUID();
	int GetDid() { return m_DId; }
	int64 GetSocketID() { return m_UID; }
	int GetDGroup() { return m_DGroup; }
	void UpdateTime(float dt);
	void SetCharacter(int _characteID);
};