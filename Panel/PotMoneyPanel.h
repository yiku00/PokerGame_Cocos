/********************************************************************
file name:	PotMoneyPanel.h

purpose:	������� ������ �̱� ���� ������� �ִ� �ִ� ó���ϴ� �κ�
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "HeroUtil.h"

class PotMoneyPanel : public Panel
{
public:
	PotMoneyPanel();
	~PotMoneyPanel();
	void Init();
	void onUpdate(float dt);
	void SetMoney(int64 _money);
	
	void ClearPotMoney();
	void ActionWinnerTakeAll(float _delay);
	void Action_MovePotMoney(int64 _money, CCPoint _moveTo, float _duration);

private:
	int64 m_Money;
	vector<SkelObject*> m_potChipList;

	void SetPotMoneyPosition();
	string GetChipKind(int _kind, int _count);

public:
	Panel* mParentPanel;
	Panel* mMainPanel;

};