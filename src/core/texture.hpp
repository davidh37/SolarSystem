#pragma once

#include <glad/glad.h>
#include <SDL2/SDL.h>
#include "common.hpp"




class Texture {
    public:
        static SDL_Surface* loadPixels(string const &path, bool flip);
        static void convertBlackToAlpha(SDL_Surface &pixels);

        void create(bool interpolate, int layers);
        void update(string const &path, bool flip, int layer = 0);
        void update(SDL_Surface &surf, int layer = 0);

        void use(int texture_unit = 0);
        void destroy();

    private:
        GLuint id = 0;
        int w = 0;
        int h = 0;
        int layers = 0;
};
