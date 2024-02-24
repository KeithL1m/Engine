#include "GameState.h"

using namespace KEIEngine;
using namespace KEIEngine::Graphics;
using namespace KEIEngine::KMath;
using namespace KEIEngine::Input;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -4.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mDirectionalLight.direction = KMath::Normalize({ 1.0f,-1.0f,1.0f });
	mDirectionalLight.ambient = { 0.5f, 0.5f,0.5f,1.0f };
	mDirectionalLight.diffuse = { 0.8f, 0.8f,0.8f,1.0f };
	mDirectionalLight.specular = { 1.0f, 1.0f,1.0f,1.0f };

	mStandardEffect.Initialize(L"../../Assets/Shaders/Standard.fx");
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);
	mStandardEffect.SetLightCamera(mShadowEffect.GetLightCamera());
	mStandardEffect.SetShadowMap(mShadowEffect.GetDepthMap());

	// missing
	mTerrainEffect.Initialize();
	mTerrainEffect.SetCamera(mCamera);

	mTerrainEffect.SetLightCamera(mCamera);

	mShadowEffect.Initialize();
	mShadowEffect.SetDirectionalLight(mDirectionalLight);

	ModelId modelId = ModelManager::Get()->LoadModel(L"../../Assets/Models/character/character.model");
	mCharacter = CreateRenderGroup(modelId);
	for (auto& renderObject : mCharacter)
	{
		renderObject.transform.position.x = 1.0f;
	}

	ModelId modelId2 = ModelManager::Get()->LoadModel(L"../../Assets/Models/character/character2.model");
	mCharacter2 = CreateRenderGroup(modelId2);
	for (auto& renderObject : mCharacter2)
	{
		renderObject.transform.position.x = -1.0f;
	}

	mTerrain.Initialize(L"../../Assets/Textures/terrain/height_map.jpg", 10.0f);

	// missing
	mGround.meshBuffer.Initialize(mTerrain.GetMesh());
	mGround.diffuseMapId = TextureManager::Get()->LoadTexture(L"terrain/dirt_seamless.jpg");
	mGround.normalMapId = TextureManager::Get()->LoadTexture(L"mountain/mountain_normal.jpg");
	mGround.specMapId = TextureManager::Get()->LoadTexture(L"mountain/mountain_spec.jpg");
	mGround.bumpMapId = TextureManager::Get()->LoadTexture(L"terrain/grass_2048");
};
void GameState::Terminate()
{
	mGround.Terminate();
	CleanupRenderGroup(mCharacter);
	CleanupRenderGroup(mCharacter2);
	mRenderTarget.Terminate();
	mStandardEffect.Terminate();
}
void GameState::Render()
{
	mShadowEffect.Begin();
		DrawRenderGroup(mShadowEffect, mCharacter);
		DrawRenderGroup(mShadowEffect, mCharacter2);
	mShadowEffect.End();

	mTerrainEffect.Begin();
		mTerrainEffect.Render(mGround);
	mTerrainEffect.End();

	mStandardEffect.Begin();
		DrawRenderGroup(mStandardEffect, mCharacter);
		DrawRenderGroup(mStandardEffect, mCharacter2);
		mStandardEffect.Render(mGround);
	mStandardEffect.End();
}
void GameState::Update(float deltaTime)
{
	UpdateCameraControl(deltaTime);
}
void GameState::DebugUI()
{
	ImGui::Begin("Debug Control", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
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
	mTerrainEffect.DebugUI();
	ImGui::End();
}

void GameState::UpdateCameraControl(float deltaTime)
{
	auto input = Input::InputSystem::Get();
	const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
	const float turnSpeed = 0.1f;

	if (input->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::E))
	{
		mCamera.Rise(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::Q))
	{
		mCamera.Rise(-moveSpeed * deltaTime);
	}
	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
	}
}