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
protected:
    virtual void CreateShape() = 0;



protected:
    struct Vertex
    {
        Vector3 position;
        Color color;
    };

    using Verticies = std::vector<Vertex>;
    Verticies mVerticies;

    ConstantBuffer mConstantBuffer;
    MeshBuffer mMeshBuffer ;
    VertexShader mVertexShader;
    ID3D11InputLayout* mInputLayout = nullptr;
    PixelShader mPixelShader;
    Camera mCamera;
    MeshPC shape = MeshBuilder::CreateCubePC(1.0f, Colors::Wheat);
};

class TriangleState : public GameState
{
public: 
    void CreateShape();
    void Update(float deltaTime);
};
