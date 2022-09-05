/********************************************************************
	filename: 	FxObject.h
	
	purpose:	����Ʈ ������Ʈ
*********************************************************************/
#pragma once

#include "NxFramework.h"

class FxObject : public SkelObject, public SkelObject::Listener
{
public:
	FxObject(const string& skel, const string& label);
	virtual ~FxObject();

public: // SkelObject::Listener
	virtual void onAnimationEnded(const string& ani) override;
};