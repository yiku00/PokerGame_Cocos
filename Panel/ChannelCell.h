#pragma once

#include "NxFramework.h"
#include "W_ChannelInfo.pb.h"

class ChannelCell : public Panel, public Button::Listener
{
public:
	ChannelCell();
	virtual ~ChannelCell();

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
public:
	virtual bool handling(STCMD &stCmd);
	void update(float dt);
	void SetCellData(W_ChannelInfo* _pInfo);

public:
	W_ChannelInfo* m_CellInfo;

	//SkelObject* m_Landmark;
	//SkelObject* m_OpenMark;

	Button* m_btnChannel;

	Nx::Label* m_labelTitle;
	//Label* m_labelTitleUnder;
	Nx::Label* m_labelSeedmoney;
	Nx::Label* m_labelUserCount;
};
