#pragma once

#include <string>
#include <glm/glm.hpp>

namespace BV
{
    class block;
}

// todo: implement blocks in renderer. also need to know location of quads
class BV::block
{
public:
    block(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& m_color = {0});
    
private:
    // world space position
    glm::vec3 m_pos = {0};
    glm::vec3 m_color = {0};
    // contains position and texcoord, also in model space
    static constexpr float vertices[] = {
                // Positions              // Texture Coords
        // Back face
        -1.0f, -1.0f, -1.0f,      0.0f, 0.0f, // bottom-left
         1.0f, -1.0f, -1.0f,      1.0f, 0.0f, // bottom-right
         1.0f,  1.0f, -1.0f,      1.0f, 1.0f, // top-right
         1.0f,  1.0f, -1.0f,      1.0f, 1.0f, // top-right
        -1.0f,  1.0f, -1.0f,      0.0f, 1.0f, // top-left
        -1.0f, -1.0f, -1.0f,      0.0f, 0.0f, // bottom-left

        // Front face
        -1.0f, -1.0f,  1.0f,      0.0f, 0.0f, // bottom-left
         1.0f, -1.0f,  1.0f,      1.0f, 0.0f, // bottom-right
         1.0f,  1.0f,  1.0f,      1.0f, 1.0f, // top-right
         1.0f,  1.0f,  1.0f,      1.0f, 1.0f, // top-right
        -1.0f,  1.0f,  1.0f,      0.0f, 1.0f, // top-left
        -1.0f, -1.0f,  1.0f,      0.0f, 0.0f, // bottom-left

        // Left face
        -1.0f,  1.0f,  1.0f,      1.0f, 0.0f, // top-right
        -1.0f,  1.0f, -1.0f,      1.0f, 1.0f, // top-left
        -1.0f, -1.0f, -1.0f,      0.0f, 1.0f, // bottom-left
        -1.0f, -1.0f, -1.0f,      0.0f, 1.0f, // bottom-left
        -1.0f, -1.0f,  1.0f,      0.0f, 0.0f, // bottom-right
        -1.0f,  1.0f,  1.0f,      1.0f, 0.0f, // top-right

        // Right face
         1.0f,  1.0f,  1.0f,      1.0f, 0.0f, // top-left
         1.0f,  1.0f, -1.0f,      1.0f, 1.0f, // top-right
         1.0f, -1.0f, -1.0f,      0.0f, 1.0f, // bottom-right
         1.0f, -1.0f, -1.0f,      0.0f, 1.0f, // bottom-right
         1.0f, -1.0f,  1.0f,      0.0f, 0.0f, // bottom-left
         1.0f,  1.0f,  1.0f,      1.0f, 0.0f, // top-left

        // Bottom face
        -1.0f, -1.0f, -1.0f,      0.0f, 1.0f, // top-right
         1.0f, -1.0f, -1.0f,      1.0f, 1.0f, // top-left
         1.0f, -1.0f,  1.0f,      1.0f, 0.0f, // bottom-left
         1.0f, -1.0f,  1.0f,      1.0f, 0.0f, // bottom-left
        -1.0f, -1.0f,  1.0f,      0.0f, 0.0f, // bottom-right
        -1.0f, -1.0f, -1.0f,      0.0f, 1.0f, // top-right

        // Top face
        -1.0f,  1.0f, -1.0f,      0.0f, 1.0f, // top-left
         1.0f,  1.0f, -1.0f,      1.0f, 1.0f, // top-right
         1.0f,  1.0f,  1.0f,      1.0f, 0.0f, // bottom-right
         1.0f,  1.0f,  1.0f,      1.0f, 0.0f, // bottom-right
        -1.0f,  1.0f,  1.0f,      0.0f, 0.0f, // bottom-left
        -1.0f,  1.0f, -1.0f,      0.0f, 1.0f  // top-left
    };
};