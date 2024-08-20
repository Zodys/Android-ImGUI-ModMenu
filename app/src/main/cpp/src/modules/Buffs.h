//
// Created by 1 on 10.08.2024.
//
#pragma once
#include "../Module.h"
#include "../memory/Il2cppResolver/IL2CPP_Resolver.hpp"
#include "../stuff/Config.h"
class Buffs : public Module
{
public:
    Buffs() : Module("Buffs"){}

    void draw() override{} //for drawList

    void drawUI() override{
        static int search_id = 0;
        static bool m_Filter = false;
        ImGui::Checkbox("Filter",&m_Filter);
        ImGui::InputInt("Search By ID", &search_id);
        if(!vars.player.buffs.names.empty()){
            if (ImGui::CollapsingHeader("Search Results")) {
                for(int i = 0; i<vars.player.buffs.names.size();i++) {
                    std::string buff = vars.player.buffs.names[i];
                    if (m_Filter && buff.find(std::to_string(search_id)) == std::string::npos) {
                        continue;
                    }
                    ImGui::Text("%s", buff.c_str());
                    ImGui::SameLine();
                    if (ImGui::Button((std::string("Add##") + std::to_string(i)).c_str())) {
                        vars.player.buffs.id = i + 1;
                        vars.player.buffs.add = true;
                    }

                }
            }
        }  else {
            ImGui::Text("Let Me Fill Buffs");
        }
    }

};