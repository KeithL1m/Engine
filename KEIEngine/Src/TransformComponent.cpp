#include "Precompiled.h"
#include "TransformComponent.h"

using namespace KEIEngine;
using namespace KEIEngine::Graphics;

void TransformComponent::DebugUI()
{
    SimpleDraw::AddTransform(GetMatrix4());
}

void TransformComponent::Deserialize(const rapidjson::Value& value)
{
    if (value.HasMember("Position"))
    {
        const auto& pos = value["Position"].GetArray();
        position.x = pos[0].GetFloat();
        position.y = pos[1].GetFloat();
        position.z = pos[2].GetFloat();
    }
    if (value.HasMember("Rotation"))
    {
        const auto& rot = value["Rotation"].GetArray();
        rotation.x = rot[0].GetFloat();
        rotation.y = rot[1].GetFloat();
        rotation.z = rot[2].GetFloat();
        rotation.w = rot[3].GetFloat();
    }
    if (value.HasMember("Scale"))
    {
        const auto& s = value["Scale"].GetArray();
        scale.x = s[0].GetFloat();
        scale.y = s[1].GetFloat();
        scale.z = s[2].GetFloat();
    }
}