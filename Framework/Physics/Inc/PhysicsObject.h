#pragma once

class btRigidBody;

namespace KEIEngine::Physics
{
	class PhysicsObject
	{
	public: 
		PhysicsObject() = default;
		virtual ~PhysicsObject() = default;

	protected:
		friend class PhysicsWorld;
		// will sync the physics world with the graphics world
		virtual void Update() = 0;
		virtual btRigidBody* GetRigidBody() { return nullptr; }
	};
}