#pragma once


namespace KEIEngine::Physics
{
    class CollisionShape final
    {
    public:
        CollisionShape() = default;
        ~CollisionShape();

        void InitializeEmpty();
        void InitializeBox(const KEIEngine::KMath::Vector3& halfExtents);
        void InitializeSphere(float radius);
        void InitializeHull(const KEIEngine::KMath::Vector3& halfExtents, const KEIEngine::KMath::Vector3& origin);
        void Terminate();

    private:
        btCollisionShape* mCollisionShape = nullptr;

        friend class RigidBody;
        btCollisionShape* GetCollisionShape() const { return mCollisionShape; }
    };
}