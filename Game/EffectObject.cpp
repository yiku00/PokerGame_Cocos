#include "pch.h"
#include "EffectObject.h"

EffectObject::EffectObject()
{
	setListener(this);
}

EffectObject::EffectObject(const string& sam, const string& anim, bool additive /*= true*/)
{
	setSuperAnim(sam);
	playAnimation(anim);
	if (additive) {
		setAdditiveBlend();
	}

	setListener(this);
}

EffectObject::~EffectObject()
{

}

void EffectObject::onAnimationEnded(const string& ani)
{
	if (isAnimationCompleted())
		removeFromParentAndCleanup(true);
}

