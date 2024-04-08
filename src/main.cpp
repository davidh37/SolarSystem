#include "core/common.hpp"
#include "core/engine.hpp"
#include "core/camera.hpp"
#include "core/mesh.hpp"
#include "core/shader.hpp"
#include "core/texture.hpp"
#include "core/input.hpp"


int main(int argc, char *argv[]){
    engine::initialize("Solar System Demo", 1024, 768, false, 3, 3);

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
    camera::setOrthographic(-1.0f, 1.0f, -1.0f, 1.0f);

    while(!input::hasQuit()){
        mat4 vp = camera::getProjectionMatrix() * camera::getViewMatrix();
        input::queryInputs();
        if(input::getKeyState(input::KEY_W)){
            cout << "pressed w " << endl;
        }
        engine::clearScreen(0.2f, 0.2, 0.5f);
        s.setUniformMat4(0, vp);
        m.draw();
        engine::swapBuffer();
    }
    
    engine::quit();
    return 0;
}


