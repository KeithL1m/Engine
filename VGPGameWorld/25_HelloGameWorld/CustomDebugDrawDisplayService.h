#pragma once

#include <../KEIEngine/Inc/KEIEngine.h>

#include "TypeIds.h"

class CustomDebugDrawComponent;

class CustomDebugDrawDisplayService : public KEIEngine::Service
{
public:
    SET_TYPE_ID(CustomServiceId::CustomDebugDrawDisplay);

    void Render() override;

    void Register(CustomDebugDrawComponent* debugDrawComponent);
    void Unregister(CustomDebugDrawComponent* debugDrawComponent);

private:
    using CustomDebugDrawComponents = std::vector<CustomDebugDrawComponent*>;
    CustomDebugDrawComponents mCustomDebugDrawComponents;
};