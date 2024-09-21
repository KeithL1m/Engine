#pragma once

#include <../KEIEngine/Inc/KEIEngine.h>
#include "TypeIds.h"

namespace KEIEngine
{
    class CameraComponent;

    class TPSCameraComponent final : public KEIEngine::Component
    {
    public:
        SET_TYPE_ID(ComponentId::TPSCamera);

        void Initialize() override;
        void Deserialize(const rapidjson::Value& value) override;
        void Terminate() override;
        void Update(float deltaTime) override;

    private:
        KEIEngine::CameraComponent* mCameraComponent = nullptr;
        KEIEngine::RigidBodyComponent* mCharacterRigidBody = nullptr;
        const KEIEngine::TransformComponent* mTransformComponent = nullptr;

        float mShiftSpeed = 10.0f;
        float mMoveSpeed = 1.0f;
        float mTurnSpeed = 0.1f;
    };
}
