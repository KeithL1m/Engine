#include <../Engine/Inc/KEIEngine.h>
#include "GameState.h"

using namespace KEIEngine;
int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config;
	config.appName = L"Hello Window";

	App myApp;
	myApp.AddState<GameState>("GameState");
	myApp.Run(config);
	
	return (0);
}