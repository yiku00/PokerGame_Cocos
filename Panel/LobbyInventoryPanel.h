/********************************************************************
file name:	LobbyInventoryPanel.h

purpose:	로비씬에서 상점 버튼 눌렀을때  상점 관련 구조창
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "CharacterListPartPanel.h"
#include "TabButtonPanel.h"
#include "ItemPartListPanel.h"
#include "LobbyLetterBoxPanel.h"
#include "NotiWidget.h"
#include "CardListPartPanel.h"
#include "ModelListPartPanel.h"

class LobbyInventoryPanel : public Panel, public Button::Listener
{
	enum INVEN_STATE{
		INVEN_LETTER,
		INVEN_CHARACTER,
		INVEN_ITEM,
		INVEN_CARD,
		INVEN_MODEL,
	};

	typedef vector<NotiWidget*> NotiWidgetContainer;
	typedef vector<TabButtonPanel*> TabButtonContainer;
public:
	LobbyInventoryPanel();
	virtual ~LobbyInventoryPanel();

public:
	virtual void onClicked(const string& name);
	virtual void onEnter() override;
public:
	virtual bool handling(STCMD &stCmd);
	virtual void update(float delta);

public:
	void HideShopPanel();
	void setCharacterSelect(int characterId);
private:
	void _init();
	void _initTopPanel();	//위에 상단바 설정
	void _initTab();		//왼쪽 메뉴 버튼 셋팅
	void _initPanel();		//해당 패널 add 시킨다.

	void refresh();
	void refreshTabBtn();	//현재 탭 선택 이미지 설정
	void refreshPanel();	//탭 선택했을때 선택창

	void addLetterPanel();
	void addCharacterListPanel();
	void addItemListPanel();
	void addCardListPanel();
	void addModelListPanel();

	void updateNotiWidget();

public:
	void setActivate();	//push 될때 처리
	void UpdateCell();
	
private:
	LobbyLetterBoxPanel* mLetterPanel;
	CharacterListPartPanel* mCharacterListPanel;
	ItemPartListPanel* mItemListPanel;
	CardListPartPanel* mCardListPanel;
	ModelListPartPanel* mModelTabPanel;
	TabButtonContainer mTabButtons;	
	Button* mGoShop;
	INVEN_STATE mInvenState;
	
	NotiWidgetContainer mNotiWidgets;
};