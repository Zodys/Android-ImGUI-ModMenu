#pragma once
#include <jni.h>
extern int touchHook(JNIEnv *env, jobject __this, jobject input_event);
extern int (*origtouchHook)(JNIEnv *env, jobject thiz, jobject inputEvent);