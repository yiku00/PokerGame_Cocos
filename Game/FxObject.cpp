#include "pch.h"
#include "FxObject.h"

FxObject::FxObject(const string& skel, const string& label)
{
	string skelPath = "spine/" + skel + ".json";
	setSkelAnim(skelPath);
	playAnimation(label);

	setListener(this);
}

FxObject::~FxObject()
{

}

void FxObject::onAnimationEnded(const string& ani)
{
	removeFromParentAndCleanup(true);
}

