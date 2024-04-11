#pragma once
#include "core/common.hpp"
#include "simulation.hpp"

namespace renderer {
    void initialize();

    void render(std::vector<simulation::Object> const&objects);

    void cleanup();
}