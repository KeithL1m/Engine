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
	KEIEngine::Graphics::Mesh mSphere;
	KEIEngine::Graphics::RenderObject mEarth;
	KEIEngine::Graphics::StandardEffect mStandardEffect;

	KEIEngine::Graphics::Camera mRenderTargetCamera;
	KEIEngine::Graphics::RenderTarget mRenderTarget;

	bool mUseCelShading = false;
	KEIEngine::Graphics::StandardEffect mCelShadingEffect;
};