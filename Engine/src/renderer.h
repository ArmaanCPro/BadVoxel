#pragma once

#include "Shader.h"

class Camera;

namespace BV
{
    class renderer;
}

class BV::renderer
{
public:
    renderer() = default;
    ~renderer() { reset(); }

    void init(std::string vsPath = "shaders/vertex.glsl", std::string fsPath = "shaders/fragment.glsl");
    void add_cube(const glm::vec3& position);
    void load_vertices(const float* verts, size_t size);
    void draw_vertices(const Camera& camera, float screenWidth, float screenHeight, bool wireframe = false);
    void set_texture(std::string texturePath);
    void reset();
private:
    unsigned int VAO, VBO;
    Shader shader;
    unsigned int textureID;
    std::vector<float> vertices;
};