#include "pch.h"
#include "LobbyCharacterShopPanel.h"
#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "SimplePopupPanel.h"
#include "GameStringDepot.h"
#include "LobbyScene.h"
#include "LobbyUIPanel.h"

LobbyCharacterShopPanel::LobbyCharacterShopPanel()
{
	mLoginProcess = false;
	m_tapIndex = 0;

	for (int _i = 0; _i < LOBBY_CHARACTER_CELL_MAX; _i++)
	{
		m_ListCell[_i] = nullptr;
	}
	m_pListContainer = nullptr;
	m_pListView = nullptr;

	InitPanel();
	InitImage();
	initButton();

	InitCharacterList();

	setButtonListener(this);
}

LobbyCharacterShopPanel::~LobbyCharacterShopPanel()
{
	//destruct();
}

void LobbyCharacterShopPanel::InitPanel()
{
	construct(getMxmlPath() + "dmy_charactershop.mxml");


}

void LobbyCharacterShopPanel::InitImage()
{
	getLabel("txt_tab1_empty")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_tab1_empty")->setVisible(false);
	getLabel("str_characterinfo")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_regulation")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_tab_out")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	CCRect _scrollRect = getDummy("dmy_scrollsize");
	CCSize _goodsSize = getDummy("dmy_goods_panel").size;
	getLabel("txt_tab_out")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_SHOP_BUTTON").c_str());
}

void LobbyCharacterShopPanel::initButton()
{
	for (int _i = 0; _i < 2; _i++)
	{
		CCPoint _tapPos = getDummy("dmy_button_tab" + StringConverter::toString(_i+1)).origin;

		m_TapBtnPanel[_i] = new Panel();
		m_TapBtnPanel[_i]->construct(getMxmlPath() + "dmy_button_tab.mxml");
		m_TapBtnPanel[_i]->setPositionX(_tapPos.x);
		m_TapBtnPanel[_i]->setPositionY(-_tapPos.y);
		addChild(m_TapBtnPanel[_i]);
		m_TapBtnPanel[_i]->release();

		m_TapButton[_i] = m_TapBtnPanel[_i]->getButton("sbtn_button");
		m_TapButton[_i]->setListener(this);

		m_TapBtnPanel[_i]->getLabel("txt_off_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_TapBtnPanel[_i]->getLabel("txt_on_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_TapBtnPanel[_i]->getLabel("txt_off_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		
		m_TapBtnPanel[_i]->getLabel("txt_on_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		
		if (_i == 0)
		{
			m_TapButton[_i]->setSkelAnimation("tab_on");
			m_TapBtnPanel[_i]->getLabel("txt_on_tab")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_HOLD_CHARACTERS").c_str());
			m_TapBtnPanel[_i]->getLabel("txt_off_tab")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_HOLD_CHARACTERS").c_str());
			m_TapBtnPanel[_i]->getLabel("txt_off_tab")->setVisible(false);

		}
		else
		{
			m_TapButton[_i]->setSkelAnimation("tab_off");
			m_TapBtnPanel[_i]->getLabel("txt_on_tab")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_MOVE_CHARACTERSHOP_BUTTON").c_str());
			m_TapBtnPanel[_i]->getLabel("txt_off_tab")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_MOVE_CHARACTERSHOP_BUTTON").c_str());
			m_TapBtnPanel[_i]->getLabel("txt_on_tab")->setVisible(false);
		}
	}

	m_TapButton[0]->setName("TAP_HOLD_CHARACTER");
	m_TapButton[1]->setName("TAP_SHOP_CHARACTER");
}


bool LobbyCharacterShopPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	m_bCancelTouch = false;
	m_bTouchEnd = false;
	m_bMoveAccel = false;
	m_moveG = 0.f;
	m_MovePoint = 0.f;

	if (pTouch->getLocation().x < 180.f)
		return false;

	if (pTouch->getLocation().y > DESIGN_HEIGHT - 150.f)
		return false;

	return true;
}

void LobbyCharacterShopPanel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if (m_bTouchEnd == true)
		return;

	if (pTouch->getLocation().x < 180.f)
		return;

	if (pTouch->getLocation().y > DESIGN_HEIGHT - 150.f)
		return;

	m_moveG = pTouch->getPreviousLocation().x - pTouch->getLocation().x;

	if (m_moveG > CHARACTER_CELL_WIDTH)
		m_moveG = CHARACTER_CELL_WIDTH;
	if (m_moveG < -CHARACTER_CELL_WIDTH)
		m_moveG = -CHARACTER_CELL_WIDTH;

	float _moveLen = pTouch->getStartLocation().x - pTouch->getLocation().x;

	int _cellCount = m_totalDataCount;
	if (_cellCount > LOBBY_CHARACTER_CELL_MAX)
		_cellCount = LOBBY_CHARACTER_CELL_MAX;

	if (abs(_moveLen) > 10.f)
	{
		m_bCancelTouch = true;
	}

	UpdateCellMoveBy(m_moveG);
}

void LobbyCharacterShopPanel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (m_bTouchEnd == true)
		return;

	m_bTouchEnd = true;

	float _moveLen = pTouch->getStartLocation().x - pTouch->getLocation().x;
	UpdateCellMoveBy(m_moveG);
	m_bMoveAccel = true;
	m_MovePoint = 0.f;
	m_bTouchEnd = true;

	if (m_bCancelTouch == true)
	{
		return;
	}

	CCPoint tableTouchPoint = pTouch->getLocation();

	//TODO : TOUCH
	auto& panelNodes = m_pListContainer->getChildren();
	for(auto _node : panelNodes)
	{
		GoodsPanel* _panel = dynamic_cast<GoodsPanel*>(_node);
		Button* _OkBtn = _panel->m_OkBtn;
		if (_OkBtn->hasCollided(_OkBtn->convertToNodeSpace(tableTouchPoint))){
			if (_OkBtn->isEnabled()){
				//string _BtnName = "CharacterInfo" + StringConverter::toString(_OkBtn->getTag());
				onClicked(_OkBtn->getName());
			}
		}
	}
}

void LobbyCharacterShopPanel::onClicked(const string& name)
{
	if (name == "TAP_HOLD_CHARACTER")
	{
		setTapOn(0);
		RemoveCharacterCellList();
		InitCharacterList();
	}

	if (name == "TAP_SHOP_CHARACTER")
	{
		setTapOn(1);
		RemoveCharacterCellList();
		InitCharacterList();
	}

	if (strncmp("ShopButton", name.c_str(), 10) == 0)
	{
		int _index = nxExtractInt(name, "ShopButton");
		if (m_tapIndex == 0)
		{
			W_CharacterInfo * info = GameDataManager::getSingletonPtr()->m_pCharacterInfoList[_index];
			if (info->expirelefttime() == 0 && info->isbase() == false)
			{
				int _size = GameDataManager::getSingletonPtr()->GetGameDataPtr()->charactershopdata_size();
				for (int _i = 0; _i < _size; _i++)
				{
					W_CharacterShopData _infoData = GameDataManager::getSingletonPtr()->GetGameDataPtr()->charactershopdata(_i);
					if (_infoData.id() == info->id())
					{
						SetBuyPopup(_i);
						return;
					}
				}
			}
			else
			{
				WebService::getSingletonPtr()->_sendCharacterSelectReq(info->id());
			}
		}
		else if (m_tapIndex == 1)
		{
			SetBuyPopup(_index);
		}
	}

	if (strncmp("CharacterInfo", name.c_str(), 13) == 0)
	{
		int _index = nxExtractInt(name, "CharacterInfo");
		
		if (m_tapIndex == 0)
		{
			W_CharacterInfo* _infoData = GameDataManager::getSingletonPtr()->m_pCharacterInfoList[_index];
			CustomPopupPanel* _popupPanel = new CustomPopupPanel(CustomPopupPanel::CustomPopupType::CHAR_INFO_TYPE, _infoData->id());
			LayerManager::getSingleton().pushDynamicLayer(_popupPanel, DYNAMIC_PUSH_LAYER);
			if (_infoData->isbase() || _infoData->expirelefttime() > 0)
			{
				_popupPanel->SetHoldItem(CustomPopupPanel::TYPE_HOLD_ITEM);
			}
			else if (_infoData->expirelefttime() == 0)
			{
				_popupPanel->SetHoldItem(CustomPopupPanel::TYPE_EXPIRED_ITEM);
			}
			else
			{
				_popupPanel->SetHoldItem(CustomPopupPanel::TYPE_NONE_ITEM);
			}


		}
		else if (m_tapIndex == 1)
		{
			W_CharacterShopData _infoData = GameDataManager::getSingletonPtr()->GetGameDataPtr()->charactershopdata(_index);
			CustomPopupPanel* _popupPanel = new CustomPopupPanel(CustomPopupPanel::CustomPopupType::CHAR_INFO_TYPE, _infoData.characterid());
			LayerManager::getSingleton().pushDynamicLayer(_popupPanel, DYNAMIC_PUSH_LAYER);

			for (int _i = 0; _i < GameDataManager::getSingletonPtr()->m_pCharacterInfoList.size(); _i++)
			{
				W_CharacterInfo* _Charainfo = GameDataManager::getSingletonPtr()->m_pCharacterInfoList[_i];
				if (_Charainfo->id() == _infoData.characterid())
				{
					if (_Charainfo->isbase() || _Charainfo->expirelefttime() > 0)
					{
						_popupPanel->SetHoldItem(CustomPopupPanel::TYPE_HOLD_ITEM);
					}
					else if (_Charainfo->expirelefttime() == 0)
					{
						_popupPanel->SetHoldItem(CustomPopupPanel::TYPE_EXPIRED_ITEM);
					}
					else
					{
						_popupPanel->SetHoldItem(CustomPopupPanel::TYPE_NONE_ITEM);
					}
					return;
				}
			}
			_popupPanel->SetHoldItem(CustomPopupPanel::TYPE_NONE_ITEM);
		}

	}
}

void LobbyCharacterShopPanel::SetBuyPopup(int _index)
{
	//안씀
}

void LobbyCharacterShopPanel::resume()
{

}

bool LobbyCharacterShopPanel::handling(STCMD &stCmd)
{
	return false;
}

void LobbyCharacterShopPanel::update(float dt)
{

}

void LobbyCharacterShopPanel::setTapOn(int _index)
{
	m_tapIndex = _index;
	for (int _i = 0; _i < 2; _i++)
	{
		if (_i == _index)
		{
			m_TapButton[_i]->setSkelAnimation("tab_on");
			m_TapBtnPanel[_i]->getLabel("txt_on_tab")->setVisible(true);
			m_TapBtnPanel[_i]->getLabel("txt_off_tab")->setVisible(false);
		}
		else
		{
			m_TapButton[_i]->setSkelAnimation("tab_off");
			m_TapBtnPanel[_i]->getLabel("txt_on_tab")->setVisible(false);
			m_TapBtnPanel[_i]->getLabel("txt_off_tab")->setVisible(true);
		}
	}
}

void LobbyCharacterShopPanel::InitCharacterList()
{
	m_curChannelIndex = 0;

	m_pListContainer = CCLayer::create();
	CCSize _contentSize = getDummy("dmy_scrollsize").size;
	CCPoint _scrollPos = getDummy("dmy_scrollsize").origin;
	_scrollPos.y = DESIGN_HEIGHT - _scrollPos.y - _contentSize.height;

	if (m_tapIndex == 0)
	{
		m_totalDataCount = GameDataManager::getSingletonPtr()->m_pCharacterInfoList.size();
	}
	else if (m_tapIndex == 1)
	{
		m_totalDataCount = GameDataManager::getSingletonPtr()->GetGameDataPtr()->charactershopdata_size();
	}
	CreateCharacterCell(m_totalDataCount);

	int _totalSize = m_totalDataCount;
	if (_totalSize > LOBBY_CHARACTER_CELL_MAX)
		_totalSize = LOBBY_CHARACTER_CELL_MAX;

	if (CHARACTER_CELL_WIDTH * _totalSize > _contentSize.width)
	{
		m_pListContainer->setContentSize(CCSizeMake(CHARACTER_CELL_WIDTH * _totalSize, _contentSize.height));
	}
	else
	{
		m_pListContainer->setContentSize(_contentSize);
	}

	m_pListView = CCScrollView::create(_contentSize, m_pListContainer);
	m_pListView->setDirection(ScrollView::Direction::HORIZONTAL);
	m_pListView->setBounceable(false);
	m_pListView->setTouchEnabled(false);
	m_pListView->setPosition(_scrollPos);
	addChild(m_pListView);
}

void LobbyCharacterShopPanel::CreateCharacterCell(int _count)
{
	for (int _i = 0; _i < LOBBY_CHARACTER_CELL_MAX; _i++)
	{
		if (_i >= _count)
			continue;

		m_ListCell[_i] = new GoodsPanel();
		m_ListCell[_i]->m_Discount->setVisible(false);
		m_ListCell[_i]->m_DiscountUnder->setVisible(false);
		m_ListCell[_i]->m_HotMark->setVisible(false);

		if (m_tapIndex == 0)
		{
			m_ListCell[_i]->SetGoodsType(TYPE_NO_RUBY_GOODS);
		}
		else if (m_tapIndex == 1)
		{
			m_ListCell[_i]->SetGoodsType(TYPE_RUBY_GOODS);
		}

		m_ListCell[_i]->setPositionX(CHARACTER_CELL_WIDTH * _i);
		m_ListCell[_i]->setPositionY(CHARACTER_CELL_HEIGHT - DESIGN_HEIGHT);
		m_pListContainer->addChild(m_ListCell[_i]);
		m_ListCell[_i]->release();	
		m_ListCell[_i]->m_OkBtn->setPaused(true);

		UpdateCharacterCell(_i, _i);
	}
}

void LobbyCharacterShopPanel::UpdateCharacterCell(int _toIdx, int _dstIdx)
{

	if (_dstIdx >= GameDataManager::getSingletonPtr()->m_pCharacterInfoList.size() && m_tapIndex == 0)
		return;

	if (_dstIdx >= GameDataManager::getSingletonPtr()->GetGameDataPtr()->charactershopdata_size() && m_tapIndex == 1)
		return;
		
	m_ListCell[_toIdx]->setTag(_dstIdx);	
	m_ListCell[_toIdx]->m_OkBtn->setTag(_dstIdx);
	m_ListCell[_toIdx]->m_OkBtn->setName("ShopButton" + StringConverter::toString(_dstIdx));
		
	W_CharacterShopData _ShopInfo;
	int _CharacterId = -1;
	if (m_tapIndex == 0)
	{
		int _size = GameDataManager::getSingletonPtr()->GetGameDataPtr()->charactershopdata_size();
		for (int _i = 0; _i < _size; _i++)
		{
			if (GameDataManager::getSingletonPtr()->m_pCharacterInfoList[_dstIdx]->id() != GameDataManager::getSingletonPtr()->GetGameDataPtr()->charactershopdata(_i).id())
				continue;

			_ShopInfo = GameDataManager::getSingletonPtr()->GetGameDataPtr()->charactershopdata(_i);
			if (_ShopInfo.has_characterid())
				_CharacterId = _ShopInfo.characterid();
		}

	}
	else if (m_tapIndex == 1)
	{
		_ShopInfo = GameDataManager::getSingletonPtr()->GetGameDataPtr()->charactershopdata(_dstIdx);
		if (_ShopInfo.has_characterid())
			_CharacterId = _ShopInfo.characterid();
	}

	SkelObject* _pSkelObj = m_ListCell[_toIdx]->m_GoodsPanel;
	int _size = GameDataManager::getSingletonPtr()->GetGameDataPtr()->characterdata_size();

	for (int _i = 0; _i < _size; _i++)
	{
		W_CharacterData _Data = GameDataManager::getSingletonPtr()->GetGameDataPtr()->characterdata(_i);
		if (_Data.has_id() && _ShopInfo.has_id())
		{
			if (_Data.id() == _ShopInfo.id())
			{
				string _textTop = "";
				if (_Data.has_name())
					_textTop = _Data.name();

				//if (_ShopInfo.has_periodday())
				//	_textTop += "\n" + StringConverter::toString(_ShopInfo.periodday()) + GameStringDepot::getSingleton().getString("TXT_DAY");

				m_ListCell[_toIdx]->m_Name->setString(_textTop.c_str());

				if (m_tapIndex == 0)
				{
					string _btnTxt = "";
					if (GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_CharacterIdx == _ShopInfo.id())
					{
						_btnTxt = GameStringDepot::getSingletonPtr()->getString("TXT_SELECTED_UNIT");
						m_ListCell[_toIdx]->m_OkBtn->setEnable(false);
						m_ListCell[_toIdx]->m_OkBtn->setGrayscale(true);
					}
					else
					{
						W_CharacterInfo* _pInfo = GameDataManager::getSingletonPtr()->m_pCharacterInfoList[_dstIdx];
						if (_pInfo->expirelefttime() == 0 && _pInfo->isbase() == false)
						{
							_btnTxt = GameStringDepot::getSingletonPtr()->getString("TXT_CHARACTER_BUY_UNIT");
						}
						else
						{
							_btnTxt = GameStringDepot::getSingletonPtr()->getString("TXT_CHANGEING_UNIT");
						}
						m_ListCell[_toIdx]->m_OkBtn->setEnable(true);
						m_ListCell[_toIdx]->m_OkBtn->setGrayscale(false);
					}
					 
					m_ListCell[_toIdx]->SetBtnText(_btnTxt.c_str());
				}
				else if (_ShopInfo.has_cash() && m_tapIndex == 1)
					m_ListCell[_toIdx]->SetBtnText(StringConverter::toString(_ShopInfo.cash()).c_str());

				string _rewardText = "";
				if (m_tapIndex == 1)
				{
					if (_ShopInfo.has_rewardinfo())
					{
						int _rewardSize = _ShopInfo.rewardinfo().rewardset_size();

						for (int _j = 0; _j < _rewardSize; _j++)
						{
							W_RewardInfo_RewardSet _set = _ShopInfo.rewardinfo().rewardset(_j);


							//if (_set.has_id());

							if (_set.has_amount())
							{
								_rewardText += GameStringDepot::getSingleton().getString("TXT_IMMEDIATELY");
								_rewardText += " " + GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_set.amount()), 1);
								_rewardText += " " + GameStringDepot::getSingleton().getString("TXT_GET_UNIT");
							}
						}
					}
				}

				m_ListCell[_toIdx]->mCenteTitle->setString((_rewardText).c_str());

				int _size = _Data.effect_size();
				string _sDesc = "";

				bool _hasEffect = true;
				for (int _i = 0; _i < _size; _i++)
				{
					W_CharacterData_CharacterEffect _dataEff = _Data.effect(_i);
					_sDesc += _dataEff.desc();
					if (_i < _size - 1)
					{
						_sDesc += "\n";
					}
				}
				m_ListCell[_toIdx]->m_Spec->setString(_sDesc.c_str());

				int _day = 0;
				string _sLimitDay = "";
				if (m_tapIndex == 0)
				{
					W_CharacterInfo* _pInfo = GameDataManager::getSingletonPtr()->m_pCharacterInfoList[_dstIdx];
					if (_pInfo->isbase())
					{
						_sLimitDay = GameStringDepot::getSingletonPtr()->getString("TXT_UNLIMIT");
					}
					else
					{
						_sLimitDay = GameDataManager::getSingletonPtr()->GetTimeString(_pInfo->expirelefttime()) + GameStringDepot::getSingletonPtr()->getString("TXT_TIMELEFT");
					}
					
				}
				else if (m_tapIndex == 1)
				{
					_day = _ShopInfo.periodday();
					_sLimitDay = GameStringDepot::getSingletonPtr()->getString("TXT_LIMITTIME") + ":" + StringConverter::toString(_day) + GameStringDepot::getSingletonPtr()->getString("TXT_DAY");
				}
				m_ListCell[_toIdx]->m_DayLimit->setString(_sLimitDay.c_str());
			}
		}
	}
}

void LobbyCharacterShopPanel::RemoveCharacterCellList()
{
	if (m_pListContainer)
		m_pListContainer->removeFromParent();
	m_pListContainer = nullptr;
	if (m_pListView)
		m_pListView->removeFromParent();
	m_pListView = nullptr;

	for (int _i = 0; _i < LOBBY_CHARACTER_CELL_MAX; _i++)
	{
		m_ListCell[_i] = nullptr;
	}
}


void LobbyCharacterShopPanel::UpdateCellMoveBy(float _move)
{
	if (m_totalDataCount == 0)
	{
		return;
	}

	m_offset = m_pListView->getContentOffset();

	if (_move < 0 && m_offset.x == 0)
	{
		return;
	}

	float _maxMoveX = (CHARACTER_CELL_WIDTH * m_totalDataCount);

	if (m_offset.x >= _move && _move < 0.f)
	{
		m_offset.x = 0.f;
	}
	else
	{
		m_offset.x -= _move;
	}

	if (m_offset.x < -CHARACTER_CELL_WIDTH * 2.5f && _move > 0 && m_curChannelIndex + LOBBY_CHARACTER_CELL_MAX < m_totalDataCount)
	{
		m_curChannelIndex++;
		m_offset.x += CHARACTER_CELL_WIDTH;
		UpdateCell();
	}

	if (m_offset.x > -CHARACTER_CELL_WIDTH * 1.5 && _move < 0 && m_curChannelIndex >= 1)
	{
		m_curChannelIndex--;
		m_offset.x -= CHARACTER_CELL_WIDTH;
		UpdateCell();
	}

	m_pListView->setContentOffset(m_offset, false);
}

void LobbyCharacterShopPanel::UpdateCell()
{
	if (m_pListView == NULL)
		return;

	for (int _i = 0; _i < LOBBY_CHARACTER_CELL_MAX; _i++)
	{
		if (m_totalDataCount <= _i)
			continue;

		int _index = _i + m_curChannelIndex;
		if (m_totalDataCount <= _index)
		{
			_index = _index % m_totalDataCount;
		}

		if (_index < 0)
		{
			_index = m_totalDataCount + (_index % m_totalDataCount);
			if (_index == m_totalDataCount)
			{
				_index = 0;
			}
		}

		UpdateCharacterCell(_i, _index);
	}
}