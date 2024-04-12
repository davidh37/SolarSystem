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
    simulation::initialize();

    input::lockMouse();
}

void cleanup(int code){
    simulation::cleanup();
    ui_layer::cleanup();
    engine::quit(code);
}

bool updateInput(float delta){
    float move_power = 150.0f * delta;

    int mouse_delta_x, mouse_delta_y;
    input::getMouseDelta(mouse_delta_x, mouse_delta_y);
    float mouseDeltaX = -delta * 0.5f * mouse_delta_x;
    float mouseDeltaY = delta * 0.5f * mouse_delta_y;
    camera::addOrientation(mouseDeltaX, mouseDeltaY);

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
    if(input::getKeyState(input::KEY_L)){
        input::unlockMouse();
    }
    

    if(input::hasQuit() || input::getKeyState(input::KEY_ESC)){
        return true;
    }
    return false;
}

void render(int fps, int frame_time, int bodies){

    engine::clearScreen(0.0f, 0.0f, 0.0f);

    simulation::render();

    ui_layer::drawStringUnscaled("fps ", 0.83f, 0.92f, 0.03f, COLOR_RED);
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

    float fixed_step = 1.0f / 120.0f;
    float acc = 0.0f;
    int frame = 0;
    uint32_t frame_time = 0;

    uint32_t timestamp = engine::getMs();
    engine::sleep(1);

    // simulate solar system init
    for(int i = 0; i < 100000; i++){
        simulation::update(fixed_step);
    }

    while(true){
        uint32_t new_stamp = engine::getMs();
        float diff = 0.001f * (new_stamp - timestamp);
        timestamp = new_stamp;

        acc += diff;
        if(acc < fixed_step){
            continue;
        }


        
        while(acc >= fixed_step){
            acc -= fixed_step;
            if(updateInput(fixed_step)){
                cleanup(0);
            }

            uint32_t temp_stamp1 = engine::getMs();
            int objects = simulation::update(fixed_step);
            render(1.0f / fixed_step, (int)frame_time, objects);
            frame_time = engine::getMs() - temp_stamp1;

            if(engine::queryErrors()){
                cleanup(1);
            }
        }
    }

    return 0;
}


