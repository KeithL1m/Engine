#pragma once
#include <../KEIEngine/Inc/KEIEngine.h>
#include "TypeIds.h"

namespace KEIEngine
{
	class CharacterControllerComponent : public KEIEngine::Component
	{
	public:
		SET_TYPE_ID(ComponentId::CharacterController);

		void Initialize() override;
		void Terminate() override;
		void Update(float deltaTime) override;

		// function that is called to make character roll
		void CharacterRoll();

	private:
		float mMovementSpeed = 0.0f;
		int mCurrentAnimationIndex = 0;
		bool mIsRolling = false;
		KEIEngine::AnimatorComponent* mCharacterAnimation = nullptr;
		KEIEngine::RigidBodyComponent* mCharacterRigidBody = nullptr;
		KEIEngine::TransformComponent* mCharacterTransform = nullptr;
	};
}
