//
// Created by 1 on 10.08.2024.
//
#pragma once
#include "../Module.h"
#include "../memory/Il2cppResolver/IL2CPP_Resolver.hpp"
#include "../stuff/Config.h"
class Player : public Module
{
public:
    Player() : Module("Player"){}

    void draw() override{
        //vars.global.drawList->AddCircle(ImVec2(vars.global.screenWidth/2,vars.global.screenHeight/2),150.f,ImColor(255,0,0),0,3); just example. this method can be used for esp and other stuff
    }

    void drawUI() override{
        ImGui::Checkbox("Inf Mana And Health", &vars.player.more_mana_health);
        ImGui::Checkbox("Fast Mine", &vars.player.fast_pickaxe);
        ImGui::Checkbox("Print values", &vars.player.print_values);
    }

};