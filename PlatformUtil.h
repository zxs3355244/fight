
#ifndef PlatformUtil_h__
#define PlatformUtil_h__

#include "cocos2d.h"
#include "string"

using std::string;


class PlatformUtil
{
public:
	static void callBilling(int payPoint);
	static void onPayResult(const int state, const char* code);
	static int getUiInfo(int paypoint);
};


#endif // PlatformUtil_h__
