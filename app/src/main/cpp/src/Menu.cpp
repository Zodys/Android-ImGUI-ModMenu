#include <jni.h>
#include <imgui.h>
#include <android/keycodes.h>
#include <GLES2/gl2.h>
#include "Menu.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_android.h"
#include "imgui_internal.h"
#include "stuff/Config.h"
#include "Categories.h"
#include "stuff/font/IconsMaterialDesign.h"
#include "stuff/font/MaterialDesignData.h"
#include "stuff/font/NotoSansData.h"
namespace Renderer {
    ScreenSize screenSize;
    bool _initialized = false;

    void Menu() {
        ImGui::SetNextWindowCollapsed(true, ImGuiCond_::ImGuiCond_Once);
        ImGui::SetNextWindowSize(ImVec2(screenSize.width * 0.65, screenSize.height * 0.7),
                                 ImGuiCond_::ImGuiCond_Once);
        ImGui::Begin("Mod Menu", nullptr, ImGuiWindowFlags_NoResize);
        if (ImGui::BeginTabBar("bar")) {
            for (Category category: Category::_values()) {
                const char *name = category._to_string();
                if (ImGui::BeginTabItem(name)) {
                    CategoryHandler(category);
                    ImGui::EndTabItem();
                }
            }


            ImGui::EndTabBar();
        }
        ImGui::End();
    }

    void Render() {
        // Start the Dear ImGui frame
        if(!_initialized)
            return;
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplAndroid_NewFrame(screenSize.width, screenSize.height);
        ImGui::NewFrame();
        auto gloabalDrawList = ImGui::GetBackgroundDrawList();
        gloabalDrawList->Flags &= ~ImDrawListFlags_AntiAliasedLinesUseTex;

        Menu();

        ImGuiIO &io = ImGui::GetIO();
        ImGui::EndFrame();
        diasableKeys();
        ImGui::Render();
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void SetupRender() {
        if (_initialized) {
            return;
        }
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        ImGui::StyleColorsDark();
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

        io.Fonts->AddFontFromMemoryCompressedBase85TTF(notosans_regular_compressed_data_base85, (38.0f),nullptr,io.Fonts->GetGlyphRangesCyrillic());

        _initialized = true;
    }

    void Resize(int width, int height) {
        if(!_initialized)
            return;
        screenSize.width = width;
        screenSize.height = height;
        ImGuiIO &io = ImGui::GetIO();
        io.DisplaySize = ImVec2(screenSize.width, screenSize.height);
        glViewport(0, 0, (int) io.DisplaySize.x, (int) io.DisplaySize.y);


    }


    void setUpKeyboard() {
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

    void diasableKeys() {
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

}