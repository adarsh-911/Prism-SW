#pragma once
#include <bits/stdc++.h>
#include <glm/glm.hpp>
#include <object.hpp>

struct Button {
  bool forward, right, left, backward;
  Button(bool f = false, bool r = false, bool l = false, bool b = false) : forward(f), right(r), left(l), backward(b) {}
};

class Player {
public:
  Player();
  void setPosition(float x, float y, float z);
  void setDirection(float x, float y, float z);

  glm::vec3 getPosition() const;
  glm::vec3 getDirection() const;

  // Interrupt callback for buttons
  void handleButtons(Button button);

  void updatePosition(float deltaTime);
  void updateDirection();

  glm::vec3 getPosition() const;
  glm::vec3 getDirection() const;
  
private:
  glm::vec3 position;
  glm::vec3 direction;
  glm::vec3 velocity;
  float speed;

  void onCollision(const Object* obj, std::string state);
};