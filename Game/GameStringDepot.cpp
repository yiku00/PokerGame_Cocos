#include "pch.h"
#include "GameStringDepot.h"
#include "HeroUtil.h"

template<> GameStringDepot* Singleton<GameStringDepot>::msSingleton = 0;

#define MIN_FONT_SIZSE 8

#ifdef COCOS2D_DEBUG
	//#define LOGINGTEST
#endif

//#define GOOGLE_PLAY_TW

GameStringDepot::~GameStringDepot()
{

}

GameStringDepot::GameStringDepot()
{
	mLanguageTable.insert(LanguageTable::value_type(Korean, "KOR"));
	mLanguageTable.insert(LanguageTable::value_type(English, "ENG"));
	mLanguageTable.insert(LanguageTable::value_type(Japanese, "JPN"));
	mLanguageTable.insert(LanguageTable::value_type(Chinese, "CHN"));
	
	mLanguage = Korean;
	//mLanguage = English;

	NXASSERT(mLanguageTable.find(mLanguage) != mLanguageTable.end());
	strNull = " ";
	LoadDataXml();
}

void GameStringDepot::LoadDataXml()
{
	NXASSERT(mLanguageTable.find(mLanguage) != mLanguageTable.end());
	
	pugi::xml_document doc;
	if (false == loadXMLDocReal("xml/game_data_string.xml", &doc))
		return;

	pugi::xml_node stringNode = doc.child("GAMEDATASTRING");

	string langKey = mLanguageTable[mLanguage];
	string langSizeKey = langKey + "_SIZE";
	for( pugi::xml_node node = stringNode.first_child() ; node != NULL ; node = node.next_sibling() )
	{
		std::string strKey = node.child_value("KEY");
		NXASSERT(!node.child(langKey.c_str()).empty());
		if(node.child(langKey.c_str()).empty()) {
			CCLOG ("Error Empty = %s" , strKey.c_str());
		}
		else{
			std::string strVal = ""; 
			//std::string strVal = "中"; 		
			strVal	+= node.child_value(langKey.c_str());
			strVal = nxReplaceNewl(strVal);
			NXASSERT(!node.child(langSizeKey.c_str()).empty() , "%s" , strKey.c_str());
			uint strSize = node.child(langSizeKey.c_str()).empty() ? MIN_FONT_SIZSE : StringConverter::parseUnsignedInt(node.child_value(langSizeKey.c_str()));

			mStringTable.insert(StringTable::value_type(strKey, StringValue(strVal, strSize)));
		}
	}


#ifdef LOGINGTEST
	setStringTest();
#endif

}

bool GameStringDepot::hasString(const std::string& stringKey)
{
	return mStringTable.find(stringKey) != mStringTable.end();
}

const std::string& GameStringDepot::getString(const std::string& stringKey)
{
	NXASSERT(mStringTable.find(stringKey) != mStringTable.end(), "string key - %s", stringKey.c_str());
	StringTable::iterator it = mStringTable.find(stringKey);
	if( it != mStringTable.end() )
	{
		return it->second.str;
	}

	//return NULL 일경우 참조 하는곳에서  if(NULL) 체크를 매번해야함..
	return strNull;
}

const std::wstring GameStringDepot::getWString(const std::string& stringKey)
{
	return StringConverter::toWstring(getString(stringKey));
}

uint GameStringDepot::getStringSize(const std::string& stringKey)
{
	NXASSERT(mStringTable.find(stringKey) != mStringTable.end(), "string key - %s", stringKey.c_str());
	StringTable::iterator it = mStringTable.find(stringKey);
	if( it != mStringTable.end() )
	{
		return it->second.size;
	}


	return 0;
}

void GameStringDepot::LoadDataXmlLongstring()
{
	pugi::xml_document doc;
	if (false == loadXMLDocReal("xml/game_data_longstring.xml", &doc))
		return;

	pugi::xml_node stringNode = doc.child("GAMEDATASTRING");

	for( pugi::xml_node node = stringNode.first_child() ; node != NULL ; node = node.next_sibling() )
	{
		std::string strKey = node.child_value("KEY");
		std::string strVal = node.child_value("VALUE");

		m_longStringTable.insert( std::make_pair(strKey, strVal) );
	}
}

const std::string& GameStringDepot::getLongString( const std::string& stringKey )
{
	std::map<std::string, std::string>::iterator it = m_longStringTable.find(stringKey);
	if( it != m_longStringTable.end() )
	{
		return it->second;
	}

	//return NULL 일경우 참조 하는곳에서  if(NULL) 체크를 매번해야함..
	return strNull;
}

void GameStringDepot::ClearLongStringData()
{
	m_longStringTable.clear();
}

void GameStringDepot::changeLanguage(LanguageId id)
{
	NXASSERT(mLanguageTable.find(id) != mLanguageTable.end());
	mLanguage = id;

	reload();
}

void GameStringDepot::reload()
{
	mStringTable.clear();
	LoadDataXml();
}

void GameStringDepot::setLabel(Nx::Label* targetLabel , const std::string& stringKey)
{
	NXASSERT(targetLabel);
	if (!targetLabel)
		return;
	targetLabel->setString(getString(stringKey).c_str());
	targetLabel->setFontSize((float)getStringSize(stringKey));
}

void GameStringDepot::setStringTest()
{
	
}
