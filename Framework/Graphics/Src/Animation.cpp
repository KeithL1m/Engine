#include "Precompiled.h"
#include "Animation.h"

using namespace KEIEngine;
using namespace KEIEngine::Graphics;

namespace
{
	float GetLerpTime(float startTime, float endTime, float time)
	{
		float t = (time - startTime) / (endTime - startTime);
		return t;
	}
}

Transform Animation::GetTransform(float time) const
{
	Transform transform;
	transform.position = GetPosition(time);
	transform.rotation = GetRotation(time);
	transform.scale = GetScale(time);
	return transform;
}

float Animation::GetDuration() const
{
	return mDuration;
}

KMath::Vector3 Animation::GetPosition(float time) const
{
	for (uint32_t i = 0; i < mPositionKeys.size(); ++i)
	{
		if (time < mPositionKeys[i].time)
		{
			if (i > 0)
			{
				float t = GetLerpTime(mPositionKeys[i - 1].time, mPositionKeys[i].time, time);
				return KMath::Lerp(mPositionKeys[i - 1].key, mPositionKeys[i].key, t);
			}
			return mPositionKeys[i].key;
		}
	}

	if (!mPositionKeys.empty())
	{
		return mPositionKeys.back().key;
	}

	return KMath::Vector3::Zero;
}

KMath::Quaternion Animation::GetRotation(float time) const
{
	for (uint32_t i = 0; i < mRotationKeys.size(); ++i)
	{
		if (time < mRotationKeys[i].time)
		{
			if (i > 0)
			{
				float t = GetLerpTime(mRotationKeys[i - 1].time, mRotationKeys[i].time, time);
				return KMath::Quaternion::Slerp(mRotationKeys[i - 1].key, mRotationKeys[i].key, t);
			}
			return mRotationKeys[i].key;
		}
	}

	if (!mRotationKeys.empty())
	{
		return mRotationKeys.back().key;
	}

	return KMath::Quaternion::Identity;
}

KMath::Vector3 Animation::GetScale(float time) const
{
	for (uint32_t i = 0; i < mScaleKeys.size(); ++i)
	{
		if (time < mScaleKeys[i].time)
		{
			if (i > 0)
			{
				float t = GetLerpTime(mScaleKeys[i - 1].time, mScaleKeys[i].time, time);
				return KMath::Lerp(mScaleKeys[i - 1].key, mScaleKeys[i].key, t);
			}
			return mScaleKeys[i].key;
		}
	}

	if (!mScaleKeys.empty())
	{
		return mScaleKeys.back().key;
	}

	return KMath::Vector3::One;
}
