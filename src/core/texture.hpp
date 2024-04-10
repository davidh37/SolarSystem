#pragma once

#include <glad/glad.h>
#include <SDL2/SDL.h>
#include "common.hpp"




class Texture {
    public:
        static SDL_Surface* loadPixels(string const &path, bool flip);
        static void convertBlackToAlpha(SDL_Surface &pixels);

        void create(bool interpolate);
        void create(string const &path, bool flip, bool interpolate);
        void update(SDL_Surface &surf);

        void use(int texture_unit = 0);
        void destroy();

    private:
        GLuint id = 0;
        bool uploaded = false;
};
