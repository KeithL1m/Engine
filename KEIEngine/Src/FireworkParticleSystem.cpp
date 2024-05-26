#include "Precompiled.h"
#include "FireworkParticleSystem.h"

using namespace KEIEngine;
using namespace KEIEngine::Graphics;
using namespace KEIEngine::KMath;

void FireworkParticle::Initialize()
{
	Particle::Initialize();

	ParticleSystemInfo info;
	info.spawnDelay = 0.0f;
	info.systemLifeTime = 0.0f;
	info.minParticlePerEmit = 20;
	info.maxParticlePerEmit = 30;
	info.minSpawnAngle = -180.0f * 3.141592 / 180.0f;
	info.maxSpawnAngle = 180.0f * 3.141592 / 180.0f;
	info.minSpeed = 5.0f;
	info.maxSpeed = 10.0f;
	info.minLifeTime = 0.5f;
	info.maxLifeTime = 1.0f;
	info.minStartColor = Colors::Red;
	info.maxStartColor = Colors::OrangeRed;
	info.minEndColor = Colors::White;
	info.maxEndColor = Colors::LightYellow;
	info.minStartScale = KMath::Vector3::One;
	info.maxStartScale = KMath::Vector3::One;
	info.minEndScale = KMath::Vector3::Zero;
	info.maxEndScale = KMath::Vector3::Zero;
	info.maxParticles = 50;
	info.particleTextureId = TextureManager::Get()->LoadTexture("Images/bullet2.png");
	mExplosionEffect.Initialize(info);
}

void FireworkParticle::Terminate()
{
	Particle::Terminate();
	mExplosionEffect.Terminate();
}

void FireworkParticle::Activate(const ParticleActivateData& data)
{
	Particle::Activate(data);
}

void FireworkParticle::Update(float deltaTime)
{
	if (mLifeTime > 0.0f)
	{
		Particle::Update(deltaTime);
		if (mLifeTime < 0.0f)
		{
			OnDeath();
		}
	}

	if (mExplosionEffect.IsActive())
	{
		mExplosionEffect.Update(deltaTime);
	}
}

void FireworkParticle::OnDeath()
{
	mExplosionEffect.SetPosition(mTransform.position);
	mExplosionEffect.SpawnParticles();
}

void FireworkParticle::SetCamera(const Graphics::Camera camera)
{
	mExplosionEffect.SetCamera(camera);
}

void FireworkParticleSystem::SetCamera(const Graphics::Camera& camera)
{
	ParticleSystem::SetCamera(camera);
	for (auto& p : mParticles)
	{
		FireworkParticle* fp = static_cast<FireworkParticle*>(p.get());
		fp->SetCamera(camera);
	}
}

void FireworkParticleSystem::InitializeParticles(uint32_t count)
{
	mParticleIndexes.resize(count);
	mParticles.resize(count);
	for (uint32_t i = 0; i < count; ++i)
	{
		mParticleIndexes[i] = i;
		mParticles[i] = std::make_unique<FireworkParticle>();
		mParticles[i]->Initialize();
	}
}
