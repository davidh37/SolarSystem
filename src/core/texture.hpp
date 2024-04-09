#pragma once

#include <glad/glad.h>
#include <SDL2/SDL.h>
#include "common.hpp"


struct Texture {
    SDL_Surface *surf;
    GLuint id = 0;

    // create() doesn't upload!
    void create(string const &path, bool flip);
    uint8_t* get_pixels(int &pitch);
    void convert_black_to_alpha();

    // required!
    void upload(bool interpolate);

    void load(int texture_unit = 0);
    void destroy();
};
