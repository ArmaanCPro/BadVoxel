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
    // make sure to call init() after constructing the object!
    renderer(std::string vsPath = "shaders/vertex.glsl", std::string fsPath = "shaders/fragment.glsl") : shader(vsPath.c_str(), fsPath.c_str()) {}
    ~renderer() { reset(); }
    renderer(const renderer&) = delete;
    renderer& operator=(const renderer&) = delete;

    // initializes all OpenGL stuff. Constructor does not call this.
    void init();

    // currently no rotation or size.
    void add_cube(const glm::vec3& position);
    // Used internally but can also be used externally to load vertices into the buffer. Make sure the vertices are in the layout of 3 for the position and 2 for the texcoords.
    void load_vertices(const float* verts, size_t size);

    // this is the final draw call. it should handle all opengl related rendering commands, so you shouldn't have those in your render loop.
    void draw_vertices(const Camera& camera, float screenWidth, float screenHeight, bool wireframe = false);

    /* @params
     * texturePath - this is the filepath to the texture.
     * imageFormat - this is the RGBA format of the image. Generally only GL_RGBA or GL_RGB */
    void set_texture(const std::string& texturePath, unsigned int imageFormat = GL_RGBA);

    // the reset function basically reverts all allocations. is called in the destructor
    void reset();
private:
    unsigned int VAO = 0, VBO = 0;
    Shader shader;
    unsigned int textureID = 0;
    std::vector<float> vertices;
};