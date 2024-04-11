#include <glad/glad.h>
#include <SDL2/SDL.h>
#include "common.hpp"
#include "engine.hpp"


namespace engine {

    static SDL_Window *window = nullptr;
    static SDL_GLContext context;

    void initialize(string window_name, int res_x, int res_y, bool resizable, bool vsync, int gl_major, int gl_minor){
        
        assert(res_x > 0);
        assert(res_y > 0);
        assert(gl_major > 0 && gl_major <= 4);
        assert(gl_minor > 0 && gl_minor <= 6);

        if(SDL_Init(SDL_INIT_VIDEO) < 0){
            showErrorMessage("[engine] SDL could not initialize");
            quit(1);
        }

        Uint32 flag = resizable ? (SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE) : SDL_WINDOW_OPENGL;
        window = SDL_CreateWindow(window_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, res_x, res_y, flag);
        if (window == NULL) {
            showErrorMessage("[engine] SDL could not create window");
            quit(1);
        }
        
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, gl_major);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, gl_minor);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        
        context = SDL_GL_CreateContext(window);
        if(context == NULL){
            showErrorMessage("[engine] failed to create GL context");
            quit(1);
        }
        SDL_GL_SetSwapInterval(vsync ? 1 : 0); //vsync off

        if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)){
            showErrorMessage("[engine] failed to initialize GLAD");
            quit(1);
        }

        glEnable(GL_CULL_FACE);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST); // required for Z
        glDepthFunc(GL_LESS);  
    }

    

    uint32_t getMs(){
        return SDL_GetTicks();
    }

    void sleep(uint32_t ms){
        SDL_Delay(ms);
    }
	

    void getWindowSize(int &w, int &h){
        SDL_GetWindowSize(window, &w, &h);
    }

    void getScreenSize(int &w, int &h){
        SDL_DisplayMode display_mode;
        SDL_GetCurrentDisplayMode(0, &display_mode);
        w = display_mode.w;
        h = display_mode.h;
    }
    
	void setViewport(int x, int y, int w, int h){
        assert(w > 0);
        assert(h > 0);
        assert(x >= 0);
        assert(y >= 0);
        glViewport(x, y, w, h);
    }

	void swapBuffer(){
        SDL_GL_SwapWindow(window);
    }

    void clearScreen(float r, float g, float b){
        assert(r >= 0.0f);
        assert(g >= 0.0f);
        assert(b >= 0.0f);
        assert(r < 1.0f);
        assert(g < 1.0f);
        assert(b < 1.0f);
        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void showErrorMessage(string message){
        if(window == nullptr){
            cout << message << endl;
        }else{
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", message.c_str(), window);
        }
    }

    bool queryErrors(int max_print){
        GLenum err;
        bool error = false;
        while((err = glGetError()) != GL_NO_ERROR && max_print > 0){
            showErrorMessage("[engine] OpenGL error " + to_string(err));
            max_print--;
            error = true;
        }
        string sdlerror = SDL_GetError();
        if(sdlerror.size() != 0){
            showErrorMessage("[engine] SDL error " + sdlerror);
            return true;
        }
        return error;
    }

    void quit(int code){
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        std::exit(code);
    }
}