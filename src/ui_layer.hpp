#pragma once
#include "core/common.hpp"

namespace ui_layer{
    void initialize();

    void cleanup();

    void drawBox(float x, float y, float w, float h, vec3 color);

    void drawChar(int character, float x, float y, float w, float h, vec3 color);

    void drawString(string text, float x, float y, float w, float h, vec3 color);

    void drawStringUnscaled(string text, float x, float y, float scale, vec3 color);

    void render();
}



