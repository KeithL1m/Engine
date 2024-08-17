#pragma once

#include "Common.h"
#include "App.h"
#include "AppState.h"

#include "FireworkParticleSystem.h"
#include "Particle.h"
#include "ParticleSystem.h"

#include "Event.h"
#include "EventManager.h"

#include "GameObject.h"
#include "GameWorld.h"
#include "GameObjectFactory.h"
#include "GameObjectHandle.h"

// components
#include "Component.h"
#include "AnimatorComponent.h"
#include "CameraComponent.h"
#include "FPSCameraComponent.h"
#include "MeshComponent.h"
#include "ModelComponent.h"
#include "RenderObjectComponent.h"
#include "SoundBankComponent.h"
#include "SoundEffectComponent.h"
#include "TransformComponent.h"
#include "RigidBodyComponent.h"

// services
#include "Service.h"
#include "CameraService.h"
#include "RenderService.h"
#include "UpdateService.h"
#include "PhysicsService.h"

namespace KEIEngine
{
    App& MainApp();
}