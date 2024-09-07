#include "Precompiled.h"
#include "TPSCameraComponent.h"

#include "CameraComponent.h"
#include "GameObject.h"

#include "GameWorld.h"
#include "UpdateService.h"

using namespace KEIEngine;
using namespace KEIEngine::Graphics;
using namespace KEIEngine::KMath;
using namespace KEIEngine::Input;

void TPSCameraComponent::Initialize()
{
    UpdateService* updateService = GetOwner().GetWorld().GetService<UpdateService>();
    ASSERT(updateService != nullptr, "TPSCameraComponent: game world requires an update service");
    updateService->Register(this);

    mCameraComponent = GetOwner().GetComponent<CameraComponent>();
}
void TPSCameraComponent::Terminate()
{
    UpdateService* updateService = GetOwner().GetWorld().GetService<UpdateService>();
    ASSERT(updateService != nullptr, "TPSCameraComponent: game world requires an update service");
    updateService->Unregister(this);

    mCameraComponent = nullptr;
}

void TPSCameraComponent::Update(float deltaTime)
{
}

void TPSCameraComponent::Deserialize(const rapidjson::Value& value)
{
}

