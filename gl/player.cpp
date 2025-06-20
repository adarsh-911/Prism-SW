#include <player.hpp>

Player::Player() : position(0.0f), direction(0.0f, 0.0f, -1.0f), velocity(0.0f), speed(1.0f) {}

void Player::setPosition(float x, float y, float z) {
  this->position = glm::vec3(x, y, z);
}

void Player::setDirection(float x, float y, float z) {
  this->direction = glm::normalize(glm::vec3(x, y, z));
}

void Player::handleButtons(Button button) {
  updateDirection();
  glm::vec3 direction2D = glm::normalize(glm::vec3(direction.x, 0.0f, direction.z)); // Floors in XZ plane
  glm::vec3 up(0.0f, 1.0f, 0.0f); // Y-axis

  if (button.forward) this->velocity = speed * direction2D;
  if (button.left) this->velocity = speed * glm::normalize(glm::cross(up, direction2D));
  if (button.right) this->velocity = speed * glm::normalize(glm::cross(direction2D, up));
  if (button.backward) this->velocity = -speed * direction2D;
}

void Player::onCollision(const Object* obj, std::string state) {
  if (state == "enter") {
    this->velocity = glm::vec3(0.0f); // Stop motion
    // Play collision sound specific to the object
  }
  if (state == "stay") {
    glm::vec3 normal = obj->getCollisionNormal(position);

    // Project velocity onto the tangent (sliding direction)
    glm::vec3 slide = velocity - glm::dot(velocity, normal) * normal;
    this->velocity = slide;
  }
  if (state == "exit") {
    ; // Exit collision-specific UI
  }
}

void Player::updatePosition(float deltaTime) {
  this->position += velocity * deltaTime;
}

void Player::updateDirection() {
  // this->direction = glm::normalize(gyro.getOrientation());
}

glm::vec3 Player::getPosition() const {
  return this->position;
}

glm::vec3 Player::getDirection() const {
  return this->direction;
}
