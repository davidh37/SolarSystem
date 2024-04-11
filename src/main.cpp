#include "core/common.hpp"
#include "core/engine.hpp"
#include "core/camera.hpp"
#include "core/mesh.hpp"
#include "core/shader.hpp"
#include "core/texture.hpp"
#include "core/input.hpp"
#include "meshloader.hpp"
#include "ui_layer.hpp"
#include "renderer.hpp"


meshing::Mesh m;

void initialize(){
    engine::initialize("Solar System Demo", 1024, 768, false, false, 3, 3);
    ui_layer::initialize();
    renderer::initialize();

    input::lockMouse();

    m.create(meshing::STATIC, meshing::TRIANGLE);
    meshing::VertexBuffer vb;
    //meshloader::addRect(vb, {-1.0f, 0.0f, 0.0f}, {0.5f, 0.5f}, COLOR_BLACK, {0.0f, 0.0f}, {1.0f, 1.0f});
    meshloader::addObj(vb, "resources/sphere2.obj");
    meshloader::addObj(vb, "resources/sphere2.obj", vec3(3.0f, 0.0f, 0.0f));
    m.update(vb);
}

void cleanup(int code){
    renderer::cleanup();
    ui_layer::cleanup();

    m.destroy();

    engine::quit(code);
}

bool update(float delta){
    float move_power = 3.0f * delta;

    int mouse_delta_x, mouse_delta_y;
    input::getMouseDelta(mouse_delta_x, mouse_delta_y);

    float mouseDeltaX = -delta * 0.5f * mouse_delta_x;
    float mouseDeltaY = delta * 0.5f * mouse_delta_y;

    input::queryInputs();
    if(input::getKeyState(input::KEY_W)){
        camera::addPosition({0.00f, 0.0f, -move_power});
    }
    if(input::getKeyState(input::KEY_S)){
        camera::addPosition({0.00f, 0.0f, move_power});
    }
    if(input::getKeyState(input::KEY_A)){
        camera::addPosition({-move_power, 0.0f, 0.0f});
    }
    if(input::getKeyState(input::KEY_D)){
        camera::addPosition({move_power, 0.0f, 0.0f});
    }
    if(input::getKeyState(input::KEY_SHIFT)){
        camera::addPosition({0.0f, -move_power, 0.0f});
    }
    if(input::getKeyState(input::KEY_SPACE)){
        camera::addPosition({0.0f, move_power, 0.0f});
    }
    camera::addOrientation(mouseDeltaX, mouseDeltaY);

    if(input::hasQuit() || input::getKeyState(input::KEY_ESC)){
        return true;
    }
    return false;
}

void render(int fps, int frame_time, int bodies){

    engine::clearScreen(0.2f, 0.2f, 0.2f);

    mat4 modelMatrix = glm::scale(vec3(1.0f));
    renderer::render(m, modelMatrix, camera::getViewMatrix(), camera::getProjectionMatrix(), 0, 1.5f, 2.3f, 0.15f, 16.0f);

    ui_layer::drawStringUnscaled("fps ", 0.83f, 0.92f, 0.03f, COLOR_WHITE);
    ui_layer::drawStringUnscaled(to_string(fps), 0.87f, 0.92f, 0.03f, COLOR_WHITE);
    ui_layer::drawStringUnscaled("frame time ", 0.83f, 0.88f, 0.03f, COLOR_WHITE);
    ui_layer::drawStringUnscaled(to_string(frame_time), 0.94f, 0.88f, 0.03f, COLOR_WHITE);
    ui_layer::drawStringUnscaled("objects ", 0.83f, 0.84f, 0.03f, COLOR_WHITE);
    ui_layer::drawStringUnscaled(to_string(bodies), 0.91f, 0.84f, 0.03f, COLOR_WHITE);
    ui_layer::render();

    engine::swapBuffer();
}

int main(int argc, char *argv[]){
    
    initialize();

    camera::setProjection(90.0f, 0.01f, 100.0f);
    camera::setPosition({0.0f, 0.0f, 3.0f});

    uint32_t timestamp = engine::getMs();
    engine::sleep(1);
    while(true){
        uint32_t new_stamp = engine::getMs();
        uint32_t diff = new_stamp - timestamp;
        timestamp = new_stamp;
        float delta = 0.001f * diff;

        if(update(delta)){
            cleanup(0);
        }
        if(engine::queryErrors()){
            cleanup(1);
        }
        
        render(1.0f / delta, (int) diff, 0);
        engine::sleep(1);
    }

    return 0;
}


