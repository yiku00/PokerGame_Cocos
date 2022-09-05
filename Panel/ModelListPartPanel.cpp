#include "pch.h"
#include "ModelListPartPanel.h"
#include "GameDataManager.h"
#include "ModellsBackPanel.h"
#include "GameStringDepot.h"
#include "ModelTempTabel.h"

ModelListPartPanel::ModelListPartPanel(MODEL_TYPE type)
{
	mListType = type;
	mTabType = MAXIM_TAB;

	initPanel();

}

ModelListPartPanel::~ModelListPartPanel()
{

}

void ModelListPartPanel::initPanel()
{
	

	mMainPanel = new Panel();
	addChild(mMainPanel);
	mMainPanel->release();

	// �г� ����
	if (mListType == MODEL_INVEN) {

        m_vModelIdx.clear();
		for (int x = 0; x < GameDataManager::getSingletonPtr()->getModelList(mTabType).size(); x++)
		{
			m_vModelIdx.push_back(GameDataManager::getSingletonPtr()->getModelList(mTabType)[x]);
		}
	}

	mMainPanel->construct(getMxmlPath() + "dmy_shopin4.mxml");

	// �г� �⺻ ����
	mContentsSize = mMainPanel->getContentSize();
	mMainPanel->setPositionY(mContentsSize.height - DESIGN_HEIGHT - mContentsSize.height / 2.f);
	mMainPanel->setPositionX(-mContentsSize.width / 2.f);
	mMainPanel->setContentSize(mContentsSize);
	this->setContentSize(mContentsSize);
	mMainPanel->setButtonListener(this);
	
	// ���̺�� ����
	mCellSize = mMainPanel->getDummy("dmy_model_panel").size;
    CCRect tableViewRect = mMainPanel->getDummyUI("dmy_scrollsize");
    mTableView = Nx::TableView::create(this, tableViewRect.size);
    mMainPanel->addChild(mTableView);
	// �𵨸���Ʈ â������ ���ν�ũ���̰� �������� ���� ��ũ���̴�.
	if (mListType == MODEL_SHOP || mListType == MODEL_INVEN)
	{
		mTableView->setDirection(ScrollView::Direction::HORIZONTAL);
	}
	else {
		mTableView->setDirection(ScrollView::Direction::VERTICAL);
	}
	
    mTableView->setPosition(tableViewRect.origin);
    mTableView->setDelegate(this);
	mTableView->setBounceable(true);
    mTableView->reloadData();	

	// �� ��ư ����
	CCPoint pos = mMainPanel->getDummy("dmy_rank_tabl").origin;
	pos.y = -pos.y;
	Panel* maximTabPanel = new Panel();
	mMainPanel->addChild(maximTabPanel);
	maximTabPanel->release();
	maximTabPanel->construct(getMxmlPath() + "dmy_rank_tabl.mxml");
	maximTabPanel->setPosition(pos);

	mTabMaximBtnLabel = maximTabPanel->getLabel("txt_title");
	mTabMaximBtnUnderLabel = maximTabPanel->getLabel("txt_title_under");
	mTabMaximBtnLabel->setString(GameStringDepot::getSingletonPtr()->getString("MAXIM_TAB_NAME").c_str());
	mTabMaximBtnUnderLabel->setString(GameStringDepot::getSingletonPtr()->getString("MAXIM_TAB_NAME").c_str());

	mTabMaximBtn = maximTabPanel->getButton("sbtn_tab");
	mTabMaximBtn->setName("maximTab");
	mTabMaximBtn->setListener(this);

	pos = mMainPanel->getDummy("dmy_rank_tabr").origin;
	pos.y = -pos.y;
	Panel* racingTabPanel = new Panel();
	mMainPanel->addChild(racingTabPanel);
	racingTabPanel->release();
	racingTabPanel->construct(getMxmlPath() + "dmy_rank_tabl.mxml");
	racingTabPanel->setPosition(pos);

	mTabRacingBtnLabel = racingTabPanel->getLabel("txt_title");
	mTabRacingBtnUnderLabel = racingTabPanel->getLabel("txt_title_under");
	mTabRacingBtnLabel->setString(GameStringDepot::getSingletonPtr()->getString("RACING_TAB_NAME").c_str());
	mTabRacingBtnUnderLabel->setString(GameStringDepot::getSingletonPtr()->getString("RACING_TAB_NAME").c_str());

	mTabRacingBtn = racingTabPanel->getButton("sbtn_tab");
	mTabRacingBtn->setName("racingTab");
	mTabRacingBtn->setListener(this);

	refresh();
}

void ModelListPartPanel::refresh()
{
	refreshTabBtn();

}

void ModelListPartPanel::refreshTabBtn()
{
	ccColor3B _onColor = ccc3(240, 216, 165);
	ccColor3B _offColor = ccc3(144, 130, 99);
	if (mTabType == MAXIM_TAB) {
		mTabMaximBtn->getButtonSkelObject()->playAnimation("tab_rankl_on");
		mTabRacingBtn->getButtonSkelObject()->playAnimation("tab_rankl_off");
		mTabMaximBtnLabel->setColor(_onColor);
		mTabRacingBtnLabel->setColor(_offColor);
	}
	else if (mTabType == RACING_TAB) {
		mTabMaximBtn->getButtonSkelObject()->playAnimation("tab_rankl_off");
		mTabRacingBtn->getButtonSkelObject()->playAnimation("tab_rankl_on");
		mTabMaximBtnLabel->setColor(_offColor);
		mTabRacingBtnLabel->setColor(_onColor);
	}
}


void ModelListPartPanel::onClicked(const string& buttonName)
{
	if (buttonName == "maximTab") {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		if (mTabType != MAXIM_TAB) {
			mTabType = MAXIM_TAB;

			refresh();
		}
	}
	/* ���� ���ҽ��� ���� �ӽ� �ּ�
	else if (buttonName == "racingTab") {
		//GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		//if (mTabType != RACING_TAB) {
		//	mTabType = RACING_TAB;
		//	refresh();
		//}
	}
	/* ���� ���ҽ��� ���� �ӽ� �ּ�
	* ���߿� ���̽� ���� ����� ���� �ش� �� ó���� ����� �Ѵ�.
	}*/
}

void ModelListPartPanel::onLayerMessage(const string& msg)
{
	if (msg == "BUY_BTN")
	{
		CCPoint cur = mTableView->getContentOffset();
		UpdateCell();
		mTableView->setContentOffset(cur);
	}
}

void ModelListPartPanel::update(float delta)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
    static bool triggerred = false;
    if (!triggerred && GetAsyncKeyState(VK_F2)) {
        triggerred = true;
    }

    if (triggerred && !GetAsyncKeyState(VK_F2)) {
        triggerred = false;
		UpdateCell();
    }
#endif
}

cocos2d::CCSize ModelListPartPanel::cellSizeForTable(CCTableView *table)
{
	return mCellSize;
}

CCTableViewCell* ModelListPartPanel::tableCellAtIndex(CCTableView *table, ssize_t idx)
{
	idx = (maxCount - 1) - idx;
	CCTableViewCell* cell = table->dequeueCell();
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
		ModellsBackPanel* pPanel = new ModellsBackPanel();
		cell->addChild(pPanel);
		pPanel->release();
		pPanel->setTag(1);
		if (mListType == MODEL_SHOP) {
			pPanel->SetModelType(MODEL_TYPE::MODEL_SHOP);
		}
		else {
			pPanel->SetModelType(MODEL_TYPE::MODEL_INVEN);
		}
		pPanel->setIndex(idx, getIndices(idx),-1,mTabType);	// ���⼭ ����� getIndices(idx)�� ���� ���� 0���ϸ� �󽽷��� ������ �ȴ�.
		pPanel->setPosition(ccp(0, -pPanel->getContentSize().height / 2.f + 16.f));
		pPanel->setListener(this);
	}
	else {
		ModellsBackPanel* pPanel = dynamic_cast<ModellsBackPanel*>(cell->getChildByTag(1));
		if (pPanel) {
			pPanel->setIndex(idx, getIndices(idx),-1,mTabType);
		}
	}
	return cell;
}


vector<int> ModelListPartPanel::getIndices(int idx)
{
	// ���� ���� ��� -1�� ����� ���� ǥ�� ��ü�� ���ϰ�
	// -100�� ��� �� ������ ǥ���Կ� ����
	vector<int> outData;
    if (mListType == MODEL_SHOP) {
        for (int i = idx * 3; i < (idx * 3 + 3); ++i)
        {
			// ���߿� mTabType == RACING_TAB �� ����� g_MaximModelListTable ������ ��� �Ѵ�.
			int _size = mTabType == MAXIM_TAB ? GameDataManager::getSingletonPtr()->TitleModel_MAXIM.size() : 
				GameDataManager::getSingletonPtr()->TitleModel_RACING.size();

			if (i < _size) {
				if (mTabType == MAXIM_TAB) {
					int result_index = GameDataManager::getSingletonPtr()->getModelInfo(GameDataManager::getSingletonPtr()->TitleModel_MAXIM[i].id(), MODEL_INDEX);
				}
				else {
					int result_index = GameDataManager::getSingletonPtr()->getModelInfo(GameDataManager::getSingletonPtr()->TitleModel_RACING[i].id(), MODEL_INDEX);
				}
				outData.push_back(i);
			}
			else
				outData.push_back(-1);	// ���� ������ �������� �������� ǥ�� ���� ����
        }
	} else if (mListType == MODEL_INVEN) {
		for (int i = idx * 3; i < (idx * 3 + 3); ++i)
		{
			// �κ��� �𵨸���Ʈ�� ���δ�.
			int _size = mTabType == MAXIM_TAB ? GameDataManager::getSingletonPtr()->TitleModel_MAXIM.size() :
				GameDataManager::getSingletonPtr()->TitleModel_RACING.size();

			if (i < _size) {
				if (mTabType == MAXIM_TAB) {
					int result_index = GameDataManager::getSingletonPtr()->getModelInfo(GameDataManager::getSingletonPtr()->TitleModel_MAXIM[i].id(), MODEL_INDEX);
				}
				else {
					int result_index = GameDataManager::getSingletonPtr()->getModelInfo(GameDataManager::getSingletonPtr()->TitleModel_RACING[i].id(), MODEL_INDEX);
				}
				outData.push_back(i);
			}
			else
				outData.push_back(-100);
			//if (i < m_vModelIdx.size())
			//	outData.push_back(m_vModelIdx[i]);
			//else
			//{
			//	// ���� ������ ��� -100�� ���� �󽽷��� ǥ�� �ϵ��� �Ѵ�.
			//	if (GameDataManager::getSingleton().hasSlot(idx))
			//		outData.push_back(-100);
			//}
		}
    }
	return outData;
}

ssize_t ModelListPartPanel::numberOfCellsInTableView(CCTableView *table)
{
	uint count = 0;
	// ���⼱ ������ �𵨸���Ʈ�� ���� �ش�
	count = GameDataManager::getSingletonPtr()->TitleModel_MAXIM.size();
	maxCount = count % 3 > 0 ? (count / 3) + 1 : (count / 3);
	return maxCount;
}

void ModelListPartPanel::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
	ModellsBackPanel* pPanel = dynamic_cast<ModellsBackPanel*>(cell->getChildByTag(1));
	if (pPanel){
		pPanel->cellTouch(table->getTouchPoint());
	}
}

void ModelListPartPanel::setActivate(bool activate)
{
	if (activate) {
		setVisible(true);
		mTableView->reloadData();
		if (getPositionX() < 0) {
			setPositionX(getPositionX() + DESIGN_WIDTH);
		}		
	}
	else {
		setVisible(false);
		if (getPositionX() > 0) {
			setPositionX(getPositionX() - DESIGN_WIDTH);
		}
	}
}

void ModelListPartPanel::UpdateCell()
{
	if (mTableView)
		mTableView->reloadData();
}
void ModelListPartPanel::onEnter()
{
	Panel::onEnter();

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	scheduleUpdate();
#endif
}