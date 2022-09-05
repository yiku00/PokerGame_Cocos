/********************************************************************
	file name:	LoadingPanel.h
	
	purpose:	로딩창에서의 게이지 와 텍스트
*********************************************************************/
#pragma once
#include "NxFramework.h"

class LoadingPanel : public Panel 
{
public:
	LoadingPanel();
	virtual ~LoadingPanel();

public:
	void setTextStr(const string& loadingText);
	const string& getTextStr();	
	void setDelayClose(float dt);
private:
	void closePanel();

private:
	Nx::Label* mLoadingDesc;	
	Nx::Label* m_company_name_label;
	string mTextStr;
};
