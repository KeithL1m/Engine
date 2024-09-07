#pragma once

#include <../KEIEngine/Inc/KEIEngine.h>

enum class CustomComponentId
{
    CustomDebugDraw = static_cast<uint32_t>(KEIEngine::ComponentId::Count)
};

enum class CustomServiceId
{
    CustomDebugDrawDisplay = static_cast<uint32_t>(KEIEngine::ServiceId::Count)
};