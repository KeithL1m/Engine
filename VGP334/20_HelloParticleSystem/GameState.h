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

	void OnExplosionEvent(const KEIEngine::Event* e);

private:
	void UpdateCameraControl(float deltaTime);

	KEIEngine::Graphics::Camera mCamera;
	KEIEngine::Graphics::DirectionalLight mDirectionalLight;

	KEIEngine::Graphics::ParticleEffect mParticleEffect;
	KEIEngine::ParticleSystem mParticleSystem;
	KEIEngine::FireworkParticleSystem mFireworks;

	KEIEngine::Audio::SoundId mSoundId;
	std::size_t mExplosionEventId;
	float mTime = 0.0f;
};