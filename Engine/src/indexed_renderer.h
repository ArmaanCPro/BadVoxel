#pragma once

#include "Camera.h"
#include "Camera.h"
#include "Camera.h"
#include "Camera.h"
#include "renderer.h"

namespace BV
{
    class indexeded_renderer;
}

class BV::indexeded_renderer : public BV::renderer
{
public:
    void init() override;

    void load_face(const float* vertsIn, const uint32_t* indicesIn, uint32_t num_verts, uint32_t num_indices, const glm::vec3& position);

    void draw_vertices(const Camera& camera, float screenWidth, float screenHeight, bool wireframe) override;
private:
    unsigned int EBO = 0;

    std::vector<unsigned int> indices;
};