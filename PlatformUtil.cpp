
#include "PlatformUtil.h"
#include "JniUtil.h"

#include "GiftLayer.h"
#include "GameLayer.h"
#include "GameData.h"

USING_NS_CC;

#define FREE_VERSION 0

void PlatformUtil::callBilling(int payPoint)
{

#if FREE_VERSION
	onPayResult(0, "0");
	return;
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	jni_payLT(payPoint);
#else
	onPayResult(0, "0");
#endif
}



int PlatformUtil::getUiInfo(int payPoint)
{
	#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		return jni_getUiInfo(payPoint);
	#else
		return 1;
	#endif
}

void PlatformUtil::onPayResult(const int state, const char* code)
{
	CCLOG("results state : %d, code : %s", state, code);

	
	if (GiftLayer::getInstance()->getParent())
	{
		GiftLayer::getInstance()->onPayResultHandle(state);
	}
	
}


