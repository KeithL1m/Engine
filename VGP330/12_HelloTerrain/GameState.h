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

    KEIEngine::Graphics::Camera mCamera;
    KEIEngine::Graphics::DirectionalLight mDirectionalLight;
    KEIEngine::Graphics::StandardEffect mStandardEffect;
    KEIEngine::Graphics::TerrainEffect mTerrainEffect;
    KEIEngine::Graphics::ShadowEffect mShadowEffect;

    KEIEngine::Graphics::RenderGroup mCharacter;
    KEIEngine::Graphics::RenderGroup mCharacter2;
    KEIEngine::Graphics::RenderObject mGround;
    KEIEngine::Graphics::Terrain mTerrain;

    KEIEngine::KMath::Vector3 mCharacterPosition;
    KEIEngine::KMath::Vector3 mCharacter2Position;
};