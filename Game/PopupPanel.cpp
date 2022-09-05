#include "pch.h"
#include "PopupPanel.h"
#include "HeroUtil.h"
#include "GameStringDepot.h"
#include "GameDataManager.h"

PopupPanel::PopupPanel( PopupBtnType type , const string&text ):Panel("PopupPanel")
{
	mType = WholeNotice;
	mTarget = NULL;
	mGeneralListener = NULL;

	mBtnType = type;	
	initPanel();	
	initDesc(text);
	setTextType();
	setBtnType();
}

PopupPanel::~PopupPanel()
{
}

void PopupPanel::onClicked(const string& name)
{
	if (GameDataManager::getSingletonPtr()->m_pOptionValue->m_voice == true)
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
	//	SoundManager::getSingleton().playEffect(BTN_CLICK);

	if(name == mMiddleOkBtn->getName()){
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		clearThisPanel();
		if (mGeneralListener) 
			(mTarget->*mGeneralListener)(PopupOk);			
		else
			fireMessage(PopupOk);
	}
	else if(name == mOkBtn->getName()){
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		clearThisPanel();
		if (mGeneralListener) 
			(mTarget->*mGeneralListener)(PopupOk);			
		else
			fireMessage(PopupOk);		
	}
	else if(name == mCancelBtn->getName()){
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		clearThisPanel();
		if (mGeneralListener) 
			(mTarget->*mGeneralListener)(PopupCancel);			
		else
			fireMessage(PopupCancel);		
	}
}

void PopupPanel::setBtnType()
{
	if(mBtnType == Confirm){		
		setVislbleButton(mOkBtn,false);
		setVislbleButton(mCancelBtn,false);
		mOkBtnText->setVisible(false);
		mCancelBtnText->setVisible(false);
	}else if(mBtnType == CancelOk){
		setVislbleButton(mMiddleOkBtn,false);
		mMiddleOkBtnText->setVisible(false);
	}	
}

void PopupPanel::initPanel()
{
	addMouseBlockPanel(this);

	construct( getMxmlPath() + "pop_warning_notice.mxml");

	mMiddleOkBtn = getButton("btn_actionSmallBlue2");	
	mCancelBtn = getButton("btn_actionSmallRed");	
	mOkBtn = getButton("btn_actionSmallBlue");

	mWholeDesc = getLabel("txt_body4");
	mDesc = getLabel("txt_body1");	
	mItemName = getLabel("txt_itemtitle");

	mTitle = getLabel("txt_toptitle");
	mMiddleOkBtnText = getLabel("txt_btntitle2");
	mOkBtnText = getLabel("txt_btntitle3");
	mCancelBtnText = getLabel("txt_btntitle1");
	mResourceTitle = getLabel("txt_subtitle");
	mNoticeText = getLabel("txt_friendsinfo");

	addTitle(GameStringDepot::getSingleton().getString("PopupTitle"));	
	GameStringDepot::getSingleton().setLabel(mMiddleOkBtnText , "ConfirmBtnStr");
	GameStringDepot::getSingleton().setLabel(mOkBtnText , "ConfirmBtnStr");
	GameStringDepot::getSingleton().setLabel(mCancelBtnText , "CancelBtnStr");

	CCRect position = getDummy("dmy_coinbg");
	mRewardPosition = UI_CCP(position.getMidX() , position.getMidY());

	setButtonListener(this);	
	setUseNotice(false);
}

void PopupPanel::setTextType()
{
	//종류에 따라 사이즈가 다르다. 우선 다 text 를 뿌리고 상황에 따라 visible 로 관리한다.	
	mWholeDesc->setVisible(false);
	mItemName->setVisible(false);
	mResourceTitle->setVisible(false);

	switch (mType)
	{
	case PopupPanel::WholeNotice:
		mWholeDesc->setVisible(true);
		break;
	case PopupPanel::NormalNotice:	
		break;
	case PopupPanel::PriceNotice:	
		mResourceTitle->setVisible(true);
		break;
	case PopupPanel::ItemNotice:
	
		mResourceTitle->setVisible(true);
		break;	
	}
}

void PopupPanel::setResourceTitle( const wstring& gameStringStr )
{
	mResourceTitle->setString(gameStringStr.c_str());
}

void PopupPanel::addTitle( const string& title )
{
	if(!title.empty()){
		mType = NormalNotice;
		mTitle->setString(title.c_str());	
		setTextType();
	}
}

void PopupPanel::initDesc(const string& text)
{
	mWholeDesc->setString( nxReplaceNewl(text).c_str());	
	mDesc->setString(nxReplaceNewl(text).c_str());		
}

void PopupPanel::addNotice( const string& notice )
{
	setUseNotice(true);
	mNoticeText->setString(notice.c_str());		
}

void PopupPanel::setUseNotice( bool flag )
{
	mNoticeText->setVisible(flag);
}

void PopupPanel::clearThisPanel()
{
	if(this->isDynamic())
		LayerManager::getSingleton().popLayer(this);
}

void PopupPanel::onRefresh()
{
	setVisible( true );

}
