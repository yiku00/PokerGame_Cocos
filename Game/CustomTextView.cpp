#include "pch.h"
#include "CustomTextView.h"
#include "NxUtil.h"
#include "NxLabel.h"
#include "ReplayGameManager.h"


//////////////////////////////////////////////////////////////////////////
CustomTextCell* CustomTextCell::create()
{
	CustomTextCell* cell = new CustomTextCell();
	return cell;
}

void CustomTextCell::setText(const string& _name, const string& text, const CCSize& size, float fontSize, ccColor4B color)
{
	if (mLabel) {
		mLabel->setString(text.c_str());
	}
	else {
		mLabel = new Nx::Label();
		mLabel->initWithString(text.c_str(), CCSizeMake(size.width - NAME_WIDTH - 10, size.height), kCCTextAlignmentLeft, fontSize, kCCVerticalTextAlignmentCenter);
		mLabel->setColor(ccc3(color.r, color.g, color.b));
		mLabel->setOpacity(color.a);
		mLabel->setAnchorPoint(ccp(0, 0));
		mLabel->setPositionX(NAME_WIDTH + 5);
		addChild(mLabel);
		mLabel->release();

	}

	if (mNameLabel) {
		mNameLabel->setString(_name.c_str());
	}
	else {
		mNameLabel = new Nx::Label();
		mNameLabel->initWithString(_name.c_str(), CCSizeMake(NAME_WIDTH, size.height), kCCTextAlignmentLeft, fontSize, kCCVerticalTextAlignmentCenter);
		mNameLabel->setColor(ccc3(color.r, color.g, color.b));
		mNameLabel->setOpacity(color.a);
		mNameLabel->setAnchorPoint(ccp(0, 1));
		mNameLabel->setPosition(ccp(0.f, mLabel->getContentSize().height));
		addChild(mNameLabel);
		mNameLabel->release();

	}
}

const CCSize& CustomTextCell::getTextSize()
{
	if (mLabel) {
		return mLabel->getContentSize();
	}

	return CCSizeZero;
}

//////////////////////////////////////////////////////////////////////////
CustomTextView::CustomTextView()
{

}

CustomTextView::~CustomTextView()
{
	removeAllChildren();
}

CustomTextView* CustomTextView::create(const CCSize& size, float fontSize)
{
	CustomTextView* view = new CustomTextView();
	view->init(size, fontSize);
	return view;
}

bool CustomTextView::init(const CCSize& size, float fontSize)
{
	mSize = size;
	//mColor = ccc4(ccWHITE.r, ccWHITE.g, ccWHITE.b, 0xFF);
	mFontSize = fontSize;

	int _size = ReplayGameManager::getSingletonPtr()->GetCommentDataSize();
	for (int _i = 0; _i < _size; _i++)
	{
		string _sName = ReplayGameManager::getSingletonPtr()->GetCommentData(_i, COMMENT_NAME);
		string _text = ReplayGameManager::getSingletonPtr()->GetCommentData(_i, COMMENT_TEXT);
		ccColor4B _color = ReplayGameManager::getSingletonPtr()->GetCommentColor(_i);

		mNameLines.push_back(_sName);
		mTextLines.push_back(_text);
		mLineColors.push_back(_color);
	}
		
	//nxTokenize(text, "[nl]", back_inserter(mTextLines));
	//nxTokenize(_name, "[nl]", back_inserter(mNameLines));

	for (uint i = 0; i < mTextLines.size(); ++i)
	{
		CustomTextCell* cell = new CustomTextCell();
		cell->setText(mNameLines[i], mTextLines[i], CCSizeMake(mSize.width, 0), mFontSize, mLineColors[i]);
		mTextSizes.push_back(cell->getTextSize());
		delete cell;
	}

	mTableView = CCTableView::create(this, mSize);
	mTableView->setVerticalFillOrder(Nx::TableView::VerticalFillOrder::TOP_DOWN);
	mTableView->setDelegate(this);
	addChild(mTableView);

	return true;
}

void CustomTextView::addText(const string& _name, const string& text, ccColor4B _fontcolor)
{
	mTextLines.push_back(text);

	CustomTextCell* cell = new CustomTextCell();
	cell->setText(_name, text, CCSizeMake(mSize.width, 0), mFontSize, _fontcolor);
	mTextSizes.push_back(cell->getTextSize());
	delete cell;
}

void CustomTextView::reload()
{
	mTableView->reloadData();
}

void CustomTextView::goToEnd()
{
	mTableView->setContentOffset(mTableView->maxContainerOffset());
}

CCTableViewCell* CustomTextView::tableCellAtIndex(CCTableView *table, ssize_t idx)
{
	CustomTextCell* cell = dynamic_cast<CustomTextCell*>(table->dequeueCell());
	if (!cell) {
		cell = new CustomTextCell();
		cell->autorelease();
	}

	cell->setText(mNameLines[idx], mTextLines[idx], CCSizeMake(mSize.width, 0), mFontSize, mLineColors[idx]);

	return cell;
}

ssize_t CustomTextView::numberOfCellsInTableView(CCTableView *table)
{
	return mTextLines.size();
}

CCSize CustomTextView::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
	return mTextSizes[idx];
}

void CustomTextView::clearTexts()
{
	mTextLines.clear();
	mTextSizes.clear();
	reload();
}

void CustomTextView::SetColorAtIndex(int _index, ccColor4B color)
{
	CustomTextCell* _cell = dynamic_cast<CustomTextCell*>(tableCellAtIndex(mTableView, _index));
	if (_cell)
	{
		mLineColors[_index] = color;
		_cell->setNameColor(color.r, color.g, color.b);
		_cell->setTextColor(color.r, color.g, color.b);

		mTableView->updateCellAtIndex(_index);
	}

}
