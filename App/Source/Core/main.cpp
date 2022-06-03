#include "pch.h"
#include "Application.h"

int main()
{
#if defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    Application* app = new Application();
    app->Run();
    delete app;

    return 0;
}