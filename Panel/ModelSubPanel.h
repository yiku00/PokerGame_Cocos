#pragma once

#include "NxFramework.h"

enum ModelSubPanelType
{
	TYPE_MODEL_SUB_SHOP,
	TYPE_MODEL_SUB_INVEN
};

//static const string BUY_BTN_SEND_MSG = "BUY_BTN";
//static const string INFO_BTN_SEND_MSG = "INFO_BTN";

class ModelSubPanel : public Panel, public Panel::Listener
{
public:
	ModelSubPanel();
    virtual ~ModelSubPanel();

	void InitPanel();
	void InitImage();
	void initButton();	

	void SetSubModelType(ModelSubPanelType _type);
	void SetBtnText(const wstring& _text);
	void setIndex(int idx);
	bool isValidIndex() { return mIdx >= 0; }

	void ModelShot();
	void BuyModel();
	void UnlockModel();

	virtual void onLayerMessage(const string& msg);

    Label* m_Name1;
	Label* m_Name2;
    Panel* m_ButtonPanel;
    Button* m_OkBtn;
	bool test;

    SkelObject* m_ModelSubPanel;
    SkelObject* m_Cover;
    Widget* mCharacter;

private:
	ModelSubPanelType m_panelType;
	int mIdx;
	Widget* mCoverImg;
};
