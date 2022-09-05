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
	vector<CardData*> * m_pCardList;	// 카드 정보 포인터

	vector<CardData*>	m_HighJokboCardList;	// 하이 족보 카드 정렬 정보
	vector<CardData*>	m_LowJokboCardList;		// 로우 족보 카드 정렬 정보
	vector<CardData*>	m_HighJokboRepCardList;	// 대표 족보 번호 리스트
	vector<CardData*>	m_LowJokboRepCardList;	// 대표 족보 번호 리스트
	HighJokboKind		m_HighJokboKind;		// 하이 족보
	LowJokboKind		m_LowJokboKind;			// 로우 족보

public:
	void Init();											// 초기화 함수
	void SetCardInfo(vector<CardData*> * p_CardList);		// 카드 정보 초기화

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