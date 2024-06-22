#include "GameState.h"

using namespace KEIEngine;
using namespace KEIEngine::Graphics;
using namespace KEIEngine::KMath;
using namespace KEIEngine::Input;
using namespace KEIEngine::Audio;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 2.0f, -15.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mDirectionalLight.direction = KMath::Normalize({ 1.0f,-1.0f,1.0f });
	mDirectionalLight.ambient = { 0.5f, 0.5f,0.5f,1.0f };
	mDirectionalLight.diffuse = { 0.8f, 0.8f,0.8f,1.0f };
	mDirectionalLight.specular = { 1.0f, 1.0f,1.0f,1.0f };

	mParticleEffect.Initialize();
	mParticleEffect.SetCamera(mCamera);

	mStandardEffect.Initialize(L"../../Assets/Shaders/Standard.fx");
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);

	Mesh ball = MeshBuilder::CreateSphere(60, 60, 2.0f);
	mDisco.meshBuffer.Initialize(ball);
	mDisco.diffuseMapId = TextureManager::Get()->LoadTexture("Images/misc/discoball.jpg");

	Mesh ground = MeshBuilder::CreateGroundPlane(100, 100, 1.0f);
	mGround.meshBuffer.Initialize(ground);
	mGround.diffuseMapId = TextureManager::Get()->LoadTexture("Images/misc/concrete.jpg");

	// Adding Particles

	// Firework
	ParticleSystemInfo info;
	info.spawnPosition = { 0.0f, 0.0f, 13.0f };
	info.spawnDirection = KMath::Vector3::YAxis;
	info.spawnDelay = 0.0f;
	info.systemLifeTime = 99999.0f;
	info.minParticlePerEmit = 20;
	info.maxParticlePerEmit = 50;
	info.minTimeBetweenEmit = 0.5f;
	info.maxTimeBetweenEmit = 3.0f;
	info.minSpawnAngle = -10.0f * 3.141592 / 180.0f;
	info.maxSpawnAngle = 10.0f * 3.141592 / 180.0f;
	info.minSpeed = 10.0f;
	info.maxSpeed = 15.0f;
	info.minLifeTime = 1.0f;
	info.maxLifeTime = 2.0f;
	info.minStartColor = Colors::White;
	info.maxStartColor = Colors::White;
	info.minEndColor = Colors::CadetBlue;
	info.maxEndColor = Colors::Blue;
	info.minStartScale = KMath::Vector3::One;
	info.maxStartScale = KMath::Vector3::One;
	info.minEndScale = KMath::Vector3::Zero;
	info.maxEndScale = KMath::Vector3::Zero;
	info.maxParticles = 10;
	info.particleTextureId = TextureManager::Get()->LoadTexture("Images/bullet1.png");
	mFireworks.Initialize(info);
	mFireworks.SetCamera(mCamera);

	// Sparkles
	info.spawnPosition = { 0.0f, 0.0f, 5.0f };
	info.spawnDirection = KMath::Vector3::YAxis;
	info.spawnDelay = 0.0f;
	info.systemLifeTime = 99999.0f;
	info.minParticlePerEmit = 3;
	info.maxParticlePerEmit = 5;
	info.minTimeBetweenEmit = 0.1f;
	info.maxTimeBetweenEmit = 0.3f;
	info.minSpawnAngle = -30.0f * 3.141592 / 180.0f;
	info.maxSpawnAngle = 30.0f * 3.141592 / 180.0f;
	info.minSpeed = 5.0f;
	info.maxSpeed = 10.0f;
	info.minLifeTime = 0.3f;
	info.maxLifeTime = 1.0f;
	info.minStartColor = Colors::White;
	info.maxStartColor = Colors::White;
	info.minEndColor = Colors::Gold;
	info.maxEndColor = Colors::DarkGoldenrod;
	info.minStartScale = KMath::Vector3::One;
	info.maxStartScale = KMath::Vector3::One;
	info.minEndScale = KMath::Vector3::Zero;
	info.maxEndScale = KMath::Vector3::Zero;
	info.maxParticles = 100;
	info.particleTextureId = TextureManager::Get()->LoadTexture("Images/bullet2.png");
	mSparkles.Initialize(info);
	mSparkles.SetCamera(mCamera);

	// Adding Characters

	mCharacterId = ModelManager::Get()->LoadModel("../../Assets/Models/characterfin/zombie.model");
	mCharacter = CreateRenderGroup(mCharacterId, &mCharacterAnimator);

	mCharacterPosition.x = 5.0f;
	mCharacterPosition.y = 0.0f;
	SetRenderGroupPosition(mCharacter, mCharacterPosition);

	mCharacterId2 = ModelManager::Get()->LoadModel("../../Assets/Models/characterfin/moose.model");
	mCharacter2 = CreateRenderGroup(mCharacterId2, &mCharacterAnimator2);

	mCharacter2Position.x = -5.0f;
	mCharacter2Position.y = 0.0f;
	SetRenderGroupPosition(mCharacter2, mCharacter2Position);

	// Add Animations

	ModelManager::Get()->AddAnimation(mCharacterId, "../../Assets/Models/characterfin/Animations/mutant_run.model");
	ModelManager::Get()->AddAnimation(mCharacterId, "../../Assets/Models/characterfin/Animations/house_dancing.model");
	ModelManager::Get()->AddAnimation(mCharacterId, "../../Assets/Models/characterfin/Animations/mutant_dying.model");
	mCharacterAnimator.Initialize(mCharacterId);
	mCharacterAnimator.PlayAnimation(1, true);

	ModelManager::Get()->AddAnimation(mCharacterId2, "../../Assets/Models/characterfin/Animations/moose_run.model");
	ModelManager::Get()->AddAnimation(mCharacterId2, "../../Assets/Models/characterfin/Animations/moose_dance.model");
	ModelManager::Get()->AddAnimation(mCharacterId2, "../../Assets/Models/characterfin/Animations/moose_dying.model");
	mCharacterAnimator2.Initialize(mCharacterId2);
	mCharacterAnimator2.PlayAnimation(1, true);

	// Disco Animation
	//mAnimation = AnimationBuilder()
		
};
void GameState::Terminate()
{
	CleanupRenderGroup(mCharacter);
	CleanupRenderGroup(mCharacter2);
	mFireworks.Terminate();
	mGround.Terminate();
	mStandardEffect.Terminate();
}
void GameState::Render()
{
	SimpleDraw::AddGroundPlane(10.0f, Colors::White);
	SimpleDraw::Render(mCamera);

	mParticleEffect.Begin();
		mFireworks.Render(mParticleEffect);
		mSparkles.Render(mParticleEffect);
	mParticleEffect.End();

	mDisco.transform.position.y = 5.0f;

	mStandardEffect.Begin();
	if (mDrawSkeleton)
	{
		AnimationUtil::BoneTransforms boneTransforms;
		AnimationUtil::ComputerBoneTransform(mCharacterId, boneTransforms, &mCharacterAnimator);
		AnimationUtil::DrawSkeleton(mCharacterId, boneTransforms);

		AnimationUtil::BoneTransforms boneTransforms2;
		AnimationUtil::ComputerBoneTransform(mCharacterId2, boneTransforms2, &mCharacterAnimator2);
		AnimationUtil::DrawSkeleton(mCharacterId2, boneTransforms2);
	}
	else
	{
		DrawRenderGroup(mStandardEffect, mCharacter);
		DrawRenderGroup(mStandardEffect, mCharacter2);
	}
		mStandardEffect.Render(mGround);
		mStandardEffect.Render(mDisco);
	mStandardEffect.End();
}
void GameState::Update(float deltaTime)
{
	mTime += deltaTime;
	UpdateCameraControl(deltaTime);
	mCharacterAnimator.Update(deltaTime);
	mCharacterAnimator2.Update(deltaTime);
	mFireworks.Update(deltaTime);
	mSparkles.Update(deltaTime);
	//auto input = Input::InputSystem::Get();
	//int targetAnim = mAnimationIndex;
	//if (input->IsKeyPressed(Input::KeyCode::UP))
	//{
	//	targetAnim = 0;
	//}
	//else if (input->IsKeyPressed(Input::KeyCode::DOWN))
	//{
	//	targetAnim = 1;
	//}
	//else if (input->IsKeyPressed(Input::KeyCode::LEFT))
	//{
	//	targetAnim = 2;
	//}
	//else if (input->IsKeyPressed(Input::KeyCode::RIGHT))
	//{
	//	targetAnim = 3;
	//}

	//if (targetAnim != mAnimationIndex)
	//{
	//	mAnimationIndex = targetAnim;
	//	mCharacterAnimator.PlayAnimation(mAnimationIndex, true);
	//}
}
void GameState::DebugUI()
{
	ImGui::Begin("Debug Control", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("Time : ");
	ImGui::SameLine();
	ImGui::Text("%.1f", mTime);
	if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::DragFloat3("Direction", &mDirectionalLight.direction.x, 0.01f))
		{
			mDirectionalLight.direction = KMath::Normalize(mDirectionalLight.direction);
		}

		ImGui::ColorEdit4("Ambient##Light", &mDirectionalLight.ambient.r);
		ImGui::ColorEdit4("Diffuse##Light", &mDirectionalLight.diffuse.r);
		ImGui::ColorEdit4("Specular##Light", &mDirectionalLight.specular.r);

		if (ImGui::DragInt("AnimationIndex", &mAnimationIndex, 1, -1, mCharacterAnimator.GetAnimationCount() - 1))
		{
			mCharacterAnimator.PlayAnimation(mAnimationIndex, true);
			mCharacterAnimator2.PlayAnimation(mAnimationIndex, true);
		}
	}
	mStandardEffect.DebugUI();
	ImGui::Checkbox("DrawSkeleton", &mDrawSkeleton);
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