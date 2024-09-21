#pragma once

#include "PhysicsObject.h"

namespace KEIEngine::Graphics
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
        void SetRotationVelocity(const KEIEngine::KMath::Vector3& velocity);
        
        KMath::Vector3 GetPosition();
        KMath::Vector3 GetVelocity();

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