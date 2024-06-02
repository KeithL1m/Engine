#include "Precompiled.h"
#include "EventManager.h"

using namespace KEIEngine;

namespace
{
	std::unique_ptr<EventManager> sEventManager;
}

void EventManager::StaticInitialize()
{
	ASSERT(sEventManager == nullptr, "EventManager: is already initialized");
	sEventManager = std::make_unique<EventManager>();
	sEventManager->Initialize();
}

void EventManager::StaticTerminate()
{
	if (sEventManager != nullptr)
	{
		sEventManager->Terminate();
		sEventManager.reset();
	}
}

EventManager* KEIEngine::EventManager::Get()
{
	ASSERT(sEventManager == nullptr, "EventManager: is not initialized");
	return sEventManager.get();
}

void EventManager::Broadcast(const Event* event)
{
	EventManager::Get()->BroadcastPrivate(event);
}


void EventManager::Initialize()
{
	mListeners.clear();
}

void EventManager::Terminate()
{
	mListeners.clear();
}

void EventManager::AddListener(EventType eventType, EventCallback&& cb)
{
	mListeners[eventType].push_back(cb);
}

void EventManager::RemoveListener(EventType eventType, EventCallback&& cb)
{
	//auto& listeners = mListeners[eventType];
	//auto iter = std::find(listeners.begin(), listeners.end(), cb);
	//if (iter != listeners.end())
	//{
	//	listeners.erase(iter);
	//}
}

void EventManager::BroadcastPrivate(const Event* event)
{
	auto& listeners = mListeners[event->GetType()];

	for (auto& cb : listeners)
	{
		cb(event);
	}
}