#include "core/common.hpp"
#include "core/engine.hpp"
#include "core/camera.hpp"
#include "core/mesh.hpp"
#include "core/shader.hpp"
#include "core/texture.hpp"
#include "core/input.hpp"
#include "meshloader.hpp"

static uint32_t timestamp;

int main(int argc, char *argv[]){
    engine::initialize("Solar System Demo", 1024, 768, false, false, 3, 3);

    Shader s;
    s.create("resources/texture.vert", "resources/texture.frag");
    s.use();

    Texture t;
    t.create(false, 2);
    t.update("resources/test.png", false, 0);
    t.update("resources/test2.png", false, 1);
    t.use();
    s.setUniformInteger(1, 0);

    meshing::Mesh m;
    meshing::VertexBuffer vb;

    meshloader::addSquare(vb, {-1.0f, 0.0f, 0.0f}, {0.5f, 0.5f}, COLOR_BLACK, {0.0f, 0.0f}, {1.0f, 1.0f});
    //meshloader::addObj(vb, "resources/bunny.obj");
    m.create(vb, meshing::STATIC, meshing::TRIANGLE);

    camera::setProjection(90.0f, 0.01f, 100.0f);
    camera::setPosition({0.0f, 0.0f, -2.0f});
    
    input::lockMouse();
    timestamp = engine::getMs();
    bool escapeKeyPressed = false;
    while(!input::hasQuit() && !escapeKeyPressed){
        uint32_t new_stamp = engine::getMs();
        uint32_t diff = new_stamp - timestamp;
        timestamp = new_stamp;
        float delta = 0.001f * diff;
        float move_power = 3.0f * delta;

        int mouse_delta_x, mouse_delta_y;
        input::getMouseDelta(mouse_delta_x, mouse_delta_y);
        //cout << delta << endl;
        //cout << mouse_delta_x << " | " << mouse_delta_y << endl;
        //cout << "fps: " << 1.0f / delta << endl;
        float mouseDeltaX = delta * 0.5f * mouse_delta_x;
        float mouseDeltaY = -delta * 0.5f * mouse_delta_y;

        input::queryInputs();
        if(input::getKeyState(input::KEY_W)){
            camera::addPosition({0.00f, 0.0f, move_power});
        }
        if(input::getKeyState(input::KEY_S)){
            camera::addPosition({0.00f, 0.0f, -move_power});
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
        if(input::getKeyState(input::KEY_ESC)){
            escapeKeyPressed = true;
        }
        camera::addOrientation(mouseDeltaX, mouseDeltaY);
        engine::clearScreen(0.2f, 0.2, 0.5f);
        
        mat4 vp = camera::getProjectionMatrix() * camera::getViewMatrix();
        s.setUniformMat4(0, vp);
        m.draw();
        if(engine::queryErrors()){
            engine::quit(1);
        }
        engine::swapBuffer();
        engine::sleep(1);

    }
    
    engine::quit();
    return 0;
}


