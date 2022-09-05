/********************************************************************
file name:	JackpotPanel.h

purpose:	��Ʈ����Ʈ �÷��� �� ����3�� �������� ����� �ϰ� �����ִ� â
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