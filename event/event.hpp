#pragma once
#include <string>
#include "position.hpp"

enum EventType {
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

enum EventTarget {
    PLAYER,
    ENTITY,
    SECOND_ENTITY,
    UI,
    SOUND_SYSTEM,
    COUNT
};

struct Event {
    EventType type;
    EventTarget target;
    float timestamp;

    // Data carried by the event
    Position position;
    std::string itemName;
    int intValue; // For ammo count etc.
    bool flagValue; // Used/crouched/stun/etc.
    float floatValue; // For stun duration/cooldowns/multiplier
};