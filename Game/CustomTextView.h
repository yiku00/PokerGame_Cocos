/********************************************************************
	file name:	CustomTextView.h
	
	purpose:	텍스트 스크롤 뷰

	edit :		라벨 추가 및 색상 컨트롤
*********************************************************************/
#pragma once

#include "NxPrerequisites.h"
#include "NxLabel.h"

#define NAME_WIDTH 100.f


class CustomTextCell : public CCTableViewCell
{
public:
	CustomTextCell() : mLabel(NULL), mNameLabel(NULL) {};
	virtual ~CustomTextCell() {};

	static CustomTextCell* create();

	void setText(const string& _name, const string& text, const CCSize& size, float fontSize, ccColor4B color);
	const CCSize& getTextSize();

	void setNameColor(double _r, double _g, double _b) { mNameLabel->setColor(ccc3(_r, _g, _b)); }
	void setTextColor(double _r, double _g, double _b) { mLabel->setColor(ccc3(_r, _g, _b)); }

private:
	Nx::Label* mNameLabel;
	Nx::Label* mLabel;
};

class CustomTextView : public CCNode, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	CustomTextView();
	virtual ~CustomTextView();

	//static CustomTextView* create(const string& _name, const string& text, const CCSize& size, float fontSize, ccColor4B color = ccc4(ccWHITE.r, ccWHITE.g, ccWHITE.b, 0xFF));
	static CustomTextView* create(const CCSize& size, float fontSize);

	bool init(const CCSize& size, float fontSize);
	void addText(const string& _name, const string& text, ccColor4B _fontcolor);
	void SetColorAtIndex(int _index, ccColor4B color);
	void clearTexts();
	void reload();
	void goToEnd();

	//////////////////////////////////////////////////////////////////////////
public: // CCTableViewDataSource
	virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);
	virtual CCSize cellSizeForTable(CCTableView *table) { return CCSizeZero; }
	virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(CCTableView *table);

	//////////////////////////////////////////////////////////////////////////
public: // CCTableViewDelegate
	virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell) {};
	virtual void tableCellHighlight(CCTableView* table, CCTableViewCell* cell){};
	virtual void tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell){};
	virtual void tableCellWillRecycle(CCTableView* table, CCTableViewCell* cell){};

public:
	virtual void scrollViewDidScroll(CCScrollView* view) {};
	virtual void scrollViewDidZoom(CCScrollView* view) {};

private:
	CCSize mSize;
	//ccColor4B mColor;
	float mFontSize;
	CCTableView* mTableView;
	vector<string> mTextLines;
	vector<CCSize> mTextSizes;

	vector<string> mNameLines;
	vector<ccColor4B> mLineColors;
};
