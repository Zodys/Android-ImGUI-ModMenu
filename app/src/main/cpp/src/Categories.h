#pragma once
#include "stuff/enum.h"
namespace Renderer{
    BETTER_ENUM(Category,int,Player,NPCs,Buffs,Items,Customization) //just for exaple

    void Player(){
        ImGui::Checkbox("Inf Mana And Health", &vars.player.more_mana_health);
        ImGui::Checkbox("Fast Mine", &vars.player.fast_pickaxe);
        ImGui::Checkbox("Print values", &vars.player.print_values);
    }

    char searchBuff[256];
    void Buffs(){
        if(!vars.player.buffs.names.empty()){
            ImGui::InputText("Search By Name / ID", searchBuff, IM_ARRAYSIZE(searchBuff));
            if (ImGui::CollapsingHeader("Search Results")) {
                for(int i = 0; i<vars.player.buffs.names.size();i++){
                    std::string buff = vars.player.buffs.names[i];
                    if(buff.find(searchBuff) != std::string::npos){
                        ImGui::Text("%s", buff.c_str()); ImGui::SameLine();
                        if (ImGui::Button((std::string("Add##") + std::to_string(i)).c_str())) {
                            vars.player.buffs.id = i + 1;
                            vars.player.buffs.add = true;
                        }
                    }
                }
            }
        }  else {
            ImGui::Text("Let Me Fill Buffs");
        }
    }

    char searchItem[256];
    void Items(){
        if(!vars.player.items.names.empty()){
            ImGui::InputText("Search By Name / ID", searchItem, IM_ARRAYSIZE(searchItem));
            ImGui::InputInt("Amount", &vars.player.items.amount);
            if (ImGui::CollapsingHeader("Search Results")) {
                for(int i = 0; i<vars.player.items.names.size();i++){
                    std::string item = vars.player.items.names[i];
                    if(item.find(searchItem) != std::string::npos){
                        ImGui::Text("%s", item.c_str()); ImGui::SameLine();
                        if (ImGui::Button((std::string("Add##") + std::to_string(i)).c_str())) {
                            vars.player.items.id = i + 1;
                            vars.player.items.add = true;
                        }
                    }
                }
            }
        }  else {
            ImGui::Text("Let Me Fill Items");
        }
    }
    void CategoryHandler(Category category){
        switch (category) {
            case Category::Player:
                Player();
                break;
            case Category::Buffs:
                Buffs();
                break;
            case Category::Items:
                Items();
                break;
            default:
                Player();
                break;
        }
    }
}