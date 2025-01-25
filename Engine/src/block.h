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
    glm::vec3 m_pos = glm::vec3{0};
    
    // contains position and texcoord, also in model space
    // Unique vertices: Positions and Texture Coords
    static constexpr float vertices[] = {
        // Positions          // Texture Coords
        -1.0f, -1.0f, -1.0f,  0.0f, 0.0f, // 0 - Back Bottom Left
         1.0f, -1.0f, -1.0f,  1.0f, 0.0f, // 1 - Back Bottom Right
         1.0f,  1.0f, -1.0f,  1.0f, 1.0f, // 2 - Back Top Right
        -1.0f,  1.0f, -1.0f,  0.0f, 1.0f, // 3 - Back Top Left

        -1.0f, -1.0f,  1.0f,  0.0f, 0.0f, // 4 - Front Bottom Left
         1.0f, -1.0f,  1.0f,  1.0f, 0.0f, // 5 - Front Bottom Right
         1.0f,  1.0f,  1.0f,  1.0f, 1.0f, // 6 - Front Top Right
        -1.0f,  1.0f,  1.0f,  0.0f, 1.0f, // 7 - Front Top Left
    };
    
    // Indices defining 12 triangles (2 triangles per face, 6 faces total)
    static constexpr unsigned int indices[] = {
        // Back face (quad made of 2 triangles)
        0, 1, 2, // Triangle 1
        2, 3, 0, // Triangle 2

        // Front face
        4, 5, 6, // Triangle 1
        6, 7, 4, // Triangle 2

        // Left face
        3, 7, 4, // Triangle 1
        4, 0, 3, // Triangle 2

        // Right face
        1, 5, 6, // Triangle 1
        6, 2, 1, // Triangle 2

        // Bottom face
        0, 1, 5, // Triangle 1
        5, 4, 0, // Triangle 2

        // Top face
        3, 2, 6, // Triangle 1
        6, 7, 3  // Triangle 2
    };

};

/*
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
    */