#include "pch.h"
#include "SelectCharacterPanel.h"

#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"
#include "LobbyUIPanel.h"
#include "PokerResourceHelper.h"

SelectCharacterPanel::SelectCharacterPanel() : Panel("SelectCharacterPanel")
{
	mLoginProcess = false;

	m_pReplayListView = nullptr;
	m_pReplayListContainer = nullptr;

	m_pSelectListView = nullptr;
	m_pSelectListContainer = nullptr;

	InitPanel();
	InitImage();
	initButton();

	setButtonListener(this);
	
	SetSelectList();

	ShowPanel(true);

	LayerManager::getSingleton().pushDynamicLayer(this, DYNAMIC_PUSH_LAYER);
	GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_SELECT_CHARACTER_POPUP);
}

SelectCharacterPanel::~SelectCharacterPanel()
{
	mMainPanel->destruct();
}

Panel * SelectCharacterPanel::GetMainPanel()
{
	return mMainPanel;
}

void SelectCharacterPanel::InitPanel()
{
	addMouseBlockPanel(this);

	mMainPanel = new Panel();
	mMainPanel->construct(getMxmlPath() + "dmy_possession_character.mxml");

	mSelectIdx = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_CharacterIdx;
}

void SelectCharacterPanel::InitImage()
{
	mMainPanel->getLabel("txt_tab1_empty")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
}

void SelectCharacterPanel::initButton()
{
	mMainPanel->getButton("sbtn_title_cancel_stay")->setType(Button::NoPressImg);
	mMainPanel->getButton("sbtn_title_cancel_stay")->getButtonSkelObject()->setSkin("mark_cancel");
	mMainPanel->getButton("sbtn_title_cancel_stay")->setListener(this);
	mMainPanel->getButton("sbtn_title_cancel_stay")->setTouchable(true, 0, false);

	CCSize _contentSize = mMainPanel->getDummy("dmy_possession_character").size;
	CCPoint _pos = mMainPanel->getDummy("dmy_possession_character").origin;

	//mMainPanel->setPosition(ccp(_pos.x, _contentSize.height + _pos.y - DESIGN_HEIGHT));// _contentSize.width / -2.f, _contentSize.height / -2.f));

	mMainPanel->setPositionY(_contentSize.height - DESIGN_HEIGHT - _contentSize.height / 2.f);
	mMainPanel->setPositionX(-_contentSize.width / 2.f);
	mMainPanel->setContentSize(_contentSize);
	this->setContentSize(_contentSize);
	this->setPositionX(DESIGN_WIDTH / 2);
	this->setPositionY(DESIGN_HEIGHT / 2);

	addChild(mMainPanel, 15);
	mMainPanel->release();
	mMainPanel->setVisible(true);

	mMainPanel->getSkel("skel_small_title")->setSkin("title_characterinfo");

}


bool SelectCharacterPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	
	return false;
}


void SelectCharacterPanel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	
}


void SelectCharacterPanel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	
}

void SelectCharacterPanel::resume()
{
}

void SelectCharacterPanel::onClicked(const string& name)
{
	if (mLoginProcess)
		return;

	if (name == "sbtn_title_cancel_stay")
	{
		ShowPanel(false);
	}
	else if (name.find("sbtn_exclamation_mark_stay") != string::npos)
	{
		string nameset1 = nxReplace(name, "sbtn_exclamation_mark_stay", "");
		W_CharacterInfo * info = GameDataManager::getSingletonPtr()->m_pCharacterInfoList[StringConverter::parseInt(nameset1)];
		int _id = info->id();
		LayerManager::getSingleton().pushDynamicLayer(new CustomPopupPanel(CustomPopupPanel::CustomPopupType::CHAR_INFO_TYPE, _id), DYNAMIC_PUSH_LAYER);
	}
	else if (name.find("sbtn_small_button_") != string::npos)
	{
		string nameset1 = nxReplace(name, "sbtn_small_button_", "");
		W_CharacterInfo * info = GameDataManager::getSingletonPtr()->m_pCharacterInfoList[StringConverter::parseInt(nameset1)];

		WebService::getSingletonPtr()->_sendCharacterSelectReq(info->id());
	}
}

void SelectCharacterPanel::update(float dt)
{
	ScrollViewOffsetProcess();
}

bool SelectCharacterPanel::handling(STCMD &stCmd)
{
	return false;
}

void SelectCharacterPanel::SetSelectList()
{
	int _size = GameDataManager::getSingletonPtr()->m_pCharacterInfoList.size();
	CreateCharacterCell(_size);
	for (int _i = 0; _i < _size; _i++)
	{
		int _dataIndex = _i;
		UpdateCharacterCell(_i, _dataIndex);
	}
}

void SelectCharacterPanel::ClearSelectList()
{
	if (m_pSelectListContainer)
	{
		m_pSelectListContainer->cleanup();
		m_pSelectListContainer->removeFromParent();
	}
	m_pSelectListContainer = nullptr;

	if (m_pSelectListView)
	{
		m_pSelectListView->cleanup();
		m_pSelectListView->removeFromParent();
	}
	m_pSelectListView = nullptr;
}

void SelectCharacterPanel::CreateCharacterCell(int _count)
{
	int _MakeCellCount = _count;
	if (CHARACTER_CELL_MAX < _MakeCellCount)
		_MakeCellCount = CHARACTER_CELL_MAX;

	ClearSelectList();
	m_pSelectListContainer = CCLayer::create();
	CCSize _contentSize = mMainPanel->getDummy("dmy_tab1_scrollsize_1").size;

	for (int _i = 0; _i < _MakeCellCount; _i++)
	{
		m_pListCell[_i] = new Panel();
		m_pListCell[_i]->setTag(-1);
		//m_pListCell[_i]->construct(getMxmlPath() + "dmy_pocha_panel.mxml");
		CCSize _ButtonPanelSize = m_pListCell[_i]->getDummy("dmy_pocha_panel").size;

		m_pListCell[_i]->setPosition(ccp(10.f + (CHARACTER_CELL_SIZE * _i), _ButtonPanelSize.height - DESIGN_HEIGHT));
		m_pSelectListContainer->addChild(m_pListCell[_i]);
		m_pListCell[_i]->release();

		m_pListCell[_i]->getButton("sbtn_small_button_2")->getButtonSkelObject()->setSkin("txt_use");
		m_pListCell[_i]->getButton("sbtn_small_button_2")->setListener(this);
		m_pListCell[_i]->getButton("sbtn_small_button_2")->setTouchable(true, 0, false);
		m_pListCell[_i]->getButton("sbtn_small_button_2")->setType(Button::NoPressImg);
		// 이름 다시 설정
		m_pListCell[_i]->getButton("sbtn_small_button_2")->setName("sbtn_small_button_" + StringConverter::toString(_i));

		m_pListCell[_i]->getButton("sbtn_exclamation_mark_stay")->setListener(this);
		m_pListCell[_i]->getButton("sbtn_exclamation_mark_stay")->setTouchable(true, 0, false);
		m_pListCell[_i]->getButton("sbtn_exclamation_mark_stay")->setName("sbtn_exclamation_mark_stay" + StringConverter::toString(_i));
		
		m_pListCell[_i]->getLabel("txt_character_name")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_pListCell[_i]->getLabel("txt_character_name_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_pListCell[_i]->getLabel("txt_limit")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_pListCell[_i]->getLabel("txt_spec")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

		DrawCharacterCell(m_pListCell[_i], _i, true);
	}

	if (CHARACTER_CELL_SIZE*_count > _contentSize.width)
	{
		m_pSelectListContainer->setContentSize(CCSizeMake(CHARACTER_CELL_SIZE*_count, _contentSize.height));
	}
	else
	{
		m_pSelectListContainer->setContentSize(_contentSize);
	}

	mMainPanel->getLabel("txt_tab1_empty")->setVisible(_count == 0);

	m_pSelectListView = CCScrollView::create(_contentSize, m_pSelectListContainer);
	m_pSelectListView->setDirection(extension::ScrollView::Direction::HORIZONTAL);
	m_pSelectListView->setBounceable(false);
	//가장 상단으로 올리기.
	//m_pFrinedListView->setContentOffset(ccp(-CHARACTER_CELL_SIZE * (_size-1) , 0), false);
	m_pSelectListView->setContentOffset(ccp(0, 0), false);

	CCPoint _ListPos = (_contentSize / -2.f);
	m_pSelectListView->setPosition(_ListPos);
	mMainPanel->getSkel("skel_tab1_panel_f1_2_center")->addChild(m_pSelectListView, 10);
}

void SelectCharacterPanel::UpdateCharacterCell(int _cellIndex, int _dataIndex)
{
	if (_dataIndex >= GameDataManager::getSingletonPtr()->GetGameDataPtr()->charactershopdata_size())
		return;

	if (m_pListCell[_cellIndex]->getTag() == _dataIndex)
		return;

	m_pListCell[_cellIndex]->setTag(_dataIndex);

	CCSize _ButtonPanelSize = m_pListCell[_cellIndex]->getDummy("dmy_pocha_panel").size;
	m_pListCell[_cellIndex]->setPosition(ccp(10.f + (CHARACTER_CELL_SIZE * _dataIndex), _ButtonPanelSize.height - DESIGN_HEIGHT));
	m_pListCell[_cellIndex]->setTag(_dataIndex);
	DrawCharacterCell(m_pListCell[_cellIndex], _cellIndex, true);
}

void SelectCharacterPanel::DrawCharacterCell(Panel * chpanel, int idx, bool isAllDraw)
{
	W_CharacterInfo * info = GameDataManager::getSingletonPtr()->m_pCharacterInfoList[idx];

	int charIdx = info->id();

	if (isAllDraw)
	{
		string _skinName = PokerResourceHelper::getCharacterImgName(charIdx);
		chpanel->getSkel("skel_goods_penal_1_stay")->playAnimation("goods_penal_1_stay");
		//chpanel->getSkel("skel_goods_penal_1_stay")->setSkin(_skinName);
	}

	string remainTxt = "";
	if (info->isbase())
		remainTxt = GameStringDepot::getSingletonPtr()->getString("TXT_UNLIMIT");
	else
		remainTxt = GameDataManager::getSingletonPtr()->GetRemainTime(info->expirelefttime(), true, false);
	chpanel->getLabel("txt_limit")->setString(remainTxt.c_str());

	W_GameData * gameData = GameDataManager::getSingletonPtr()->GetGameDataPtr();

	W_CharacterData data;
	for (int i = 0, j = gameData->characterdata_size(); i < j; i++)
	{
		data = GameDataManager::getSingletonPtr()->GetGameDataPtr()->characterdata(i);
		if (data.id() == charIdx)
		{
			chpanel->getLabel("txt_character_name")->setString(data.name().c_str());
			chpanel->getLabel("txt_character_name_under")->setString(data.name().c_str());

			string _spec = "";
			int _size = data.effect_size();
			for (int _index = 0; _index < _size; _index++)
			{
				_spec += data.effect(_index).desc();
				if (_index < _size - 1)
				{
					_spec += "\n";
				}
			}
			chpanel->getLabel("txt_spec")->setString(_spec.c_str());
			break;
		}
	}

	SetCharacterCellUse(chpanel, charIdx);
}

void SelectCharacterPanel::SetCharacterCellUse(Panel * chpanel, int charIdx)
{
	string _btnName = "sbtn_small_button_2";
	if (charIdx == mSelectIdx)
	{
		chpanel->getButton(_btnName)->setEnable(false);
		chpanel->getButton(_btnName)->getButtonSkelObject()->setSkin("txt_useing");
		chpanel->getButton(_btnName)->setSkelAnimation("small_button_2_change ");
		chpanel->getButton(_btnName)->setSkelAppendAnimation("small_button_2_off");
	}
	else
	{
		chpanel->getButton(_btnName)->setEnable(true);
		chpanel->getButton(_btnName)->getButtonSkelObject()->setSkin("txt_use");
		chpanel->getButton(_btnName)->setSkelAnimation("small_button_2_off_change");
		chpanel->getButton(_btnName)->setSkelAppendAnimation("small_button_2_stay");

	}
}

void SelectCharacterPanel::ChangeCharacterCellUse()
{
	int yetSeelctIdx = mSelectIdx;
	mSelectIdx = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_CharacterIdx;
	int _count = GameDataManager::getSingletonPtr()->m_pCharacterInfoList.size();

	for (int _i = 0; _i < _count; _i++)
	{
		if (_i < CHARACTER_CELL_MAX)
		{
			W_CharacterInfo * info = GameDataManager::getSingletonPtr()->m_pCharacterInfoList[_i];

			int charIdx = info->id();
			if (charIdx == yetSeelctIdx || charIdx == mSelectIdx)
				DrawCharacterCell(m_pListCell[_i], _i, false);
		}
	}
}

void SelectCharacterPanel::ShowPanel(bool isVisible)
{
	if (!isVisible)
	{
		GameDataManager::getSingletonPtr()->PopUiState();
		clearThisPanel();
	}
		
}

void SelectCharacterPanel::clearThisPanel()
{
	GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
	if (this->isDynamic())
		LayerManager::getSingleton().popLayer(this);
}

void SelectCharacterPanel::ScrollViewOffsetProcess()
{
	if (m_pSelectListView == nullptr)
		return;

	float _offSetPoint = -m_pSelectListView->getContentOffset().x;

		int _size = GameDataManager::getSingletonPtr()->GetGameDataPtr()->charactershopdata_size();

		if (_size <= CHARACTER_CELL_MAX)					//셀 수가 SHOP_CELL_SHOW_MAX보다 많고
			return;

		if (_offSetPoint >= CHARACTER_CELL_SIZE * 2.f)	//두칸 이상 셀이 이동 했을 때
		{
			int _toIdx = (_offSetPoint - (CHARACTER_CELL_SIZE * 2.f)) / CHARACTER_CELL_SIZE;
			int _dstIdx = _toIdx + CHARACTER_CELL_MAX;
			_toIdx = _toIdx % CHARACTER_CELL_MAX;
			UpdateCharacterCell(_toIdx, _dstIdx);

			//지워지는 셀의 위의 셀은 새로 나타난 셀로 판단하고 갱신
			_toIdx = (_toIdx + 1) % CHARACTER_CELL_MAX;
			_dstIdx = _dstIdx - (CHARACTER_CELL_MAX - 1);
			UpdateCharacterCell(_toIdx, _dstIdx);
		}
		else
		{
			UpdateCharacterCell(0, 0);
		}
}

void SelectCharacterPanel::onEnter()
{
	Panel::onEnter();

	setTouchable(true);
	scheduleUpdate();
}