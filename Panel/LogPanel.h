#pragma once
#include "NxFramework.h"

class LogPanel : public LogPanel
{
public:
	LogPanel();
	virtual ~LogPanel();

	virtual void construct(const string& mxml, const string& forcedFont  = "");
};
