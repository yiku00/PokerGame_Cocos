/********************************************************************
	file name:	ModellsBackPopupPanel.h
	
	purpose:	모델별 리스트를 보여주는 판넬
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "SmallButtonPanel.h"
#include "ModelListPartPanel.h"

class ModellsBackPopupPanel : public Panel, public Button::Listener, public Nx::Layer::Listener,
	public CCTableViewDelegate, public CCTableViewDataSource
{	
public:
	ModellsBackPopupPanel(int mIdx,MODEL_TYPE modelType, TAB_TYPE tabType);
	~ModellsBackPopupPanel();

public: // Button::Listener
	virtual void onClicked(const string& name);	
	virtual void onLayerMessage(const string& msg);

	virtual CCSize cellSizeForTable(CCTableView* table);
	virtual CCTableViewCell* tableCellAtIndex(CCTableView* table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(CCTableView* table);
	virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
	virtual void scrollViewDidScroll(CCScrollView* view) {};
	virtual void scrollViewDidZoom(CCScrollView* view) {}
	virtual void onEnter() override;
public:
	void setIndex(int idx, TAB_TYPE tapType = MAXIM_TAB);

	typedef  std::vector<std::vector<int>> MODELID_Container;

private:
	void initPanel();
	
private:		
	Panel* mMainPanel;
	int mModelListIDX;

	CCSize mCellSize;
	CCSize mContentsSize;
	TAB_TYPE mtapType;
	Nx::TableView* mTableView;
	MODELID_Container m_vModelIdx;
	uint maxCount;

	std::vector<int> getIndices(int idx, TAB_TYPE taptype = TAB_TYPE::MAXIM_TAB);

	MODEL_TYPE mListType;
};
