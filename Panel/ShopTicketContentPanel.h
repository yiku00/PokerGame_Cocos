/********************************************************************
file name:	ShopTicketContentPanel.h

purpose:	멤버쉽 , 상점에서 스티커로 표시하는 부분 처리
*********************************************************************/
#pragma once
#include "NxFramework.h"

class ShopTicketContentPanel : public Panel
{	
public:	
	ShopTicketContentPanel();
	virtual ~ShopTicketContentPanel();

private:
	void initPanel();			
	
public:
	void setMemberRamain(int day);	//몇일 남았는지 표시
	void setRubyPlusRemain(int day);	//루비 플러스샵 몇일 남았는지 표시
	void setMemberStop(int day);	//대기중 몇일 남음

private:	
	Panel* mMainPanel;
	CCSize mContentSize;
	SkelObject* mStickerIcon;
	Nx::Label* mTitieLabel;
	Nx::Label* mTitleUnderLabel;
	Nx::Label* mRemainLabel;
	Nx::Label* mRemainUnderLabel;
};
