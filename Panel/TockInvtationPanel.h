#ifndef __TockInvtationPanel_H__
#define __TockInvtationPanel_H__

#include "NxFramework.h"
#include "W_FriendInfo.pb.h"


class TockInvtationPanel : public Panel, public Button::Listener
{
public:
	TockInvtationPanel();
	virtual ~TockInvtationPanel();

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

	void SetFriendlList();
	void ClearFriendlList();

	void ShowPopupPanel();
	void HidePopupPanel();
private:
	void ScrollViewOffsetProcess();

	bool cellTouchStart(const CCPoint& tableTouchPoint);
	bool cellTouchCancel(const CCPoint& tableTouchPoint);
	bool cellTouch(const CCPoint& tableTouchPoint);
	void cellTouchEnd(CCNode* node);
public:
	bool mLoginProcess;

	CCScrollView* m_pTockFrinedListView;
	CCLayer* m_pTockFrinedListContainer;

	bool m_bTouchCancel;

	Panel* m_ListCell[10];

	Panel* mParentPanel;
	Panel* mMainPanel;
};


#endif
