#pragma once

#include "ModelManager.h"

namespace KEIEngine::Graphics::AnimationUtil
{
	using BoneTransforms = std::vector<KMath::Matrix4>;

	void ComputerBoneTransform(ModelId id, BoneTransforms& boneTransform);
	void ApplyBoneOffsets(ModelId id, BoneTransforms& boneTransform);
	void DrawSkeleton(ModelId id, BoneTransforms& boneTransform);
}