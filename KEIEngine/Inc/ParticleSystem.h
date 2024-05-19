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
	};

	class ParticleSystem
	{
	public:
		ParticleSystem() = default;
		~ParticleSystem() = default;

		void Initialize(const ParticleSystemInfo& info);
		void Terminate();
		void Update(float deltaTime);

		void DebugUI();

		void SetCamera(Graphics::Camera camera);

		template<class Effect>
		void Render(Effect& effect)
		{
			if (mLifeTime > 0.0f)
			{
				ParticleInfo particleInfo;
				for (const Particle& particle : mParticles)
				{
					if (particle.IsActive())
					{
						particle.GetCurrentInfo(particleInfo);
						mRenderObject.transform = particle.GetTransform();
						mRenderObject.transform.scale = particleInfo.currentScale;
						effect.Render(mRenderObject, particleInfo.currentColor);
					}
				}
			}
		}

	private:
		void SpawnParticles();
		void SpawnParticle();

		//particles
		using Particles = std::vector<Particle>;
		Particles mParticles;
		std::vector<int> mParticleIndexes;

		// render info
		Graphics::RenderObject mRenderObject;
		const Graphics::Camera* mCamera = nullptr;

		// particle system info
		ParticleSystemInfo mInfo;
		int mNextAvailableParticleIndex;
		float mNextSpawnTime = 0.0f;
		float mLifeTime = 0.0f;
	};
}