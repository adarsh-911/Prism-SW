#pragma once
#include <unordered_map>
#include <vector>
#include <queue>
#include <memory>
#include <algorithm>
#include "Event.hpp"

class EventListener {
public:
    virtual void onEvent(const std::shared_ptr<Event>& event) = 0;
    virtual ~EventListener() = default;
};

class EventManager {
private:
    std::queue<std::shared_ptr<Event>> eventQueue;
    std::unordered_map<Event::Type, std::vector<EventListener*>> listeners;
    float currentTime = 0.0f;
    bool isProcessing = false;

public:
    static EventManager& getInstance() {
        static EventManager instance;
        return instance;
    }

    EventManager() = default;

    template<typename T, typename... Args>
    void queueEvent(Args&&... args) {
        auto event = std::make_shared<T>(std::forward<Args>(args)...);
        event->timestamp = currentTime;
        eventQueue.push(event);
    }

    void subscribe(Event::Type type, EventListener* listener) {
        listeners[type].push_back(listener);
    }

    void unsubscribe(Event::Type type, EventListener* listener) {
        auto& vec = listeners[type];
        vec.erase(std::remove(vec.begin(), vec.end(), listener), vec.end());
    }

    void processEvents() {
        if (isProcessing) return;
        isProcessing = true;

        while (!eventQueue.empty()) {
            auto event = eventQueue.front();
            eventQueue.pop();

            auto it = listeners.find(event->type);
            if (it != listeners.end()) {
                for (auto* listener : it->second) {
                    listener->onEvent(event);
                }
            }
        }

        isProcessing = false;
    }

    void update(float deltaTime) {
        currentTime += deltaTime;
    }
};
