#include "GameState.h"

using namespace KEIEngine;
using namespace KEIEngine::Graphics;
using namespace KEIEngine::KMath;
using namespace KEIEngine::Input;

void GameState::Initialize()
{
    CameraService* cs = mGameWorld.AddService<CameraService>();
    mGameWorld.AddService<UpdateService>();
    mGameWorld.AddService<RenderService>();
    mGameWorld.Initialize();

    mGameWorld.AddGameObject(&mCameraObject);
    mGameWorld.AddGameObject(&mTestGameObject);

    GameObjectFactory::Make("../../Assets/Templates/fps_camera.json", mCameraObject);
    mCameraObject.Initialize();
    std::string name = "CameraObject";
    mCameraObject.SetName(name);

    // Game Object Factory
    GameObjectFactory::Make("../../Assets/Templates/test_object.json", mTestGameObject);
    name = "test_object";
    mTestGameObject.SetName(name);
    mTestGameObject.Initialize();
};
void GameState::Terminate()
{
    mCameraObject.Terminate();
    mTestGameObject.Terminate();

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