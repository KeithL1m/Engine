#include "Precompiled.h"
#include "Camera.h"

#include "GraphicsSystem.h"

using namespace KEIEngine;
using namespace KEIEngine::Graphics;

void Camera::SetMode(ProjectionMode mode)
{
	mProjectionMode = mode;
}

void Camera::SetPosition(const KMath::Vector3& position)
{
	mPosition = position;
}

void Camera::SetDirection(const KMath::Vector3& direction)
{
	// Prevent setting direction straight up or down
	auto dir = KMath::Normalize(direction);
	if (KMath::Abs(KMath::Dot(dir, KMath::Vector3::YAxis)) < 0.995f)
		mDirection = dir;
}

void Camera::SetLookAt(const KMath::Vector3& target)
{
	SetDirection(target - mPosition);
}

void Camera::SetFov(float fov)
{
	constexpr float kMinFov = 10.0f * KMath::Constants::DegToRad;
	constexpr float kMaxFov = 170.0f * KMath::Constants::DegToRad;
	mFov = KMath::Clamp(fov, kMinFov, kMaxFov);
}

void Camera::SetAspectRatio(float ratio)
{
	mAspectRatio = ratio;
}

void Camera::SetSize(float width, float height)
{
	mWidth = width;
	mHeight = height;
}

void Camera::SetNearPlane(float nearPlane)
{
	mNearPlane = nearPlane;
}

void Camera::SetFarPlane(float farPlane)
{
	mFarPlane = farPlane;
}

void Camera::Walk(float distance)
{
	mPosition += mDirection * distance;
}

void Camera::Strafe(float distance)
{
	const KMath::Vector3 right = KMath::Normalize(Cross(KMath::Vector3::YAxis, mDirection));
	mPosition += right * distance;
}

void Camera::Rise(float distance)
{
	mPosition += KMath::Vector3::YAxis * distance;
}

void Camera::Yaw(float radian)
{
	KMath::Matrix4 matRotate = KMath::Matrix4::RotationY(radian);
	mDirection = KMath::TransformNormal(mDirection, matRotate);
}

void Camera::Pitch(float radian)
{
	const KMath::Vector3 right = KMath::Normalize(Cross(KMath::Vector3::YAxis, mDirection));
	const KMath::Matrix4 matRot = KMath::Matrix4::RotationAxis(right, radian);
	const KMath::Vector3 newLook = KMath::TransformNormal(mDirection, matRot);
	SetDirection(newLook);
}

void Camera::Zoom(float amount)
{
	constexpr float minZoom = 170.0f * KMath::Constants::DegToRad;
	constexpr float maxZoom = 10.0f * KMath::Constants::DegToRad;
	mFov = KMath::Clamp(mFov - amount, maxZoom, minZoom);
}

const KMath::Vector3& Camera::GetPosition() const
{
	return mPosition;
}

const KMath::Vector3& Camera::GetDirection() const
{
	return mDirection;
}

KMath::Matrix4 Camera::GetViewMatrix() const
{
	const KMath::Vector3 l = mDirection;
	const KMath::Vector3 r = KMath::Normalize(KMath::Cross(KMath::Vector3::YAxis, l));
	const KMath::Vector3 u = KMath::Normalize(KMath::Cross(l, r));
	const float x = -KMath::Dot(r, mPosition);
	const float y = -KMath::Dot(u, mPosition);
	const float z = -KMath::Dot(l, mPosition);

	return
	{
		r.x, u.x, l.x, 0.0f,
		r.y, u.y, l.y, 0.0f,
		r.z, u.z, l.z, 0.0f,
		x,   y,   z,   1.0f
	};
}

KMath::Matrix4 Camera::GetProjectionMatrix() const
{
	return (mProjectionMode == ProjectionMode::Perspective) ? GetPerspectiveMatrix() : GetOrthographicMatrix();
}

KMath::Matrix4 Camera::GetPerspectiveMatrix() const
{
	const float a = (mAspectRatio == 0.0f) ? GraphicsSystem::Get()->GetBackBufferAspectRatio() : mAspectRatio;
	const float h = 1.0f / tan(mFov * 0.5f);
	const float w = h / a;
	const float zf = mFarPlane;
	const float zn = mNearPlane;
	const float q = zf / (zf - zn);

	return {
		w,    0.0f, 0.0f,    0.0f,
		0.0f, h,    0.0f,    0.0f,
		0.0f, 0.0f, q,       1.0f,
		0.0f, 0.0f, -zn * q, 0.0f
	};
}

KMath::Matrix4 Camera::GetOrthographicMatrix() const
{
	const float w = (mWidth == 0.0f) ? GraphicsSystem::Get()->GetBackBufferWidth() : mWidth;
	const float h = (mHeight == 0.0f) ? GraphicsSystem::Get()->GetBackBufferHeight() : mHeight;
	const float f = mFarPlane;
	const float n = mNearPlane;
	return 	{
		2 / w, 0.0f,  0.0f,        0.0f,
		0.0f,  2 / h, 0.0f,        0.0f,
		0.0f,  0.0f,  1 / (f - n), 0.0f,
		0.0f,  0.0f,  n / (n - f), 1.0f
	};
}