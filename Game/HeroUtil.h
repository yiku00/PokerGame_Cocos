/********************************************************************
	file name:	HeroUtil.h
	
	purpose:	잡동사니 유틸리티 (TODO : 정리 필요)
*********************************************************************/
#pragma once

#include "NxFramework.h"
#include "TypeDefine.pb.h"
//#include "SecureString.pb.h"

namespace Nx {
	class TableView;
}

#define DELAY_REFRESH 10.0f
#define ITEMDESC_NAME_FONT_SIZE 14

#define ImageFolder "ui"
#define FONT_GLAY  ccc3(0x87,0x87,0x87)
#define INCREASE_ABIL	ccc3(0x00,0xe8,0x26)

#define NORMAL_TAB_COLOR ccc3(0xD7,0x7F,0x33)
#define SELECT_TAB_COLOR ccc3(0xFF,0xFF,0xFF)

#define SHOP_POSSIBLE_COLOR ccc3(0x99, 0xFF, 0xFF)
#define FONT_GREEN ccc3(0x1D, 0xDC , 0x3C)
#define FONT_RED ccc3(0xff, 0x40 , 0x00)
#define FONT_ORANGE  ccc3(0xFF,0x92,0x26)

#define DISACTIVE_OPERCITY 192
#define ACTIVE_OPERCITY 255
#define CELL_TOUCH_TIME 0.2f

static const string ITEM_NAME_COLOR = "<FFBF00>";
static const string ITEM_TYPE_COLOR = "<FF794C>";

#define DYNAMIC_PUSH_LAYER 64

#define BUILD_1_0_5

struct STBufferHolder
{
	~STBufferHolder()
	{
		delete[] pBuffer;
		pBuffer = nullptr;
	}
	STBufferHolder()
	{
		bufferSize = 0;
		pBuffer = nullptr;
	}

	ssize_t bufferSize;
	unsigned char *pBuffer;
};

struct IconButton
{
	Button* btn;
	Nx::Label* btnText;
	SuperObject* icon;
};

enum ButtonType{
	Confirm,	//확인 버튼만,
	CancelOk,		//취소 확인
};

//
eMarketType getMarketType();

// Panel-related
Panel* addMouseBlockPanel(Nx::Layer* layer , bool transparency = false);
string getMxmlPath();

bool loadXMLDocReal(const std::string& xmlPath, pugi::xml_document *pXmlDoc );
float getScaleFit(CCSize originalSize , CCSize fitSize);
string getButtonName(Button* button);
void setUseButton(Button* button , bool flag = true);
void setVislbleButton(Button* button , bool flag = true);
void setUseIconButton(IconButton button , bool flag = true);
void setVisibleIconButton(IconButton button , bool flag = true);
void setTableViewReload(Nx::TableView* tableView);

//void encodeSecureString(const string& in, SecureString& out);
//void decodeSecureString(const SecureString& in, string& out);

//string nxGetConnectTimeFormat(long sec);

float getScaleFit(CCSize originalSize, CCSize fitSize);
bool isFileExist(string fileName);