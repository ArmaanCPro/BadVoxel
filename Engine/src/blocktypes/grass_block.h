#pragma once

#include "block.h"

namespace BV
{
    class grass_block;
}

class BV::grass_block : public BV::block
{
public:
    grass_block(const glm::vec3& position)
        :
    block(position, glm::vec3(12, 230, 16))
    {}
};
