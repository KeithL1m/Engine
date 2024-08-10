#include <../KEIEngine/Inc/KEIEngine.h>
#include "GameState.h"



int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    KEIEngine::App& mainApp = KEIEngine::MainApp();
    mainApp.AddState<GameState>("GameState");

    KEIEngine::AppConfig config;
    config.appName = L"Hello Game World";
    config.winWidth = 1280;
    config.winHeight = 780;
    mainApp.Run(config);

    return(0);
}