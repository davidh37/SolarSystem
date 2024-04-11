#include "core/common.hpp"
#include "meshloader.hpp"
#include "core/engine.hpp"
#include <fstream>
#include <cstdlib>

namespace meshloader {

    // helper function that reads a float & advances offset
    static bool tryReadFloat(string s, size_t &index, float &f){
        char *startptr = &s[0] + index;
        char *endptr;
        f = strtof(startptr, &endptr);
        if(endptr - startptr <= 0){
            // we failed to read
            return false;
        }
        index += endptr - startptr;
        return true;
    }

    static bool tryReadInt(string s, size_t &index, int &i){
        char *startptr = &s[0] + index;
        char *endptr;
        i = (int)strtol(startptr, &endptr, 0);
        if(endptr - startptr <= 0){
            // we failed to read
            return false;
        }
        index += endptr - startptr;
        return true;
    }

    void addObj(meshing::VertexBuffer &vb, string path, vec3 pos, vec3 fallback_color){
        std::ifstream myfile(path);
        if(!myfile.is_open()) {
            cout << "addObj PARSE ERROR: couldn't open .obj file " << path << endl;
            engine::quit(1);
        }

        std::string line = "";

        std::vector<float> position_list;
        std::vector<float> uv_list;
        std::vector<float> normal_list;

        // for adding to vertexbuffer
        int total_count = 0;

        // first read for lists of vertex, uv, normal
        while(!myfile.eof()){
            std::getline(myfile, line);

            size_t i = 0;
            if(line.size() == 0 || (line.size() >= 1 && line[i] == '#') || (line.size() == 1 && line[i] == ' ')){
                // do nothing for empty lines
                continue;
            }else if(line.size() >= 2 && line[i] == 'v' && line[i+1] == ' '){
                // vertex data
                i += 2;

                float x, y, z;
                if(!tryReadFloat(line, i, x)){
                    cout << "[meshloader] invalid x" << endl;
                    goto parse_error;
                }
                if(!tryReadFloat(line, i, y)){
                    cout << "[meshloader] invalid y" << endl;
                    goto parse_error;
                }
                if(!tryReadFloat(line, i, z)){
                    cout << "[meshloader] invalid z" << endl;
                    goto parse_error;
                }
                position_list.push_back(x);
                position_list.push_back(y);
                position_list.push_back(z);

                // we dont care about optional w
            }else if(line.size() >= 3 && line[i] == 'v' && line[i+1] == 't' && line[i+2] == ' '){
                // uv data
                i += 3;

                float tx, ty, tz;
                if(!tryReadFloat(line, i, tx)){
                    cout << "[meshloader] invalid uv 2" << endl;
                    goto parse_error;
                }
                if(!tryReadFloat(line, i, ty)){
                    cout << "[meshloader] invalid uv 1" << endl;
                    goto parse_error;
                }
                if(tryReadFloat(line, i, tz)){
                    // we can't read 3D tex coords
                    if(tz != 0.0f){
                        cout << "[meshloader] too many tex coords" << endl;
                        goto parse_error;
                    }
                }
                uv_list.push_back(tx);
                uv_list.push_back(ty);
            }else if(line.size() >= 3 && line[i] == 'v' && line[i+1] == 'n' && line[i+2] == ' '){
                // normal data
                i += 3;

                float nx, ny, nz;
                if(!tryReadFloat(line, i, nx)){
                    cout << "[meshloader] invalid normal 0" << endl;
                    goto parse_error;
                }
                if(!tryReadFloat(line, i, ny)){
                    cout << "[meshloader] invalid normal 1" << endl;
                    goto parse_error;
                }
                if(!tryReadFloat(line, i, nz)){
                    cout << "[meshloader] invalid normal 2" << endl;
                    goto parse_error;
                }
                normal_list.push_back(nx);
                normal_list.push_back(ny);
                normal_list.push_back(nz);
            }else if(line.size() >= 2 && line[i] == 'f' && line[i+1] == ' '){
                continue;
            }else{
                // parse warning
                cout << "[meshloader] unknown line " << line << endl;
            }
        }

        // reset file pointer
        myfile.clear();
        myfile.seekg(0);

        cout << "[meshloader] loading \'" << path << "\'" << endl;
        cout << "[meshloader] " << position_list.size() / 3 << " positions loaded" << endl;
        cout << "[meshloader] " << normal_list.size() / 3 << " normals loaded" << endl;
        cout << "[meshloader] " << uv_list.size() / 2 << " uvs loaded" << endl;

        // second read for face construction
        while(!myfile.eof()){
            std::getline(myfile, line);

            size_t i = 0;
            if(line.size() >= 2 && line[i] == 'f' && line[i+1] == ' '){
                i = 2;

                int position_index[3] = {0, 0, 0};
                int uv_index[3] = {0, 0, 0};
                int normal_index[3] = {0, 0, 0};

                // fill indices
                for(int k = 0; k < 3; k++){
                    if(!tryReadInt(line, i, position_index[k])){
                        cout << "[meshloader] invalid position at " << k << endl;
                        goto parse_error;
                    }
                    if((i < line.size() && line[i] == ' ') || (i == line.size() && k == 2)){
                        // only position
                        i += 1;
                    }else if(i + 1 < line.size() && line[i] == '/' && line[i+1] == '/'){
                        // position and normal
                        i += 2;
                        if(!tryReadInt(line, i, normal_index[k])){
                            cout << "[meshloader] (1) invalid normal at " << k << endl;
                            goto parse_error;
                        }
                    }else if(i < line.size() && line[i] == '/'){
                        // position and uv...
                        i += 1;
                        if(!tryReadInt(line, i, uv_index[k])){
                            cout << "[meshloader] invalid uv at " << k << endl;
                            goto parse_error;
                        }
                        if(i < line.size() && line[i] == '/'){
                            i += 1;
                            if(!tryReadInt(line, i, normal_index[k])){
                                cout << "[meshloader] (2) invalid normal at " << k << endl;
                                goto parse_error;
                            }
                        }
                    }else{
                        goto parse_error;
                    }
                }

                // check if the line continues (we only want triangle compatability)
                while(i < line.size()){
                    if(line[i] != ' ' && line[i] != '\n'){
                        goto parse_error;
                    }
                    i++;
                }

                // finally add vertex   
                for(int k = 0; k < 3; k++){
                    meshing::Vertex v;
                    
                    // adjust for off by one
                    position_index[k] -= 1;
                    uv_index[k] -= 1;
                    normal_index[k] -= 1;

                    // set position
                    assert(position_index[k] >= 0);
                    if(position_index[k] >= (int) position_list.size() / 3){
                        cout << "position index out of range at " << k << endl;
                        goto parse_error;
                    }
                    v.position = {position_list[position_index[k] * 3 + 0], position_list[position_index[k] * 3 + 1], position_list[position_index[k] * 3 + 2]};
                    v.position += pos;

                    // set normal
                    if(normal_index[k] == -1){
                        v.extra = fallback_color;
                    }else{
                        if(normal_index[k] < 0 || normal_index[k] >= (int) normal_list.size() / 3){
                            cout << "normal index out of range at " << k << endl;
                            goto parse_error;
                        }
                        v.extra = {normal_list[normal_index[k] * 3 + 0], normal_list[normal_index[k] * 3 + 1], normal_list[normal_index[k] * 3 + 2]};
                    }

                    // set uv
                    if(uv_index[k] == -1){
                        v.extra2 = vec2(0.0f, 0.0f);
                    }else{
                        if(uv_index[k] < 0 || uv_index[k] >= (int) uv_list.size() / 2){
                            cout << "uv index out of range at " << k << endl;
                            goto parse_error;
                        }
                        v.extra2 = {uv_list[uv_index[k] * 2 + 0], uv_list[uv_index[k] * 2 + 1]};
                    }
                    
                    vb.push_back(v);
                    
                    total_count++;
                }
                
            }else{
                continue;
            }
        }

        cout << "[meshloader] " << total_count / 3 << " triangles loaded" << endl;
        myfile.close();
        return;

        parse_error:
            myfile.close();
            cout << "[meshloader] PARSE ERROR: couldn't parse .obj file " << path << " at line " << "\"" << line << "\"" << endl;
            engine::quit(1);
    }

    void addCircle(meshing::VertexBuffer &vb, int segments, vec3 pos, vec2 scale, vec3 color, vec2 uv_pos, vec2 uv_scale){
        vb.reserve(vb.size() + segments * 3);

        meshing::Vertex origin = {pos, color, vec2(0.5f, 0.5f)};
        
        float increment = 2.0f * M_PI / segments;
        float angle = 0.0f;

        meshing::Vertex first;

        for(int i = 0; i < segments; i++){
            angle += increment;
            float cosine = cos(angle);
            float sine = sin(angle);
            vec3 vpos = vec3(pos.x + scale.x * cosine, pos.y + scale.y * sine, pos.z);
            vec2 uv = vec2(uv_pos.x + 0.5f * uv_scale.x * cosine, uv_pos.y + 0.5f * uv_scale.y * sine);
            meshing::Vertex v = {vpos, color, uv};
            if(i > 0){
                vb.push_back(v);
            }else{
                first = v;
            }
            vb.push_back(origin);
            vb.push_back(v);
        }
        vb.push_back(first);
    }

    void addRect(meshing::VertexBuffer &vb, vec3 pos, vec2 scale, vec3 color, vec2 uv_pos, vec2 uv_scale){
        float x1 = pos.x;
        float x2 = pos.x + scale.x;
        float y1 = pos.y;
        float y2 = pos.y + scale.y;

        meshing::Vertex v[4];
        v[0] = {vec3(x1, y2, pos.z), color, vec2(uv_pos.x, uv_pos.y)};
        v[1] = {vec3(x1, y1, pos.z), color, vec2(uv_pos.x, uv_pos.y+ uv_scale.y)};
        v[2] = {vec3(x2, y1, pos.z), color, vec2(uv_pos.x + uv_scale.x, uv_pos.y+ uv_scale.y)};
        v[3] = {vec3(x2, y2, pos.z), color, vec2(uv_pos.x + uv_scale.x, uv_pos.y)};

        vb.push_back(v[0]);
        vb.push_back(v[1]);
        vb.push_back(v[2]);
        vb.push_back(v[0]);
        vb.push_back(v[2]);
        vb.push_back(v[3]);
    }
}