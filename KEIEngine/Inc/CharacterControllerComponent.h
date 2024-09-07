#pragma once

#include "Component.h"

namespace KEIEngine
{
	class CharacterControllerComponent : public Component
	{
	public:
		SET_TYPE_ID(ComponentId::CharacterController);

		void Initialize() override;
		void Terminate() override;
		void Update(float deltaTime) override;
		void DebugUI() override;
		void Deserialize(const rapidjson::Value& value) override;

		// function that is called to make character roll
		void CharacterRoll();

	private:
		float mMovementSpeed = 0.0f;
	};
}
