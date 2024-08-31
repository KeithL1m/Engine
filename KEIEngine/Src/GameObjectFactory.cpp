#include "Precompiled.h"
#include "GameObjectFactory.h"

#include "GameObject.h"

//components
#include "TransformComponent.h"
#include "CameraComponent.h"
#include "FPSCameraComponent.h"
#include "MeshComponent.h"
#include "ModelComponent.h"
#include "AnimatorComponent.h"
#include "RigidBodyComponent.h"
#include "SoundBankComponent.h"
#include "SoundEffectComponent.h"
#include "UISpriteComponent.h"
#include "UIButtonComponent.h"
#include "UITextComponent.h"

using namespace KEIEngine;
namespace rj = rapidjson;

namespace
{
    using namespace KEIEngine;

    CustomMake TryMake;

    Component* AddComponent(const std::string& componentName, GameObject& gameObject)
    {
        Component* component = TryMake(componentName, gameObject);
        if (component != nullptr)
        {
            LOG("Custom component %s was added successfuly", componentName.c_str());
        }
        else if (componentName == "TransformComponent")
        {
            component = gameObject.AddComponent<TransformComponent>();
        }
        else if (componentName == "CameraComponent")
        {
            component = gameObject.AddComponent<CameraComponent>();
        }
        else if (componentName == "FPSCameraComponent")
        {
            component = gameObject.AddComponent<FPSCameraComponent>();
        }
        else if (componentName == "MeshComponent")
        {
            component = gameObject.AddComponent<MeshComponent>();
        }
        else if (componentName == "ModelComponent")
        {
            component = gameObject.AddComponent<ModelComponent>();
        }
        else if (componentName == "AnimatorComponent")
        {
            component = gameObject.AddComponent<AnimatorComponent>();
        }
        else if (componentName == "RigidBodyComponent")
        {
            component = gameObject.AddComponent<RigidBodyComponent>();
        }
        else if (componentName == "SoundBankComponent")
        {
            component = gameObject.AddComponent<SoundBankComponent>();
        }
        else if (componentName == "SoundEffectComponent")
        {
            component = gameObject.AddComponent<SoundEffectComponent>();
        }
        else if (componentName == "UISpriteComponent")
        {
            component = gameObject.AddComponent<UISpriteComponent>();
        }
        else if (componentName == "UIButtonComponent")
        {
            component = gameObject.AddComponent<UIButtonComponent>();
        }
        else if (componentName == "UITextComponent")
        {
            component = gameObject.AddComponent<UITextComponent>();
        }
        else
        {
            ASSERT(false, "GameObjectFactory: unrecognized component %s", componentName.c_str());
        }

        return component;
    }
}

void GameObjectFactory::SetCustomMake(CustomMake customMake)
{
    TryMake = customMake;
}

void GameObjectFactory::Make(const std::filesystem::path& templatePath, GameObject& gameObject)
{
    FILE* file = nullptr;
    auto err = fopen_s(&file, templatePath.u8string().c_str(), "r");
    ASSERT(err == 0, "GameObjectFactory: failed to open file %s", templatePath.u8string().c_str());

    char readBuffer[65536];
    rj::FileReadStream readStream(file, readBuffer, sizeof(readBuffer));
    fclose(file);

    rj::Document doc;
    doc.ParseStream(readStream);
    auto components = doc["Components"].GetObj();
    for (auto& component : components)
    {
        Component* newComponent = AddComponent(component.name.GetString(), gameObject);
        if (newComponent != nullptr)
        {
            newComponent->Deserialize(component.value);
        }
    }
}
