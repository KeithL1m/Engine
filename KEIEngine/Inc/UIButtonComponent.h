#pragma once

#include "UIComponent.h"

namespace KEIEngine {

    enum class ButtonState
    {
        None,
        Default,
        Hover,
        Click,
        Disabled,
        Count
    };

    class UIButtonComponent : public UIComponent
    {
    public:
        SET_TYPE_ID(ComponentId::UIButton);
        void Initialize() override;
        void Terminate() override;  
        //void Update(float deltaTime) override;
        void Render() override;
        //void Deserialize(const rapidjson::Value& value);

    private:
        void OnClick();

        RECT mRect = { 0, 0, 0, 0 };
        Graphics::UISprite mButtonStates[static_cast<uint32_t>(ButtonState::Count)];
        std::string mButtonStateTextures[static_cast<uint32_t>(ButtonState::Count)];
        ButtonState mCurrentState = ButtonState::Default;
    };
}