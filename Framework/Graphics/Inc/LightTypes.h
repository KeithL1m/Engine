#pragma once

#include "Colors.h"

namespace KEIEngine::Graphics
{
    struct DirectionalLight
    {
        KMath::Vector3 direction = KMath::Vector3::Zero;
        float padding = 0.0f;
        Color ambient = Colors::White;
        Color diffuse = Colors::White;
        Color specular = Colors::White;
    };

    struct PointLight
    {
        KMath::Vector3 direction = KMath::Vector3::Zero;
        float padding0 = 0.0f;
        KMath::Vector3 position = KMath::Vector3::Zero;
        float padding1 = 0.0f;
        Color ambient = Colors::White;
        Color diffuse = Colors::White;
        Color specular = Colors::White;
        float attenConstant = -1.0f;
        float attenLinear = 0.0f;
        float attenQuad = 0.0f;
        float padding2 = 0.0f;
    };
}
