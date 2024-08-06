# Code
* [Categories](Categories.h) - menu tabs
* [Hooks](Hooks.cpp) - example of hook functions with il2cpp resolver
* [Menu](Menu.cpp) - setup menu
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
* [Better Enums](https://github.com/aantron/better-enums) by aantron
