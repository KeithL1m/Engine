#pragma once

#include "Bone.h"

namespace KEIEngine::Graphics
{
    struct Skeleton
    {
        Bone* root = nullptr;
        std::vector<std::unique_ptr<Bone>> bones;
    };
}