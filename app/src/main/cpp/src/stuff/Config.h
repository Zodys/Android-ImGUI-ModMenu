#pragma once

#include <imgui.h>
#include "json.hpp"

using namespace std;

struct Settings {
    struct {
        bool fly;
        bool more_mana_health;
        bool light;
        bool fast_pickaxe;
        bool print_values;
        struct {
            int id;
            bool add;
            std::vector<std::string> names;
        } buffs;
        struct {
            int id;
            int amount;
            bool add;
            std::vector<std::string> names;
        } items;

    } player;
};
extern Settings vars;
