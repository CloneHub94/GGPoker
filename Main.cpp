#include "Common.hpp"
#include "Core.hpp"

using namespace Green;

void MainThread()
{
    g_Logger = std::make_unique<Logger>();
    auto injectStr = skCrypt("GGPoker injected.");
    g_Logger->Info(injectStr);
    injectStr.clear();

    g_Core = std::make_unique<Core>();
    auto coreStr = skCrypt("g_Core Initialized.");
    g_Logger->Info(coreStr);
    coreStr.clear();

    while (g_Running)
    {
        if (IsKeyPressed(0x50))
            g_Running = false;

        std::this_thread::sleep_for(3ms);
        std::this_thread::yield();
    }

    std::this_thread::sleep_for(500ms);

    auto unloadStr = skCrypt("GGPoker unloaded.");
    g_Logger->Info(unloadStr);
    unloadStr.clear();
    g_Logger.reset();

    FreeLibraryAndExitThread(g_Module, 0);
}

BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD reason, LPVOID reserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        Beep(220, 100);
        g_Module = hInstance;

        _beginthread((_beginthread_proc_type)MainThread, 0, NULL);
    }

    return TRUE;
}