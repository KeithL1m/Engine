#pragma once

#include <../KEIEngine/Inc/KEIEngine.h>
#include "TypeIds.h"

class CustomDebugDrawComponent : public KEIEngine::Component
{
public:
    SET_TYPE_ID(CustomComponentId::CustomDebugDraw);

    void Initialize() override;
    void Terminate() override;

    void Update(float deltaTime) override;

    void AddDebugDraw();
    void Deserialize(const rapidjson::Value& value) override;

private:
    const KEIEngine::TransformComponent* mTransformComponent;
    KEIEngine::KMath::Vector3 mPosition = KEIEngine::KMath::Vector3::Zero;
    KEIEngine::Color mColor = KEIEngine::Colors::White;
    uint32_t mSlices = 0;
    uint32_t mRings = 0;
    float mRadius = 0.0f;
};