#pragma once

#ifndef __USER_JOKBO_INFO_H__
#define __USER_JOKBO_INFO_H__

#include "NxFramework.h"
#include "TypeDefine.pb.h"
#include "NxDefine.h"
#include "GameDataManager.h"

enum SortKind
{
	CARD_SORT_LOW = 0,
	CARD_SORT_HIGH = 1
};

class UserJokboInfo
{
public:
	UserJokboInfo();
	~UserJokboInfo();

private:
	vector<CardData*> * m_pCardList;	// ī�� ���� ������

	vector<CardData*>	m_HighJokboCardList;	// ���� ���� ī�� ���� ����
	vector<CardData*>	m_LowJokboCardList;		// �ο� ���� ī�� ���� ����
	vector<CardData*>	m_HighJokboRepCardList;	// ��ǥ ���� ��ȣ ����Ʈ
	vector<CardData*>	m_LowJokboRepCardList;	// ��ǥ ���� ��ȣ ����Ʈ
	HighJokboKind		m_HighJokboKind;		// ���� ����
	LowJokboKind		m_LowJokboKind;			// �ο� ����

public:
	void Init();											// �ʱ�ȭ �Լ�
	void SetCardInfo(vector<CardData*> * p_CardList);		// ī�� ���� �ʱ�ȭ

	void HighJokboCheck();
	void LowJokboCheck();
	void SetHighJokboRepCardNum();
	void SetLowJokboRepCardNum();

	HighJokboKind GetHighJokboKind() { return m_HighJokboKind;  }
	LowJokboKind GetLowJokboKind() { return m_LowJokboKind; }

	vector<CardData*>& GetHighJokboCardList() { return m_HighJokboCardList;  }
	vector<CardData*>& GetLowJokboCardList() { return m_LowJokboCardList; }

	vector<CardData*>& GetHighJokboRepCardList() { return m_HighJokboRepCardList; }
	vector<CardData*>& GetLowJokboRepCardList() { return m_LowJokboRepCardList; }

	string GetFullJokboString();
	string GetHighJokboString();
	string GetLowJokboString();
	string GetBadukiJokboString(bool _isFull = true);

	void BadukiJokboCheck();
	void SortCard(vector<CardData *> &p_sortCardContainer, SortKind sortKind, int start = 0, int end = 100);

	void HoldemJokboCheck();

private:
	bool SetHighJokbo(HighJokboKind kind);
	bool SetLowJokbo(LowJokboKind kind);
	int StraightFlushCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList, int flushShape, bool * royalCheck);
	int FourCardCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList, int fourCardNum);
	int FullHouseCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList, int tripleCardNum, int onepairCardNum);
	int FlushCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList, int flushShape);
	int StraightCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList, bool * royalCheck);
	int TripleCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList, int tripleCardNum);
	int PairCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList, char * getCardNumber, int onepaircardNum);
	int TopCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList);

	int LowTopCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList);
	int LowOnePairCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList, char * getCardNumber);
	int LowTwoPairCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList, char * getCardNumber);
	int LowTripleCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList, char * getCardNumber);
	int LowStraightCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList);
	int LowTopDownCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList);
	
	int BadukiThirdCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList, bool * royalCheck);
	int BadukiTopCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList);
	int BadukiBaseCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList, char * getCardNumber, char * getCardKind);
	void SetBadukiJokboRepCardNum();
};
#endif