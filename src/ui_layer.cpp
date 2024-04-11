#include "ui_layer.hpp"

#include "meshloader.hpp"
#include "core/common.hpp"
#include "core/mesh.hpp"
#include "core/texture.hpp"
#include "core/shader.hpp"


namespace ui_layer{



    static constexpr int CHARS_TOTAL = 256;
    static const int CHARS_FIRST = 32;
    static const int CHARS_CELLS_ROW = 16;
    static const int CHAR_CELL_WIDTH = 32;
    static vec4 char_uvs[CHARS_TOTAL];

    static void generate_char_uvs(SDL_Surface &surf){

        int pitch = surf.pitch;
        uint8_t *pixels = (uint8_t*)surf.pixels;


        for(int c = 0; c < CHARS_TOTAL; c++){
            int cx = (c % CHARS_CELLS_ROW) * CHAR_CELL_WIDTH;
            int cy = (c / CHARS_CELLS_ROW) * CHAR_CELL_WIDTH;

            int offset_x1 = -1;
            int offset_x2 = -1;
          
            for(int px = 0; px < CHAR_CELL_WIDTH; px++){
                for(int py = 0; py < CHAR_CELL_WIDTH; py++){
                    int x = cx + px;
                    int y = cy + py;

                    if(pixels[(y * pitch + x * 4 + 0)] > 0){
                        if(offset_x1 == -1){
                            offset_x1 = px;
                        }
                        offset_x2 = px;
                        break;
                    }
                }
            }

            float pixel_to_uv = 1.0f / ((float) CHARS_CELLS_ROW * CHAR_CELL_WIDTH);

            if(offset_x1 == -1 || offset_x2 == -1){
                offset_x1 = 0;
                offset_x2 = 2;
            }

            char_uvs[c][0] = pixel_to_uv * (cx + offset_x1 - 1);
            char_uvs[c][1] = pixel_to_uv * (cy);
            char_uvs[c][2] = pixel_to_uv * (offset_x2 - offset_x1 + 3);
            char_uvs[c][3] = pixel_to_uv * CHAR_CELL_WIDTH;
        }
    }

    static Shader shader;
    static Texture fontTexture;
    static meshing::Mesh mesh;
    static meshing::VertexBuffer vertices;
    int textureUnit = 0;

    void initialize(){
        mesh.create(meshing::STREAM, meshing::TRIANGLE);

        shader.createAndUpdate("resources/shaders/texture.vert", "resources/shaders/texture_colormix.frag");

        fontTexture.create(false, 1);
        SDL_Surface *surf = Texture::loadPixels("resources/calibri32clean.bmp", false);
        Texture::convertBlackToAlpha(*surf);
        generate_char_uvs(*surf);
        fontTexture.update(*surf);
        SDL_FreeSurface(surf);

        cout << "[ui_layer] initialized" << endl;
    }

    void cleanup(){
        shader.destroy();
        fontTexture.destroy();
        mesh.destroy();
        cout << "[ui_layer] cleanup" << endl;
    }

    void drawBox(float x, float y, float w, float h, vec3 color){
        meshloader::addRect(vertices, vec3(x, y, 0.0f), vec2(w, h), color, vec2(0.0f, 0.0f), vec2(1.0f, 1.0f));
    }

    void drawChar(int character, float x, float y, float w, float h, vec3 color){
        assert(character >= CHARS_FIRST && character < CHARS_FIRST + CHARS_TOTAL);
        character = character - CHARS_FIRST;
        vec4 uvs = char_uvs[character];
        meshloader::addRect(vertices, vec3(x, y, 0.0f), vec2(w, h), color, vec2(uvs[0], uvs[1]), vec2(uvs[2], uvs[3]));
    }

    void drawString(string text, float x, float y, float w, float h, vec3 color){
        int n = text.size();
        assert(n > 0);

        //calculate total width needed
        float text_width = 0.0f;
        for(int i = 0; i < n; i++){
            int c = text[i] - CHARS_FIRST;
            text_width += char_uvs[c][2];
        }

        float uv_scale = w / text_width;

        float accumulator = x;
        for(int i = 0; i < n; i++){
            int c = text[i] - CHARS_FIRST;
            vec4 uv = char_uvs[c];
            float scaled_w = uv[2] * uv_scale;
            drawChar(c + CHARS_FIRST, accumulator, y, scaled_w, h, color);
            accumulator += scaled_w;
        }
    }

    void drawStringUnscaled(string text, float x, float y, float scale, vec3 color){
        int n = text.size();

        float accumulator = x;
        for(int i = 0; i < n; i++){
            int c = text[i] - CHARS_FIRST;
            vec4 uv = char_uvs[c];
            float w = scale * uv[2] / uv[3];
            float h = scale;
            drawChar(c + CHARS_FIRST, accumulator, y, w, h, color);
            accumulator += w;
        }
    }

    void render(){
        mat4 to_ndc = {
            2.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 2.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 2.0f, 0.0f,
            -1.0f, -1.0f, -1.0f, 1.0f
        };

        fontTexture.use(textureUnit);
        shader.use();
        shader.setUniformMat4(0, to_ndc);
        shader.setUniformInteger(1, textureUnit);

        mesh.update(vertices);
        mesh.draw();

        // reset gui so it doesnt explode lol
        vertices.clear();
    }
}