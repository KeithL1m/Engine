#include "Precompiled.h"
#include "KEIEngine.h"

KEIEngine::App& KEIEngine::MainApp()
{
	static App sApp;
	return sApp;
}