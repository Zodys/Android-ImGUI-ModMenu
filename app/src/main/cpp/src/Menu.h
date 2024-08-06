namespace Renderer{
    struct ScreenSize{
        int width;
        int height;
    };


    extern void SetupRender();
    extern void Render();
    extern void Resize(int width, int height);

    extern bool _initialized;

    void setUpKeyboard();

    void diasableKeys();

    void Menu();
}

