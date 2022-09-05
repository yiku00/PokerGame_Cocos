/********************************************************************
	file name:	EffectObject.h
	
	purpose:	Sam 애니메이션 재생 후 자동으로 파괴되는 객체
*********************************************************************/
#ifndef __EffectObject_H__
#define __EffectObject_H__

#include "NxFramework.h"

class EffectObject : public SuperObject, public SuperObject::Listener
{
public:
	EffectObject();
	EffectObject(const string& sam, const string& anim, bool additive = true);
	virtual ~EffectObject();

protected:
	virtual void onAnimationEnded(const string& ani);
};

#endif