#pragma once

#include "PhysicsObject.h"

namespace KEIEngine::Physics
{
	struct Transform;
}

namespace KEIEngine::Physics
{
	class CollisionShape;

	class RigidBody final : public PhysicsObject
	{
	public:
		RigidBody() = default;
		~RigidBody() override;

		void Initialize(KEIEngine::Graphics::Transform& graphicsTransform, const CollisionShape& shape, float mass = 0.0f);
		void Terminate();

		void SetPosition(const KEIEngine::KMath::Vector3& position);
		void SetVelocity(const KEIEngine::KMath::Vector3& velocity);

		bool IsDynamic() const;
	protected:
		void Update() override;

		btRigidBody* GetRigidBody() override;

		btRigidBody* mRigidBody = nullptr;
		btDefaultMotionState* mMotionState = nullptr;
		float mMass = 0.0f;

		KEIEngine::Graphics::Transform* mGraphicsTransform = nullptr;
	};
}