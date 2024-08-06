#pragma once
#include <android/log.h>
#define Resolver_TAG "zodys_Resolver"
#define Resolver_LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG,   Resolver_TAG, __VA_ARGS__))
#define Resolver_LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR,   Resolver_TAG, __VA_ARGS__))
#define Resolver_LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO,    Resolver_TAG, __VA_ARGS__))
#define Resolver_LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARNING, Resolver_TAG, __VA_ARGS__))