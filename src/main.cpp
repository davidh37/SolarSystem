#include "core/common.hpp"
#include "core/engine.hpp"
#include "core/camera.hpp"
#include "core/mesh.hpp"
#include "core/shader.hpp"
#include "core/texture.hpp"
#include "core/input.hpp"

static uint32_t timestamp;

int main(int argc, char *argv[]){
    engine::initialize("Solar System Demo", 1024, 768, false, false, 3, 3);


    Texture t;
    Mesh m;
    Shader s;
    s.compile("resources/color.vert", "resources/color.frag");
    s.load();
    t.create("resources/test.png", false);
    t.load();
    Mesh::Vertex v1 = {{0.0f, 0.5f, 0.0f}, COLOR_RED, {0.0f, 0.0f}};
    Mesh::Vertex v2 = {{0.5f, 0.0f, 0.0f}, COLOR_RED, {1.0f, 0.0f}};
    Mesh::Vertex v3 = {{-0.5f, 0.0f, 0.0f}, COLOR_RED, {0.0f, 1.0f}};
    Mesh::VertexBuffer vb = {v1, v2, v3};
    Mesh::IndexBuffer ib = {0, 1, 2};
    m.upload(vb, ib, Mesh::STATIC, false);
    camera::setProjection(90.0f, 0.01f, 100.0f);
    camera::setPosition({0.0f, 0.0f, -5.0f});



    
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
        cout << delta << endl;
        cout << mouse_delta_x << " | " << mouse_delta_y << endl;
        cout << "fps: " << 1.0f / delta << endl;
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
        engine::swapBuffer();
        engine::sleep(1);

    }
    
    engine::quit();
    return 0;
}


