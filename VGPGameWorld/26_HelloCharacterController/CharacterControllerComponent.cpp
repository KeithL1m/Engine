#include "CharacterControllerComponent.h"
#include "TPSCameraComponent.h"

using namespace KEIEngine;
using namespace KEIEngine::Graphics;
using namespace KEIEngine::Input;

void CharacterControllerComponent::Initialize()
{
	mCharacterAnimation = GetOwner().GetComponent<AnimatorComponent>();
	mCharacterRigidBody = GetOwner().GetComponent<RigidBodyComponent>();
	mCharacterTransform = GetOwner().GetComponent<TransformComponent>();

	UpdateService* updateService = GetOwner().GetWorld().GetService<UpdateService>();
	updateService->Register(this);
}

void CharacterControllerComponent::Terminate()
{
	UpdateService* updateService = GetOwner().GetWorld().GetService<UpdateService>();
	updateService->Unregister(this);
}

void CharacterControllerComponent::Update(float deltaTime)
{
	InputSystem* input = InputSystem::Get();
	Matrix4 transform = mCharacterTransform->GetMatrix4();
	Vector3 foward = KMath::GetLook(transform);
	Vector3 right = KMath::GetRight(transform);
	Vector3 velocity = Vector3::Zero;
	Vector3 currentVelocity = mCharacterRigidBody->GetVelocity();
	int desiredAnimation = 0;

	if (mIsRolling)
	{
		if (mCharacterAnimation->IsFinished())
		{
			mIsRolling = false;
			desiredAnimation = 0;
		}
	}

	if (input->IsKeyDown(KeyCode::UP) || input->IsKeyDown(KeyCode::W))
	{
		velocity = foward * -2.5f;
		desiredAnimation = 1;
	}
	else if (input->IsKeyDown(KeyCode::DOWN) || input->IsKeyDown(KeyCode::S))
	{
		velocity = foward * 1.0f;
		desiredAnimation = 2;
	}
	if (input->IsKeyDown(KeyCode::LEFT) || input->IsKeyDown(KeyCode::A))
	{
		velocity += right * 1.5f;
		desiredAnimation = 2;
	}
	else if (input->IsKeyDown(KeyCode::RIGHT) || input->IsKeyDown(KeyCode::D))
	{
		velocity += right * -1.5f;
		desiredAnimation = 2;
	}

	if (input->IsKeyPressed(KeyCode::LSHIFT))
	{
		CharacterRoll();
		velocity = foward * 1.0f;
	}

	if (input->IsKeyDown(KeyCode::M))
	{
		mCharacterRigidBody->SetRotationVelocity({ 0.0f, 1.0f, 0.0f });
	}
	else if (input->IsKeyDown(KeyCode::N))
	{
		mCharacterRigidBody->SetRotationVelocity({ 0.0f, -1.0f, 0.0f });
	}
	else
	{
		mCharacterRigidBody->SetRotationVelocity({ 0.0f, 0.0f, 0.0f });
	}
	velocity.y = currentVelocity.y;
	
	mCharacterRigidBody->SetVelocity(velocity);

	if (!mIsRolling && desiredAnimation != mCurrentAnimationIndex)
	{
		//set animation
		mCurrentAnimationIndex = desiredAnimation;
		mCharacterAnimation->Play(mCurrentAnimationIndex, true);
	}
}

void CharacterControllerComponent::CharacterRoll()
{
	// wait until complete, then set animation
	// play, is looping = false
	mCurrentAnimationIndex = 3;
	mIsRolling = true;
	mCharacterAnimation->Play(mCurrentAnimationIndex, false);
}
