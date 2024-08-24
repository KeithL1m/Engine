#pragma once

#include "Component.h"

namespace KEIEngine
{
    class UIComponent : public Component
    {
    public:
        virtual void Render() = 0;
    };
}