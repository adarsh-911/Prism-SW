#include "scene.hpp"

namespace gl
{
    Model& Scene::make_model(const std::string &model_name)
    {
        this->model_name_map[model_name] = this->scene_models.size();
        this->scene_models.push_back(new Model());
        return *this->scene_models.back();
    }

    Object* Scene::make_object(const std::string &inst_model_name, const std::string &object_name)
    {
        if( this->model_name_map.find(inst_model_name) == this->model_name_map.end() )
        {
            return nullptr;
        }

        auto modelID = this->model_name_map[inst_model_name];
        auto model = this->scene_models[modelID];

        this->obj_name_map[object_name] = this->scene_models.size();

        this->scene_objects.push_back(Object(model));

        return &this->scene_objects.back();
    }
    Object *Scene::get_object(const std::string &object_name)
    {
        if( this->obj_name_map.find(object_name) == this->obj_name_map.end() )
        {
            return nullptr;
        }
        auto objID = this->obj_name_map[object_name];

        return &this->scene_objects[objID];
    }
    Scene::~Scene()
    {
        for(auto model : this->scene_models )
        {
            delete model;
        }
    }
}
