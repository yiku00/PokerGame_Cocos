/********************************************************************
file name:	PotMoneyPanel.h

purpose:	결과에서 딜리가 이긴 돈을 사람에게 주는 애니 처리하는 부분
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