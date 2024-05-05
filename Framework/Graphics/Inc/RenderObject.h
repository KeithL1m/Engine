#pragma once

#include "Material.h"
#include "MeshBuffer.h"
#include "Transform.h"
#include "TextureManager.h"
#include "ModelManager.h"

namespace KEIEngine::Graphics
{
	struct Model;
	class Animator;
	class RenderObject
	{
	public:
		void Terminate();

		Transform transform;
		MeshBuffer meshBuffer;

		ModelId modelId;
		Material material;
		TextureId diffuseMapId;
		TextureId normalMapId;
		TextureId specMapId;
		TextureId bumpMapId;

		const Skeleton* skeleton = nullptr;
		const Animator* animator = nullptr;
	};

	using RenderGroup = std::vector<RenderObject>;
	[[nodiscard]] RenderGroup CreateRenderGroup(ModelId id, Animator* animator = nullptr);
	[[nodiscard]] RenderGroup CreateRenderGroup(const Model& model, Animator* animator = nullptr);
	void CleanupRenderGroup(RenderGroup& renderGroup);
	void SetRenderGroupPosition(RenderGroup& renderGroup, const KMath::Vector3& position);

	template<class Effect>
	void DrawRenderGroup(Effect& effect, const RenderGroup& renderGroup)
	{
		for (const RenderObject& renderObject : renderGroup)
		{
			effect.Render(renderObject);
		}
	}
}