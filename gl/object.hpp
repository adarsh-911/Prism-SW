#pragma once

#include <iostream>

#include "model.hpp"

namespace gl
{
    class Object : public BoundedGeometry
    {
        private:
            Model* model;
            glm::mat4 rotation;

            glm::vec3 total_force;
            glm::vec3 total_impluse;
        public:
            // will this object not move at all?
            bool isStatic = true;
            // should this object be rendered?
            bool isVisible = false;
            // should this object be considered for physics calculation?
            bool isActive = true;

            glm::vec3 position;
            glm::vec3 scale;

            float mass;
            glm::vec3 velocity;
        public:
            Object() : model(nullptr), mass(1.0f), scale(1.0f) {};
            Object(Model* _model) : mass(1.0f), scale(1.0f) {  model = _model; }

            // applies rotation on top of existing rotation
            void rotate(glm::vec3 axis, float angle_in_radians);
            // sets the rotation of the model
            void set_rotation(glm::vec3 axis, float angle_in_radians);

            // update the physics of the system
            void euler_update(float deltaTime);

            // apply some force to the object
            void apply_force(glm::vec3 force);

            // apply some impluse to the object
            void apply_impulse(glm::vec3 impulse);

            // get the matrix appyling all the transformations done to it
            glm::mat4 get_model_matrix();

            // get the bounding box of the object
            glm::AABB getBoundingBox();

            ~Object() = default;
    };
}


