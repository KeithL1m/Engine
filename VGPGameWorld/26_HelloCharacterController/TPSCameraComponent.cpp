#include "TPSCameraComponent.h"

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

    mCharacterPosition = GetOwner().GetComponent<TransformComponent>();
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
    Camera& camera = mCameraComponent->GetCamera();

    
}

void TPSCameraComponent::Deserialize(const rapidjson::Value& value)
{
    if (value.HasMember("MoveSpeed"))
    {
        mMoveSpeed = value["MoveSpeed"].GetFloat();
    }
    if (value.HasMember("TurnSpeed"))
    {
        mTurnSpeed = value["TurnSpeed"].GetFloat();
    }
    if (value.HasMember("ShiftSpeed"))
    {
        mShiftSpeed = value["ShiftSpeed"].GetFloat();
    }
}

