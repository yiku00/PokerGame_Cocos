/********************************************************************
	file name:	ViewerPanel.h
	
	purpose:	캐릭터 뷰어 패널
*********************************************************************/
#pragma once

class ViewerPanel : public Panel, public Button::Listener, public CCTableViewDataSource, public CCTableViewDelegate, public SkelObject::EventListener
{
public:
	ViewerPanel();
	virtual ~ViewerPanel();

public: // Button::Listener
	virtual void onClicked(const string& buttonName);
	virtual void onChecked(const string& buttonName);
	virtual void onUnchecked(const string& buttonName);

public:
	void onEvent(int trackIdx, spEvent* event) override;

public: // CCTableViewDataSource
	virtual CCSize cellSizeForTable(CCTableView *table);
	virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
	virtual ssize_t numberOfCellsInTableView(CCTableView *table);

public: // CCScrollViewDelegate
	virtual void scrollViewDidScroll(CCScrollView* view) {};
	virtual void scrollViewDidZoom(CCScrollView* view) {};

public: // CCTableViewDelegate
	virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);

public:
	virtual void update(float dt) override;
	virtual void onEnter() override;
public:
	void setSuperObject(const string& filename);
	void setSkelObject(const string& filename);
	void setPanel(const string& filename);
	void setMap(const string& filename);

	void resetSuperObject();
	void resetSkelObject();
	void resetPanel();
	void resetMap();

private:
	void _updateSamParts();

	void _moveTarget(const CCPoint& dist);
	void _scaleTarget(float scale);
	void _resetTarget();
	
private:
	SuperObject* mObject;
	SkelObject* mSkelObject;
	Panel* mPanel;
	class BattleMap* mMap;
	string mObjectName;
	Nx::Label* mInfoLabel;

	vector<string> mAnimationLabels;
	CCTableView* mAnimationListView;

	//PartsDataDepot::PartsGroups mParts;
	//vector<Button*> mPartButtons;
	//vector<PartInfo> mPartInfos;
	//uint mCurrentPartButtonIdx;
};