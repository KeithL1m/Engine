#include "GameState.h"

using namespace KEIEngine;
using namespace KEIEngine::Graphics;
using namespace KEIEngine::KMath;
using namespace KEIEngine::Input;

void GameState::Initialize()
{
    mDirectionalLight.direction = KMath::Normalize({ 1.0f,-1.0f,1.0f });
    mDirectionalLight.ambient = { 0.5f, 0.5f,0.5f,1.0f };
    mDirectionalLight.diffuse = { 0.8f, 0.8f,0.8f,1.0f };
    mDirectionalLight.specular = { 1.0f, 1.0f,1.0f,1.0f };

    mGameWorld.AddService<CameraService>();
    mGameWorld.AddService<UpdateService>();
    mGameWorld.Initialize();

    mGameWorld.AddGameObject(&mGameObject);

    mGameObject.AddComponent<TransformComponent>();
    CameraComponent* cc = mGameObject.AddComponent<CameraComponent>();
    mGameObject.AddComponent<FPSCameraComponent>();
    mGameObject.Initialize();
    std::string name = "GameObject1";
    mGameObject.SetName(name);


    mStandardEffect.Initialize(L"../../Assets/Shaders/Standard.fx");
    mStandardEffect.SetCamera(cc->GetCamera());
    mStandardEffect.SetDirectionalLight(mDirectionalLight);
};
void GameState::Terminate()
{
    mGameObject.Terminate();
    mStandardEffect.Terminate();

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