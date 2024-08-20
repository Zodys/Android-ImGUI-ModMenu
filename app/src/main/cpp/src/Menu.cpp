#include <jni.h>
#include <imgui.h>
#include <android/keycodes.h>
#include <GLES2/gl2.h>
#include "Menu.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_android.h"
#include "imgui_internal.h"
#include "stuff/Config.h"
#include "Module.h"
#include "stuff/font/IconsMaterialDesign.h"
#include "stuff/font/MaterialDesignData.h"
#include "stuff/font/NotoSansData.h"

void Menu::AddModule(Module * module) {
    m_modules.push_back(module);
}

void Menu::Draw() {
    ImGui::SetNextWindowCollapsed(false, ImGuiCond_::ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(vars.global.screenWidth * 0.65, vars.global.screenHeight * 0.7),
                             ImGuiCond_::ImGuiCond_Once);
    ImGui::Begin("Mod Menu", nullptr, ImGuiWindowFlags_NoResize);
    {
        //scroll();
        if (ImGui::BeginTabBar("bar")) {
            for(Module* module : m_modules){
                const char* name = module->get_name().c_str();
                if (ImGui::BeginTabItem(name)) {
                    module->drawUI();
                    ImGui::EndTabItem();
                }
            }


            ImGui::EndTabBar();
        }
    }
    ImGui::End();
}

void Menu::Render() {
    // Start the Dear ImGui frame
    if (!initialized)
        return;
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(vars.global.screenWidth, vars.global.screenHeight);
    ImGui::NewFrame();
    auto gloabalDrawList = ImGui::GetBackgroundDrawList();
    gloabalDrawList->Flags &= ~ImDrawListFlags_AntiAliasedLinesUseTex;
    vars.global.drawList = gloabalDrawList;
    for(Module* draw_module : m_modules){
        draw_module->draw(); //drawList
    }
    Draw();

    ImGuiIO &io = ImGui::GetIO();
    ImGui::EndFrame();
    diasableKeys();
    ImGui::Render();
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Menu::SetupRender() {
    if (initialized) {
        return;
    }
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    ImGui::StyleColorsDark();
//    io.BackendPlatformName = ("imgui_impl_android");
    ImGui_ImplAndroid_Init(nullptr);
    ImGui_ImplOpenGL3_Init("#version 300 es");
    setUpKeyboard();

    ImGui::GetStyle().ScaleAllSizes(3.5f);
    ImGuiStyle &style = ImGui::GetStyle();
    style.ScrollbarSize = 55.0f;
    ImFontConfig icons_config;
    icons_config.GlyphMinAdvanceX = 13.0f;
    icons_config.PixelSnapH = true;
    icons_config.MergeMode = true;
    static const ImWchar icons_ranges[] = {
            ICON_MIN_MD, ICON_MAX_MD,
            0
    };
    icons_config.GlyphOffset = ImVec2(0.0f, 6.0f);

    io.Fonts->AddFontFromMemoryCompressedBase85TTF(notosans_regular_compressed_data_base85,
                                                   (38.0f), NULL,
                                                   io.Fonts->GetGlyphRangesCyrillic());

    initialized = true;
}

void Menu::Resize(int screenWidth, int screenHeight) {
    if (!initialized)
        return;
    vars.global.screenWidth = screenWidth;
    vars.global.screenHeight = screenHeight;
    ImGuiIO &io = ImGui::GetIO();
    io.DisplaySize = ImVec2(vars.global.screenWidth, vars.global.screenHeight);
    glViewport(0, 0, (int) io.DisplaySize.x, (int) io.DisplaySize.y);
}


void Menu::setUpKeyboard() {
    ImGuiIO &io = ImGui::GetIO();
    io.KeyMap[ImGuiKey_UpArrow] = 19;
    io.KeyMap[ImGuiKey_DownArrow] = 20;
    io.KeyMap[ImGuiKey_LeftArrow] = 21;
    io.KeyMap[ImGuiKey_RightArrow] = 22;
    io.KeyMap[ImGuiKey_Tab] = 61;
    io.KeyMap[ImGuiKey_Enter] = 66;
    io.KeyMap[ImGuiKey_Backspace] = 67;
    io.KeyMap[ImGuiKey_PageUp] = 92;
    io.KeyMap[ImGuiKey_PageDown] = 93;
    io.KeyMap[ImGuiKey_Escape] = 111;
    io.KeyMap[ImGuiKey_Delete] = 112;
    io.KeyMap[ImGuiKey_Home] = 122;
    io.KeyMap[ImGuiKey_End] = 123;
    io.KeyMap[ImGuiKey_Insert] = 124;
}

void Menu::diasableKeys() {
    ImGuiIO &io = ImGui::GetIO();
    io.KeysDown[io.KeyMap[ImGuiKey_UpArrow]] = false;
    io.KeysDown[io.KeyMap[ImGuiKey_DownArrow]] = false;
    io.KeysDown[io.KeyMap[ImGuiKey_LeftArrow]] = false;
    io.KeysDown[io.KeyMap[ImGuiKey_RightArrow]] = false;
    io.KeysDown[io.KeyMap[ImGuiKey_Tab]] = false;
    io.KeysDown[io.KeyMap[ImGuiKey_Enter]] = false;
    io.KeysDown[io.KeyMap[ImGuiKey_Backspace]] = false;
    io.KeysDown[io.KeyMap[ImGuiKey_PageUp]] = false;
    io.KeysDown[io.KeyMap[ImGuiKey_PageDown]] = false;
    io.KeysDown[io.KeyMap[ImGuiKey_Escape]] = false;
    io.KeysDown[io.KeyMap[ImGuiKey_Delete]] = false;
    io.KeysDown[io.KeyMap[ImGuiKey_Home]] = false;
    io.KeysDown[io.KeyMap[ImGuiKey_End]] = false;
    io.KeysDown[io.KeyMap[ImGuiKey_Insert]] = false;
}

bool Menu::isAnyScrollBarActive() {
    ImGuiWindow *window = ImGui::GetCurrentWindow();
    ImGuiID active_id = ImGui::GetActiveID();
    return (active_id && (active_id == ImGui::GetWindowScrollbarID(window, ImGuiAxis_X) || active_id == ImGui::GetWindowScrollbarID(window, ImGuiAxis_Y)));
}

void Menu::scroll() {
    ImGuiIO &io = ImGui::GetIO();
    ImVec2 windowPos = ImGui::GetWindowPos();
    ImVec2 windowSize = ImGui::GetWindowSize();

    if (!isAnyScrollBarActive() &&
        io.MousePos.x >= windowPos.x && io.MousePos.x <= windowPos.x + windowSize.x &&
        io.MousePos.y >= windowPos.y && io.MousePos.y <= windowPos.y + windowSize.y
            ) {
        ImVec2 mouse_delta = io.MouseDelta;
        if (mouse_delta.x != 0.0f && mouse_delta.x <= 100.0f) {
            ImGui::SetScrollX(ImGui::GetScrollX() + -mouse_delta.x);
        }

        if (mouse_delta.y != 0.0f && mouse_delta.y <= 100.0f) {
            ImGui::SetScrollY(ImGui::GetScrollY() + -mouse_delta.y);
        }
    }
}
Menu Gui;