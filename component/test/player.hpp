#pragma once
#include <glm/glm.hpp>
#include <glm-aabb/AABB.hpp>
#include <vector>
#include "interactableObject.hpp"
#include "eventManager.hpp"

class Player {
private:
    glm::vec3 position;
    glm::vec3 velocity;
    float speed = 2.0f;
    glm::AABB aabb;
    InteractableObject* heldItem = nullptr;

public:
    Player(const glm::vec3& pos)
        : position(pos), velocity(0.0f), aabb(pos - glm::vec3(0.5f), pos + glm::vec3(0.5f)) {}

    void move(const glm::vec3& dir, float deltaTime) {
        velocity = glm::normalize(dir) * speed;
        position += velocity * deltaTime;
        glm::vec3 halfSize = aabb.getDiagonal() * 0.5f;
        aabb = glm::AABB(position - halfSize, position + halfSize);
        if (heldItem) heldItem->setPosition(position);
    }

    void tryPick(std::vector<InteractableObject*>& object, EventManager& manager) {
        for (auto* obj : object) {
            if (!obj->isHeld() && obj->intersects(aabb)) {
                if (heldItem) {
                    Event dropOld{ ITEM_DROPPED, PLAYER, 0.0f, position, heldItem->getName() };
                    manager.addEvent(dropOld);
                    Event alertEntity{ ENTITY_ALERTED, ENTITY, 0.0f, position, heldItem->getName() };
                    manager.addEvent(alertEntity);
                }
                heldItem = obj;
                Event pickNew{ ITEM_PICKED, PLAYER, 0.0f, position, obj->getName() };
                manager.addEvent(pickNew);
                break;
            }
        }
    }

    void tryDrop(EventManager& manager) {
        if (heldItem) {
            Event drop{ ITEM_DROPPED, PLAYER, 0.0f, position, heldItem->getName() };
            manager.addEvent(drop);
            Event alert{ ENTITY_ALERTED, ENTITY, 0.0f, position, heldItem->getName() };
            manager.addEvent(alert);
            heldItem = nullptr;
        }
    }

    void handleEvent(const Event& e, std::vector<InteractableObject*>& object, EventManager& manager) {
        if (e.type == ITEM_DROPPED && heldItem && heldItem->getName() == e.itemName) {
            heldItem = nullptr;
        }
    }

    void updateHeldItemPosition() {
        if (heldItem) {
            heldItem->updatePosition(position);
        }
    }

    glm::vec3 getPosition() const { return position; }
    glm::AABB getAABB() const { return aabb; }
};