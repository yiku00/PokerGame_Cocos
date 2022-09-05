/********************************************************************
file name:	JackpotPanel.h

purpose:	스트레이트 플러쉬 등 상위3개 나왔을때 스페셜 하게 보여주는 창
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "HeroUtil.h"

class JackpotPanel : public Panel, public SkelObject::EventListener
{
public:
	JackpotPanel();
	~JackpotPanel();
	void Init();
	void InitImage();

	void StartJackpotAnimation(int _kind);
	void SetCard(int _idx, const string _skinName);
	void OnUpdate(float _dt);
	virtual void onEvent(int trackIdx, spEvent* event);
private:
	SkelObject* m_pJackpotBottom;
	SkelObject* m_pJackpotTop;
	SkelObject* m_pCard[5];

	int m_JokboKind;

	float m_dTime;
public:
	Panel* mParentPanel;
	Panel* mMainPanel;
	bool m_bMakeGoldChip;

};