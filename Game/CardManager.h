#pragma once
#include "NxFramework.h"
#include "PokerCardWidget.h"
#include "NxSkelObject.h"

class CardData
{
public:
	CardData()
	{
		m_pCard = nullptr;
	}
	virtual ~CardData()
	{
		if(m_pCard)
			m_pCard->removeFromParent();
	}
public:
	int m_idx;
	int m_Number;
	int m_Kind;
	PokerCardWidget* m_pCard;
};

class CardManager
{
public:
	CardManager();
	~CardManager();

	void SetData();
	void SetCardPanel(Panel* _pPanel) { m_pCardPanel = _pPanel; }

	CCRect GetTableCardRect(int _idx) { return m_TableCardRect[_idx]; }

	void AddCard(int _number, int _kind, bool _showBack = false, float _delay = 0.f);
	void EraseCard(int _idx);
	void ChangeCard(int _idx, int number, int _kind, bool isPaeShow);
	void ClearCardList();

	void ActionMoveCard(unsigned int _idx, CCPoint _moveTo, float _duration, float _scale = 1.0f, float _delay = 0.f);
	void ActionFadeToCard(int _idx, unsigned int _opacity);
	void ActionSelectedCard(int _idx, bool _cancel);

	void ActionShareMoveCard(int _idx, CCPoint _moveto, bool _rand = false, float _delay = 0.f);
	void ActionCardSort();
	void ActionFlipCard(int _idx, bool _open, float _delay);

	void ActionAllCloseCard(bool isPlayerOut = false); //die

	void setVisibleCard(bool visible);	//기덕 추가 카드 사라지게 한다.

	void LastCardCheck();
	void CallBackCardMoveEnd();
	bool IsLastCard();
	void SetLastCardTriger(int _triger) { m_bLastCardTriger = _triger; }
	
	//Badugi
	void BadugiAddCard(int _number, int _kind, bool _showBack, float _delay = 0.f);
	void BadugiChangeCard(int _idx, int _number, int _kind, bool isPaeShow);
	int m_UserIdx;		//클라이언트 상의 유저 위치.
	int m_UserPo;		//서버 상의 유저 위치.
	vector<CardData*> m_CardList;

	int m_bLastCardTriger;

	Panel* m_pCardPanel;

	void setActionSpeed();	//action 속도..
private:
	CCRect m_TableCardRect[7];	
};