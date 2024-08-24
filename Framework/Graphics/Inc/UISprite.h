#pragma once

#include "Colors.h"
#include "TextureManager.h"

namespace KEIEngine::Graphics
{
	enum class Pivot
	{
		TopLeft,
		Top,
		TopRight,
		Left,
		Center,
		Right,
		BottomLeft,
		Bottom,
		BottomRight
	};
	enum class Flip
	{
		None,
		Horizontal,
		Vertical,
		Both
	};
	class UISprite
	{
	public:
		UISprite() = default;
		virtual ~UISprite();

		void Initialize(const std::filesystem::path& filePath);
		void Terminate();

		void SetPosition(const KMath::Vector2& position);
		void SetScale(const KMath::Vector2& scale);
		void SetRect(uint32_t top, uint32_t left, uint32_t right, uint32_t bottom);
		void SetPivot(Pivot pivot);
		void SetFlip(Flip flip);
		void SetColor(const Color& color);

	private:
		void UpdateOrigin();

		friend class UISpriteRenderer;

		TextureId mTextureId;
		RECT mRect = { 0, 0, 100, 100 };
		DirectX::XMFLOAT2 mPosition = { 0.0f, 0.0f };
		DirectX::XMFLOAT2 mOrigin = { 0.0f, 0.0f };
		DirectX::XMFLOAT2 mScale = { 1.0f, 1.0f };
		DirectX::XMVECTOR mColor = DirectX::Colors::White;
		float mRotation = 0.0f;
		Pivot mPivot = Pivot::TopLeft;
		DirectX::SpriteEffects mFlip = DirectX::SpriteEffects_None;
	};
}