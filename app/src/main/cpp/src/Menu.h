#pragma once
#include <vector>
#include "Module.h"
using namespace std;
class Menu{
public:
    Menu();
    ~Menu(){};

    void Draw();
    void SetupRender();
    void Render();
    void Resize(int screenWidth, int screenHeight);
    void AddModule(Module* module);
    bool initialized;
private:
    void setUpKeyboard();
    void diasableKeys();
    void scroll();
    bool isAnyScrollBarActive();
    std::vector<Module*> m_modules;

};
extern Menu Gui;