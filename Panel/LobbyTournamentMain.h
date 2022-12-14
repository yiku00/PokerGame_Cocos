/********************************************************************
filename: 	LobbyTournamentMain.h

purpose:	로비에서 시즌 토너먼트창
*********************************************************************/
#pragma once

#include "NxFramework.h"
#include "LobbyTournamentBottomPannel.h"
//#include "LobbyTournamentSubTop.h"

#define MAX_EARTH_OBJECT 10

class LobbyTournamentMain : public Panel, public Button::Listener
{
public:
	LobbyTournamentMain(int firstIndex = 0);
	virtual ~LobbyTournamentMain();
	void InitPanel();
	void InitImage();
	void InitButton();

	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onRefresh();

// Button::Listener
	virtual void onClicked(const string& name);
	virtual bool handling(STCMD &stCmd);
	virtual void onEnter() override;

	void update(float dt);
	void RotateObject(float _angle);
	void SetDestination(int _cityName, bool _action = false);
	int GetFristEnableCell();
	void UpdateChannelCellMoveBy(float _moveX);
	void SetMoveShipWave(bool _visible);
	int GetSelectedCellIndex();
	int GetCityId(int _cellIndex);

	void SetMoveStop();
	void SetCenterCell();
	void ReleaseCenterCell();

	//void CreateCell();
	void UpdateCell();
	void SetFirstViewCell();

	void UpdateChannelState();
	void SetTabButtonActivation(int _index, bool _active, int _zoder = 0);
	void SelectGameMode(GameKind _gameKind, bool _action = true);

	void setVisibleChannelCell(bool visible);

	void moveCellAndSelect(int ticketIdx);

private:
	void CheckAutoMove(float _moveLen);
	void AutoMoveUpdate();
public:
	bool m_bIsMoveWave;
	bool m_bCancelTouch;

	Panel* m_earth;
	LobbyTournamentBottomPannel* m_BottomUi;
	Panel* m_pTabPanel[4];
	Panel* m_pTabMain;

	//LobbyTournamentSubTop* m_SubTopPanel;

	float m_ObjAngle[MAX_EARTH_OBJECT];
	CCNode* m_ObjectHeadNode[MAX_EARTH_OBJECT];
	SkelObject* m_Object[MAX_EARTH_OBJECT];
	CCPoint m_ObjCenterPos;

	float m_RootAngle;
	float m_DstAngle;
	bool m_bActionRotate;
	CCPoint m_offset;

private:
	bool m_bMoveAccel;
	bool m_bAutoMove;
	bool m_bTouchEnd;
	float m_moveG;
	float m_MovePoint;
	int mFirstCellIndex;
};
