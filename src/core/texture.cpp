#include "common.hpp"
#include "texture.hpp"
#include "engine.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


SDL_Surface* Texture::loadPixels(string const &path, bool flip){
    stbi_set_flip_vertically_on_load(flip);
    int width, height, bytesPerPixel;
    void* data = stbi_load(path.c_str(), &width, &height, &bytesPerPixel, 0);

    assert(SDL_BYTEORDER == SDL_LIL_ENDIAN);
    assert(bytesPerPixel == 3 || bytesPerPixel == 4);

    int pitch = width * bytesPerPixel;
    int Rmask, Gmask, Bmask, Amask;
    Rmask = 0x000000FF;
    Gmask = 0x0000FF00;
    Bmask = 0x00FF0000;
    Amask = (bytesPerPixel == 4) ? 0xFF000000 : 0;
    
    //create inefficiently non padded RGB surface
    SDL_Surface* helper = SDL_CreateRGBSurfaceFrom(data, width, height, bytesPerPixel*8, pitch, Rmask, Gmask, Bmask, Amask);
    if(!helper){
        stbi_image_free(data); //equivalent to free, don't forget to free this in the other
        engine::showErrorMessage("[texture] failed to read file " + path);
        engine::quit(1);
    }

    //create standalone surface to return
    SDL_Surface *surf = SDL_ConvertSurfaceFormat(helper, SDL_PIXELFORMAT_RGBA32, 0);
    SDL_FreeSurface(helper);
    stbi_image_free(data);

    if(surf == nullptr){
        engine::showErrorMessage("[texture] failed to convert file " + path);
        engine::quit(1);
    }

    SDL_LockSurface(surf);

    assert(surf->format->BytesPerPixel == 4);
    assert(surf->format->BitsPerPixel = 32);

    return surf;
}

void Texture::convertBlackToAlpha(SDL_Surface &surf){
    uint8_t *pixels = (uint8_t*) surf.pixels;
    int pitch = surf.pitch;
    for(int y = 0; y < surf.h; y++){
        for(int x = 0; x < surf.w; x++){
            uint16_t r = pixels[(y * pitch + x * 4 + 0)];
            pixels[(y * pitch + x * 4 + 3)] = r;
        }
    }
}

void Texture::create(bool interpolate, int layers){
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D_ARRAY, id);
    if(interpolate){
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }else{
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    this->layers = layers;
}

void Texture::update(string const &path, bool flip, int layer){
    SDL_Surface *surf = loadPixels(path, flip);
    Texture::update(*surf, layer);
    SDL_FreeSurface(surf);
}

void Texture::update(SDL_Surface &surf, int layer){
    assert(id != 0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, id);    
    if(w == 0){
        glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, surf.w, surf.h, layers, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL); // refer to glTexStorage3D() 
        w = surf.w;
        h = surf.h;
    }
    if(w != surf.w || h != surf.h){
        engine::showErrorMessage("[texture] texture size is incompatible with texture array");
        engine::quit(1);
    }
    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, layer, surf.w, surf.h, 1, GL_RGBA, GL_UNSIGNED_BYTE, surf.pixels);
}

void Texture::use(int texture_unit){
    glActiveTexture(GL_TEXTURE0 + texture_unit);
    glBindTexture(GL_TEXTURE_2D_ARRAY, id);
}

void Texture::destroy(){
    glDeleteTextures(1, &id);
    id = 0;
    layers = 0;
    w = 0;
    h = 0;
}

