#pragma once

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "RenderTarget.h"
#include "VertexShader.h"

namespace KEIEngine::Graphics
{
	class RenderObject;

	class GaussianBlurEffect
	{
	public:

	private:
		struct SettingsData
		{
			float screenWidth;
			float screenHeigth;
			float multiplier;
			float padding;
		};

		using SettingsBuffer = TypedConstantBuffer<SettingsData>;
		SettingsBuffer mSettingsBuffer;

		RenderTarget mHorizontalBlurRenderTarget;
		RenderTarget mVerticalBlurRenderTarget;

		VertexShader mVertexShader;
		PixelShader mHorizontalBlurPixelShader;
		PixelShader mVerticalBlurPixelShader;

		Sampler mSampler;

		const Texture* mSourceTexture = nullptr;
		int mBlurIterrations = 1;
		float mBlurSaturation = 1.0f;
	};
}