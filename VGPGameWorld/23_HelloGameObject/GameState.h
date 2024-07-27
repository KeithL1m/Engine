#pragma once
#include <../KEIEngine/Inc/KEIEngine.h>


class GameState : public KEIEngine::AppState
{
public:
    ~GameState() = default;
    void Initialize() override;
    void Terminate() override;
    void Render() override;
    void Update(float deltaTime) override;
    void DebugUI() override;

private:

    void MoveRight();
    void OnSpacePressedEvent(const KEIEngine::Event* event);

    KEIEngine::Graphics::DirectionalLight mDirectionalLight;
    KEIEngine::Graphics::StandardEffect mStandardEffect;

    KEIEngine::GameObject mGameObject;
    KEIEngine::GameWorld mGameWorld;

};