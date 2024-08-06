#include <thread>
#include <KittyInclude.hpp>
#include <dobby.h>
#include <android/input.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_android.h>
#include <imgui_internal.h>
#include "memory/Il2cppResolver/IL2CPP_Resolver.hpp"
#include "Hooks.h"
#include "Main.h"
#include "Menu.h"
#include "stuff/logger.h"
#include "stuff/Config.h"
using namespace std;
using namespace KittyMemory;

ElfScanner g_il2cppBaseMap;

bool isFirstStart = false;
Unity::System_String *(*GetBuffName)(int);

Unity::System_String *(*old_GetItemNameValue)(int);
Unity::System_String  *_GetItemNameValue(int id) {
    if (!isFirstStart) {
        for(int i = 1; i <= 328 ; i++) {
            std::string name = GetBuffName(i)->ToString() + " - " + to_string(i);
            vars.player.buffs.names.push_back(name);
        }
        for(int i = 1; i <= 5124 ; i++) {
            std::string name = old_GetItemNameValue(i)->ToString() + " - " + to_string(i);

            vars.player.items.names.push_back(name);
        }
        isFirstStart = true;
    }
    return old_GetItemNameValue(id);
}

void (*old_Player_Update)(void*);
void _Player_Update(void *_this) {
    if(_this != nullptr){
        if(vars.player.buffs.add) {
            IL2CPP::Class::Utils::InvokeMethod<void>(_this,"Terraria.Player","AddBuff",vars.player.buffs.id,10800,true,false);
            vars.player.buffs.add = false;
        }
        if(vars.player.items.add) {
            IL2CPP::Class::Utils::InvokeMethod<void>(_this,"Terraria.Player","QuickSpawnItem",vars.player.items.id, vars.player.items.amount);
            vars.player.items.add = false;
        }
        if(vars.player.fast_pickaxe){
            IL2CPP::Class::Utils::SetFieldValue(_this, "Terraria.Player","pickSpeed",0.001f);
        }
        if(vars.player.more_mana_health) {

            IL2CPP::Class::Utils::SetFieldValue(_this, "Terraria.Player", "statMana", 20000);
            IL2CPP::Class::Utils::SetFieldValue(_this, "Terraria.Player", "statDefense", 100000);
            IL2CPP::Class::Utils::SetFieldValue(_this, "Terraria.Player", "statLife", 1000000);
        }
        if(vars.player.print_values){
            int statMana = IL2CPP::Class::Utils::GetFieldValue<int>(_this,"Terraria.Player", "statMana");
            int statDefense = IL2CPP::Class::Utils::GetFieldValue<int>(_this,"Terraria.Player", "statDefense");
            int statLife = IL2CPP::Class::Utils::GetFieldValue<int>(_this,"Terraria.Player", "statLife");
            Unity::System_String* name = IL2CPP::Class::Utils::GetFieldValue<Unity::System_String*>(_this,"Terraria.Player", "name");
            LOGI("statMana %i | statDefense %i | statLife %i | | name %s",statMana,statDefense,statLife, name->ToString().c_str());

            vars.player.print_values = false;
        }

    }
    old_Player_Update(_this);
}



void main_thread(){
    do {
        sleep(1);
        g_il2cppBaseMap = ElfScanner::createWithPath("libil2cpp.so");
    } while (!g_il2cppBaseMap.isValid());

    auto unityELF = ElfScanner::createWithPath("libunity.so");
    RegisterNativeFn nativeInjectEvent = KittyScanner::findRegisterNativeFn(unityELF, "nativeInjectEvent");
    if(nativeInjectEvent.isValid()) {
        DobbyHook(reinterpret_cast<void*>(nativeInjectEvent.fnPtr), reinterpret_cast<void*>(touchHook),reinterpret_cast<void**>(&origtouchHook));
    }
    if (!IL2CPP::Initialize()) {
        LOGE("IL2CPP initialization failed.");
    }
    sleep(1);
    void* Player_Update_NPCCollision = IL2CPP::Class::Utils::GetMethodPointer("Terraria.Player","Update_NPCCollision");
    void* Lang_GetItemNameValue = IL2CPP::Class::Utils::GetMethodPointer("Terraria.Lang","GetItemNameValue");

    GetBuffName = (Unity::System_String*(*) (int)) IL2CPP::Class::Utils::GetMethodPointer("Terraria.Lang", "GetBuffName");
    DobbyHook((void*)Player_Update_NPCCollision,(void*)&_Player_Update,(void**)&old_Player_Update);
    DobbyHook((void*)Lang_GetItemNameValue,(void*)&_GetItemNameValue,(void**)&old_GetItemNameValue);
}

namespace game {
    namespace hook {
        void init() {
            thread(main_thread).detach();
        }
    }
}