#include "indexed_renderer.h"

void BV::indexeded_renderer::init()
{
    renderer::init();

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}
void BV::indexeded_renderer::load_face(const float* vertsIn, const uint32_t* indicesIn, uint32_t num_verts, uint32_t num_indices, const glm::vec3& position)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(0.5f));

    model_tforms.emplace_back(model);

    std::copy_n(vertsIn, num_verts, std::back_inserter(vertices));
    std::copy_n(indicesIn, num_indices, std::back_inserter(indices));

    glBindVertexArray(VAO);
    
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    
}
void BV::indexeded_renderer::draw_vertices(const Camera& camera, float screenWidth, float screenHeight, bool wireframe)
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
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
    glBindVertexArray(0);
}
