#include "Precompiled.h"
#include "AnimationUtil.h"

using namespace KEIEngine;
using namespace KEIEngine::Graphics;

void AnimationUtil::ComputerBoneTransform(ModelId id, BoneTransforms& boneTransform)
{
	// compute the world transform of the bone
}

void AnimationUtil::ApplyBoneOffsets(ModelId id, BoneTransforms& boneTransform)
{
	// apply the offset transform of the bone
}

void AnimationUtil::DrawSkeleton(ModelId id, BoneTransforms& boneTransform)
{
	// draw the bone
	const Model* model = ModelManager::Get()->GetModel(id);
	if (model->skeleton != nullptr)
	{
		for (auto& bone : model->skeleton->bones)
		{
			if (bone->parent != nullptr)
			{
				//get position of bone
				// getposition of parent bone
				// SimpleDraw::AddLine(bonePos, parentBonePos, Colors::Blue);
				// SimpleDraw::AddSphere(10, 10, 0.03f, bonePos, 
				//const KMath::Vector3 posA = KMath::Get
			}
		}
	}
}
