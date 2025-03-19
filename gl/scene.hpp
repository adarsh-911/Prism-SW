#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>

#include <global/panic.hpp>
#include "model.hpp"
#include "object.hpp"

namespace gl
{
    typedef std::unordered_map<std::string, uint16_t> model_name_map_t;

    class Scene
    {
        private:
            std::vector<Model*> scene_models;
            std::unordered_map<std::string, uint16_t> model_name_map;

            std::vector<Object> scene_objects;
            std::unordered_map<std::string, uint16_t> obj_name_map;
        public:
            bool isCurrentScene = false;
        public:
            Scene() {};

            /// @brief Makes a model
            /// @param model_name the name of the model
            /// @return the new model
            Model& make_model(const std::string& model_name);
            /// @brief Makes a object
            /// @param inst_model_name the name of the model this object is instantiated from
            /// @param object_name the name of the object
            /// @return nullptr if model was not found.
            Object* make_object(const std::string& inst_model_name, const std::string& object_name);

            /// @brief Get a object with a name
            /// @param object_name The object containing a 
            /// @return nullptr if object was not found.
            Object* get_object(const std::string& object_name);

            inline std::vector<Object>& getSceneObjects() { return scene_objects; }

            // deletes all the models
            ~Scene();
    };
}
