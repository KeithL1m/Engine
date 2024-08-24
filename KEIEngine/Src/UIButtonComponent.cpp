#include "Precompiled.h"
#include "UIButtonComponent.h"
#include "UIRenderService.h"
#include "GameWorld.h"

using namespace KEIEngine;
using namespace KEIEngine::Graphics;
using namespace KEIEngine::Input;

void UIButtonComponent::Initialize()
{
    for (uint32_t i = 0; i < static_cast<uint32_t>(ButtonState::Count); ++i)
    {
        if (!mButtonStateTextures[i].empty())
        {
            mButtonStates[i].Initialize(mButtonStateTextures[i]);
        }
    }

    if (mRect.right == 0 || mRect.bottom == 0)
    {
        mRect = mButtonStates[0].GetRect();
    }

    auto uiRenderService = GetOwner().GetWorld().GetService<UIRenderService>();
    uiRenderService->Register(this);
}

void UIButtonComponent::Terminate()
{
    auto uiRenderService = GetOwner().GetWorld().GetService<UIRenderService>();
    uiRenderService->Unregister(this);
}

// missing all

//void UIButtonComponent::Update(float deltaTime)
//{
//    mCurrentState = ButtonState::Default;
//
//    auto input = InputSystem::Get();
//    int mouseX = input->GetMouseScreenX();
//    int mouseY = input->GetMouseScreenY();
//    if (mouseX > mRect.left + mPosition.x && mouseX <= mRect.right = mPosition.x
//        && mouseY >= mRect.top + mPosition.y && mouseY <= mRect.bottom = mPosition.y)
//    {
//        mCurrentState = ButtonState::Hover;
//        if (input->IsMouseDown(MouseButton::LBUTTON))
//        {
//            mCurrentState = ButtonState::Click;
//        }
//        if (input->IsMousePressed(MouseButton::LBUTTON))
//        {
//            OnClick();
//        }
//    }
//
//}
//
void UIButtonComponent::Render()
{
    uint32_t buttonState = static_cast<uint32_t>(mCurrentState);
    if (mButtonStateTextures[buttonState].empty())
    {

    }
}
//
//void UIButtonComponent::Deserialize(const rapidjson::Value& value)
//{
//    for (uint32_t i = 0; i < static_cast<uint32_t>(ButtonState::Count); ++i)
//    {
//        ButtonState state = 
//        std::string buttonStateString = "";
//        switch (i)
//        {
//        case ButtonState::Default: buttonStateString = "Default" break;
//        case ButtonState::Hover: buttonStateString = "Hover" break;
//        case ButtonState::Click: buttonStateString = "Click" break;
//        case ButtonState::Disabled: buttonStateString = "Disabled" break;
//        }
//    }
//
//    if (value.HasMember("Texture"))
//    {
//        mTexturePath = value["Texture"].GetString();
//    }
//
//    if (value.HasMember("Scale"))
//    {
//        auto pos = value["Scale"].GetArray();
//        const float x = pos[0].GetFloat();
//        const float y = pos[1].GetFloat();
//        mUISprite.SetScale({ x, y });
//    }
//    if (value.HasMember("Color"))
//    {
//        auto color = value["Color"].GetArray();
//        const float r = color[0].GetFloat();
//        const float g = color[1].GetFloat();
//        const float b = color[2].GetFloat();
//        const float a = color[3].GetFloat();
//        mUISprite.SetColor({ r, g, b, a });
//    }
//    if (value.HasMember("Flip"))
//    {
//        std::string flip = value["Flip"].GetString();
//        if (flip == "None")
//        {
//            mUISprite.SetFlip(Flip::None);
//        }
//        else if (flip == "Horizontal")
//        {
//            mUISprite.SetFlip(Flip::Horizontal);
//        }
//        else if (flip == "Vertical")
//        {
//            mUISprite.SetFlip(Flip::Vertical);
//        }
//        else if (flip == "Both")
//        {
//            mUISprite.SetFlip(Flip::Both);
//        }
//        else
//        {
//            ASSERT(false, "UISpriteComponent: invalid flip %s", flip.c_str());
//        }
//    }
//}

void UIButtonComponent::OnClick()
{
    LOG("BUTTON WAS CLICKED!!!!");
}
