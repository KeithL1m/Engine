#pragma once


#include "MeshTypes.h"

namespace KEIEngine::Graphics
{
    class Terrain final
    {
    public:
        void Initialize(const std::filesystem::path& fileName, float heightScale);
        float GetHeight(const KMath::Vector3& position) const;
        const Mesh& GetMesh() const { return mMesh; }

        float GetWidth() const { return static_cast<float>(mColumns); }
        float GetHeight() const { return static_cast<float>(mRows); }

    private:
        Mesh mMesh;
        uint32_t mRows = 0;
        uint32_t mColumns = 0;
    };
}