#include "pch.h"
#include "ItemPartListPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GoodsPanel.h"
#include "GameStringDepot.h"
#include "TicketContentPanel.h"
#include "LobbyTournamentMain.h"
#include "LobbyTourSelectPanel.h"
#include "LobbyScene.h"

ItemPartListPanel::ItemPartListPanel()
{
	makeTickerId();
	initPanel();	
	makeTickerId();
	initContentPanel();
}

ItemPartListPanel::~ItemPartListPanel()
{

}

void ItemPartListPanel::initPanel()
{
	mMainPanel = new Panel();
	addChild(mMainPanel);
	mMainPanel->release();
	mMainPanel->construct(getMxmlPath() + "dmy_inventory3.mxml");
	mContentsSize = mMainPanel->getContentSize();
	mMainPanel->setPositionY(mContentsSize.height - DESIGN_HEIGHT - mContentsSize.height / 2.f);
	mMainPanel->setPositionX(-mContentsSize.width / 2.f);
	mMainPanel->setContentSize(mContentsSize);
	this->setContentSize(mContentsSize);	
	mMainPanel->getLabel("txt_characterinfo")->setString(GameStringDepot::getSingleton().getString("TICKET_TAB_TITLE").c_str());	
}

void ItemPartListPanel::onLayerMessage(const string& msg)
{
	if (msg.find("SELECT_TICKET") != string::npos){
		int ticketIndex = nxExtractInt(msg, "SELECT_TICKET");		
		int moveType = (int)(GameDataManager::getSingleton().GetGameDataPtr()->ticketdata(ticketIndex).movetype());
		LayerManager::getSingleton().popLayer();	//창 내린다.

		Layer* curLayer = LayerManager::getSingleton().getCurrentLayer();
		//select Panel 인데 stage 가 같으면 냅두고
		LobbyTourSelectPanel* pSelectPanel = dynamic_cast<LobbyTourSelectPanel*>(curLayer);
		if (pSelectPanel) {
			LayerManager::getSingleton().popLayer(pSelectPanel);
		}

		LobbyTournamentMain* pPanel = dynamic_cast<LobbyTournamentMain*>(curLayer);
		if (pPanel) {
			LayerManager::getSingleton().popLayer(pPanel);
			return;
		}		

		int secondStep = -1;
		if (moveType == 1) {			
			secondStep = -1;
		}
		else if (moveType < 4) {			
			secondStep = moveType - 2;
		}
		else if (moveType < 6) {			
			secondStep = moveType - 4;
		}


		GameDataManager::getSingleton().setTicketStackIndex(moveType);
		GameDataManager::getSingleton().setTicketStepIndex(secondStep);
		WebService::getSingletonPtr()->TournamentInfoReq();
	}
	else if (msg.find("SUM_TICKET") != string::npos)
	{
		
		int ticketIndex = nxExtractInt(msg, "SUM_TICKET");
		W_TicketData TicketData = GameDataManager::getSingleton().GetGameDataPtr()->ticketdata(ticketIndex);
		int targetIndex = getSumTargetIdx(ticketIndex);
		string exchangefee = getExchangefee(ticketIndex);
		string fromname = TicketData.name() + StringConverter::toString(TicketData.step()) + "R";
		string targetname = GameDataManager::getSingleton().GetGameDataPtr()->ticketdata(targetIndex).name() + StringConverter::toString(TicketData.step()) + "R";

		int moveType = (int)(GameDataManager::getSingleton().GetGameDataPtr()->ticketdata(ticketIndex).movetype());
		string _title = GameStringDepot::getSingleton().getString("TXT_INFORMATION"); //팝업 이미지의 제목
		string _content = NxGetFormatString(GameStringDepot::getSingleton().getString("TXT_TICKET_SUM_CONTENT"), fromname, targetname, exchangefee);
		SimplePopupPanel* _popupPanel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::ShopYESNONotice, _content, _title);
		//SimplePopupPanel* _popupPanel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::LOG_OUT, "TXT_TEST_CONTENT", "TXT_TEST_TITLE");
		if (_popupPanel)
		{
			string tmp = "ReqExchange" + StringConverter::toString(ticketIndex);
			_popupPanel->SetOkEventMsg(tmp);
			_popupPanel->setListener(this);
			LayerManager::getSingleton().pushDynamicLayer(_popupPanel, DYNAMIC_PUSH_LAYER);
		}
	}
	else if (msg.find("ReqExchange") != string::npos)
	{
		int ticketIndex = nxExtractInt(msg, "ReqExchange");
		
		//WebService::sendTicketSummaryReq(ticketIndex);

		//void WebService::sendTicketSummary(int ticketidx)
		//{
		//	W_TicketSummaryReq req;
		//	req.set_ticketid = ticketIndex;
		////	HttpMessage msg(req, HttpResponseHandler(WebService::recvTicketSummary), this);
		//	HttpManager::getSingleton().send(msg);
		//}

		//void WebService::recvTicketSummary(HttpMessage * msg)
		//{
		//	if (msg->hasCode()) {
		//		return;
		//	}
		//	W_TicketSummaryRes res;
		//	res.ParseFromArray(msg->getData(), msg->getSize());
		//	NXASSERT(res.IsInitialized());

		//	if (res.success() == false)
		//	{
		//		if (res.has_errorcode()) {
		//			//ParsingErrorCode(res.errorcode());
		//		}
		//		if (res.has_errorstring())
		//		{
		//			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		//		}

		//		return;
		//	}
		// 
		// GameDataManager::getSingletonPtr()->m_TourOfInfo = new W_TourOfInfo(res.tourofinfo());
		//}
	}
}

void ItemPartListPanel::setActivate(bool activate)
{
	if (activate) {
		setVisible(true);
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

void ItemPartListPanel::makeTickerId()
{
	//티켓 관련 item 만든다.
	mIds.clear();		//우선 하드 코딩이다.
	mIds.push_back(101);
	mIds.push_back(102);
	mIds.push_back(103);
	mIds.push_back(104);
	mIds.push_back(105);
}

void ItemPartListPanel::moveTourment()
{

}

int ItemPartListPanel::getSumTargetIdx(int FromIdx)
{
	int result = -1;
	switch (FromIdx)
	{
	case 0: //프로페셔널 1R 티켓
		result = 1;
		break;
	case 1://마스터즈 1R 티켓
		result = 3;
		break;
	case 2://마스터즈 2R 티켓
		result = 4;
		break;
	default:
		result = -1;
		break;
	}
	return result;
}

string ItemPartListPanel::getExchangefee(int FromIdx)
{
	int64 result = 0;
	switch (FromIdx)
	{
	case 0: //프로페셔널 1R 티켓
		result = 10000000000;
		break;
	case 1://마스터즈 1R 티켓
		result = 100000000000;
		break;
	case 2://마스터즈 2R 티켓
		result = 500000000000;
		break;
	default:
		result = -1;
		break;
	}
	string tmp = StringConverter::toString(result);
	return GameDataManager::getSingletonPtr()->GetKoreanLiteral(tmp,1);
}

void ItemPartListPanel::initContentPanel()
{
	int ticketSize = GameDataManager::getSingleton().GetGameDataPtr()->ticketdata_size();
	for (int i = 0; i < ticketSize; i++)
	{
		string dmyStr = "dmy_pannel_ticket" + StringConverter::toString(i + 1);
		TicketContentPanel* pPanel = new TicketContentPanel(i);
		mMainPanel->addChild(pPanel);
		pPanel->release();
		pPanel->setPosition(mMainPanel->getImage(dmyStr)->getPosition());
		pPanel->setListener(this);
		mContents.push_back(pPanel);
	}
}

void ItemPartListPanel::refreshData()
{
	for (int i = 0; i < mContents.size(); i++)
	{
		mContents[i]->refreshData();
	}
}
