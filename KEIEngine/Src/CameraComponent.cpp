#include "Precompiled.h"
#include "CameraComponent.h"

#include "GameObject.h"
#include "GameWorld.h"
#include "CameraService.h"

using namespace KEIEngine;
using namespace KEIEngine::Graphics;

void CameraComponent::Initialize()
{
    CameraService* cameraService = GetOwner().GetWorld().GetService<CameraService>();
    ASSERT(cameraService != nullptr, "CameraComponent: GameWorld needs a camera service");

    cameraService->Register(this);
}

void CameraComponent::Deserialize(const rapidjson::Value& value)
{
    if (value.HasMember("Position"))
    {
        const auto& pos = value["Position"].GetArray();
        float x = pos[0].GetFloat();
        float y = pos[1].GetFloat();
        float z = pos[2].GetFloat();
        mCamera.SetPosition({ x, y, z });
    }
    if (value.HasMember("LookAt"))
    {
        const auto& look = value["LookAt"].GetArray();
        float x = look[0].GetFloat();
        float y = look[1].GetFloat();
        float z = look[2].GetFloat();
        mCamera.SetLookAt({ x, y, z });
    }
}

void CameraComponent::Terminate()
{
    CameraService* cameraService = GetOwner().GetWorld().GetService<CameraService>();
    ASSERT(cameraService != nullptr, "CameraComponent: GameWorld needs a camera service");

    cameraService->Unregister(this);
}

Graphics::Camera& CameraComponent::GetCamera()
{
    return mCamera;

}

const Graphics::Camera& CameraComponent::GetCamera() const
{
    return mCamera;

}
