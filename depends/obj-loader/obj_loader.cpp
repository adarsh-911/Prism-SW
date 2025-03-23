#pragma once
/*
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "gl/model.hpp" 
#include "gl/priv/buffers.hpp"
#include "gl/priv/vertex.hpp"

namespace gl {

class OBJLoader 
{
public:
    // Load an OBJ file and return a Model
    static Model* loadOBJ(const std::string& path) 
    {
        std::ifstream file(path);
        if (!file.is_open()) 
        {
            std::cerr << "Load OBJ File FAILED. File at :" << path << "not found." <<std::endl;
            return nullptr;
        }

        // temp vars
        std::vector<glm::vec3> temp_positions;
        std::vector<glm::vec2> temp_texcoords;
        std::vector<glm::vec3> temp_normals;
        
        Model* model = new Model();
        
        // Base index for the vertices (to account for exisiting global buffer)
        size_t base_index = gl::globalVertexBuffer.size();
        
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string prefix;
            iss >> prefix;

            // Vertex data
            if (prefix == "v") 
            {
                glm::vec3 position;
                iss >> position.x >> position.y >> position.z;
                temp_positions.push_back(position);
            }

            // Texture coordinates
            else if (prefix == "vt") 
            {
                glm::vec2 texcoord;
                iss >> texcoord.x >> texcoord.y;
                temp_texcoords.push_back(texcoord);
            }

            // Normals
            else if (prefix == "vn") 
            {
                glm::vec3 normal;
                iss >> normal.x >> normal.y >> normal.z;
                temp_normals.push_back(normal);
            }

            // Face data
            else if (prefix == "f") 
            {
                processFace(iss, temp_positions, temp_texcoords, model, base_index);
            }
            // No Support for Materials, Groups, etc, for now
        }

        file.close();
        return model;
    }

private:
    // Process a face line and add the resulting triangle(s) to the model
    static void processFace(std::istringstream& iss, 
                            const std::vector<glm::vec3>& positions,
                            const std::vector<glm::vec2>& texcoords,
                            Model* model, size_t base_index) {
        std::string vertex_data;
        std::vector<index_t> face_indices;
        
        while (iss >> vertex_data) 
        {
            // vertex_data : (format: vertex_idx/texcoord_idx/normal_idx)
            std::vector<int> indices = parseVertexData(vertex_data);
            
            // OBJ indices are 1-based, convert to 0-based
            int pos_idx = indices[0] - 1;
            
            // create new vertex
            vertex_t new_vertex;
            new_vertex.position = positions[pos_idx];
            
            // set texture coordinates
            if (indices.size() > 1 && indices[1] > 0 && !texcoords.empty()) 
            {
                int tex_idx = indices[1] - 1;
                new_vertex.texture_uv = texcoords[tex_idx];
            } 
            else 
            {
                new_vertex.texture_uv = glm::vec2(0.0f, 0.0f);
            }
            
            // add vertex to global buffer
            gl::globalVertexBuffer.push_back(new_vertex);
            
            face_indices.push_back(base_index + gl::globalVertexBuffer.size() - 1);
        }
        
        // make triangles the face (assumes convex polygon)
        for (size_t i = 1; i < face_indices.size() - 1; ++i) 
        {
            index_t triangle_indices[3] = {face_indices[0], face_indices[i], face_indices[i + 1]};
            // Add the triangle
            model->triangle_buffer.push_back(Triangle(triangle_indices));
        }
    }
    
    // Parse vertex data in the format "v/vt/vn" or "v//vn" or "v/vt" or "v"
    static std::vector<int> parseVertexData(const std::string& vertex_data) {
        std::vector<int> indices;
        std::stringstream ss(vertex_data);
        std::string index;
        
        while (std::getline(ss, index, '/')) {
            if (index.empty()) {
                indices.push_back(0); // handle no index 
            } else {
                indices.push_back(std::stoi(index));
            }
        }
        
        return indices;
    }
};

}*/