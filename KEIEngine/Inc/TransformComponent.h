#pragma once

#include "Component.h"

namespace KEIEngine
{
    class TransformComponent final : public Component, public Graphics::Transform
    {
    public:
        SET_TYPE_ID(ComponentId::Transform);

        void DebugUI() override;
        void Serialize(rapidjson::Document& doc, rapidjson::Value& value);
        void Deserialize(const rapidjson::Value& value) override;
    };
}