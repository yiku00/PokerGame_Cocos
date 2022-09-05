/********************************************************************
file name:	LobbyLatelybarContentPanel.h

purpose:	내뇽 뿌려주는 창
*********************************************************************/
#pragma once
#include "NxFramework.h"

class LobbyLatelybarContentPanel : public Panel
{

public:
	enum LATELYBAR_TYPE {
		BAR_TOURMENT_TYPE,
		BAR_SURVIVAL_TYPE,
	};

	LobbyLatelybarContentPanel(LATELYBAR_TYPE type);
	virtual ~LobbyLatelybarContentPanel();

public:
	void setBar(string day, string match, int ranking, int honnor);
	void setSurvival(string day, string match, int ranking, int64 money);
private:
	void initPanel();
private:	
	LATELYBAR_TYPE mType;
	Panel* mMainPanel;
	CCSize mContentSize;
	Nx::Label* mDay;	//날짜 2016.07.06
	Nx::Label* mMatch;	//중급 토너먼트
	Nx::Label* mRanking;	// 본선 100 위
	Nx::Label* mFrame;		// + 100
};
