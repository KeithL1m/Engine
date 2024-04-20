#pragma once

#include "Common.h"

namespace KEIEngine::Graphics
{
	struct Transform
	{
		KEIEngine::KMath::Vector3 position = KEIEngine::KMath::Vector3::Zero;
		KEIEngine::KMath::Quaternion rotation = KEIEngine::KMath::Quaternion::Identity;
		KEIEngine::KMath::Vector3 scale = KEIEngine::KMath::Vector3::One;

		KEIEngine::KMath::Matrix4 GetMatrix4() const
		{
			KMath::Matrix4 mat = KMath::Matrix4::MatrixRotationQuaternion(rotation);
			return {
				KEIEngine::KMath::Matrix4::Scaling(scale) *
				KEIEngine::KMath::Matrix4::MatrixRotationQuaternion(rotation) *
				KEIEngine::KMath::Matrix4::Translation(position)
			};
		}
	};
}