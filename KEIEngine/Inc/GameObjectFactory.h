#pragma once

namespace KEIEngine
{
    class GameObject;

    namespace GameObjectFactory
    {
        void Make(const std::filesystem::path& templatePath, GameObject& gameObject);
    }
}