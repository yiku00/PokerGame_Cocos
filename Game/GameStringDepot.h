/********************************************************************
	file name:	GameStringDepot.h
	
	purpose:	게임 문자열 데이타 관리
*********************************************************************/
#pragma once

#include "NXFramework.h"

class GameStringDepot : public Singleton<GameStringDepot>
{
public:
	enum LanguageId
	{
		Korean,
		English,
		Japanese,
		Chinese,
	};

	struct StringValue
	{
		StringValue(const string& strVal, uint sizeVal) : str(strVal), size(sizeVal) {}
		string str;
		uint size;
	};

private:
	typedef map<LanguageId, string> LanguageTable;
	typedef map<string, StringValue> StringTable;

public:
	~GameStringDepot();
	GameStringDepot();

	void reload();
	void LoadDataXml();
	bool hasString(const std::string& stringKey);
	const std::string& getString(const std::string& stringKey);
	const std::wstring getWString(const std::string& stringKey);
	uint getStringSize(const std::string& stringKey);
	
	void LoadDataXmlLongstring();
	const std::string& getLongString(const std::string& stringKey);
	void ClearLongStringData();
	void changeLanguage(LanguageId id);
	void setLabel(Nx::Label* targetLabel , const std::string& stringKey);	
	LanguageId getLanguage() { return mLanguage; }

private:
	void setStringTest();

private:
	LanguageTable mLanguageTable;
	StringTable mStringTable;
	std::map<std::string, std::string> m_longStringTable;

	LanguageId mLanguage;
	std::string strNull;
};
