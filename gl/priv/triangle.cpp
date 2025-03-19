#include "triangle.hpp"

namespace gl
{
    float max3(float a, float b, float c)
    {
        return std::max(std::max(a, b), c);
    }

    float min3(float a, float b, float c)
    {
        return std::min(std::min(a, b), c);
    }

    void Triangle::init()
    {
        Triangle::triangle_cnt = 0;
    }

    Triangle::Triangle(index_t v[3])
    {
        this->indices[0] = v[0];
        this->indices[1] = v[1];
        this->indices[2] = v[2];
    }

    glm::AABB Triangle::getBoundingBox(glm::mat4 model_mat)
    {
        //TODO: potential SIMD optimization here
        glm::vec4 t_a = model_mat * glm::vec4(globalVertexBuffer[indices[0]].position, 1.0f);
        glm::vec4 t_b = model_mat * glm::vec4(globalVertexBuffer[indices[1]].position, 1.0f);
        glm::vec4 t_c = model_mat * glm::vec4(globalVertexBuffer[indices[2]].position, 1.0f);

        auto maxV = glm::vec3(
                        max3(t_a.x, t_b.x, t_c.x),
                        max3(t_a.y, t_b.y, t_c.y),
                        max3(t_a.z, t_b.z, t_c.z)
                    );
        auto minV = glm::vec3(
                        min3(t_a.x, t_b.x, t_c.x),
                        min3(t_a.y, t_b.y, t_c.y),
                        min3(t_a.z, t_b.z, t_c.z)
                    );
        
        return glm::AABB(minV, maxV);
    }
    
    Triangle::~Triangle()
    {
        ;
    }
}