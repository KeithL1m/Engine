#include "Precompiled.h"
#include "BillboardEffect.h"

#include "Camera.h"
#include "GraphicsSystem.h"
#include "RenderObject.h"
#include "TextureManager.h"
#include "VertexTypes.h"

using namespace KEIEngine;
using namespace KEIEngine::Graphics;

void BillboardEffect::Initialize()
{
    std::filesystem::path filePath = L"../../Assets/Shaders/Billboard.fx";
    mVertexShader.Initialize<Vertex>(filePath);
    mPixelShader.Initialize(filePath);
    mConstantBuffer.Initialize(sizeof(KMath::Matrix4));
    mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
    mBlendState.Initialize(BlendState::Mode::AlphaBlend);

}

void BillboardEffect::Terminate()
{
    mSampler.Terminate();
    mConstantBuffer.Terminate();
    mPixelShader.Terminate();
    mVertexShader.Terminate();
    mBlendState.Terminate();
}

void BillboardEffect::Begin()
{
    mVertexShader.Bind();
    mPixelShader.Bind();
    mConstantBuffer.BindVS(0);
    mSampler.BindPS(0);
    mBlendState.Set();
}

void BillboardEffect::End()
{
    Texture::UnbindPS(0);
    BlendState::ClearState();
}

void BillboardEffect::Render(const RenderObject& renderObject)
{
    KMath::Matrix4 matView = mCamera->GetViewMatrix();
    KMath::Matrix4 matWV = KMath::Matrix4::Translation(KMath::TransformCoord(renderObject.transform.position, matView));
    KMath::Matrix4 matProj = mCamera->GetProjectionMatrix();
    KMath::Matrix4 matFinal = matWV * matProj;
    KMath::Matrix4 wvp = KMath::Transpose(matFinal);

    mConstantBuffer.Update(&wvp);
    TextureManager* tm = TextureManager::Get();
    tm->BindPS(renderObject.diffuseMapId, 0);
    renderObject.meshBuffer.Render();
}

void BillboardEffect::SetCamera(const Camera& camera)
{
    mCamera = &camera;
}
