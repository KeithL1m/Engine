#include "Precompiled.h"
#include "RigidBody.h"
#include "PhysicsWorld.h"
#include "CollisionShape.h"

#include <Graphics/Inc/Transform.h>

using namespace KEIEngine;
using namespace KEIEngine::Physics;
using namespace KEIEngine::Graphics;

RigidBody::~RigidBody()
{
    ASSERT(mRigidBody == nullptr, "RigidBody: Terminate must be called!");
}

void RigidBody::Initialize(KEIEngine::Graphics::Transform& graphicsTransform, const CollisionShape& shape, float mass)
{
    mGraphicsTransform = &graphicsTransform;
    mMass = mass;

    mMotionState = new btDefaultMotionState(ConvertTobtTransform(graphicsTransform));
    mRigidBody = new btRigidBody(mMass, mMotionState, shape.GetCollisionShape());
    // add bounce
    //mRigidBody->setRestitution(1.5f);
    //PhysicsWorld::Get()->Register(this);
}

void RigidBody::Terminate()
{
    //PhysicsWorld::Get()->Unregister(this);
    SafeDelete(mRigidBody);
    SafeDelete(mMotionState);
}

void RigidBody::SetPosition(const KEIEngine::KMath::Vector3& position)
{
    if (IsDynamic())
    {
        mRigidBody->activate();
    }
    mGraphicsTransform->position = position;
    mRigidBody->setWorldTransform(ConvertTobtTransform(*mGraphicsTransform));
}

void RigidBody::SetVelocity(const KEIEngine::KMath::Vector3& velocity)
{
    mRigidBody->activate();
    mRigidBody->setLinearVelocity(ConvertTobtVector3(velocity));
}
void RigidBody::SetRotationVelocity(const KEIEngine::KMath::Vector3& velocity)
{
    mRigidBody->activate();
    mRigidBody->setAngularVelocity(ConvertTobtVector3(velocity));
}

KMath::Vector3 RigidBody::GetVelocity()
{
    return ConvertToVector3(mRigidBody->getLinearVelocity());
}

KMath::Vector3 RigidBody::GetPosition()
{
    return ConvertToVector3(mRigidBody->getWorldTransform().getOrigin());
}

bool RigidBody::IsDynamic() const
{
    return mMass > 0.0f;
}

void RigidBody::Update()
{
    btTransform& worldTransform = mRigidBody->getWorldTransform();
    mGraphicsTransform->position = ConvertToVector3(worldTransform.getOrigin());
    mGraphicsTransform->rotation = ConvertToQuaternion(worldTransform.getRotation());
}

btRigidBody* RigidBody::GetRigidBody()
{
    return mRigidBody;
}


