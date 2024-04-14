#include "Precompiled.h"
#include "AnimationBuilder.h"

using namespace KEIEngine;
using namespace KEIEngine::Graphics;

namespace
{
	template<class T>
	inline void PushKey(Keyframes<T>& keyframes, const T& value, float t, EaseType easeType)
	{
		ASSERT(keyframes.empty() || keyframes.back().time <= t, "AnimationBuild: cannot push key");
		keyframes.emplace_back(value, t, easeType);
	}
}

AnimationBuilder& AnimationBuilder::AddPositionKey(const KMath::Vector3& pos, float time, EaseType easeType)
{
	PushKey(mWorkingCopy.mPositionKeys, pos, time, easeType);
	mWorkingCopy.mDuration = KMath::Max(mWorkingCopy.mDuration, time);
	return *this;
}

AnimationBuilder& AnimationBuilder::AddRotationKey(const KMath::Quaternion& rotation, float time, EaseType easeType)
{
	PushKey(mWorkingCopy.mRotationKeys, rotation, time, easeType);
	mWorkingCopy.mDuration = KMath::Max(mWorkingCopy.mDuration, time);
	return *this;
}

AnimationBuilder& AnimationBuilder::AddScaleKey(const KMath::Vector3& scale, float time, EaseType easeType)
{
	PushKey(mWorkingCopy.mScaleKeys, scale, time, easeType);
	mWorkingCopy.mDuration = KMath::Max(mWorkingCopy.mDuration, time);
	return *this;
}

Animation AnimationBuilder::Build()
{
	ASSERT(!mWorkingCopy.mPositionKeys.empty() ||
		!mWorkingCopy.mRotationKeys.empty() ||
		!mWorkingCopy.mScaleKeys.empty(),
		"AnimationBuilder: no animation keys are present");
	return mWorkingCopy;
}
