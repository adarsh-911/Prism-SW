#include "object.hpp"

#include <global/panic.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace gl
{
    void Object::rotate(glm::vec3 axis, float angle_in_radians)
    {
        this->rotation = glm::rotate(this->rotation, angle_in_radians, axis);
    }
    void Object::set_rotation(glm::vec3 axis, float angle_in_radians)
    {
        this->rotation = glm::rotate(glm::mat4(1.0f), angle_in_radians, axis);
    }
    void Object::euler_update(float deltaTime)
    {
        // reset the total_force and total_impluse
        this->total_force = glm::vec3(0);
        this->total_impluse = glm::vec3(0);

        // if the object is static/not active, no need to update
        if(this->isStatic || !this->isActive) return;

        this->velocity += (this->total_force * deltaTime + this->total_impluse) / this->mass;
        this->position += this->velocity * deltaTime;
    }
    void Object::apply_force(glm::vec3 force)
    {
        this->total_force += force;
    }
    void Object::apply_impulse(glm::vec3 impulse)
    {
        this->total_impluse += impulse;
    }
    glm::mat4 Object::get_model_matrix()
    {
        auto translation = glm::translate(glm::mat4(1.0f), this->position);
        auto scale = glm::scale(glm::mat4(1.0f), this->scale);

        return translation * rotation * scale;
    }
    glm::AABB Object::getBoundingBox()
    {
        if(!this->model) PANIC("model is nullptr!");

        return this->model->getBoundingBox(this->get_model_matrix());
    }
}
