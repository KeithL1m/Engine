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

// components
#include "Component.h"
#include "CameraComponent.h"
#include "FPSCameraComponent.h"
#include "TransformComponent.h"

// services
#include "Service.h"
#include "CameraService.h"
#include "UpdateService.h"

namespace KEIEngine
{
    App& MainApp();
}