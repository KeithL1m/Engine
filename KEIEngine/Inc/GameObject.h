#pragma once

#include "Component.h"

namespace KEIEngine
{
	class GameObject final
	{
	public:
		GameObject() = default;

		void Initialize();
		void Terminate();
		void DebugUI();

		void SetName(std::string& name);
		const std::string& GetName() const;
		uint32_t GetUniqueId() const;

		template<class ComponentType>
		ComponentType* AddComponent()
		{
			static_assert(std::is_base_of_v<Component, ComponentType>,
				"GameObject: componentType must be of type Component");

			ASSERT(!mInitialized, "GameObject: cannot add components once initialized");
			ASSERT(!HasA<ComponentType>(), "GameObject: already has component type");

			auto& newComponent = mComponents.emplace_back(std::make_unique<ComponentType>());
			newComponent->mOwner = this;
			return static_cast<ComponentType*>(newComponent.get());
		}

		template<class ComponentType>
		bool HasA()
		{
			// how do you find a component?
		}

		template<class ComponentType>
		const ComponentType* GetComponent() const
		{
			
		}

		template<class ComponentType>
		ComponentType* GetComponent()
		{
			return const_cast<ComponentType*>(GetComponent());
		}

	private:
		std::string mName = "EMPTY";
		bool mInitialized = false;
		uint32_t mUniqueId = 0;

		using Components = std::vector<std::unique_ptr<Component>>;
		Components mComponents;
	};
}