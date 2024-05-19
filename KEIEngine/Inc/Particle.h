#pragma once

namespace KEIEngine
{
	struct ParticleActivateData
	{
		float lifeTime = 0.0;
		Color startColor = Colors::White;
		Color endColor = Colors::White;
		KMath::Vector3 startScale = KMath::Vector3::One;
		KMath::Vector3 endScale = KMath::Vector3::One;
		KMath::Vector3 position = KMath::Vector3::Zero;
		KMath::Vector3 velocity = KMath::Vector3::Zero;
	};

	struct ParticleInfo
	{
		Color currentColor = Colors::White;
		KMath::Vector3 currentScale = KMath::Vector3::One;
	};
	class Particle
	{
	public:
		Particle() = default;

		void Initialize();
		void Terminate();

		void Activate(const ParticleActivateData& data);
		void Update(float deltaTime);

		bool IsActive() const;
		void GetCurrentInfo (ParticleInfo& info) const;
		const Graphics::Transform& GetTransform() const;

	private:
		Graphics::Transform mTransform;
		Physics::RigidBody mRigidBody;
		Physics::CollisionShape mCollisionShape;
		ParticleActivateData mData;

		float mLifeTime = 0.0f;
	};
}