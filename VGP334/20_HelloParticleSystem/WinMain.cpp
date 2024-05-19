#include <../KEIEngine/Inc/KEIEngine.h>
#include "GameState.h"



int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	KEIEngine::App& mainApp = KEIEngine::MainApp();
	mainApp.AddState<GameState>("GameState");

	KEIEngine::AppConfig config;
	config.appName = L"Hello Particle System";
	config.winWidth = 1280;
	config.winHeight = 780;
	config.debugDrawLimit = 100000;
	mainApp.Run(config);

	return(0);
}