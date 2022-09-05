/********************************************************************
filename: 	LobbyRewardPanel.h

purpose:	토너먼트 끝났을때 결과 보상창
*********************************************************************/
#pragma once

#include "NxFramework.h"
#include "TypeDefine.pb.h"

#define COLOR_GOLD_LABEL	ccc3(255, 234, 141)
#define COLOR_GOLD_NUMBER	ccc3(255, 215,  37)
#define COLOR_FAME_LABEL	ccc3(184, 245, 135)
#define COLOR_FAME_NUMBER	ccc3( 85, 255,  33)
#define COLOR_DISABLE		ccc3(151, 151, 151)

enum RewardType
{
	REWARD_TOURNAMENT,
	REWARD_SURVIVAL
};

class LobbyRewardPanel : public Panel, public Button::Listener
{
public:
	LobbyRewardPanel(RewardType type);
	virtual ~LobbyRewardPanel();

	void SetType(int _type) { m_Type = (RewardType)_type; }
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
	void update(float dt);

	void SetTitleText(std::string _title, GameMode _mode);
	void SetRewardGold(int64 _gold);
	void SetRewardFame(int _fame);
	void SetMyRank(int _my, int _all);
	void SetDesc(std::string _desc);
public:
	Panel* m_MiddleButton;

	RewardType m_Type;
};
