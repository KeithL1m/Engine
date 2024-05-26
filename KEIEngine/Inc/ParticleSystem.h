#pragma once

#include "Particle.h"

namespace KEIEngine
{
	struct ParticleSystemInfo
	{
		KMath::Vector3 spawnPosition = KMath::Vector3::Zero;
		KMath::Vector3 spawnDirection = KMath::Vector3::YAxis;
		float spawnDelay = 0.0f;
		float systemLifeTime = 0.0f;
		int minParticlePerEmit = 0;
		int maxParticlePerEmit = 0;
		float minTimeBetweenEmit = 0.0f;
		float maxTimeBetweenEmit = 0.0f;
		float minSpawnAngle = 0.0f;
		float maxSpawnAngle = 0.0f;
		float minSpeed = 0.0f;
		float maxSpeed = 0.0f;
		float minLifeTime = 0.0f;
		float maxLifeTime = 0.0f;
		Color minStartColor = Colors::White;
		Color maxStartColor = Colors::White;
		Color minEndColor = Colors::White;
		Color maxEndColor = Colors::White;
		KMath::Vector3 minStartScale = KMath::Vector3::One;
		KMath::Vector3 maxStartScale = KMath::Vector3::One;
		KMath::Vector3 minEndScale = KMath::Vector3::One;
		KMath::Vector3 maxEndScale = KMath::Vector3::One;
		int maxParticles = 100;
		Graphics::TextureId particleTextureId = 0;
		bool startPlaying = true;
	};

	class ParticleSystem
	{
	public:
		ParticleSystem() = default;
		~ParticleSystem() = default;

		virtual void Initialize(const ParticleSystemInfo& info);
		virtual void Terminate();
		virtual void Update(float deltaTime);

		void Play(float lifeTime);
		void SetPosition(const KMath::Vector3& position);
		bool IsActive() const;

		void DebugUI();

		virtual void SetCamera(const Graphics::Camera& camera);

		template<class Effect>
		void Render(Effect& effect)
		{
			if (IsActive())
			{
				ParticleInfo particleInfo;
				for (const auto& particle : mParticles)
				{
					if (particle->IsActive())
					{
						particle->GetCurrentInfo(particleInfo);
						mRenderObject.transform = particle->GetTransform();
						mRenderObject.transform.scale = particleInfo.currentScale;
						effect.Render(mRenderObject, particleInfo.currentColor);
					}
				}
			}
		}

		void SpawnParticles();
	protected:
		virtual void InitializeParticles(uint32_t count);
		void SpawnParticle();

		//particles
		using Particles = std::vector<std::unique_ptr<Particle>>;
		Particles mParticles;
		std::vector<int> mParticleIndexes;

		// render info
		Graphics::RenderObject mRenderObject;
		const Graphics::Camera* mCamera = nullptr;

		// particle system info
		ParticleSystemInfo mInfo;
		int mNextAvailableParticleIndex = 0;
		float mNextSpawnTime = 0.0f;
		float mLifeTime = 0.0f;
	};
}