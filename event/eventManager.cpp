#include "eventManager.hpp"

// Update the current time with the delta time
void EventManager::update(float deltaTime) {
    currentTime += deltaTime;
}

// Add an event to the appropriate queue, with a timestamp based on the current time
void EventManager::addEvent(const Event& e) {
    Event event = e;  // Make a copy of the event to modify
    event.timestamp = currentTime;  // Set the event's timestamp
    queues[event.target].push(event);  // Add to the correct target queue
}

// Dispatch all events in the player and entity queues
void EventManager::dispatch(
    const std::function<void(const Event&)>& playerHandler,
    const std::function<void(const Event&)>& entityHandler
) {
    dispatchQueue(PLAYER, playerHandler);  // Dispatch player-related events
    dispatchQueue(ENTITY, entityHandler);  // Dispatch entity-related events
}

// Helper function to dispatch all events in a specific queue
void EventManager::dispatchQueue(
    EventTarget target, 
    const std::function<void(const Event&)>& handler
) {
    auto& q = queues[target];  // Get the queue for the specified target
    while (!q.empty()) {  // Process all events in the queue
        handler(q.front());  // Handle the event
        q.pop();  // Remove the event from the queue after processing
    }
}

