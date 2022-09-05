#pragma once
#include "NxFramework.h"
#include "GameDataManager.h"
//enum MODEL_TYPE {
//	MODEL_SHOP,
//	MODEL_SHOP_SUB,
//	MODEL_INVEN,
//	MODEL_INVEN_SUB,
//};
typedef std::vector<vector<int>> MODELID_Container;

class ModelListPartPanel : public Panel, public Button::Listener, public Nx::Layer::Listener,
	public CCTableViewDelegate, public CCTableViewDataSource
{	
public:
	//typedef vector<int> MODELID_Container;


	ModelListPartPanel(MODEL_TYPE type);
	~ModelListPartPanel();

public:
	virtual void onClicked(const string& buttonName);
	virtual void onLayerMessage(const string& msg);
	virtual void update(float delta);
	virtual void onEnter() override;

    void setActivate(bool activate);
    void UpdateCell();

    virtual CCSize cellSizeForTable(CCTableView* table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView* table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(CCTableView* table);
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    virtual void scrollViewDidScroll(CCScrollView* view) {};
    virtual void scrollViewDidZoom(CCScrollView* view) {}

private:
	TAB_TYPE mTabType;

	Button* mTabMaximBtn;
	Nx::Label* mTabMaximBtnLabel;
	Nx::Label* mTabMaximBtnUnderLabel;

	Button* mTabRacingBtn;
	Nx::Label* mTabRacingBtnLabel;
	Nx::Label* mTabRacingBtnUnderLabel;

	void refresh();
	void refreshTabBtn();

    void initPanel();
	vector<int> getIndices(int idx);

	CCSize mCellSize;
	CCSize mContentsSize;
	Nx::TableView* mTableView;
	MODEL_TYPE mListType;
	Panel* mMainPanel;
	MODELID_Container m_vModelIdx;
	uint maxCount;
};
