
#ifndef JniUtil_h__
#define JniUtil_h__


#define EXTERN_C_BEGIN extern "C" {
#define EXTERN_C_END }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
EXTERN_C_BEGIN


void jni_payLT(const int payPoint);
int jni_getUiInfo(int payPoint);

EXTERN_C_END

#endif


#endif // JniUtil_h__

