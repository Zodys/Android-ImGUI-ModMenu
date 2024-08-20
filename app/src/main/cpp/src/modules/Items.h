//
// Created by 1 on 10.08.2024.
//
#pragma once
#include "../Module.h"
#include "../memory/Il2cppResolver/IL2CPP_Resolver.hpp"
#include "../stuff/Config.h"
class Items : public Module
{
public:
    Items() : Module("Items"){}

    void draw() override{} //for drawList

    void drawUI() override{
        static int search_id = 0;
        static bool m_Filter = false;
        ImGui::Checkbox("Filter",&m_Filter);
        ImGui::InputInt("Search By ID", &search_id);
        ImGui::InputInt("Amount", &vars.player.items.amount);
        if(!vars.player.items.names.empty()){
            if (ImGui::CollapsingHeader("Search Results")) {
                for(int i = 0; i<vars.player.items.names.size();i++) {
                    std::string item = vars.player.items.names[i];
                    if (m_Filter && item.find(std::to_string(search_id)) == std::string::npos) {
                        continue;
                    }
                    ImGui::Text("%s", item.c_str());
                    ImGui::SameLine();
                    if (ImGui::Button((std::string("Add##") + std::to_string(i)).c_str())) {
                        vars.player.items.id = i + 1;
                        vars.player.items.add = true;
                    }

                }
            }
        }  else {
            ImGui::Text("Let Me Fill Items");
        }
    }

};