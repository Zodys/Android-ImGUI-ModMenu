#ifndef CLEAN_IMGUI_JAVA_H
#define CLEAN_IMGUI_JAVA_H
namespace Java {
    JavaVM *publicJVM;
    struct ScreenSize{
        int width;
        int height;
    };
    jobject getGlobalContext(JNIEnv *env) {
        jclass activityThread = env->FindClass("android/app/ActivityThread");
        jmethodID currentActivityThread = env->GetStaticMethodID(activityThread,
                                                                 "currentActivityThread",
                                                                 "()Landroid/app/ActivityThread;");
        jobject at = env->CallStaticObjectMethod(activityThread, currentActivityThread);
        jmethodID getApplication = env->GetMethodID(activityThread, "getApplication",
                                                    "()Landroid/app/Application;");
        jobject context = env->CallObjectMethod(at, getApplication);
        return context;
    }

    ScreenSize getRealSize() {
        JNIEnv *env{};
        publicJVM->GetEnv((void **) &env, JNI_VERSION_1_6);
/*        jobject globalcontext = getGlobalContext(env);

        jclass application = env->FindClass("android/app/Application");
        jmethodID getBaseContext = env->GetMethodID(application, "getBaseContext",
                                                    "()Landroid/content/Context;");
        jobject contextObj = env->CallObjectMethod(globalcontext, getBaseContext);

        jclass contextClass = env->GetObjectClass(contextObj);
        jmethodID getSystemServiceID = env->GetMethodID(contextClass, "getSystemService",
                                                        "(Ljava/lang/String;)Ljava/lang/Object;");
        jstring windowServiceName = env->NewStringUTF("window");
        jobject windowManagerObj = env->CallObjectMethod(contextObj, getSystemServiceID,
                                                         windowServiceName);
        jclass windowManagerClass = env->GetObjectClass(windowManagerObj);

        // Get screen size
        jmethodID getDefaultDisplayID = env->GetMethodID(windowManagerClass, "getDefaultDisplay",
                                                         "()Landroid/view/Display;");
        jobject defaultDisplayObj = env->CallObjectMethod(windowManagerObj, getDefaultDisplayID);
        jclass displayClass = env->GetObjectClass(defaultDisplayObj);
        jmethodID getRealSizeID = env->GetMethodID(displayClass, "getRealSize",
                                                   "(Landroid/graphics/Point;)V");

        jclass pointClass = env->FindClass("android/graphics/Point");
        jobject pointObj = env->NewObject(pointClass,
                                          env->GetMethodID(pointClass, "<init>", "()V"));
        env->CallVoidMethod(defaultDisplayObj, getRealSizeID, pointObj);

        jfieldID heightFieldId = env->GetFieldID(pointClass, "y", "I");
        jint height = env->GetIntField(pointObj, heightFieldId);

        jfieldID widthFieldId = env->GetFieldID(pointClass, "x", "I");
        jint width = env->GetIntField(pointObj, widthFieldId);*/

        jclass surface = env->FindClass("com/zodys/gui/Surface");
        jfieldID screenHeight = env->GetStaticFieldID(surface,"screenHeight", "I");
        jint height = env->GetStaticIntField(surface, screenHeight);
        jfieldID screenWidth = env->GetStaticFieldID(surface,"screenWidth", "I");
        jint width = env->GetStaticIntField(surface, screenWidth);
        ScreenSize size;
        size.height = height;
        size.width = width;
        return size;
    }
    void show_soft_input(bool open) {
        JNIEnv *env{};
        publicJVM->GetEnv((void **) &env, JNI_VERSION_1_6);
        jobject context = getGlobalContext(env);
        jclass contextClass = env->FindClass("android/content/Context");
        jmethodID getSystemService = env->GetMethodID(contextClass, "getSystemService",
                                                      "(Ljava/lang/String;)Ljava/lang/Object;");
        jobject clipboard = env->CallObjectMethod(context, getSystemService,
                                                  env->NewStringUTF("input_method"));
        env->CallVoidMethod(clipboard, env->GetMethodID(
                env->FindClass("android/view/inputmethod/InputMethodManager"), "toggleSoftInput",
                "(II)V"), (open ? 2 : 0), 0);
    }
}
#endif //CLEAN_IMGUI_JAVA_H
