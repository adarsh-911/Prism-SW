#include "model.hpp"

namespace gl
{
    Model::Model()
    {
        ;
    }

    glm::AABB Model::getBoundingBox(glm::mat4 model_mat)
    {
        glm::AABB boundingBox;
        boundingBox.setNull();
        for(auto& triangle : this->triangle_buffer)
        {
            auto tBoundBox = triangle.getBoundingBox(model_mat);

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

