#include "Precompiled.h"
#include "TerrainEffect.h"

#include "Camera.h"
#include "Texture.h"
#include "RenderObject.h"

using namespace KEIEngine;
using namespace KEIEngine::Graphics;

void TerrainEffect::Initialize()
{
	std::filesystem::path shaderFile = L"../../Assets/Shaders/Terrain.fx";
	mVertexShader.Initialize<Vertex>(shaderFile);
	mPixelShader.Initialize(shaderFile);

	mTransformBuffer.Initialize();
	mLightingBuffer.Initialize();
	mMaterialBuffer.Initialize();
	mSettingsBuffer.Initialize();
	mMaterialBuffer.Initialize();
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void TerrainEffect::Terminate()
{
	mSampler.Terminate();
	mSettingsBuffer.Terminate();
	mMaterialBuffer.Terminate();
	mLightingBuffer.Terminate();
	mTransformBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
}

void TerrainEffect::Begin()
{
	mVertexShader.Bind();
	mPixelShader.Bind();

	mTransformBuffer.BindVS(0);

	mLightingBuffer.BindVS(1);
	mLightingBuffer.BindPS(1);

	mMaterialBuffer.BindPS(2);

	//mSettingsBuffer.BindVS();
}

void TerrainEffect::End()
{
	if (mShadowMap != nullptr)
	{
		Texture::UnbindPS(3);
	}
}

void TerrainEffect::Render(const RenderObject& renderObject)
{
	ASSERT(mCamera != nullptr, "TerrainEffect: no camera specified");
	ASSERT(mDirectionalLight != nullptr, "TerrainEffect: no light specified");

	//missing
	//const Matrix4 matWorld = renderObject.transform.GetMatrix4();
	//const Matrix4 matView = mCamera->GetViewMatrix();
	//const Matrix4 matProj = mCamera->GetProjectionMatrix();

	SettingsData settingsData;
	settingsData.useNormalMap = mSettingsData.useNormalMap > 0;
	settingsData.useShadowMap = mSettingsData.useShadowMap > 0 && mShadowMap != nullptr;
	settingsData.depthBias = mSettingsData.depthBias;
	

	TransformData transformData;
	//transformData.wvp = Transpose(matWorld * matView * matProj);
	//transformData.world = Transpose(matWorld);
	transformData.viewPosition = mCamera->GetPosition();

	if (settingsData.useShadowMap > 0)
	{
		//matView = mLightCamera->GetViewMatrix();
		//matProj = mLightCamera->GetProjectionMatrix();
		//transformData.viewPosition = Transpose(matWorld * matView * matProj);

		
	}

}

void TerrainEffect::DebugUI()
{
	if (ImGui::CollapsingHeader("TerrainEffect", ImGuiTreeNodeFlags_DefaultOpen))
	{
		// missing
		bool useNormalMap = mSettingsData.useNormalMap > 0;
		if (ImGui::Checkbox("UseNorm##Terrain", &useNormalMap))
		{
			mSettingsData.useNormalMap = useNormalMap ? 1 : 0;
		}
		bool useSpecMap = mSettingsData.useSpecMap > 0;
		if (ImGui::Checkbox("UseNorm##Terrain", &useNormalMap))
		{
			mSettingsData.useSpecMap = useSpecMap ? 1 : 0;
		}
		bool useShadowMap = mSettingsData.useShadowMap > 0;
		if (ImGui::Checkbox("UseNorm##Terrain", &useShadowMap))
		{
			mSettingsData.useShadowMap = useShadowMap ? 1 : 0;
		}
		ImGui::DragFloat("DepthBias##Terrain", &mSettingsData.depthBias, 0.000001f, 0.0f, 0.0f, ".6f");
	}
}

void TerrainEffect::SetCamera(const Camera& camera)
{
	mCamera = &camera;
}

void TerrainEffect::SetLightCamera(const Camera& camera)
{
	mLightCamera = &camera;
}

void TerrainEffect::SetDirectionalLight(const DirectionalLight& directionalLight)
{
	mDirectionalLight = &directionalLight;
}

void TerrainEffect::SetShadowMap(const Texture& shadowMap)
{
	mShadowMap = &shadowMap;
}
