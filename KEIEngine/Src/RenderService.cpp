#include "Precompiled.h"
#include "RenderService.h"

#include "GameWorld.h"

#include "CameraService.h"
#include "AnimatorComponent.h"
#include "RenderObjectComponent.h"
#include "TransformComponent.h"

using namespace KEIEngine;
using namespace KEIEngine::Graphics;

void RenderService::Initialize()
{
    mCameraService = GetWorld().GetService<CameraService>();
    mDirectionalLight.direction = KMath::Normalize({ 1.0f,-1.0f,1.0f });
    mDirectionalLight.ambient = { 0.5f, 0.5f,0.5f,1.0f };
    mDirectionalLight.diffuse = { 0.8f, 0.8f,0.8f,1.0f };
    mDirectionalLight.specular = { 1.0f, 1.0f,1.0f,1.0f };

    mShadowEffect.Initialize();
    mShadowEffect.SetDirectionalLight(mDirectionalLight);

    mStandardEffect.Initialize(L"../../Assets/Shaders/Standard.fx");
    mStandardEffect.SetDirectionalLight(mDirectionalLight);
    mStandardEffect.SetLightCamera(mShadowEffect.GetLightCamera());
    mStandardEffect.SetShadowMap(mShadowEffect.GetDepthMap());
}

void RenderService::Terminate()
{
    mStandardEffect.Terminate();
    mShadowEffect.Terminate();
}

void RenderService::Update(float deltaTime)
{
    mFPS = 1.0f / deltaTime;
}

void RenderService::Render()
{
    const Camera& camera = mCameraService->GetMain();
    mStandardEffect.SetCamera(camera);
    for (Entry& entry : mRenderEntries)
    {
        for (RenderObject& renderObject : entry.renderGroup)
        {
            renderObject.transform = *entry.transformComponent;
        }
    }

    mShadowEffect.Begin();
    for (Entry& entry : mRenderEntries)
    {
        if (entry.castShadow)
        {
            DrawRenderGroup(mShadowEffect, entry.renderGroup);
        }
        }
    mShadowEffect.End();

    mStandardEffect.Begin();
    for (Entry& entry : mRenderEntries)
    {
        DrawRenderGroup(mStandardEffect, entry.renderGroup);
    }
    mStandardEffect.End();
}

void RenderService::DebugUI()
{
    ImGui::Text("FPS: %f", mFPS);
    if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ImGui::DragFloat3("Direction", &mDirectionalLight.direction.x, 0.01f))
        {
            mDirectionalLight.direction = KMath::Normalize(mDirectionalLight.direction);
        }

        ImGui::ColorEdit4("Ambient##Light", &mDirectionalLight.ambient.r);
        ImGui::ColorEdit4("Diffuse##Light", &mDirectionalLight.diffuse.r);
        ImGui::ColorEdit4("Specular##Light", &mDirectionalLight.specular.r);
    }
    mStandardEffect.DebugUI();
    mShadowEffect.DebugUI();
}

void RenderService::Deserialize(const rapidjson::Value& value)
{
    if (value.HasMember("LightDirection"))
    {
        auto dir = value["LightDirection"].GetArray();
        const float x = dir[0].GetFloat();
        const float y = dir[1].GetFloat();
        const float z = dir[2].GetFloat();
        mDirectionalLight.direction = KMath::Normalize({ x, y, z });
    }
    if (value.HasMember("ColorAmbient"))
    {
        auto dir = value["ColorAmbient"].GetArray();
        const float r = dir[0].GetFloat();
        const float g = dir[1].GetFloat();
        const float b = dir[2].GetFloat();
        const float a = dir[3].GetFloat();
        mDirectionalLight.ambient = { r, g, b, a };
    }
    if (value.HasMember("ColorDiffuse"))
    {
        auto dir = value["ColorDiffuse"].GetArray();
        const float r = dir[0].GetFloat();
        const float g = dir[1].GetFloat();
        const float b = dir[2].GetFloat();
        const float a = dir[3].GetFloat();
        mDirectionalLight.diffuse = { r, g, b, a };
    }
    if (value.HasMember("ColorSpecular"))
    {
        auto dir = value["ColorSpecular"].GetArray();
        const float r = dir[0].GetFloat();
        const float g = dir[1].GetFloat();
        const float b = dir[2].GetFloat();
        const float a = dir[3].GetFloat();
        mDirectionalLight.specular = { r, g, b, a };
    }
}

void RenderService::Register(const RenderObjectComponent* renderObjectComponent)
{
    Entry& entry = mRenderEntries.emplace_back();

    const GameObject& gameObject = renderObjectComponent->GetOwner();
    entry.renderComponent = renderObjectComponent;
    entry.transformComponent = gameObject.GetComponent<TransformComponent>();
    entry.castShadow = renderObjectComponent->CastShadow();

    const Animator* animator = nullptr;
    const AnimatorComponent* animatorComponent = gameObject.GetComponent<AnimatorComponent>();
    if (animatorComponent != nullptr)
    {
        animator = &animatorComponent->GetAnimator();
    }
    if (renderObjectComponent->GetModelId() != 0)
    {
        entry.renderGroup = CreateRenderGroup(renderObjectComponent->GetModelId(), animator);
    }
    else
    {
        entry.renderGroup = CreateRenderGroup(renderObjectComponent->GetModel(), animator);
    }
}

void RenderService::Unregister(const RenderObjectComponent* renderObjectComponent)
{
    auto iter = std::find_if(
        mRenderEntries.begin(),
        mRenderEntries.end(),
        [&](const Entry& entry)
        {
            return entry.renderComponent == renderObjectComponent;
        }
    );
    if (iter != mRenderEntries.end())
    {
        CleanupRenderGroup(iter->renderGroup);
        mRenderEntries.erase(iter);
    }
}
