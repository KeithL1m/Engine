#pragma once

namespace KEIEngine
{
    class AppState
    {
    public:
        virtual ~AppState() = default;
        virtual void Initialize() {}
        virtual void Terminate() {}
        virtual void Update(float deltaTime) {} // read inout and graphicsSystem::Get->SetClearColor(Colors::red)... press another, set another color)
        virtual void Render() {}
        virtual void DebugUI() {}
    };
}