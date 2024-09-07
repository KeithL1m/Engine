#include "GameState.h"


using namespace KEIEngine;
using namespace KEIEngine::Graphics;
using namespace KEIEngine::KMath;
using namespace KEIEngine::Input;


void GameState::Initialize()
{
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