#include "pch.h"
#include "UserJokboInfo.h"

const char CARD_HIGH_ORDER[] = { 13, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
const char CARD_LOW_ORDER[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

const bool MOUNTAIN_LIST[] = { true, false, false, false, false, false, false, false, false, true, true, true, true };
const bool BACK_STRAIGHT_LIST[] = { true, true, true, true, true, false, false, false, false, false, false, false, false };

const bool GOLF_LIST[] = { true, true, true, true, false, false, false, false, false, false, false, false, false };
const bool SECOND_LIST[] = { true, true, true, false, true, false, false, false, false, false, false, false, false };
const bool THIRD_LIST[] = { true, true, false, true, true, false, false, false, false, false, false, false, false };

UserJokboInfo::UserJokboInfo()
{
	m_pCardList = nullptr;
	Init();
}

UserJokboInfo::~UserJokboInfo()
{
	Init();
}

void UserJokboInfo::Init()
{
	m_HighJokboKind = HighJokboKind::HIGH_NO;
	m_LowJokboKind = LowJokboKind::LOW_NO;

	m_HighJokboCardList.clear();
	m_LowJokboCardList.clear();
	m_HighJokboRepCardList.clear();
	m_LowJokboRepCardList.clear();
}

void UserJokboInfo::SetCardInfo(vector<CardData*> * p_CardList)
{
	m_pCardList = p_CardList;
	Init();
}

void UserJokboInfo::HoldemJokboCheck()
{
	if (m_pCardList == nullptr)
		return;

	if (m_pCardList->size() == 0)
		return;

	m_HighJokboCardList.clear();

	char getCardKind[4];					// 각 카드 종류별 받은 갯수(스다하크)
	char getCardNumber[14];					// 카드번호별 가진 갯수
	bool royalCheck[14];					// 마운틴, 백스트레이트 체크용

	memset(getCardKind, 0, 4);
	memset(getCardNumber, 0, 14);
	memset(royalCheck, false, 14);

	// 순서 정렬
	vector<CardData*>	sortCardContainer;
	int max = 0;

	for (int i = 0; i < 2; i++)
		sortCardContainer.push_back((*m_pCardList)[i]);

	int _size = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_CommunityCardList.size();
	for (int _i = 0; _i < _size; _i++)
	{
		CardData* _pCardData = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_CommunityCardList[_i];
		sortCardContainer.push_back(_pCardData);
	}
	int num = sortCardContainer.size();

	CardData * data1;
	CardData * data2;
	CardData * tmp;

	for (int i = 0; i < num - 1; i++)
	{
		max = i;
		for (int j = i + 1; j < num; j++)
		{
			data1 = sortCardContainer[max];
			data2 = sortCardContainer[j];

			if (CARD_HIGH_ORDER[data1->m_Number] > CARD_HIGH_ORDER[data2->m_Number] ||
				(CARD_HIGH_ORDER[data1->m_Number] == CARD_HIGH_ORDER[data2->m_Number] && data1->m_Kind > data2->m_Kind))
				max = j;
		}
		if (i != max)
		{
			tmp = sortCardContainer[i];
			sortCardContainer[i] = sortCardContainer[max];
			sortCardContainer[max] = tmp;
		}
	}
	
	CardData * p_tmpCardData;

	int flushShape = -1;
	int fourCardNum = -1;
	int straightStartNumber = 0;
	int tripleCardNum = -1;
	int onepairCardNum = -1;

	char tmpIdx;

	for (int i = 0, j = sortCardContainer.size(); i < j; i++)
	{
		p_tmpCardData = sortCardContainer[i];

		if (p_tmpCardData->m_Kind < 0 || p_tmpCardData->m_Kind > 3)
			continue;

		// 플러쉬 가능 여부 체크
		getCardKind[p_tmpCardData->m_Kind]++;
		if (getCardKind[p_tmpCardData->m_Kind] >= 5)
			flushShape = p_tmpCardData->m_Kind;

		// 포카드 가능 여부 체크
		getCardNumber[p_tmpCardData->m_Number]++;
		if (getCardNumber[p_tmpCardData->m_Number] == 4)
			fourCardNum = p_tmpCardData->m_Number;
	}
	// 처음과 끝은 A로 (계산 편의상)
	getCardNumber[13] = getCardNumber[0];

	// 트리플 가능 여부 체크
	for (int i = sizeof(getCardNumber) - 1; i >= 1; i--)
	{
		tmpIdx = getCardNumber[i];
		if (tmpIdx >= 3 && tmpIdx > tripleCardNum)
		{
			tripleCardNum = i;
		}
	}
	//  원페어 가능 여부 체크
	for (int i = sizeof(getCardNumber) - 1; i >= 1; i--)
	{
		tmpIdx = getCardNumber[i];

		if (tmpIdx >= 2 && i != tripleCardNum && i > onepairCardNum)
		{
			onepairCardNum = i;
		}
	}

	// 원페어가 13이면 13도 A이므로 A로 세팅한다.
	if (onepairCardNum == 13)
		onepairCardNum = 0;

	if (tripleCardNum == 13)
		tripleCardNum = 0;

	if (SetHighJokbo((HighJokboKind)StraightFlushCheck(m_HighJokboCardList, sortCardContainer, flushShape, royalCheck)))
		return;
	if (SetHighJokbo((HighJokboKind)FourCardCheck(m_HighJokboCardList, sortCardContainer, fourCardNum)))
		return;
	if (SetHighJokbo((HighJokboKind)FullHouseCheck(m_HighJokboCardList, sortCardContainer, tripleCardNum, onepairCardNum)))
		return;

	if (SetHighJokbo((HighJokboKind)FlushCheck(m_HighJokboCardList, sortCardContainer, flushShape)))
		return;
	if (SetHighJokbo((HighJokboKind)StraightCheck(m_HighJokboCardList, sortCardContainer, royalCheck)))
		return;
	if (SetHighJokbo((HighJokboKind)TripleCheck(m_HighJokboCardList, sortCardContainer, tripleCardNum)))
		return;
	if (SetHighJokbo((HighJokboKind)PairCheck(m_HighJokboCardList, sortCardContainer, getCardNumber, onepairCardNum)))
		return;
	if (SetHighJokbo((HighJokboKind)TopCheck(m_HighJokboCardList, sortCardContainer)))
		return;
}

void UserJokboInfo::HighJokboCheck()
{
	m_HighJokboCardList.clear();

	char getCardKind[4];					// 각 카드 종류별 받은 갯수(스다하크)
	char getCardNumber[14];					// 카드번호별 가진 갯수
	bool royalCheck[14];					// 마운틴, 백스트레이트 체크용

	memset(getCardKind, 0, 4);
	memset(getCardNumber, 0, 14);
	memset(royalCheck, false, 14);

	// 순서 정렬
	vector<CardData*>	sortCardContainer;
	SortCard(sortCardContainer, SortKind::CARD_SORT_HIGH);

	CardData * p_tmpCardData;

	int flushShape = -1;
	int fourCardNum = -1;
	int straightStartNumber = 0;
	int tripleCardNum = -1;
	int onepairCardNum = -1;

	char tmpIdx;

	for (int i = 0, j = sortCardContainer.size(); i < j; i++)
	{
		p_tmpCardData = sortCardContainer[i];
		
		// 플러쉬 가능 여부 체크
		getCardKind[p_tmpCardData->m_Kind]++;
		if (getCardKind[p_tmpCardData->m_Kind] >= 5)
			flushShape = p_tmpCardData->m_Kind;

		// 포카드 가능 여부 체크
		getCardNumber[p_tmpCardData->m_Number]++;
		if (getCardNumber[p_tmpCardData->m_Number] == 4)
			fourCardNum = p_tmpCardData->m_Number;
	}
	// 처음과 끝은 A로 (계산 편의상)
	getCardNumber[13] = getCardNumber[0];

	// 트리플 가능 여부 체크
	for (int i = sizeof(getCardNumber) - 1; i >= 1; i--)
	{
		tmpIdx = getCardNumber[i];
		if (tmpIdx >= 3 && tmpIdx > tripleCardNum)
		{
			tripleCardNum = i;
		}
	}
	//  원페어 가능 여부 체크
	for (int i = sizeof(getCardNumber) - 1; i >= 1; i--)
	{
		tmpIdx = getCardNumber[i];

		if (tmpIdx >= 2 && i != tripleCardNum && i > onepairCardNum)
		{
			onepairCardNum = i;
		}
	}

	// 원페어가 13이면 13도 A이므로 A로 세팅한다.
	if (onepairCardNum == 13)
		onepairCardNum = 0;

	if (tripleCardNum == 13)
		tripleCardNum = 0;

	if (SetHighJokbo((HighJokboKind)StraightFlushCheck(m_HighJokboCardList, sortCardContainer, flushShape, royalCheck)))
		return;
	if (SetHighJokbo((HighJokboKind)FourCardCheck(m_HighJokboCardList, sortCardContainer, fourCardNum)))
		return;
	if (SetHighJokbo((HighJokboKind)FullHouseCheck(m_HighJokboCardList, sortCardContainer, tripleCardNum, onepairCardNum)))
		return;

	if (SetHighJokbo((HighJokboKind)FlushCheck(m_HighJokboCardList, sortCardContainer, flushShape)))
		return;
	if (SetHighJokbo((HighJokboKind)StraightCheck(m_HighJokboCardList, sortCardContainer, royalCheck)))
		return;
	if (SetHighJokbo((HighJokboKind)TripleCheck(m_HighJokboCardList, sortCardContainer, tripleCardNum)))
		return;
	if (SetHighJokbo((HighJokboKind)PairCheck(m_HighJokboCardList, sortCardContainer, getCardNumber, onepairCardNum)))
		return;
	if (SetHighJokbo((HighJokboKind)TopCheck(m_HighJokboCardList, sortCardContainer)))
		return;
}

void UserJokboInfo::LowJokboCheck()
{
	m_LowJokboCardList.clear();

	char getCardKind[4];					// 각 카드 종류별 받은 갯수(스다하크)
	char getCardNumber[14];					// 카드번호별 가진 갯수
	bool royalCheck[14];					// 마운틴, 백스트레이트 체크용

	memset(getCardKind, 0, 4);
	memset(getCardNumber, 0, 14);
	memset(royalCheck, false, 14);

	// 순서 정렬
	vector<CardData*>	sortCardContainer;
	SortCard(sortCardContainer, SortKind::CARD_SORT_HIGH);

	CardData * p_tmpCardData;

	int flushShape = -1;
	int fourCardNum = -1;
	int straightStartNumber = 0;
	int tripleCardNum = -1;
	int onepairCardNum = -1;

	char tmpIdx;

	for (int i = 0, j = sortCardContainer.size(); i < j; i++)
	{
		p_tmpCardData = sortCardContainer[i];

		// 플러쉬 가능 여부 체크
		getCardKind[p_tmpCardData->m_Kind]++;
		if (getCardKind[p_tmpCardData->m_Kind] >= 5)
			flushShape = p_tmpCardData->m_Kind;

		// 포카드 가능 여부 체크
		getCardNumber[p_tmpCardData->m_Number]++;
		if (getCardNumber[p_tmpCardData->m_Number] == 4)
			fourCardNum = p_tmpCardData->m_Number;
	}
	// 처음과 끝은 A로 (계산 편의상)
	getCardNumber[13] = getCardNumber[0];

	// 트리플 가능 여부 체크
	for (int i = sizeof(getCardNumber) - 1; i >= 1; i--)
	{
		tmpIdx = getCardNumber[i];
		if (tmpIdx >= 3 && i < tripleCardNum)
		{
			tripleCardNum = i;
		}
	}
	
	if (tripleCardNum == 13)
		tripleCardNum = 0;


	if (SetLowJokbo((LowJokboKind)StraightFlushCheck(m_LowJokboCardList, sortCardContainer, flushShape, royalCheck)))
		return;
	if (SetLowJokbo((LowJokboKind)FourCardCheck(m_LowJokboCardList, sortCardContainer, fourCardNum)))
		return;
	if (SetLowJokbo((LowJokboKind)FullHouseCheck(m_LowJokboCardList, sortCardContainer, tripleCardNum, onepairCardNum)))
		return;

	sortCardContainer.clear();
	SortCard(sortCardContainer, SortKind::CARD_SORT_LOW);
			

	if (SetLowJokbo((LowJokboKind)LowTopCheck(m_LowJokboCardList, sortCardContainer)))
		return;
	if (SetLowJokbo((LowJokboKind)LowOnePairCheck(m_LowJokboCardList, sortCardContainer, getCardNumber)))
		return;
	if (SetLowJokbo((LowJokboKind)LowTwoPairCheck(m_LowJokboCardList, sortCardContainer, getCardNumber)))
		return;
	if (SetLowJokbo((LowJokboKind)LowTripleCheck(m_LowJokboCardList, sortCardContainer, getCardNumber)))
		return;
	if (SetLowJokbo((LowJokboKind)LowStraightCheck(m_LowJokboCardList, sortCardContainer)))
		return;
	if (SetLowJokbo((LowJokboKind)LowTopDownCheck(m_LowJokboCardList, sortCardContainer)))
		return;
}

void UserJokboInfo::BadukiJokboCheck()
{
	m_LowJokboCardList.clear();

	char getCardKind[4];					// 각 카드 종류별 받은 갯수(스다하크)
	char getCardNumber[14];					// 카드번호별 가진 갯수
	bool royalCheck[14];					// 마운틴, 백스트레이트 체크용

	memset(getCardKind, 0, 4);
	memset(getCardNumber, 0, 14);
	memset(royalCheck, false, 14);

	// 순서 정렬
	vector<CardData*>	sortCardContainer;
	SortCard(sortCardContainer, SortKind::CARD_SORT_HIGH);

	CardData * p_tmpCardData;

	int cardNum = 4;
	for (int i = 0, j = sortCardContainer.size(); i < j; i++)
	{
		p_tmpCardData = sortCardContainer[i];

		if (p_tmpCardData->m_Kind < 0 || p_tmpCardData->m_Kind > 3)
			continue;

		getCardKind[p_tmpCardData->m_Kind]++;
		getCardNumber[p_tmpCardData->m_Number]++;
		if (getCardNumber[p_tmpCardData->m_Number] >= 2 || getCardKind[p_tmpCardData->m_Kind] >= 2)
			cardNum--;
	}
	// 처음과 끝은 A로 (계산 편의상)
	getCardNumber[13] = getCardNumber[0];

	sortCardContainer.clear();
	SortCard(sortCardContainer, SortKind::CARD_SORT_LOW);

	// 1. 문양이나 숫자가 모두 다른 경우 세컨드까지 체크
	if (cardNum == 4)
	{
		if (SetLowJokbo((LowJokboKind)BadukiThirdCheck(m_LowJokboCardList, sortCardContainer, royalCheck)))
			return;
		if (SetLowJokbo((LowJokboKind)BadukiTopCheck(m_LowJokboCardList, sortCardContainer)))
			return;
	}
	
	if (SetLowJokbo((LowJokboKind)BadukiBaseCheck(m_LowJokboCardList, sortCardContainer, getCardNumber, getCardKind)))
		return;
}


bool UserJokboInfo::SetHighJokbo(HighJokboKind kind)
{
	m_HighJokboKind = kind;
	CCLOG("UserJokboInfo::SetHighJokbo = %d", kind);

	if (kind == HighJokboKind::HIGH_NO)
		return false;

	SetHighJokboRepCardNum();

	return true;
}

bool UserJokboInfo::SetLowJokbo(LowJokboKind kind)
{
	m_LowJokboKind = kind;

	if (kind == LowJokboKind::LOW_NO)
		return false;

	if (kind >= BADUKI_GOLF)
		SetBadukiJokboRepCardNum();
	else
		SetLowJokboRepCardNum();

	return true;
}

void UserJokboInfo::SetHighJokboRepCardNum()
{
	m_HighJokboRepCardList.clear();
	// 족보가 같으면 동률 체크
	switch (m_HighJokboKind)
	{
		case HIGH_FULL_HOUSE:
			m_HighJokboRepCardList.push_back(m_HighJokboCardList[0]);
			m_HighJokboRepCardList.push_back(m_HighJokboCardList[3]);
			break;
		case HIGH_TWO_PAIR:
			m_HighJokboRepCardList.push_back(m_HighJokboCardList[0]);
			m_HighJokboRepCardList.push_back(m_HighJokboCardList[2]);
			break;
		default:
			m_HighJokboRepCardList.push_back(m_HighJokboCardList[0]);
			break;
	}
}

void UserJokboInfo::SetLowJokboRepCardNum()
{
	m_LowJokboRepCardList.clear();
	// 족보가 같으면 동률 체크
	switch (m_LowJokboKind)
	{
		case LOW_TWO_PAIR:
			m_LowJokboRepCardList.push_back(m_LowJokboCardList[0]);
			m_LowJokboRepCardList.push_back(m_LowJokboCardList[2]);
			break;
		default:
			m_LowJokboRepCardList.push_back(m_LowJokboCardList[0]);
			break;
	}
}

void UserJokboInfo::SetBadukiJokboRepCardNum()
{
	if (m_LowJokboCardList.size() == 0)
		return;

	m_LowJokboRepCardList.clear();
	// 족보가 같으면 동률 체크
	switch (m_LowJokboKind)
	{
		case BADUKI_BASE:
			m_LowJokboRepCardList.push_back(m_LowJokboCardList[0]);
			m_LowJokboRepCardList.push_back(m_LowJokboCardList[1]);
			m_LowJokboRepCardList.push_back(m_LowJokboCardList[2]);
			break;
		case BADUKI_TWO_BASE:
			m_LowJokboRepCardList.push_back(m_LowJokboCardList[0]);
			m_LowJokboRepCardList.push_back(m_LowJokboCardList[1]);
			break;
		case BADUKI_TWO_BASE_DOWN:
			m_LowJokboRepCardList.push_back(m_LowJokboCardList[0]);
			break;
		default:
			m_LowJokboRepCardList.push_back(m_LowJokboCardList[0]);
			m_LowJokboRepCardList.push_back(m_LowJokboCardList[1]);
			m_LowJokboRepCardList.push_back(m_LowJokboCardList[2]);
			m_LowJokboRepCardList.push_back(m_LowJokboCardList[3]);
			break;
	}
}

int UserJokboInfo::StraightFlushCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList, int flushShape, bool * royalCheck)
{
	jokboCardList.clear();
	int num = sortCardList.size();
	
	// 1. 플러쉬이면 스티플 이상 체크 
	if (flushShape > -1)
	{
		// 1.1 로티플 체크
		memset(royalCheck, false, 14);

		for (int i = num - 1; i >= 0; i--)
		{
			if (MOUNTAIN_LIST[sortCardList[i]->m_Number] && !royalCheck[sortCardList[i]->m_Number] && flushShape == sortCardList[i]->m_Kind)
			{
				royalCheck[sortCardList[i]->m_Number] = true;
				jokboCardList.push_back(sortCardList[i]);
				if (jokboCardList.size() >= 5)
				{
					return HighJokboKind::HIGH_ROYAL_STRAIGHT_FLUSH;
				}
			}
		}

		jokboCardList.clear();
		memset(royalCheck, false, 14);
		for (int i = num - 1; i >= 0; i--)
		{
			if (BACK_STRAIGHT_LIST[sortCardList[i]->m_Number] && !royalCheck[sortCardList[i]->m_Number] && flushShape == sortCardList[i]->m_Kind)
			{
				royalCheck[sortCardList[i]->m_Number] = true;
				jokboCardList.push_back(sortCardList[i]);
				if (jokboCardList.size() >= 5)
				{
					return HighJokboKind::HIGH_STRAIGHT_FLUSH;
				}
			}
		}

		// 1.3 스티플 체크
		int straightStartNumber = -100;
		jokboCardList.clear();
		for (int i = num - 1; i >= 0; i--)
		{
			if (flushShape == sortCardList[i]->m_Kind)
			{
				if (straightStartNumber - 1 == sortCardList[i]->m_Number)
				{
					jokboCardList.push_back(sortCardList[i]);
					straightStartNumber -= 1;
				}
				else if (flushShape == sortCardList[i]->m_Kind && straightStartNumber != sortCardList[i]->m_Number)
				{
					straightStartNumber = sortCardList[i]->m_Number;
					jokboCardList.clear();
					jokboCardList.push_back(sortCardList[i]);
				}
				if (jokboCardList.size() >= 5)
				{
					return HighJokboKind::HIGH_STRAIGHT_FLUSH;
				}
			}
		}
	}

	return HighJokboKind::HIGH_NO;
}


// 2. 포카드 체크
int UserJokboInfo::FourCardCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList, int fourCardNum)
{
	jokboCardList.clear();
	int num = sortCardList.size();

	// 1. 플러쉬이면 스티플 이상 체크 
	if (fourCardNum < 0)
		return HighJokboKind::HIGH_NO;

	for (int i = num - 1; i >= 0; i--)
	{
		if (sortCardList[i]->m_Number == fourCardNum)
		{
			jokboCardList.push_back(sortCardList[i]);
			if (jokboCardList.size() == 4)
				break;
		}
	}

	for (int i = num - 1; i >= 0; i--)
	{
		if (sortCardList[i]->m_Number != fourCardNum)
		{
			jokboCardList.push_back(sortCardList[i]);
			break;
		}
	}

	return HighJokboKind::HIGH_FOUR_CARD;
}

// 3. 풀하우스 체크
int UserJokboInfo::FullHouseCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList, int tripleCardNum, int onepairCardNum)
{
	if (tripleCardNum == -1 || onepairCardNum == -1)
		return HighJokboKind::HIGH_NO;

	jokboCardList.clear();
	int num = sortCardList.size();
	int onepairCount = 0;

	// 트리플 먼저 넣기
	for (int i = num - 1; i >= 0; i--)
	{
		if (sortCardList[i]->m_Number == tripleCardNum)
		{
			jokboCardList.push_back(sortCardList[i]);
			if (jokboCardList.size() == 3)
				break;
		}
	}

	/// 다음 원페어 넣기
	for (int i = num - 1; i >= 0; i--)
	{
		if (sortCardList[i]->m_Number == onepairCardNum)
		{
			if (onepairCount >= 2)
				continue;
			onepairCount++;
			jokboCardList.push_back(sortCardList[i]);
			if (jokboCardList.size() == 5)
				break;
		}
	}

	return HighJokboKind::HIGH_FULL_HOUSE;
}

// 4. 플러쉬 체크
int UserJokboInfo::FlushCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList, int flushShape)
{
	if (flushShape <= -1)
		return HighJokboKind::HIGH_NO;

	jokboCardList.clear();
	int num = sortCardList.size();

	for (int i = num - 1; i >= 0; i--)
	{
		if (sortCardList[i]->m_Kind == flushShape)
		{
			jokboCardList.push_back(sortCardList[i]);
			if (jokboCardList.size() >= 5)
				break;
		}
	}
	return HighJokboKind::HIGH_FLUSH;
}

// 5. 마운틴, 스트레이트 체크
int UserJokboInfo::StraightCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList, bool * royalCheck)
{
	jokboCardList.clear();
	int num = sortCardList.size();
	if (num < 5)
		return HighJokboKind::HIGH_NO;
	
	// 5. 마운틴 체크
	memset(royalCheck, false, 14);
	for (int i = num - 1; i >= 0; i--)
	{
		if (MOUNTAIN_LIST[sortCardList[i]->m_Number] && !royalCheck[sortCardList[i]->m_Number])
		{
			royalCheck[sortCardList[i]->m_Number] = true;
			jokboCardList.push_back(sortCardList[i]);
			if (jokboCardList.size() >= 5)
				return HighJokboKind::HIGH_MOUNTAIN;
		}
	}

	// 6. 백스트레이트 체크
	jokboCardList.clear();
	memset(royalCheck, false, 14);
	for (int i = num - 1; i >= 0; i--)
	{
		if (BACK_STRAIGHT_LIST[sortCardList[i]->m_Number] && !royalCheck[sortCardList[i]->m_Number])
		{
			royalCheck[sortCardList[i]->m_Number] = true;
			jokboCardList.push_back(sortCardList[i]);

			if (jokboCardList.size() >= 5)
				return HighJokboKind::HIGH_BACK_STRAIGHT;
		}
	}
	// 7. 스트레이트 체크
	jokboCardList.clear();
	int straightStartNumber = -100;
	for (int i = num - 1; i >= 0; i--)
	{
		if (straightStartNumber - 1 == sortCardList[i]->m_Number)
		{
			jokboCardList.push_back(sortCardList[i]);
			straightStartNumber -= 1;
		}
		else if (straightStartNumber != sortCardList[i]->m_Number)
		{
			straightStartNumber = sortCardList[i]->m_Number;
			jokboCardList.clear();
			jokboCardList.push_back(sortCardList[i]);
		}

		if (jokboCardList.size() >= 5)
			return HighJokboKind::HIGH_STRAIGHT;
	}

	return HighJokboKind::HIGH_NO;
}

// 6. 트리플 체크
int UserJokboInfo::TripleCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList, int tripleCardNum)
{
	if (tripleCardNum == -1)
		return HighJokboKind::HIGH_NO;

	jokboCardList.clear();
	int num = sortCardList.size();

	// 트리플 먼저 넣기
	for (int i = num - 1; i >= 0; i--)
	{
		if (sortCardList[i]->m_Number == tripleCardNum)
		{
			jokboCardList.push_back(sortCardList[i]);
			if (jokboCardList.size() == 3)
				break;
		}
	}

	if (num > 3)
	{
		/// 트리플 이외에 가장 높은 숫자를 2개 채워넣는다.
		for (int i = num - 1; i >= 0; i--)
		{
			if (sortCardList[i]->m_Number != tripleCardNum)
			{
				jokboCardList.push_back(sortCardList[i]);
				if (jokboCardList.size() == 5)
					break;
			}
		}
	}
	return HighJokboKind::HIGH_TRIPLE;
}

// 6. 투페어/원페어 체크
int UserJokboInfo::PairCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList, char * getCardNumber, int onepaircardNum)
{
	if (onepaircardNum == -1)
		return HighJokboKind::HIGH_NO;

	jokboCardList.clear();
	int num = sortCardList.size();

	char twopairNumber[2];
	memset(twopairNumber, -1, 2);

	int jokboMatchCount = 0;
	for (int i = num - 1; i >= 0; i--)
	{
		if (getCardNumber[sortCardList[i]->m_Number] >= 2)
		{
			jokboCardList.push_back(sortCardList[i]);
			jokboMatchCount = jokboCardList.size();
			if (jokboMatchCount >= 4)
				break;

			if (jokboMatchCount == 1 || jokboMatchCount == 3)
				twopairNumber[jokboMatchCount / 2] = sortCardList[i]->m_Number;
		}
	}

	HighJokboKind jokboKind;
	if (jokboMatchCount == 4)
	{
		jokboKind = HighJokboKind::HIGH_TWO_PAIR;
	}
	else
	{
		jokboKind = HighJokboKind::HIGH_ONE_PAIR;
	}
	if (num > 2)
	{
		for (int i = num - 1; i >= 0; i--)
		{
			if (sortCardList[i]->m_Number != twopairNumber[0] && sortCardList[i]->m_Number != twopairNumber[1])
			{
				jokboCardList.push_back(sortCardList[i]);
				if (jokboCardList.size() >= 5)
					break;
			}
		}
	}

	return jokboKind;
}

int UserJokboInfo::TopCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList)
{
	jokboCardList.clear();
	int num = sortCardList.size();

	for (int i = num - 1; i >= 0; i--)
	{
		jokboCardList.push_back(sortCardList[i]);
		if (jokboCardList.size() >= 5)
			break;
	}

	return HighJokboKind::HIGH_TOP;
}

int UserJokboInfo::LowTopCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList)
{
	jokboCardList.clear();
	int num = sortCardList.size();

	int yetNum = -1;
	int straightCount = 0;
	int straightStartNumber = -1;
	for (int i = 0; i < num; i++)
	{
		// 페어가 되면 안되므로 무시
		if (yetNum == sortCardList[i]->m_Number)
			continue;

		if (straightStartNumber + 1 == sortCardList[i]->m_Number)
		{
			// 스트레이트가 될거 같으면 다음으로 점프
			if (straightCount == 4)
				continue;
			straightStartNumber += 1;
			straightCount++;
		}
		else
		{
			straightStartNumber = sortCardList[i]->m_Number;
			straightCount = 1;
		}

		yetNum = sortCardList[i]->m_Number;
		jokboCardList.push_back(sortCardList[i]);
		if (jokboCardList.size() >= 5)
			break;
	}

	// 3.1 갯수가 충족하는지 체크 
	// 5개 미만일때는 모두를 이용해서 top 족보가 나오게
	// 5개 이상일때는 5개로 top 족보가 나오게
	int jokboCnt = jokboCardList.size();
	if (jokboCnt == 5 || jokboCnt == sortCardList.size())
	{
		LowJokboKind jokboKind;
		if (jokboCardList[jokboCnt - 1]->m_Number >= 5)
		{
			jokboKind = (LowJokboKind)(LowJokboKind::LOW_SIX_TOP + jokboCardList[jokboCnt - 1]->m_Number - 5);
		}
		else
			jokboKind = LowJokboKind::LOW_TOP_DOWN;

		if (jokboCnt < 5)
			jokboKind = LowJokboKind::LOW_TOP_DOWN;

		return jokboKind;
	}

	return LowJokboKind::LOW_NO;
}

int UserJokboInfo::LowOnePairCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList, char * getCardNumber)
{
	jokboCardList.clear();
	int num = sortCardList.size();
	int onepairCardNum = -1;
	int yetNum = -1;

	int jokboMatchCount = 0;
	for (int i = 0; i < num; i++)
	{
		if (getCardNumber[sortCardList[i]->m_Number] >= 2)
		{
			jokboCardList.push_back(sortCardList[i]);
			if (jokboCardList.size() == 2)
			{
				onepairCardNum = sortCardList[i]->m_Number;
				break;
			}
		}
	}

	if (onepairCardNum > -1)
	{
		// 4.3 그외에 놈 충전
		for (int i = 0; i < num; i++)
		{
			if (sortCardList[i]->m_Number != onepairCardNum && sortCardList[i]->m_Number != yetNum)
			{
				jokboCardList.push_back(sortCardList[i]);
				if (jokboCardList.size() >= 5)
					break;

				yetNum = sortCardList[i]->m_Number;
			}
		}
		// 4.3 복사 갯수를 충족하면 복사
		jokboMatchCount = jokboCardList.size();
		if (jokboMatchCount == 5 || jokboMatchCount == sortCardList.size())
			return LowJokboKind::LOW_ONE_PAIR;
	}

	return LowJokboKind::LOW_NO;
}

int UserJokboInfo::LowTwoPairCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList, char * getCardNumber)
{
	if (sortCardList.size() < 4)
		return LowJokboKind::LOW_NO;

	// 5. 투페어 체크
	// 5.1 투페어로 선택할 가장 낮은 놈을 찾는다.
	jokboCardList.clear();
	int num = sortCardList.size();
	int onepairCardNum = 0;
	char twopairNumber[2];
	memset(twopairNumber, -1, 2);
	int jokboMatchCount = 0;

	for (int i = 0; i < num; i++)
	{
		if (getCardNumber[sortCardList[i]->m_Number] >= 2)
		{
			//if (onepairCardNum == 2)
			//	continue;
			//onepairCardNum++;
			jokboCardList.push_back(sortCardList[i]);
			jokboMatchCount = jokboCardList.size();
			if (jokboMatchCount >= 4)
				break;

			if (jokboMatchCount == 1 || jokboMatchCount == 3)
				twopairNumber[jokboMatchCount / 2] = sortCardList[i]->m_Number;
		}
		//else
			//onepairCardNum = 0;
	}
	if (jokboMatchCount >= 4)
	{
		for (int i = 0; i < num; i++)
		{
			if (sortCardList[i]->m_Number != twopairNumber[0] && sortCardList[i]->m_Number != twopairNumber[1])
			{
				jokboCardList.push_back(sortCardList[i]);
				if (jokboCardList.size() >= 5)
					break;
			}
		}

		jokboMatchCount = jokboCardList.size();
		if (jokboMatchCount == 5 || jokboMatchCount == sortCardList.size())
		{
			return LowJokboKind::LOW_TWO_PAIR;
		}
	}

	return LowJokboKind::LOW_NO;
}

int UserJokboInfo::LowTripleCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList, char * getCardNumber)
{
	if (sortCardList.size() < 3)
		return LowJokboKind::LOW_NO;

	jokboCardList.clear();
	int num = sortCardList.size();
	int tripleCardNum = -1;
	int jokboMatchCount = 0;

	for (int i = 0; i < num; i++)
	{
		if (getCardNumber[sortCardList[i]->m_Number] >= 3)
		{
			jokboCardList.push_back(sortCardList[i]);
			jokboMatchCount = jokboCardList.size();
			if (jokboMatchCount >= 3)
			{
				tripleCardNum = sortCardList[i]->m_Number;
				break;
			}
		}
	}
	if (tripleCardNum > -1)
	{
		for (int i = 0; i < num; i++)
		{
			if (sortCardList[i]->m_Number != tripleCardNum)
			{
				jokboCardList.push_back(sortCardList[i]);
				if (jokboCardList.size() >= 5)
					break;
			}
		}

		jokboMatchCount = jokboCardList.size();
		if (jokboMatchCount == 5 || jokboMatchCount == sortCardList.size())
		{
			return LowJokboKind::LOW_TRIPLE;
		}
	}

	return LowJokboKind::LOW_NO;
}

int UserJokboInfo::LowStraightCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList)
{
	jokboCardList.clear();
	int num = sortCardList.size();
	if (num < 5)
		return LowJokboKind::LOW_NO;

	// 7. 스트레이트 체크
	int straightStartNumber = -100;
	for (int i = 0; i < num; i++)
	{
		if (straightStartNumber + 1 == sortCardList[i]->m_Number)
		{
			jokboCardList.push_back(sortCardList[i]);
			straightStartNumber += 1;
		}
		else if (straightStartNumber != sortCardList[i]->m_Number)
		{
			straightStartNumber = sortCardList[i]->m_Number;
			jokboCardList.clear();
			jokboCardList.push_back(sortCardList[i]);
		}

		if (jokboCardList.size() >= 5)
			return LowJokboKind::LOW_STRAIGHT;
	}

	return LowJokboKind::LOW_NO;
}

int UserJokboInfo::LowTopDownCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList)
{
	jokboCardList.clear();
	int num = sortCardList.size();

	for (int i = 0; i < num; i++)
	{
		jokboCardList.push_back(sortCardList[i]);
		if (jokboCardList.size() >= 5)
			break;
	}

	return LowJokboKind::LOW_TOP_DOWN;
}

int UserJokboInfo::BadukiThirdCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList, bool * royalCheck)
{
	jokboCardList.clear();
	int num = sortCardList.size();

	// 1.1 골프 체크
	memset(royalCheck, false, 14);

	for (int i = 0; i < num; i++)
	{
		if (GOLF_LIST[sortCardList[i]->m_Number] && !royalCheck[sortCardList[i]->m_Number])
		{
			royalCheck[sortCardList[i]->m_Number] = true;
			jokboCardList.push_back(sortCardList[i]);
			if (jokboCardList.size() >= 4)
			{
				return LowJokboKind::BADUKI_GOLF;
			}
		}
	}

	// 1.2 세컨드 체크
	jokboCardList.clear();
	memset(royalCheck, false, 14);
	for (int i = 0; i < num; i++)
	{
		if (SECOND_LIST[sortCardList[i]->m_Number] && !royalCheck[sortCardList[i]->m_Number])
		{
			royalCheck[sortCardList[i]->m_Number] = true;
			jokboCardList.push_back(sortCardList[i]);
			if (jokboCardList.size() >= 4)
			{
				return LowJokboKind::BADUKI_SECOND;
			}
		}
	}

	// 1.3 써드 체크
	jokboCardList.clear();
	memset(royalCheck, false, 14);
	for (int i = 0; i < num; i++)
	{
		if (THIRD_LIST[sortCardList[i]->m_Number] && !royalCheck[sortCardList[i]->m_Number])
		{
			royalCheck[sortCardList[i]->m_Number] = true;
			jokboCardList.push_back(sortCardList[i]);
			if (jokboCardList.size() >= 4)
			{
				return LowJokboKind::BADUKI_THIRD;
			}
		}
	}

	return LowJokboKind::LOW_NO;
}

int UserJokboInfo::BadukiTopCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList)
{
	jokboCardList.clear();
	int num = sortCardList.size();

	for (int i = 0; i < num; i++)
	{
		jokboCardList.push_back(sortCardList[i]);
		if (jokboCardList.size() >= 4)
			break;
	}

	// 3.1 갯수가 충족하는지 체크 
	int jokboCnt = jokboCardList.size();
	if (jokboCnt == 4)
	{
		LowJokboKind jokboKind;
		jokboKind = (LowJokboKind)(LowJokboKind::BADUKI_FIVE_TOP + jokboCardList[jokboCnt - 1]->m_Number - 4);

		return jokboKind;
	}

	return LowJokboKind::LOW_NO;
}

int UserJokboInfo::BadukiBaseCheck(vector<CardData*> &jokboCardList, vector<CardData*> &sortCardList, char * getCardNumber, char * getCardKind)
{
	char getCompareCardNumber[14];
	char getCompareCardKind[4];

	jokboCardList.clear();
	int num = sortCardList.size();

	int cardNum = 0;

	memset(getCompareCardNumber, 0, 14);
	memset(getCompareCardKind, 0, 4);

	char isUse[4];
	memset(isUse, 0, 4);

	bool meLose;
	for (int i = 0; i < num; i++)
	{
		if (getCompareCardNumber[sortCardList[i]->m_Number] == 0 && getCompareCardKind[sortCardList[i]->m_Kind] == 0)
		{
			meLose = false;
			if (getCardNumber[sortCardList[i]->m_Number] > 1)
			{
				if (i <= num - 3 && sortCardList[i]->m_Number == sortCardList[i + 1]->m_Number && getCompareCardKind[sortCardList[i + 1]->m_Kind] == 0)
				{
					for (int j = i + 2; j < num; j++)
					{
						// 내가 같으면 내가 진거야. 그래서, 난 등록이 안됨.
						if (sortCardList[i]->m_Kind == sortCardList[j]->m_Kind)
						{
							meLose = true;
						}
						// 상대방이 같으면 내가 이긴거니 중지
						else if (sortCardList[i + 1]->m_Kind == sortCardList[j]->m_Kind)
							break;
					}
				}
			}

			if (!meLose)
			{
				jokboCardList.push_back(sortCardList[i]);
				getCompareCardNumber[sortCardList[i]->m_Number]++;
				getCompareCardKind[sortCardList[i]->m_Kind]++;

				isUse[i] = true;
				cardNum++;
			}
		}
	}


	for (int i = 0; i < num; i++)
	{
		if (!isUse[i])
		{
			jokboCardList.push_back(sortCardList[i]);
		}
	}

	if (cardNum == 3)
		return LowJokboKind::BADUKI_BASE;
	else if (cardNum == 2)
		return LowJokboKind::BADUKI_TWO_BASE;


	return LowJokboKind::BADUKI_TWO_BASE_DOWN;
}

void UserJokboInfo::SortCard(vector<CardData*> &p_container, SortKind sortKind, int start, int end)
{
	int num = m_pCardList->size();
	int max = 0;

	if (end < num - 1)
		num = end;

	for (int i = start; i < num; i++)
		p_container.push_back((*m_pCardList)[i]);
	
	CardData * data1;
	CardData * data2;
	CardData * tmp;

	for (int i = 0; i < num - 1; i++)
	{
		max = i;
		for (int j = i + 1; j < num; j++)
		{
			data1 = p_container[max];
			data2 = p_container[j];

			if (sortKind == SortKind::CARD_SORT_LOW)
			{
				if (CARD_LOW_ORDER[data1->m_Number] > CARD_LOW_ORDER[data2->m_Number] ||
					(CARD_LOW_ORDER[data1->m_Number] == CARD_LOW_ORDER[data2->m_Number] && data1->m_Kind > data2->m_Kind))
					max = j;
			}
			else
			{
				if (CARD_HIGH_ORDER[data1->m_Number] > CARD_HIGH_ORDER[data2->m_Number] ||
					(CARD_HIGH_ORDER[data1->m_Number] == CARD_HIGH_ORDER[data2->m_Number] && data1->m_Kind > data2->m_Kind))
					max = j;
			}
		}
		if (i != max)
		{
			tmp = p_container[i];
			p_container[i] = p_container[max];
			p_container[max] = tmp;
		}
	}
}

string UserJokboInfo::GetFullJokboString()
{
	string jokbo = "";
	bool isHigh = false;
	if (m_HighJokboKind > HighJokboKind::HIGH_NO)
	{
		jokbo.append(GameDataManager::getSingletonPtr()->GetCardNumStr(m_HighJokboRepCardList[0]->m_Number));
		if (m_HighJokboKind == HighJokboKind::HIGH_FULL_HOUSE || m_HighJokboKind == HighJokboKind::HIGH_TWO_PAIR)
		{
			jokbo.append(",");
			jokbo.append(GameDataManager::getSingletonPtr()->GetCardNumStr(m_HighJokboRepCardList[1]->m_Number));
		}
		//jokbo.append(" ");
		jokbo.append(GameDataManager::getSingletonPtr()->GetFullJokboStr(m_HighJokboKind));

		isHigh = true;
	}

	if (m_LowJokboKind > LowJokboKind::LOW_NO)
	{
		if (m_HighJokboKind != m_LowJokboKind)
		{
			if (isHigh)
				jokbo.append(" / ");
			if (m_LowJokboKind < LOW_SIX_TOP || (m_LowJokboKind > LOW_K_TOP && m_LowJokboKind != LOW_TOP_DOWN))
				jokbo.append(GameDataManager::getSingletonPtr()->GetCardNumStr(m_HighJokboRepCardList[0]->m_Number));
			jokbo.append(GameDataManager::getSingletonPtr()->GetFullJokboStr(m_LowJokboKind));
		}
	}

	return jokbo;
}

string UserJokboInfo::GetHighJokboString()
{
	string jokbo = "";
	if (m_HighJokboKind > HighJokboKind::HIGH_NO)
	{
		if (m_HighJokboKind != HighJokboKind::HIGH_BACK_STRAIGHT && m_HighJokboKind != HighJokboKind::HIGH_MOUNTAIN &&
			m_HighJokboKind != HighJokboKind::HIGH_ROYAL_STRAIGHT_FLUSH)
		{
			jokbo.append(GameDataManager::getSingletonPtr()->GetCardNumStr(m_HighJokboRepCardList[0]->m_Number));
			if (m_HighJokboKind == HighJokboKind::HIGH_FULL_HOUSE || m_HighJokboKind == HighJokboKind::HIGH_TWO_PAIR)
			{
				jokbo.append(",");
				jokbo.append(GameDataManager::getSingletonPtr()->GetCardNumStr(m_HighJokboRepCardList[1]->m_Number));
			}
		}

		jokbo.append(GameDataManager::getSingletonPtr()->GetFullJokboStr(m_HighJokboKind));
	}
	return jokbo;
}


string UserJokboInfo::GetLowJokboString()
{
	string jokbo = "";
	if (m_LowJokboKind > LowJokboKind::LOW_NO)
	{
		if (m_HighJokboKind != m_LowJokboKind)
		{
			if (m_LowJokboKind != LOW_TOP_DOWN && (m_LowJokboKind < LOW_SIX_TOP || m_LowJokboKind > LOW_K_TOP))
				jokbo.append(GameDataManager::getSingletonPtr()->GetCardNumStr(m_HighJokboRepCardList[0]->m_Number));
			jokbo.append(GameDataManager::getSingletonPtr()->GetFullJokboStr(m_LowJokboKind));
		}
	}
	return jokbo;
}

string UserJokboInfo::GetBadukiJokboString(bool _isFull)
{
	string jokbo = "";
	if (m_LowJokboKind > LowJokboKind::LOW_NO)
	{
		if (_isFull == true)
		{
			if (m_LowJokboKind == LowJokboKind::BADUKI_BASE || m_LowJokboKind == LowJokboKind::BADUKI_TWO_BASE)
			{
				int count = m_LowJokboRepCardList.size(); //3 - (m_LowJokboKind - LowJokboKind::BADUKI_BASE);

				for (int i = 0; i < count; i++)
				{
					if (i > 0)
						jokbo.append(",");
					jokbo.append(GameDataManager::getSingletonPtr()->GetCardNumStr(m_LowJokboRepCardList[i]->m_Number));
				}
			}
		}
		jokbo.append(GameDataManager::getSingletonPtr()->GetBadugiJokboStr(m_LowJokboKind));
	}
	return jokbo;
}
