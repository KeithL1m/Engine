#pragma once

#include "Component.h"

namespace KEIEngine
{
	class RigidBodyComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentId::RigidBody);

		void Initialize() override;
		void Terminate() override;
		void Deserialize(const rapidjson::Value& value);

		void SetPosition(const KMath::Vector3& position);
		void SetVelocity(const KMath::Vector3& velocity);
	private:
		friend class PhysicsService;
		Physics::CollisionShape mCollisionShape;
		Physics::RigidBody mRigidBody;
		float mMass = -1.0f;
	};
}