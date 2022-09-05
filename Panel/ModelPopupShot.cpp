#include "pch.h"
#include "ModelPopupShot.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "W_CouponReq.pb.h"
#include "W_CouponRes.pb.h"
#include "PanelHelper.h"
#include "GameStringDepot.h"
#include "ModelTempTabel.h"

ModelPopupShot::ModelPopupShot(int tIdx,int idx) : Panel("ModelPopupShot")
{
	this->mIdx = idx;
	this->tIdx = tIdx;
	initPanel();		
}

ModelPopupShot::~ModelPopupShot()
{
}

void ModelPopupShot::onClicked(const string& name)
{
	GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
	LayerManager::getSingleton().popLayer(this);
}

void ModelPopupShot::initPanel()
{
	addMouseBlockPanel(this, true);
	construct(getMxmlPath() + "dmy_model_shot.mxml");
	setButtonListener(this);
	Widget* img = getImage("dmy_img_character");
	img->setSpriteFrameWithFile("model/" + GameDataManager::getSingletonPtr()->FindShopModel(tIdx,mIdx).filename());
	img->setRotation(-90);
	PanelHelper::setCompactImage(img, getDummy("dmy_img_character"));
	Button* btn = new Button("dmy_close", Button::NoPressImg);
	btn->setButtonBounding(img->getBounding().size * 10);
    addChild(btn);
	btn->release();
	btn->setListener(this);
}
