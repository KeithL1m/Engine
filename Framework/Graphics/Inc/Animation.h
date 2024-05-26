#pragma once

#include "Keyframe.h"
#include "Transform.h"

namespace KEIEngine::Graphics
{
	class Animation
	{
	public:
		Transform GetTransform(float time) const;
		float GetDuration() const;

		void PlayEvents(float prevTime, float currentTime);

	private:
		KMath::Vector3 GetPosition(float time) const;
		KMath::Quaternion GetRotation(float time) const;
		KMath::Vector3 GetScale(float time) const;

		friend class AnimationBuilder;
		friend class AnimationIO;

		EventKeys mEventKeys;
		PositionKeys mPositionKeys;
		RotationKeys mRotationKeys;
		ScaleKeys mScaleKeys;
		float mDuration;
	};
}