/********************************************************************
filename: 	ChannelMainPannel.h

purpose:	각 채널( 강원 , 시드니1 등등 고르는 창)
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "ChannelBottomUiPannel.h"
//#include "LobbyTopUiPanel.h"
//#include "LobbyChannelLeftUiPanel.h"
//#include "LobbyChannelSubTopUiPanel.h"

#define MAX_EARTH_OBJECT 10

class ChannelMainPannel : public Panel, public Button::Listener
{
public:
	ChannelMainPannel();
	virtual ~ChannelMainPannel();

	void InitPanel();
	void InitImage();
	void initButton();
// CCTargetedTouchDelegate
	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
// Button::Listener
	virtual void onClicked(const string& name);
    void resume();
	virtual bool handling(STCMD &stCmd);
	virtual void onRefresh();

	void update(float dt);
	void RotateObject(float _angle);
	void SetDestination(int _cityName, bool _action = false);
	int GetFristEnableCell();
	void UpdateChannelCellMoveBy(float _moveX);
	void SetMoveShipWave(bool _visible);
	int GetSelectedCellIndex();
	int GetCityId(int _cellIndex);

	void SetFirstViewCell();

	void SetMoveStop();
	void SetCenterCell();
	void ReleaseCenterCell();

	void UpdateGameMode();
	void UpdateChannelState();
	void SetTabButtonActivation(int _index, bool _active, int _zoder = 0);
	void SelectGameMode(GameKind _gameKind, bool _action = false);
	void setVisibleChannelCell(bool visible);

	bool isPossibleOpen(GameKind gameKind);
	virtual void onEnter() override;
private:
	void CheckAutoMove(float _moveLen);
	void AutoMoveUpdate();
public:
	bool m_bIsMoveWave;
	bool m_bCancelTouch;

	Panel* m_earth;
	ChannelBottomUiPannel* m_BottomUi;
	Panel* m_pTabPanel[4];
	Panel* m_pTabMain;	

	//LobbyTopUiPanel* m_TopUi;
	//LobbyChannelLeftUiPanel* m_LeftUi;
	//LobbyChannelSubTopUiPanel* m_pTopSubUi;

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

	int m_gameKind;
};
