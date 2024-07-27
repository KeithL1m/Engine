#pragma once

#include "ModelManager.h"
#include "Bone.h"

namespace KEIEngine::Graphics
{
    class Animator
    {
    public:
        void Initialize(ModelId id);
        void PlayAnimation(int clipIndex, bool looping);
        void Update(float deltaTime);

        bool IsFinished() const;
        size_t GetAnimationCount() const;
        KMath::Matrix4 GetToParentTransform(const Bone* bone) const;

    private:
        ModelId mModelId = 0;
        int mClipIndex = -1;
        float mAnimationTick = 0.0f;
        bool mIsLooping = false;
    };
}
