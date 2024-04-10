#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <cassert>
#include <memory>
#include <vector>
#include <queue>


#define COLOR_RED vec3(1.0f, 0.0f, 0.0f)
#define COLOR_BLUE vec3(0.0f, 0.0f, 1.0f)
#define COLOR_GREEN vec3(0.0f, 1.0f, 0.0f)
#define COLOR_WHITE vec3(1.0f, 1.0f, 1.0f)
#define COLOR_BLACK vec3(0.0f, 0.0f, 0.0f)
#define COLOR_YELLOW vec3(1.0f, 1.0f, 0.0f)
#define COLOR_LIGHTGRAY vec3(0.85f, 0.85f, 0.85f)
#define COLOR_GRAY vec3(0.5f, 0.5f, 0.5f)
#define COLOR_DARKGRAY vec3(0.2f, 0.2f, 0.2f)


using std::cout;
using std::unique_ptr;
using std::endl;
using std::string;
using std::to_string;
using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;

#define array_len(x) (sizeof(x) / sizeof((x)[0]))

static string TERMINAL_CLEAR = "\033[0m";

static inline string text_float(float f){
    int len = snprintf(NULL, 0, "%f", f);
    static char buffer[128];
    snprintf(buffer, len+1, "%.2f", f);
    string s = string(buffer);
    return s;
}

static inline int rand1024(){
    return (rand() & (1024 - 1));
}

static inline float randf(float min, float max){
    return min + (max - min ) * (rand() / (float) RAND_MAX);
}

static inline vec2 randv(){
    float phi = randf(0.0f, M_PI * 2.0f);
    return vec2(cos(phi), sin(phi));
}

static inline void mutateFixed(float &out, float mutate_amount, float min, float max){
    float mut = (rand() % 2) == 0 ? -mutate_amount : mutate_amount;
    out = std::min(std::max(out + mut, min), max);
}

static inline void mutatePercentage(float &out, float mutate_amount, float min, float max){
    float mut = 1.0f + randf(-mutate_amount, mutate_amount);
    out = std::min(std::max(out * mut, min), max);
}

static inline void mutateFixed(vec3 &out, float mutate_amount, float min, float max){
    mutateFixed(out[0], mutate_amount, min, max);
    mutateFixed(out[1], mutate_amount, min, max);
    mutateFixed(out[2], mutate_amount, min, max);
}

