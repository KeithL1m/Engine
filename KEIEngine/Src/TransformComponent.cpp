#include "Precompiled.h"
#include "TransformComponent.h"

using namespace KEIEngine;
using namespace KEIEngine::Graphics;

void TransformComponent::DebugUI()
{
	SimpleDraw::AddTransform(GetMatrix4());
}
