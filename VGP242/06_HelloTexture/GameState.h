#pragma once

#include "Inc/AppState.h"
#include "Inc/KEIEngine.h"

using namespace KEIEngine;
using namespace KEIEngine::KMath;
using namespace KEIEngine::Graphics;

class GameState : public AppState
{
public:
	void Initialize();
	void Terminate();
	void Render();
	void Update(float deltaTime);
protected:
	Camera mCamera;
	ConstantBuffer mConstantBuffer;
	MeshBuffer mMeshBuffer ;
	VertexShader mVertexShader;
	PixelShader mPixelShader;

	Texture mDiffuseTexture;
	Sampler mSampler;
};

