//
// Created by 1 on 04.08.2024.
//


#include <jni.h>
#include <imgui.h>
#include <android/input.h>
#include "Main.h"
#include "stuff/Java.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_android.h"
#include "stuff/logger.h"
#include "Menu.h"

extern "C" {
JNIEXPORT void JNICALL
Java_com_rhteam_gui_Surface_DrawFrame(JNIEnv *env, jobject thiz) {
    ImGuiIO &io = ImGui::GetIO();
    static bool WantTextInputLast = false;
    if (io.WantTextInput && !WantTextInputLast)
        Java::show_soft_input(true);
    if (io.KeysDown[io.KeyMap[ImGuiKey_Enter]])
        Java::show_soft_input(false);
    WantTextInputLast = io.WantTextInput;
    Gui.Render();
}
JNIEXPORT void JNICALL
Java_com_rhteam_gui_Surface_ShutDown(JNIEnv *env, jobject thiz) {
    if (!Gui.initialized)
    {
        return;
    }
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplAndroid_Shutdown();
    ImGui::DestroyContext();
    Gui.initialized=false;
}

JNIEXPORT void JNICALL
Java_com_rhteam_gui_Surface_SurfaceCreated(JNIEnv *env, jobject thiz) {
    Gui.SetupRender();
}
JNIEXPORT void JNICALL
Java_com_rhteam_gui_Surface_SurfaceChanged(JNIEnv *env, jobject thiz, jint width, jint height) {
    Gui.Resize(width,height);
}
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    Java::publicJVM = vm;
    return JNI_VERSION_1_6;
}
}



jmethodID MotionEvent_getX, MotionEvent_getY, MotionEvent_getAction, MotionEvent_getToolType, MotionEvent_getButtonState, MotionEvent_getAxisValue;
jmethodID KeyEvent_getUnicodeChar, KeyEvent_getMetaState, KeyEvent_getAction, KeyEvent_getKeyCode, KeyEvent_getScanCode;
int (*origtouchHook)(JNIEnv *env, jobject thiz, jobject inputEvent);
int touchHook(JNIEnv *env, jobject __this, jobject input_event) {

    jclass motion_event = env->FindClass(("android/view/MotionEvent"));

    if(!motion_event){
        LOGI("Can't find MotionEvent!");
        return origtouchHook(env, __this, input_event);
    }

    ImGuiIO &io = ImGui::GetIO();

    if (env->IsInstanceOf(input_event, motion_event)) {
        if (!MotionEvent_getX) MotionEvent_getX = env->GetMethodID(motion_event, ("getX"), ("(I)F"));
        if (!MotionEvent_getY) MotionEvent_getY = env->GetMethodID(motion_event, ("getY"), ("(I)F"));
        if (!MotionEvent_getToolType) MotionEvent_getToolType = env->GetMethodID(motion_event, ("getToolType"), ("(I)I"));
        if (!MotionEvent_getAction) MotionEvent_getAction = env->GetMethodID(motion_event, ("getAction"), ("()I"));
        if (!MotionEvent_getButtonState) MotionEvent_getButtonState = env->GetMethodID(motion_event, ("getButtonState"), ("()I"));
        if (!MotionEvent_getAxisValue) MotionEvent_getAxisValue = env->GetMethodID(motion_event, ("getAxisValue"), ("(II)F"));

        auto action = env->CallIntMethod(input_event, MotionEvent_getAction);
        int32_t pointer_index = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
        action &= AMOTION_EVENT_ACTION_MASK;

        switch (action) {
            case AMOTION_EVENT_ACTION_DOWN:
            case AMOTION_EVENT_ACTION_UP:
                if ((env->CallIntMethod(input_event, MotionEvent_getToolType, pointer_index) == AMOTION_EVENT_TOOL_TYPE_FINGER) ||
                    (env->CallIntMethod(input_event, MotionEvent_getToolType, pointer_index) == AMOTION_EVENT_TOOL_TYPE_UNKNOWN)) {
                    io.MouseDown[0] = (action == AMOTION_EVENT_ACTION_DOWN);
                    io.MousePos = ImVec2(env->CallFloatMethod(input_event, MotionEvent_getX, pointer_index), env->CallFloatMethod(input_event, MotionEvent_getY, pointer_index));

                }
                break;
            case AMOTION_EVENT_ACTION_BUTTON_PRESS:
            case AMOTION_EVENT_ACTION_BUTTON_RELEASE: {
                jint button_state = env->CallIntMethod(input_event, MotionEvent_getButtonState);
                io.MouseDown[0] = ((button_state & AMOTION_EVENT_BUTTON_PRIMARY) != 0);
                io.MouseDown[1] = ((button_state & AMOTION_EVENT_BUTTON_SECONDARY) != 0);
                io.MouseDown[2] = ((button_state & AMOTION_EVENT_BUTTON_TERTIARY) != 0);
            } break;
            case AMOTION_EVENT_ACTION_HOVER_MOVE:
            case AMOTION_EVENT_ACTION_MOVE:
                io.MousePos = ImVec2(env->CallFloatMethod(input_event, MotionEvent_getX, pointer_index), env->CallFloatMethod(input_event, MotionEvent_getY, pointer_index));
                break;
            case AMOTION_EVENT_ACTION_SCROLL:
                io.MouseWheel = env->CallFloatMethod(input_event, MotionEvent_getAxisValue, AMOTION_EVENT_AXIS_VSCROLL, pointer_index);
                io.MouseWheelH = env->CallFloatMethod(input_event, MotionEvent_getAxisValue, AMOTION_EVENT_AXIS_HSCROLL, pointer_index);
                break;
            default:
                break;
        }

        if (io.WantCaptureMouse) return true;
    }

    jclass key_event = env->FindClass("android/view/KeyEvent");
    if(!key_event){
        LOGI("Can't find KeyEvent!");
        return origtouchHook(env, __this, input_event);
    }

    if (env->IsInstanceOf(input_event, key_event)) {

        if (!KeyEvent_getAction) KeyEvent_getAction = env->GetMethodID(key_event, ("getAction"), ("()I"));
        if (!KeyEvent_getKeyCode) KeyEvent_getKeyCode = env->GetMethodID(key_event, ("getKeyCode"), ("()I"));
        if (!KeyEvent_getUnicodeChar) KeyEvent_getUnicodeChar = env->GetMethodID(key_event, ("getUnicodeChar"), ("(I)I"));
        if (!KeyEvent_getMetaState) KeyEvent_getMetaState = env->GetMethodID(key_event, ("getMetaState"), ("()I"));
        if (!KeyEvent_getScanCode) KeyEvent_getScanCode = env->GetMethodID(key_event, ("getScanCode"), ("()I"));

        jint Action = env->CallIntMethod(input_event, KeyEvent_getAction);
        jint KeyCode = env->CallIntMethod(input_event, KeyEvent_getKeyCode);
        jint MetaState = env->CallIntMethod(input_event, KeyEvent_getMetaState);
        jint ScanCode = env->CallIntMethod(input_event, KeyEvent_getScanCode);


        io.KeyCtrl = ((MetaState & AMETA_CTRL_ON) != 0);
        io.KeyShift = ((MetaState & AMETA_SHIFT_ON) != 0);
        io.KeyAlt = ((MetaState & AMETA_ALT_ON) != 0);
        switch (KeyCode) {
            case 19:
                io.KeysDown[io.KeyMap[ImGuiKey_UpArrow]] = true;
                break;
            case 20:
                io.KeysDown[io.KeyMap[ImGuiKey_DownArrow]] = true;
                break;
            case 21:
                io.KeysDown[io.KeyMap[ImGuiKey_LeftArrow]] = true;
                break;
            case 22:
                io.KeysDown[io.KeyMap[ImGuiKey_RightArrow]] = true;
                break;
            case 61:
                io.KeysDown[io.KeyMap[ImGuiKey_Tab]] = true;
                break;
            case 66:
                io.KeysDown[io.KeyMap[ImGuiKey_Enter]] = true;
                break;
            case 67:
                io.KeysDown[io.KeyMap[ImGuiKey_Backspace]] = true;;
                break;
            case 92:
                io.KeysDown[io.KeyMap[ImGuiKey_PageUp]] = true;
                break;
            case 93:
                io.KeysDown[io.KeyMap[ImGuiKey_PageDown]] = true;
                break;
            case 111:
                io.KeysDown[io.KeyMap[ImGuiKey_Escape]] = true;
                break;
            case 112:
                io.KeysDown[io.KeyMap[ImGuiKey_Delete]] = true;
                break;
            case 122:
                io.KeysDown[io.KeyMap[ImGuiKey_Home]] = true;
                break;
            case 123:
                io.KeysDown[io.KeyMap[ImGuiKey_End]] = true;
                break;
            case 124:
                io.KeysDown[io.KeyMap[ImGuiKey_Insert]] = true;
                break;
        }
        switch (Action) {
            case AKEY_EVENT_ACTION_DOWN:
            case AKEY_EVENT_ACTION_UP: {
                if (io.WantCaptureKeyboard && Action != AKEY_EVENT_ACTION_UP) {
                    io.AddInputCharacter(env->CallIntMethod(input_event, KeyEvent_getUnicodeChar, MetaState));
                }
                break;
            }
            default:
                break;
        }
    }
    return origtouchHook(env, __this, input_event);
}