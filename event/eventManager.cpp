#pragma once
#include <variant>
#include <string>
#include <optional>
#include <queue>
#include <functional>
#include <vector>
#include <unordered_map>

class Position {
public: 
    float x, y;
    int floor;
    
    Position(float x = 0, float y = 0, int f = 0) : x(x), y(y), floor(f) {}
};

enum EventType{
    KEY_PICKED_UP,
    KEY_USED,
    DOOR_OPENED,
    DOOR_CLOSED,
    PLAYER_MOVED,
    PLAYER_CROUCHED,
    PLAYER_STOOD_UP,
    ENTITY_ALERTED,             // Goes to alerted location
    ENTITY_NOT_CHASING,         // Moves in random direction
    ENTITY_CHASING,             // Moves towards player
    FLOOR_CREAKED,              // Makes floor creaking sound and Gives alert to entity
    ITEM_PICKED,                // Check inventory and take new item (if already has old item then pick new drop old)
    ITEM_DROPPED,               // Makes sound
    GUN_FIRED,                  // Update ammo, cooldown, (stun entity if properly done)
    GAME_WON,                   // If main door opens
    GAME_LOST,                  // If all lives over
    STUNNED,                    // Player/Entity stunned for some time
    USED_STAIRS,                // Player/Entity used stairs (bothways)
    ENTERED_SAFE_AREA,          // Entity can't catch player, player need to crouch
    EXIT_SAFE_AREA,
    INTERACT,                   // Interact with door/item/key
    SPEED_TILE_ENTER,
    SPEED_TILE_EXIT,
    MASTER_DOOR_OPENED,         // Opens if there are 3 keys
    SECOND_ENTITY_SPAWNED,      // Spawns in a room in 2nd floor when entered
    SECOND_ENTITY_GONE,         // Gone after some time (30 sec)
    SECOND_ENTITY_NOT_CHASING,
    SECOND_ENTITY_CHASING,
    FALL                        // Falls from 2nd to 1st or basement, or 1st to basement
};

struct Event {
    EventType type;
    float timestamp;

    // Optional data carried by the event
    std::optional<Position> position;
    std::optional<std::string> itemName;
    std::optional<int> intValue; // For ammo count etc.
    std::optional<bool> flagValue; // Used/crouched/stun/etc.
    std::optional<float> floatValue; // For stun duration/cooldowns/multiplier
};

class EventManager {
public:
    using Listener = std::function<void(const Event&)>;

private:
    std::queue<Event> eventQueue;
    std::unordered_map<EventType, std::vector<Listener>> listeners;

public:
    // Add event to the queue
    void addEvent(const Event& event) {
        eventQueue.push(event);
    }

    // Subscribe a listener to an event type
    void subscribe(EventType type, Listener listener) {
        listeners[type].push_back(listener);
    }

    // Poll and dispatch all events to the appropriate listeners
    void pollEvents() {
        while (!eventQueue.empty()) {
            Event event = eventQueue.front();
            eventQueue.pop();

            auto it = listeners.find(event.type);
            if (it != listeners.end()) {
                for (const auto& listener : it->second) {
                    listener(event);
                }
            }
        }
    }
};