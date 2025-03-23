#include "model.hpp"

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

    glm::AABB getTriangleBoundingBox(size_t tid, glm::mat4 model_mat)
    {
        // get the triangle indices
        auto indices_0 = globalIndexBuffer[tid + 0];
        auto indices_1 = globalIndexBuffer[tid + 1];
        auto indices_2 = globalIndexBuffer[tid + 2];        

        //TODO: potential SIMD optimization here
        glm::vec4 t_a = model_mat * glm::vec4(globalVertexBuffer[indices_0].position, 1.0f);
        glm::vec4 t_b = model_mat * glm::vec4(globalVertexBuffer[indices_1].position, 1.0f);
        glm::vec4 t_c = model_mat * glm::vec4(globalVertexBuffer[indices_2].position, 1.0f);

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

    Model::Model()
    {
        ;
    }

    void Model::from_file(const std::string filepath)
    {
        ;
    }

    glm::AABB Model::getBoundingBox(glm::mat4 model_mat)
    {
        glm::AABB boundingBox;
        boundingBox.setNull();
        for(size_t i = 0, triangle_id = this->model_offset; i < this->triangle_cnt; i++, triangle_id += 3)
        {
            auto tBoundBox = getTriangleBoundingBox(triangle_id, model_mat);

            if(boundingBox.isNull())
            {
                boundingBox = tBoundBox;
            }
            else
            {
                boundingBox.extend(tBoundBox);
            }
        }

        return boundingBox;
    }

    Model::~Model()
    {
        ;
    }
}

