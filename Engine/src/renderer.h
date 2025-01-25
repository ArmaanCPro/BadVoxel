#pragma once

#include "Shader.h"
#include <vector>


class Camera;

namespace BV
{
    class renderer;

}

class BV::renderer
{
public:
    renderer(std::string vsPath = "shaders/vertex.glsl", std::string fsPath = "shaders/fragment.glsl") : shader(vsPath.c_str(), fsPath.c_str()) {}
    ~renderer() { reset(); }

    void init();
    void add_cube(const glm::vec3& position);
    void load_vertices(const float* verts, size_t size);
    void draw_vertices(const Camera& camera, float screenWidth, float screenHeight, bool wireframe = false);
    void set_texture(const std::string& texturePath, unsigned int imageFormat = GL_RGBA);
    void reset();
private:
    unsigned int VAO, VBO;
    Shader shader;
    unsigned int textureID;
    std::vector<float> vertices;
};