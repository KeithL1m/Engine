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
	void ChangeAnimation();
	void ChangeToEndAnimation();
	void MoveUP();

	KEIEngine::Graphics::Camera mCamera;
	KEIEngine::Graphics::DirectionalLight mDirectionalLight;
	KEIEngine::Graphics::StandardEffect mStandardEffect;

	KEIEngine::Graphics::RenderObject mGround;

	KEIEngine::Graphics::RenderObject mDisco;
	// CHARACTER
	KEIEngine::Graphics::ModelId mCharacterId;
	KEIEngine::Graphics::RenderGroup mCharacter;
	KEIEngine::Graphics::Animator mCharacterAnimator;
	KEIEngine::KMath::Vector3 mCharacterPosition;

	KEIEngine::Graphics::ModelId mCharacterId2;
	KEIEngine::Graphics::RenderGroup mCharacter2;
	KEIEngine::Graphics::Animator mCharacterAnimator2;
	KEIEngine::KMath::Vector3 mCharacter2Position;

	// PARTICLE EFFECTS
	KEIEngine::Graphics::ParticleEffect mParticleEffect;
	KEIEngine::FireworkParticleSystem mFireworks;
	KEIEngine::ParticleSystem mSparkles;

	// ANIMATION
	KEIEngine::KMath::Vector3 mOffset = KEIEngine::KMath::Vector3::Zero;
	KEIEngine::Graphics::Animation mAnimation;
	KEIEngine::Graphics::Animation mAnimationCharacter;
	float mAnimationTime = 0.0f;
	float mAnimationCharacterTime = 0.0f;

	// SOUND
	KEIEngine::Audio::SoundId mSoundID;

	int mAnimationIndex = -1;
	bool mDrawSkeleton = false;
	float mTime = 0.0f;
};