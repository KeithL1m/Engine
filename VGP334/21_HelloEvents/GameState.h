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
    void UpdateCameraControl(float deltaTime);

    void MoveRight();
    void OnSpacePressedEvent(const KEIEngine::Event* event);

    KEIEngine::Graphics::Camera mCamera;
    KEIEngine::Graphics::DirectionalLight mDirectionalLight;
    KEIEngine::Graphics::StandardEffect mStandardEffect;

    KEIEngine::Graphics::RenderObject mBall;
    KEIEngine::Graphics::RenderObject mGround;

    //animation
    KEIEngine::KMath::Vector3 mOffset = KEIEngine::KMath::Vector3::Zero;
    KEIEngine::Graphics::Animation mAnimation;
    float mAnimationTime = 0.0f;
};