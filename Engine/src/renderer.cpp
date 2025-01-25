#include "renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include <stb_image.h>

#include <algorithm>

void BV::renderer::init()
{
    shader.use();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // texture bullshits
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    // texture wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    // texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void BV::renderer::add_cube(const glm::vec3& position)
{
    // Cube data for 6 faces
    constexpr float cubeVertices[] = {
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

    // [Transform cubeVertices to world space using position and append them to the renderer's vertex list]
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(0.5f));
    model_tforms.push_back(model);
    // don't need rotation

    load_vertices(cubeVertices, 180);
}

void BV::renderer::load_vertices(const float* verts, size_t size)
{
    std::copy(verts, verts + size, std::back_inserter(vertices));
    
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
}

void BV::renderer::draw_vertices(const Camera &camera, float screenWidth, float screenHeight, bool wireframe)
{
    if (wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    shader.use();
    
    glm::mat4 view = camera.GetViewMatrix();
    shader.SetMat4("view", view);

    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), screenWidth / screenHeight, 0.1f, 100.0f);
    shader.SetMat4("projection", projection);

    //
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBindVertexArray(VAO);
    // / 180 because there are 180 floats in one cube
    for (size_t i = 0; i < vertices.size() / 180; i++)
    {
	    glm::mat4 model = glm::mat4(1.0f);
        model *= model_tforms[i];
		shader.SetMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    glDrawArrays(GL_TRIANGLES, 0, (int)vertices.size() / 5); // Assuming 5 floats per vertex (pos + texture)
    glBindVertexArray(0);
}

void BV::renderer::set_texture(const std::string& texturePath, unsigned int imageFormat)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << texturePath << std::endl;
    }
    stbi_image_free(data);
    data = nullptr;
    
    shader.use();
    
    //tell opengl for each sampler which texture unit it belongs
    shader.SetInt("texture1", 0);
}
void BV::renderer::reset()
{
    vertices.clear();
    vertices.shrink_to_fit();

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteTextures(1, &textureID);
}
