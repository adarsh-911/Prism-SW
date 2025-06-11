#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "gl.hpp"
#include "graphics/types.hpp"
#include "global/panic.hpp"

namespace gl {

class OBJLoader 
{
public:
    static bool loadOBJ(const std::string& path, Model* model, gp::vertex_buffer_t& vertices, gp::index_buffer_t& indices, gp::model_id_t& model_id) 
    {
        if (!model) {
            PANIC("Invalid model pointer provided to OBJLoader");
            return false;
        }

        std::ifstream file(path);
        if (!file.is_open()) 
        {
            PANIC("Load OBJ File FAILED. File at: " + path + " not found.");
            return false;
        }

        // temp vars
        std::vector<glm::vec3> temp_positions;
        std::vector<glm::vec2> temp_texcoords;
        std::vector<glm::vec3> temp_normals;
        
        // unique vertices 
        std::unordered_map<std::string, gp::index_t> uniqueVertices;
        
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string prefix;
            iss >> prefix;

            // Vertex positions
            if (prefix == "v") 
            {
                glm::vec3 position;
                iss >> position.x >> position.y >> position.z;
                temp_positions.push_back(position);
            }

            // Tex coords
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

            // Faces
            else if (prefix == "f") 
            {
                processFace(iss, temp_positions, temp_texcoords, temp_normals, 
                            vertices, indices, uniqueVertices);
            }
            // Materials, Groups, etc. are not supported for now
        }

        // Set the vertex and index buffers in the model
        // This assumes gl::backend has been properly initialized
        if (!gl::backend) 
        {
            PANIC("Backend not initialized in OBJLoader");
            return false;
        }
        
        // Generate the model ID
        model_id = gl::backend->generateModel(vertices, indices);
        if (model_id == 0) 
        {
            PANIC("Failed to generate model ID in OBJLoader");
            return false;
        }
        file.close();
        return true;
    }

private:
    // Process a face line and build vertex/index buffers
    static void processFace(
        std::istringstream& iss, 
        const std::vector<glm::vec3>& positions,
        const std::vector<glm::vec2>& texcoords,
        const std::vector<glm::vec3>& normals,
        gp::vertex_buffer_t& vertices,
        gp::index_buffer_t& indices,
        std::unordered_map<std::string, gp::index_t>& uniqueVertices
    ) 
    {
        std::string vertex_data;
        std::vector<gp::index_t> face_indices;
        
        // Process each vertex in the face
        while (iss >> vertex_data) 
        {
            // Check if we've already seen this vertex
            if (uniqueVertices.count(vertex_data) > 0) 
            {
                // If yes, just use the existing index
                face_indices.push_back(uniqueVertices[vertex_data]);
            } 
            else 
            {
                // vertex data (format: vertex_idx/texcoord_idx/normal_idx)
                std::vector<int> parsed_indices = parseVertexData(vertex_data);
                
                gp::vertex_t new_vertex;
                
                // OBJ indices are 1-based, convert to 0-based
                int pos_idx = parsed_indices[0] - 1;
                if (pos_idx >= 0 && pos_idx < positions.size()) 
                {
                    new_vertex.position = positions[pos_idx];
                } 
                else 
                {
                    new_vertex.position = glm::vec3(0.0f);
                }
                
                // Set texture coordinates
                if (parsed_indices.size() > 1 && parsed_indices[1] > 0 && !texcoords.empty()) 
                {
                    int tex_idx = parsed_indices[1] - 1;
                    if (tex_idx >= 0 && tex_idx < texcoords.size()) {
                        new_vertex.texture_uv = texcoords[tex_idx];
                    } else {
                        new_vertex.texture_uv = glm::vec2(0.0f, 0.0f);
                    }
                } 
                else 
                {
                    new_vertex.texture_uv = glm::vec2(0.0f, 0.0f);
                }
                
                gp::index_t new_index = static_cast<gp::index_t>(vertices.size());
                vertices.push_back(new_vertex);
                uniqueVertices[vertex_data] = new_index;
                face_indices.push_back(new_index);
            }
        }
        
        // Triangulate the face (assumes convex polygon)
        for (size_t i = 1; i < face_indices.size() - 1; ++i) 
        {
            indices.push_back(face_indices[0]);
            indices.push_back(face_indices[i]);
            indices.push_back(face_indices[i + 1]);
        }
    }
    
    // Parse vertex data in the format "v/vt/vn"
    static std::vector<int> parseVertexData(const std::string& vertex_data) 
    {
        std::vector<int> indices;
        std::stringstream ss(vertex_data);
        std::string index;
        
        while (std::getline(ss, index, '/')) {
            if (index.empty()) 
            {
                indices.push_back(0); // handle no index 
            } 
            else 
            {
                indices.push_back(std::stoi(index));
            }
        }
        
        return indices;
    }
};

}