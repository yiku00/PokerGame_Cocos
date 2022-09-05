#include "pch.h"
#include "LogPanel.h"
#include "../Game/GameDataManager.h"

LogPanel::LogPanel()
{

}

LogPanel::~LogPanel()
{
	
}

void LogPanel::construct(const string& mxml, const string& forcedFont /* = "" */)
{
	std::wstring message_w;
    message_w.assign(mxml.begin(), mxml.end());
	GameDataManager::getSingletonPtr()->_kLogPacket.Write(message_w.c_str());
	Panel::construct(mxml, forcedFont);
}
