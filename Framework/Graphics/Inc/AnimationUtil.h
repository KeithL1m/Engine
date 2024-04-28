#pragma once

#include "ModelManager.h"

namespace KEIEngine::Graphics::AnimationUtil
{
	using BoneTransforms = std::vector<KMath::Matrix4>;

	void ComputerBoneTransform(ModelId id, BoneTransforms& boneTransforms);
	void ApplyBoneOffsets(ModelId id, BoneTransforms& boneTransforms);
	void DrawSkeleton(ModelId id, BoneTransforms& boneTransforms);
}