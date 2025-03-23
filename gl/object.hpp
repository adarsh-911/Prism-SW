#pragma once

#include <iostream>

#include "BoundedObject.hpp"
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

            // has the geometry been updated?
            bool has_geometry_updated = false;

            // current bounding box
            glm::AABB boundingBox;

            glm::vec3 currPosition;
            glm::vec3 currScale;
        public:
            // will this object not move at all?
            bool isStatic = true;
            // should this object be rendered?
            bool isVisible = false;
            // should this object be considered for physics calculation?
            bool isActive = true;

            // read-only properties
            const glm::vec3& position = currPosition;
            const glm::vec3& scale = currScale;

            float mass;
            glm::vec3 velocity;
        public:
            Object() : currScale(1.0f), mass(1.0f) {};

            // laod a object from .obj file
            void from_model(Model& model);

            // set positon of the object
            inline void set_position(glm::vec3 position) { this->has_geometry_updated = true; this->currPosition = position; }

            // set scale of the object
            inline void set_scale(glm::vec3 scale) { this->has_geometry_updated = true; this->currScale = scale; }

            // applies rotation on top of existing rotation
            void rotate(glm::vec3 axis, float angle_in_radians);
            // sets the rotation of the model
            void set_rotation(glm::vec3 axis, float angle_in_radians);

            // update the physics of the system
            void euler_update(float deltaTime);

            // update the geometry of the object
            void geometry_update();

            // apply some force to the object
            void apply_force(glm::vec3 force);

            // apply some impluse to the object
            void apply_impulse(glm::vec3 impulse);

            // get the matrix appyling all the transformations done to it
            glm::mat4 get_model_matrix() const;

            // get the bounding box of the object
            glm::AABB getBoundingBox() const override;

            // draw the object
            void draw() const;

            ~Object() = default;
    };
}


