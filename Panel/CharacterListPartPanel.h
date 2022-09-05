/********************************************************************
filename: 	CharacterListPartPanel.h 

purpose:	메뉴텝을 골랐을때 캐랙터 리스트창 ( 구매창 +  리스트창(캐릭터 가지고 있는 창)
*********************************************************************/
#pragma once

#include "NxFramework.h"

class CharacterListPartPanel : public Panel, public Button::Listener, public Nx::Layer::Listener,
	public CCTableViewDelegate, public CCTableViewDataSource
{	
public:

	typedef vector<int> CHACTERID_Container;

	enum LIST_TYPE {
		CHARACTER_SHOP,
		CHARACTER_INVEN,
	};

	CharacterListPartPanel(LIST_TYPE type);
	~CharacterListPartPanel();

public:
	virtual void onClicked(const string& buttonName);
public:
	virtual void onLayerMessage(const string& msg);

private:
	void onShopLayerMessage(const string& msg);
	void onInvenLayerMessage(const string& msg);

public:
	void setActivate(bool activate);
	void UpdateCell();
public:
	virtual CCSize cellSizeForTable(CCTableView *table);
	virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(CCTableView *table);
	virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
	virtual void scrollViewDidScroll(CCScrollView* view){};
	virtual void scrollViewDidZoom(CCScrollView* view){}

private:
	void SetBuyPopup(int _index);

private:
	void drawTableView();
	void initPanel();
	int getCellCount();	
private:
	CCSize mCellSize;
	CCSize mContentsSize;
	Nx::TableView* mTableView;
	LIST_TYPE mListType;
	Panel* mMainPanel;
	Button* mInfoBtn;
	CHACTERID_Container mCharacterIdx;
};

