#pragma once

#include "ModelManager.h"
#include "Animator.h"

namespace KEIEngine::Graphics::AnimationUtil
{
    using BoneTransforms = std::vector<KMath::Matrix4>;

    void ComputerBoneTransform(ModelId id, BoneTransforms& boneTransforms, const Animator* animatior = nullptr);
    void ApplyBoneOffsets(ModelId id, BoneTransforms& boneTransforms);
    void DrawSkeleton(ModelId id, BoneTransforms& boneTransforms);
}