#include "pch.h"
#include "ViewerPanel.h"
#include "HeroUtil.h"
#include "RefApp.h"
#include "BattleMap.h"

#define PART_GROUP_COUNT 9
#define PART_INITIAL_INDEX 1

#define SCROLL_PER_SEC 320.f
#define SCALE_PER_SEC 0.2f

#define SKEL_EVENT_MAX_INT 100

ViewerPanel::ViewerPanel()
{
	mObject = nullptr;
	mSkelObject = nullptr;
	mPanel = nullptr;
	mMap = nullptr;
	//mCurrentPartButtonIdx = 0;

	// UI 구성
	construct(getMxmlPath() + "view_chr.mxml");
	//makeColored(ccc4(0x00,0x00,0x00,0xff));
	// 버튼 리스너 설정
	getButton("btn_loop_chk")->setListener(this);
	getButton("btn_rewind")->setListener(this);
	getButton("btn_previous")->setListener(this);
	getButton("btn_play")->setListener(this);
	getButton("btn_next")->setListener(this);

	// 사용하지 않는 요소 안보이게
	getLabel("txt_skill")->setVisible(false);
	getLabel("txt_skill2")->setVisible(false);

	// 버튼 기본 설정
	getButton("btn_loop_chk")->setChecked();

	// 정보 라벨
	mInfoLabel = getLabel("txt_infobody");

	CCRect animViewRect = getDummyUI("dmy_list_mask");
	mAnimationListView = Nx::TableView::create(this, animViewRect.size);
	mAnimationListView->setDirection(ScrollView::Direction::VERTICAL);
	mAnimationListView->setVerticalFillOrder(Nx::TableView::VerticalFillOrder::TOP_DOWN);
	mAnimationListView->setPosition(animViewRect.origin);
	mAnimationListView->setDelegate(this);
	addChild(mAnimationListView);

	//for (int i = 0; i < PART_GROUP_COUNT; ++i)
	//{
	//	mPartButtons.push_back(getButton("btn_boxBg"+StringConverter::toString(i+1)));
	//	mPartButtons.back()->setListener(this);
	//}

	
}

ViewerPanel::~ViewerPanel()
{
	//destruct();
}

void ViewerPanel::onClicked(const string& buttonName)
{
	//if (buttonName.find("btn_boxBg") != string::npos) {
	//	mCurrentPartButtonIdx = StringConverter::parseInt(string(&buttonName.back()))-1;
	//	for_each(mPartButtons.begin(), mPartButtons.end(), [](Button* btn) {
	//		btn->setBlink(false);
	//	});
	//	mPartButtons[mCurrentPartButtonIdx]->setBlink(true, 0.1f, 10.f);
	//}

	//if (mCurrentPartButtonIdx < mPartInfos.size()) {
	//	if (buttonName == "btn_previous") {
	//		if (mPartInfos[mCurrentPartButtonIdx].curr != PART_INITIAL_INDEX) {
	//			mPartInfos[mCurrentPartButtonIdx].curr = PART_INITIAL_INDEX;
	//			_updateSamParts();
	//		}
	//	}
	//	else if (buttonName == "btn_rewind") {
	//		if (mPartInfos[mCurrentPartButtonIdx].curr != PART_INITIAL_INDEX) {
	//			--mPartInfos[mCurrentPartButtonIdx].curr;
	//			_updateSamParts();
	//		}
	//	}
	//	else if (buttonName == "btn_play") {
	//		if (mPartInfos[mCurrentPartButtonIdx].curr != mPartInfos[mCurrentPartButtonIdx].max) {
	//			++mPartInfos[mCurrentPartButtonIdx].curr;
	//			_updateSamParts();
	//		}
	//	}
	//	else if (buttonName == "btn_next") {
	//		if (mPartInfos[mCurrentPartButtonIdx].curr != mPartInfos[mCurrentPartButtonIdx].max) {
	//			mPartInfos[mCurrentPartButtonIdx].curr = mPartInfos[mCurrentPartButtonIdx].max;
	//			_updateSamParts();
	//		}
	//	}
	//}
}

void ViewerPanel::onChecked(const string& buttonName)
{
}

void ViewerPanel::onUnchecked(const string& buttonName)
{
}

void ViewerPanel::setSuperObject(const string& filename)
{
	resetSuperObject();
	resetSkelObject();

	mObject = new SuperObject();

	const CCRect& chr = getDummy("dmy_chr");
	mObject->setPosition(UI_CCP(chr.getMidX(), chr.getMidY()));
	mObject->setSuperAnim(filename);
	//if (mObject->hasAnimation("idle")) {
	//	mObject->playAnimation("idle", true);
	//}
	addChild(mObject);
	mObject->release();

	string::size_type start = filename.rfind('/')+1;
	string::size_type length = filename.rfind('.')-start;
	mObjectName = filename.substr(start, length);

	//// 파츠 뷰 갱신
	//mCurrentPartButtonIdx = 0;

	//mParts.clear();
	//if (PartsDataDepot::getSingleton().hasPartGroup(mObjectName)) {
	//	mParts = PartsDataDepot::getSingleton().getParts(mObjectName);
	//}
	//else {
	//	HeroApp::getSingleton().showMessagePanel(mObjectName + "'s parts data is N/A!", "WARNING");
	//}

	//mPartInfos.clear();
	//mPartInfos.resize(mPartButtons.size());
	//for_each(mParts.begin(), mParts.end(), [this](const PartsDataDepot::PartsGroups::value_type& val){
	//	int idx = static_cast<int>(val.first)-1;
	//	if (!val.second.empty()) {
	//		mPartInfos[idx].avail = true;
	//		mPartInfos[idx].curr = 1;
	//		mPartInfos[idx].max = mObject->getMaxPart(val.second.front());
	//	}
	//});

	//_updateSamParts();
	//

	// 애니메이션 리스트 뷰 갱신
	mAnimationLabels.clear();
	const SuperAnimLabelArray& anims = mObject->getLabels();
	for_each(anims.begin(), anims.end(), [this](const SuperAnimLabel& label) {
		mAnimationLabels.push_back(label.mLabelName);
	});
	mAnimationListView->reloadData();
}

void ViewerPanel::setSkelObject(const string& filename)
{
	resetSuperObject();
	resetSkelObject();

	mSkelObject = new SkelObject();

	const CCRect& chr = getDummy("dmy_chr");
	mSkelObject->setPosition(UI_CCP(chr.getMidX(), chr.getMidY()));
	mSkelObject->setSkelAnim(filename);
	mSkelObject->setScale(0.5f);
	//if (mObject->hasAnimation("idle")) {
	//	mObject->playAnimation("idle", true);
	//}
	addChild(mSkelObject);
	mSkelObject->release();
	mSkelObject->addEventListener(this);
	string::size_type start = filename.rfind('/') + 1;
	string::size_type length = filename.rfind('.') - start;
	mObjectName = filename.substr(start, length);

	//// 파츠 뷰 갱신
	//mCurrentPartButtonIdx = 0;

	//mParts.clear();
	//if (PartsDataDepot::getSingleton().hasPartGroup(mObjectName)) {
	//	mParts = PartsDataDepot::getSingleton().getParts(mObjectName);
	//}
	//else {
	//	HeroApp::getSingleton().showMessagePanel(mObjectName + "'s parts data is N/A!", "WARNING");
	//}

	//mPartInfos.clear();
	//mPartInfos.resize(mPartButtons.size());
	//for_each(mParts.begin(), mParts.end(), [this](const PartsDataDepot::PartsGroups::value_type& val){
	//	int idx = static_cast<int>(val.first) - 1;
	//	if (!val.second.empty()) {
	//		mPartInfos[idx].avail = true;
	//		mPartInfos[idx].curr = 1;
	//		mPartInfos[idx].max = mObject->getMaxPart(val.second.front());
	//	}
	//});

	////_updateSamParts();
	//

	// 애니메이션 리스트 뷰 갱신
	mAnimationLabels.clear();
	const AnimLabelContainer& anims = mSkelObject->getLabels();
	for (const auto& label : anims)
	{
		mAnimationLabels.push_back(label);
	}
	
	mAnimationListView->reloadData();
}

void ViewerPanel::resetSuperObject()
{
	if (mObject) {
		const auto& model = mObject->getModelName();
		if (SamCache::getSingleton().hasSamFile(model)) {
			SamCache::getSingleton().removeSam(model);
		}

		removeChild(mObject, true);
		mObject = nullptr;
	}
}

void ViewerPanel::resetSkelObject()
{
	if (mSkelObject) {
		const auto& model = mSkelObject->getModelName();
		if (SkelCache::getSingleton().hasSkelFile(model)) {
			SkelCache::getSingleton().removeSkel(model);
		}

		removeChild(mSkelObject, true);
		mSkelObject = nullptr;
	}
}

void ViewerPanel::setPanel(const string& filename)
{
	resetPanel();

	mPanel = new Panel();
	addMouseBlockPanel(mPanel, false);
	mPanel->construct(filename);
	addChild(mPanel);
	mPanel->release();
}

void ViewerPanel::resetPanel()
{
	if (mPanel) {
		removeChild(mPanel, true);
		mPanel = nullptr;
	}

	PanelLayoutCache::getSingleton().clear();
}

void ViewerPanel::setMap(const string& filename)
{
	resetMap();

	mMap = new BattleMap(filename);
	mMap->setBattleBG();
	addChild(mMap);
	mMap->release();
}

void ViewerPanel::resetMap()
{
	if (mMap) {
		removeChild(mMap, true);
		mMap = nullptr;
	}
}

void ViewerPanel::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
	Nx::Label* label =  dynamic_cast<Nx::Label*>(cell->getChildByTag(1));
	if (label) {
		CCActionInterval* zi = CCScaleTo::create(0.1f, 0.9f, 0.9f);
		CCActionInterval* zo = CCScaleTo::create(0.1f, 1.0f , 1.0f);

		CCFiniteTimeAction* action = CCSequence::create(CCEaseSineIn::create(zi), CCEaseSineIn::create(zo), nullptr);
		label->runAction(action);

		string info;
		if (mObject) {
			mObject->playAnimation(label->getString(), getButton("btn_loop_chk")->isChecked());
			info = StringConverter::toString(mObject->getDuration());
		}
		else if (mSkelObject) {
			mSkelObject->playAnimation(label->getString(), getButton("btn_loop_chk")->isChecked());
			info = StringConverter::toString(mSkelObject->getDuration());
		}

		mInfoLabel->setString(info.c_str());
	}
}

CCTableViewCell* ViewerPanel::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	CCTableViewCell *cell = table->dequeueCell();

	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();

		Nx::Label* label = new Nx::Label();
		label->initWithString(mAnimationLabels[idx].c_str(), 20);
		label->setAnchorPoint(ccp(0.f, 0.f));
		label->setTag(1);
		cell->addChild(label);
		label->release();
	}
	else {
		Nx::Label* label =  dynamic_cast<Nx::Label*>(cell->getChildByTag(1));
		label->setString(mAnimationLabels[idx].c_str());
	}

	return cell;
}

ssize_t ViewerPanel::numberOfCellsInTableView(CCTableView *table)
{
	return mAnimationLabels.size();
}

cocos2d::CCSize ViewerPanel::cellSizeForTable(CCTableView *table)
{
	return CCSizeMake(getDummyUI("dmy_list_mask").size.width, 20.f);
}

void ViewerPanel::_updateSamParts()
{
	return;

	//SuperAnimMainDef *aMainDef = SuperAnimDefMgr::GetInstance()->Load_GetSuperAnimMainDef(mObject->getModelName());
	//for_each(aMainDef->mImageVector.begin(), aMainDef->mImageVector.end(), [&](SuperAnimImage& image) {
	//	if (image.mImageName.find("1+") != string::npos) {
	//		string part = image.mImageName.substr(image.mImageName.find('_')+1, image.mImageName.rfind('.')-image.mImageName.find('_')-1);
	//		PartGroupId partGroupId = PartsDataDepot::getSingleton().getPartGroupId(mObjectName, part);
	//		int partGrade = 1;
	//		if (partGroupId != Common) {
	//			partGrade = mPartInfos[partGroupId-1].curr;
	//		}
	//		string grade = StringConverter::toString(partGrade);
	//		string partName = image.mImageName.substr(0, image.mImageName.find('.'));
	//		mObject->changePart(partName, nxReplace(partName, "1+", grade+"+"));
	//	}
	//});

	//for (int i = 0; i < PART_GROUP_COUNT; ++i)
	//{
	//	const PartInfo& info = mPartInfos[i];
	//	mPartButtons[i]->setEnable(info.avail);

	//	string titleId = "txt_subtitle" + StringConverter::toString(i+1);
	//	string labelId = "txt_count" + StringConverter::toString(i+1);
	//	string label = StringConverter::toString(info.curr)+"/"+StringConverter::toString(info.max);
	//	getLabel(titleId)->setString(info.groupName.c_str());
	//	getLabel(labelId)->setString(label.c_str());
	//}
}

void ViewerPanel::update(float dt)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	static bool sShift = false;
	if (!sShift && mSkelObject && GetAsyncKeyState(VK_RSHIFT)) {
		mSkelObject->setFlipX(!mSkelObject->isFlipX());
		sShift = true;
	}
	else if (sShift && !GetAsyncKeyState(VK_RSHIFT)) {
		sShift = false;
	}

	if (GetAsyncKeyState(VK_LEFT)) {
		_moveTarget(ccp(-SCROLL_PER_SEC*dt, 0));
	}
	else if (GetAsyncKeyState(VK_RIGHT)) {
		_moveTarget(ccp(SCROLL_PER_SEC*dt, 0));
	}
	else if (GetAsyncKeyState(VK_UP)) {
		_moveTarget(ccp(0, SCROLL_PER_SEC*dt));
	}
	else if (GetAsyncKeyState(VK_DOWN)) {
		_moveTarget(ccp(0, -SCROLL_PER_SEC*dt));
	}

	if (GetAsyncKeyState(VK_PRIOR)) {
		_scaleTarget(-SCALE_PER_SEC*dt);
	}
	else if (GetAsyncKeyState(VK_NEXT)) {
		_scaleTarget(SCALE_PER_SEC*dt);
	}

	if (GetAsyncKeyState(VK_HOME)) {
		_resetTarget();
	}
#endif
}

void ViewerPanel::_moveTarget(const CCPoint& dist)
{
	CCNode* target = nullptr;
	if (mSkelObject) {
		target = mSkelObject;
	}
	else if (mObject) {
		target = mObject;
	}
	else if (mPanel) {
		target = mPanel;
	}
	else if (mMap) {
		target = mMap;
	}

	if (target) {
		const auto& pos = target->getPosition();
		target->setPosition(ccpAdd(pos, dist));
	}
}

void ViewerPanel::_scaleTarget(float scale)
{
	CCNode* target = nullptr;
	if (mSkelObject) {
		target = mSkelObject;
	}
	else if (mObject) {
		target = mObject;
	}
	else if (mPanel) {
		target = mPanel;
	}
	else if (mMap) {
		target = mMap;
	}

	if (target) {
		const auto& cur = target->getScale();
		if (cur + scale > 0)
		target->setScale(cur + scale);
	}
}

void ViewerPanel::_resetTarget()
{
	CCNode* target = nullptr;
	if (mSkelObject) {
		target = mSkelObject;
	}
	else if (mObject) {
		target = mObject;
	}
	else if (mPanel) {
		target = mPanel;
	}
	else if (mMap) {
		target = mMap;
	}

	if (target) {
		const CCRect& chr = getDummy("dmy_chr");
		target->setPosition(UI_CCP(chr.getMidX(), chr.getMidY()));
		target->setScale(1.f);
	}
}

void ViewerPanel::onEvent(int trackIdx, spEvent* event)
{
	string eventName(event->data->name);
	CCLOG(" onEvent NAME = %s", eventName.c_str());
	if (event->floatValue > 0.f)
		CCLOG(" onEvent FLOAT = %f", event->floatValue);
	if (event->intValue > 0 && event->intValue < SKEL_EVENT_MAX_INT)
		CCLOG(" onEvent INTEGER = %d", event->intValue);

	if (eventName == "snd_voice_start") {
		if (event->stringValue != nullptr) {
			string strVal(event->stringValue);
			CCLOG("snd_voice_start str = %s", strVal.c_str());
		}
	}
	else if (eventName == "snd_start") {
		string strVal(event->stringValue);
		CCLOG("snd_start str = %s", strVal.c_str());
	}
}

void ViewerPanel::onEnter()
{
	Panel::onEnter();

	scheduleUpdate();
}