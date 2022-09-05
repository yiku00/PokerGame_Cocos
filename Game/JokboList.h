/********************************************************************
filename: 	JokboList.h

purpose:	���� ����â ������ �ϴܿ� ������ ������� ����Ʈ�� �����ִ� â
*********************************************************************/
#pragma once
#include "NxFramework.h"

#define HIGH_JOKBO_SIZE 12
#define LOW_JOKBO_SIZE 14
#define BADUKI_JOKBO_SIZE 15
#define JOKBO_FONT_HIGHT 25.f

class JokboList : public Nx::Layer
{
public:
	JokboList();
	virtual ~JokboList();

	void Init();
	
	void ShowHighLabel(int _index);
	void ShowLowLabel(int _index);
	void ShowBadugiLabel(int _index);
private:
	void InitHighJokbo();
	void InitLowJokbo();
	void InitBabukiJokbo();
	
private:
	void refreshPokerHandsTitle();	//���̷ο� �϶��� �������� , �ο� ������ ���̰� �ƴҶ��� ������ ���δ�.
public:
	CCRect m_JokboBoardRect;
	SkelObject* m_pJokboBox;

	CCScrollView* m_pHighJokboView;
	CCScrollView* m_pLowJokboView;

	CCLayer* m_HighJokboLabelContainer;
	CCLayer* m_LowJokboLabelContainer;

	SkelObject* m_pHighJokboLabel[HIGH_JOKBO_SIZE];
	SkelObject* m_pLowJokboLabel[LOW_JOKBO_SIZE];
	SkelObject* m_pBadugiJokboLabel[BADUKI_JOKBO_SIZE];

	Panel* mParentPanel;
	Panel* mMainPanel;

	Nx::Label* mPokerHandLabel;
	Nx::Label* mPokerHand_under_Label;
	Nx::Label* mHighPokerHandLabel;
	Nx::Label* mHighPokerHand_under_Label;
	Nx::Label* mLowPokerHandLabel;
	Nx::Label* mLowPokerHand_under_Label;

};