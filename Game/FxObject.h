/********************************************************************
	filename: 	FxObject.h
	
	purpose:	이펙트 오브젝트
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