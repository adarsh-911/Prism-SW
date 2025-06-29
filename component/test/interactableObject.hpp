#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm-aabb/AABB.hpp>
#include "event.hpp"
#include <iostream>

class InteractableObject {
private:
    std::string name;
    glm::AABB aabb;
    Position pos;
    bool isPicked = false;

public:
    InteractableObject(const std::string& n, const glm::vec3& center, const glm::vec3& size)
        : name(n), aabb(center - size * 0.5f, center + size * 0.5f) {}

    void setPosition(const glm::vec3& pos) {
        glm::vec3 size = aabb.getDiagonal();
        aabb = glm::AABB(pos - size * 0.5f, pos + size * 0.5f);
    }

    void pick() { isPicked = true; }

    void drop(const glm::vec3& pos) {
        isPicked = false;
        setPosition(pos);
    }

    void updatePosition(const Position& newPos) {
        if (isPicked) {
            pos = newPos;
        }
    }

    bool isHeld() const { return isPicked; }
    std::string getName() const { return name; }

    bool intersects(const glm::AABB& other) const {
        return aabb.overlaps(other);
    }

    void handleEvent(const Event& e) {
        if (e.itemName != name) return;
        if (e.type == ITEM_PICKED) {
            pick();
            std::cout << "[Object] Picked: " << name << "\n";
        } else if (e.type == ITEM_DROPPED) {
            drop(e.position);
            std::cout << "[Object] Dropped: " << name << "\n";
        }
    }

    const glm::AABB& getAABB() const { return aabb; }
};