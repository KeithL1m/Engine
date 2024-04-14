#pragma once

#include "Animation.h"

namespace KEIEngine::Graphics
{
	class AnimationBuilder
	{
	public:
		AnimationBuilder& AddPositionKey(const KMath::Vector3& pos, float time, EaseType easeType = EaseType::Linear);
		AnimationBuilder& AddRotationKey(const KMath::Quaternion& rot, float time, EaseType easeType = EaseType::Linear);
		AnimationBuilder& AddScaleKey(const KMath::Vector3& scale, float time, EaseType easeType = EaseType::Linear);

		[[nodiscard]] Animation Build();
	private:
		Animation mWorkingCopy;
	};
}
