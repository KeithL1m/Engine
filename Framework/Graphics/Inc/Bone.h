#pragma once

#include "Common.h"

namespace KEIEngine::Graphics
{
    struct Bone
    {
        std::string name;
        int index = -1;

        Bone* parent = nullptr;
        int parentIndex = -1;

        std::vector<Bone*> children;
        std::vector<int> childrenIndices;

        KMath::Matrix4 toParentTransform;
        KMath::Matrix4 offsetTransform;
    };
}