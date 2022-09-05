#include "pch.h"
#include "HeroUtil.h"
#include "NxUtil.h"
#include "GameStringDepot.h"
#include "SocialManager.h"
#include "NxTableView.h"
#include "base64util.h"

static const string sNA = "N/A";
#define LAYER_ORDER 999
#define ENCRYPT_BLOCK_SIZE 16

Panel* addMouseBlockPanel(Nx::Layer* layer , bool transparency /*= false*/)
{
	Panel *panel = new Panel();
	panel->setTouchable(true);
	if(transparency)
		panel->makeColored(ccc4(0x00, 0x00, 0x00, 0x00));
	else
		panel->makeColored(ccc4(0x00, 0x00, 0x00, 0xc8));
	panel->setModifyOpacity(false);
	panel->setName("addmouseBlock");
	panel->setContentSizeAsBouding();
	panel->setScale(1.f);
	layer->addChild(panel);
	panel->release();
	return panel;
}

std::string getMxmlPath()
{
  return "mxml/"; 
}

eMarketType getMarketType()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	return Local;
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	return Apple;
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	//string marketStr;
	//if (SocialManager::getSingletonPtr() && SocialManager::getSingleton().getInterface()) {
	//	marketStr = SocialManager::getSingleton().getInterface()->getMarket();
	//}

	//if (marketStr.compare("GOOGLE") == 0) {
	//	return Google;
	//}
	//else if (marketStr.compare("TSTORE") == 0) {
	//	return SKT;
	//}
	//else if (marketStr.compare("NAVER") == 0) {
	//	return  SKT;
	//}
	//else {
	//	return Local;
	//}
	return Local;
	//return Google; //<-나중에 이걸로 바꿔야함 지금은 보상이 안주기 때문에 위 코드로 보상 확인
#else
	return Local;
#endif
}

bool loadXMLDocReal(const std::string& xmlPath, pugi::xml_document *pXmlDoc )
{
	STBufferHolder bufHolder;
	string path = CCFileUtils::sharedFileUtils()->fullPathForFilename(xmlPath.c_str());
	bufHolder.pBuffer = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "r", &bufHolder.bufferSize);
	if (nullptr == bufHolder.pBuffer )
	{
		char arErrorMessage[1024];
		sprintf(arErrorMessage, "%s load fail!", xmlPath.c_str());

		assert(0);
		NXASSERT(false && arErrorMessage);
		return false;
	}

	pugi::xml_parse_result parseResult = pXmlDoc->load_buffer(bufHolder.pBuffer, bufHolder.bufferSize);
	if (pugi::status_ok != parseResult.status)
	{
		char arErrorMessage[1024];
		sprintf(arErrorMessage, "%s load fail!", xmlPath.c_str());

		NXASSERT(false && arErrorMessage);
		return false;
	}

	return true;
}

float getScaleFit(CCSize originalSize , CCSize fitSize)
{
	float widthScale = fitSize.width/originalSize.width;
	float heightScale = fitSize.height/originalSize.height;
	float scale = widthScale < heightScale ? widthScale : heightScale;

	return scale;
}

std::string getButtonName( Button* button )
{
	if(button)
		return button->getName();	
	else
		return "";		
}

void setUseButton( Button* button , bool flag /*= true*/ )
{
	button->setEnable(flag);
	button->setGrayscale(!flag);
}

void setVislbleButton( Button* button , bool flag /*= true*/ )
{
	button->setEnable(flag);
	button->setVisible(flag);
}

void setUseIconButton( IconButton button , bool flag /*= true*/ )
{
	setUseButton(button.btn, flag);	
}

void setVisibleIconButton( IconButton button , bool flag /*= true*/ )
{
	setVislbleButton(button.btn, flag);	
	button.btnText->setVisible(flag);
	button.icon->setVisible(flag);
}

void setTableViewReload( Nx::TableView* tableView )
{
	CCPoint nowContentsOffset = tableView->getContentOffset();
	tableView->reloadData();	
	tableView->setContentOffset(nowContentsOffset);
}

auto accumChar = [](const string& str)->char {
	char c = '0';
	for (size_t i = 0; i < str.size(); ++i)
		c += str[i];
	return c;
};
/*
void encodeSecureString(const string& in, SecureString& out)
{
	int pre, post;
	string outStr;

	string iv = NxGetRandomString(ENCRYPT_BLOCK_SIZE);
	string key = NxGetRandomString(ENCRYPT_BLOCK_SIZE);

	NxGetEncryptString(in, outStr, key, iv, pre, post);

	string preSize = StringConverter::toString(pre);
	preSize = base64_encode(reinterpret_cast<const unsigned char*>(preSize.c_str()), preSize.length());
	out.set_presize(preSize);
	string postSize = StringConverter::toString(post);
	postSize = base64_encode(reinterpret_cast<const unsigned char*>(postSize.c_str()), postSize.length());
	out.set_postsize(postSize);
	out.set_content(outStr.c_str(), outStr.size());
	NxXorString(iv, accumChar(preSize));
	out.set_iv(iv.c_str(), iv.size());
	NxXorString(key, accumChar(postSize));
	out.set_key(key.c_str(), key.size());
}

void decodeSecureString(const SecureString& in, string& out)
{
	int pre = StringConverter::parseInt(base64_decode(in.presize()));
	int post = StringConverter::parseInt(base64_decode(in.postsize()));
	string iv = in.iv();
	NxXorString(iv, accumChar(in.presize()));
	string key = in.key();
	NxXorString(key, accumChar(in.postsize()));
	NxGetDecryptString(in.content(), out, key, iv, pre, post);
}*/

//std::string nxGetConnectTimeFormat(long sec)
//{
//	int day = (sec / 3600) / 24;
//	int hour = sec / 3600 - 24 * day;
//	int minute = (sec % 3600) / 60;
//	int second = (sec % 3600) % 60;
//
//	stringstream ss;
//	if (day > 0){
//		//	**일 **시 **분 **초		
//		const string& fmt = GameStringDepot::getSingleton().getString("Time_dd_hh_mm_ss");
//		//if( 4 == nxCountSubstring(fmt , "%d")){
//		//	ss << boost::format(fmt) %day %hour %minute %second;
//		//}
//		//return ss.str();
//		return NxGetFormatString(fmt, day, hour, minute, second);
//	}
//	else if (day == 0){
//
//		if (hour == 0){
//			if (minute > 0){
//				//**분 **초				
//				const string& fmt = GameStringDepot::getSingleton().getString("Time_mm_ss");
//				//if( 2 == nxCountSubstring(fmt , "%d")){
//				//	ss << boost::format(fmt) %minute %second;
//				//}
//				//return ss.str();
//				return NxGetFormatString(fmt, minute, second);
//			}
//			else{
//				//**초
//				const string& fmt = GameStringDepot::getSingleton().getString("Time_ss");
//				//if( 1 == nxCountSubstring(fmt , "%d")){
//				//	ss << boost::format(fmt) %second;				
//				//}
//				//return ss.str();
//				return NxGetFormatString(fmt, second);
//			}
//
//		}
//		else{
//			//** 시 ** 분 ** 초			
//			const string& fmt = GameStringDepot::getSingleton().getString("Time_hh_mm_ss");
//			//if( 3 == nxCountSubstring(fmt , "%d")){
//			//	ss << boost::format(fmt) %hour %minute %second;			
//			//}
//			//return ss.str();
//			return NxGetFormatString(fmt, hour, minute, second);
//		}
//	}
//
//	return "";
//}

bool isFileExist(string fileName)
{
	return CCFileUtils::sharedFileUtils()->isFileExist(CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName.c_str()));
}