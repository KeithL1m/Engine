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

	KEIEngine::Graphics::Mesh mClothMesh;
	KEIEngine::Graphics::RenderObject mCloth;
	KEIEngine::Physics::SoftBody mClothSB;
};