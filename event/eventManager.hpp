#pragma once

#include "event.hpp"
#include <array>
#include <queue>
#include <functional>

class EventManager {
private:
    // Queue for each event target type (e.g., player, entity, etc.)
    std::array<std::queue<Event>, COUNT> queues;
    
    // Keeps track of the current time for event timestamps
    float currentTime = 0.0f;

public:
    // Update method to increase the current time by deltaTime
    void update(float deltaTime);

    // Add a new event to the appropriate queue
    void addEvent(const Event& e);

    // Dispatch events to the correct handlers
    void dispatch(
        const std::function<void(const Event&)>& playerHandler,
        const std::function<void(const Event&)>& entityHandler
    );

private:
    // Dispatch a queue for a specific target (e.g., player, entity)
    void dispatchQueue(EventTarget target, const std::function<void(const Event&)>& handler);
};

