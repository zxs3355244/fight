

#include "JniUtil.h"
#include "PlatformUtil.h"


USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>


#define CLASS_NAME "com/ghfggfd/iuyhggf/mghgfface"

EXTERN_C_BEGIN


void jni_payLT(const int payPoint)
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "startRealPay", "(I)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, payPoint);
		t.env->DeleteLocalRef(t.classID);
	}
}

int jni_getUiInfo(int payPoint)
{
	JniMethodInfo t;
	jint ret;
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getUiInfo", "(I)I"))
	{
		ret = t.env->CallStaticIntMethod(t.classID, t.methodID, payPoint);
		t.env->DeleteLocalRef(t.classID);
	}
	return ret;
}

void Java_com_ghfggfd_iuyhggf_mghgfface_payResult(JNIEnv *env, jobject thiz, jint jstate, jstring jcode)
{
	const char* code = env->GetStringUTFChars(jcode, NULL);
	PlatformUtil::onPayResult(jstate, code);
}

EXTERN_C_END

#endif




