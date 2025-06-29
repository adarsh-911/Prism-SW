#define GLM_ENABLE_EXPERIMENTAL
#include "eventManager.hpp"
#include "player.hpp"
#include "interactableObject.hpp"
#include <glm/gtx/string_cast.hpp> // for glm::to_string

int main() {
    EventManager manager;
    Player player(glm::vec3(10.0f, 0.0f, 20.0f));
    InteractableObject vase("vase", glm::vec3(10.0f, 0.0f, 20.0f), glm::vec3(1.0f));
    InteractableObject book("book", glm::vec3(12.0f, 0.0f, 21.0f), glm::vec3(1.0f));
    std::vector<InteractableObject*> objects = { &vase, &book };

    std::cout << "== Player tries to pick 'vase' ==\n";
    player.tryPick(objects, manager);

    manager.dispatch(
        [&](const Event& e) {
            player.handleEvent(e, objects, manager);
            for (auto* obj : objects) obj->handleEvent(e);
        },
        [](const Event& e) {
            if (e.type == ENTITY_ALERTED)
                std::cout << "[Entity] Alerted to drop: " << e.itemName << " at " << glm::to_string(e.position) << "\n";
        }
    );

    std::cout << "\n== Player moves to book's position ==\n";
    player.move(glm::vec3(5.0f, 0.0f, 5.0f), 1.0f);
    std::cout << "Player Position now: " << player.getPosition() << std::endl;
    player.updateHeldItemPosition();

    std::cout << "== Player tries to pick 'book' (should drop 'vase') ==\n";
    player.tryPick(objects, manager);

    manager.dispatch(
        [&](const Event& e) {
            player.handleEvent(e, objects, manager);
            for (auto* obj : objects) obj->handleEvent(e);
        },
        [](const Event& e) {
            if (e.type == ENTITY_ALERTED)
                std::cout << "[Entity] Alerted to drop: " << e.itemName << " at " << glm::to_string(e.position) << "\n";
        }
    );

    std::cout << "\n== Player moves away ==\n";
    player.move(glm::vec3(35.0f, 0.0f, 20.0f), 1.0f);
    std::cout << "Player Position now: " << player.getPosition() << std::endl;
    player.updateHeldItemPosition();

    std::cout << "== Player drops current item ==\n";
    player.tryDrop(manager);

    manager.dispatch(
        [&](const Event& e) {
            player.handleEvent(e, objects, manager);
            for (auto* obj : objects) obj->handleEvent(e);
        },
        [](const Event& e) {
            if (e.type == ENTITY_ALERTED)
                std::cout << "[Entity] Alerted to drop: " << e.itemName << " at " << glm::to_string(e.position) << "\n";
        }
    );

    return 0;
}
