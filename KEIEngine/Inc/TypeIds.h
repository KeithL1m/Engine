#pragma once

namespace KEIEngine
{
    enum class ComponentId
    {
        Invalid,            // Invalid component id
        Transform,          // Transform for component, contains positional data
        Camera,             // Stationary camera information
        FPSCamera,          // Functionality for a camera to move
        Mesh,               // Render a mesh built shape

        Count
    };

    enum class ServiceId
    {
        Invalid,            // Invalid service id
        Camera,             // Registers and manages focus camera
        Update,             // Registers and updates any component that requires an update
        Render,             // Registers and renders any graphical components

        Count
    };
}

#define SET_TYPE_ID(id)\
    static uint32_t StaticGetTypeId() {return static_cast<uint32_t>(id);}\
    uint32_t GetTypeId() const override {return StaticGetTypeId(); }