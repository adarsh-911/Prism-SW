#ifndef EVENT_H
#define EVENT_H
#include <vector>
#include <functional>
#include <unordered_map>
#include <memory>
#include <string>
#include <iostream>
#include <queue>
#include <math.h>

class Position {
public: 
    float x, y;
    int floor;
    
    Position(float x = 0, float y = 0, int f = 0) : x(x), y(y), floor(f) {}
};


class Event {
public: 
    enum Type{
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

    Type type;
    float timestamp;

    Event(Type t): type(t), timestamp(0.0f){}
    virtual ~Event() = default;
};

class KeyPickedUpEvent: public Event{
public:
    int keyID;
    Position position;

    KeyPickedUpEvent(int id, Position p):
        Event(KEY_PICKED_UP), keyID(id), position(p){}
};

class KeyUsedEvent: public Event{
public:
    int keyID;

    KeyUsedEvent(int id):
        Event(KEY_PICKED_UP), keyID(id){}
};

class DoorEvent : public Event{
public:
    Position pos;

    DoorEvent(Type t, Position p): Event(t), pos(p){}
};

class PlayerMovedEvent: public Event{
public:
    Position newPos;

    PlayerMovedEvent(Position p): Event(PLAYER_MOVED), newPos(p){}
};

class PlayerCrouchEvent: public Event{
public:
    bool crouched;

    PlayerCrouchEvent(bool state): Event(state ? PLAYER_CROUCHED : PLAYER_STOOD_UP), crouched(state){}
};

class EntityAlertedEvent: public Event{
public:
    Position alertPos;

    EntityAlertedEvent(Position p):Event(ENTITY_ALERTED), alertPos(p){}
};

class FloorCreakedEvent: public Event{
public:
    Position pos;

    FloorCreakedEvent(Position p): Event(FLOOR_CREAKED), pos(p){}
};

class ItemEvent: public Event{
public:
    std::string itemName;
    Position pos;

    ItemEvent(Type t, std::string name, Position p): Event(t), itemName(name), pos(p){}
};

class GunFiredEvent: public Event{
public:
    int ammoLeft;
    float cooldown;

    GunFiredEvent(int ammo, float cd):Event(GUN_FIRED), ammoLeft(ammo), cooldown(cd){}
};

class StunnedEvent: public Event{
public:
    int userID;
    float duration;

    StunnedEvent(int id, float dur): Event(STUNNED), userID(id),duration(dur){}
};

class StairsUsedEvent: public Event {
public: 
    int userID;
    float duration;
    Position from, to;

    StairsUsedEvent(int id, Position f, Position t, float dur) : Event(USED_STAIRS), userID(id), from(f), to(t), duration(dur){}
};

class SafeAreaEvent : public Event{
public:
    bool entered;
    Position pos;

    SafeAreaEvent(bool ent, Position p): Event(ent ? ENTERED_SAFE_AREA : EXIT_SAFE_AREA), entered(ent), pos(p){}
};

class InteractEvent : public Event{
public:
    std::string targetName;
    Position pos;
   
    InteractEvent(std::string name, Position p): Event(INTERACT), targetName(name), pos(p){}
};

class SpeedTileEvent: public Event {
public: 
    bool entered;
    float multiplier;
    Position pos;

    SpeedTileEvent(bool ent, float mul, Position p): Event(ent ? SPEED_TILE_ENTER : SPEED_TILE_EXIT), entered(ent), multiplier(mul), pos(p){}
};

class MasterDoorOpenedEvent: public Event{
public:
    MasterDoorOpenedEvent() : Event(MASTER_DOOR_OPENED){}
};

class SecondEntityEvent: public Event{
public:
    SecondEntityEvent(Type t): Event(t){}
};

class FallEvent: public Event{
public:
    int userID;
    float stunDuration;
    Position from, to;

    FallEvent(int id, Position f, Position t, float dur) : Event(FALL), userID(id), from(f), to(t), stunDuration(dur){}
};
#endif // EVENT_H
