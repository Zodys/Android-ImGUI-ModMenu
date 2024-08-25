# A simple template for your mods :3
# Features
* Infinity Mana And Health.
* Fast Mine.
* Add Buffs.
* Add Items.
# Code
* [Modules](https://github.com/Zodys/Android-ImGUI-ModMenu/tree/master/app/src/main/cpp/src/modules) - menu tabs
* [Hooks](https://github.com/Zodys/Terraria-ImGUI/blob/master/app/src/main/cpp/src/Hooks.cpp) - example of hook functions with il2cpp resolver
* [Menu](https://github.com/Zodys/Terraria-ImGUI/blob/master/app/src/main/cpp/src/Menu.cpp) - setup menu
# How to add in unity game
* Add this to OnCreate in UnityPlayerActivity.smali:
```
const-string v0, "zodys"
invoke-static {v0}, Ljava/lang/System;->loadLibrary(Ljava/lang/String;)V
invoke-static {p0}, Lcom/zodys/gui/Surface;->Start(Landroid/content/Context;)V
```
# Credits
* [ImGui](https://github.com/ocornut/imgui) by ocornut
* [DobbyHook](https://github.com/jmpews/Dobby) by jmpwes
* [KittyMemory](https://github.com/MJx0/KittyMemory) by MJx0
* [IL2CPP_Resolver](https://github.com/sneakyevil/IL2CPP_Resolver) by sneakyevil
* [IL2CPP_Resolver_Easy_Template](https://github.com/Piotrixek/IL2CPP_Resolver_Easy_Template) by Piotrixek
