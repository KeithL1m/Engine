#include "GameState.h"

#include "CustomDebugDrawComponent.h"
#include "CustomDebugDrawDisplayService.h"

using namespace KEIEngine;
using namespace KEIEngine::Graphics;
using namespace KEIEngine::KMath;
using namespace KEIEngine::Input;

namespace
{
    Component* CustomComponentMake(const std::string& componentName, GameObject& gameObject)
    {
        if (componentName == "CustomDebugDrawComponent")
        {
            return gameObject.AddComponent<CustomDebugDrawComponent>();
        }
        return nullptr;
    }
    Service* CustomServiceMake(const std::string& serviceName, GameWorld& gameWorld)
    {
        if (serviceName == "CustomDebugDrawDisplayService")
        {
            return gameWorld.AddService<CustomDebugDrawDisplayService>();
        }
        return nullptr;
    }
}

void GameState::Initialize()
{
    GameObjectFactory::SetCustomMake(CustomComponentMake);
    GameWorld::SetCustomService(CustomServiceMake);
    mGameWorld.LoadLevel("../../Assets/Templates/Levels/test_edit_level.json");
}
void GameState::Terminate()                                                                                              
{
    mGameWorld.Terminate();
}
void GameState::Render()
{
    mGameWorld.Render();

}
void GameState::Update(float deltaTime)
{
    mGameWorld.Update(deltaTime);
}
void GameState::DebugUI()
{
    SimpleDraw::AddGroundPlane(10.0f, Colors::White);
    ImGui::Begin("Debug Control", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        mGameWorld.DebugUI();
    ImGui::End();
}