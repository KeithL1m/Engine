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
