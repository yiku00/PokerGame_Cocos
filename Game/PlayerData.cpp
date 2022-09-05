#include "pch.h"
#include "PlayerData.h"
#include "GameDataManager.h"
#include "LobbyScene.h"
#include "SceneUtil.h"
#include "LobbyUIPanel.h"

PlayerData::PlayerData()
{
	m_WeeklyRankExpireTime = 0;
	m_GoneTime = 0;
	m_fUpdateTime = 0;

	m_UID = 0;
	m_UserKind = UserKind::NORMAL;

	// temporary data
	m_NickName = "";
	m_thumbnailUrl = "";
	for (int i = 0; i < GAME_KIND_COUNT; i++)
	{
		m_WinCount[i] = 0;
		m_LoseCount[i] = 0;
	}
	m_CharacterIdx = 0;
	m_GameMoney = 0;
	m_Level = 0;
	m_Exp = 0;
	m_Chip = 0;
	m_Cash = 0;
	m_Vip = 0;
}

void PlayerData::SetData(int _uId, string _nickname, int _wincount, int _losecount, int _charIdx, int64 _gamemoney, int _level, int _exp, PlayerStatus _state, string thumbnail)
{
	m_UID = _uId;
	m_NickName = _nickname;
	m_WinCount[0] = _wincount;
	m_LoseCount[0] = _losecount;
	m_CharacterIdx = _charIdx;
	m_GameMoney = _gamemoney;
	m_Level = _level;
	m_Exp = _exp;
	m_thumbnailUrl = thumbnail;
}

void PlayerData::SetData(NewUserRes * userRes)
{
	m_UID = userRes->socketid();
	m_UserKind = userRes->userkind();
}

void PlayerData::SetDetailData(UserPlayerInfo * res)
{
	m_NickName = res->nickname();

	Record record;
	for (int i = 0, j = res->record_size(); i < j; i++)
	{
		record = res->record(i);
		m_WinCount[i] = record.win();
		m_LoseCount[i] = record.lose();
	}
	
	m_CharacterIdx = res->charidx();
	m_GameMoney = res->gamemoney();
	m_Level = res->level();
	m_Exp = 0;
}

void PlayerData::SetData(RoomPlayerInfo * playerInfo)
{
	if (playerInfo == nullptr)
		return;

	m_UID = playerInfo->socketid();
	m_DId = playerInfo->useridx();
	//m_DGroup = playerInfo->dbgroup();
	m_NickName = playerInfo->nickname();
	m_WinCount[GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind()] = playerInfo->win();
	m_LoseCount[GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind()] = playerInfo->lose();
	SetCharacter(playerInfo->charidx());
	m_GameMoney = playerInfo->gamemoney();
	m_UserKind = playerInfo->userkind();
	m_Level = playerInfo->level();
	m_Exp = 0;
	m_Chip = 0;
	m_Cash = 0;
	if (playerInfo->has_thumbnailurl())
		m_thumbnailUrl = playerInfo->thumbnailurl();

}

void PlayerData::SetCharacter(int _characteID)
{
	m_CharacterIdx = _characteID;
//#if CHARACTER_NOT_READY //TEST_CODE
//	if (m_CharacterIdx == SANTIAGO2)
//	{
//		m_CharacterIdx = SANTIAGO;
//	}
//#endif
}

void PlayerData::SetData(const W_PlayerInfo* _pPlayerInfo)
{
	if (_pPlayerInfo->has_uid()) m_DId = _pPlayerInfo->uid();
	if (_pPlayerInfo->has_dbid()) m_DGroup = _pPlayerInfo->dbid();
	if (_pPlayerInfo->has_sig()) HttpManager::getSingletonPtr()->setSignature(_pPlayerInfo->sig());

	if (_pPlayerInfo->has_imageurl()) m_thumbnailUrl = _pPlayerInfo->imageurl();

	if (_pPlayerInfo->has_name()) m_NickName = _pPlayerInfo->name();
	if (_pPlayerInfo->has_level()) m_Level = _pPlayerInfo->level();
	if (_pPlayerInfo->has_exp()) m_Exp = _pPlayerInfo->exp();
	if (_pPlayerInfo->has_safeid()) m_SafeID = _pPlayerInfo->safeid();

	if (_pPlayerInfo->has_rating()) m_Rating = _pPlayerInfo->rating();
	if (_pPlayerInfo->has_repute()) m_Repute = _pPlayerInfo->repute();

	if (_pPlayerInfo->has_gamemoney()) m_GameMoney = _pPlayerInfo->gamemoney();
	if (_pPlayerInfo->has_gamemoneybank()) m_GameMoneyBank = _pPlayerInfo->gamemoneybank();
	if (_pPlayerInfo->has_gamemoneysafe()) m_GameMoneySafe = _pPlayerInfo->gamemoneysafe();
	if (_pPlayerInfo->has_gamemoneyloss()) m_GameMoneyLoss = _pPlayerInfo->gamemoneyloss();

	if (_pPlayerInfo->has_chip()) m_Chip = _pPlayerInfo->chip();
	if (_pPlayerInfo->has_cash()) m_Cash = _pPlayerInfo->cash();
	if (_pPlayerInfo->has_vip()) m_Vip = _pPlayerInfo->vip();
	if (_pPlayerInfo->has_cashpayment()) m_CashPayment = _pPlayerInfo->cashpayment();

	if (_pPlayerInfo->has_gamemoneymax()) m_GameMoneyMax = _pPlayerInfo->gamemoneymax();
	if (_pPlayerInfo->has_bankbax()) m_BankMax = _pPlayerInfo->bankbax();
	if (_pPlayerInfo->has_chipmax()) m_ChipMax = _pPlayerInfo->chipmax();

	if (_pPlayerInfo->has_usecharacter()) SetCharacter(_pPlayerInfo->usecharacter());
	if (_pPlayerInfo->has_freerefillplaycnt()) m_FreeRefillCount = _pPlayerInfo->freerefillplaycnt();
	if (_pPlayerInfo->has_monthlyclassid()) m_MonthlyClassID = _pPlayerInfo->monthlyclassid();
	if (_pPlayerInfo->has_monthlyclassexpiretime()) m_MonthlyClassDay = _pPlayerInfo->monthlyclassexpiretime();
	if (_pPlayerInfo->has_monthlycashid()) m_MonthlyCashID = _pPlayerInfo->monthlycashid();
	if (_pPlayerInfo->has_monthlycashexpiretime()) m_MonthlyCashDay = _pPlayerInfo->monthlycashexpiretime();
	if (_pPlayerInfo->has_dailyattendday()) m_DailyAttendDay = _pPlayerInfo->dailyattendday();
	if (_pPlayerInfo->has_slotmachinecount()) m_SlotMachineCount = _pPlayerInfo->slotmachinecount();
	if (_pPlayerInfo->has_isnamechange()) m_isNameChange = _pPlayerInfo->isnamechange();

	if (_pPlayerInfo->has_basecharacter()) m_BaseCharacter = _pPlayerInfo->basecharacter();

	if (_pPlayerInfo->has_weeklyrankexpiretime())
	{
		m_WeeklyRankExpireTime = _pPlayerInfo->weeklyrankexpiretime();
		m_GoneTime = 0;
	}

	//m_DId;
	//m_DGroup;
	//int		m_WinCount[5];
	//int		m_LoseCount[5];
	//UserKind m_UserKind;
}

void PlayerData::SetGameMoney(int64 gameMoney) 
{
	m_GameMoney = gameMoney; 
}

int64 PlayerData::GetUID() 
{
	return m_DId;
}

void PlayerData::UpdateTime(float dt)
{
	m_fUpdateTime += dt;
	if (m_fUpdateTime > 1.f)
	{
		m_GoneTime += 1;
		m_fUpdateTime -= 1.f;

		if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
		{
			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
			if (_pScene == nullptr)
				return;

			if (_pScene->m_LobbyUIPanel == nullptr)
				return;

			string _time = GameDataManager::getSingletonPtr()->GetRemainWeeklyBonusTime();
			//_pScene->m_LobbyUIPanel->SetRankingTimeLimitUpdate(_time);
		}
	}
}