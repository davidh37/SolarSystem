# SolarSystem
A 3D OpenGL demo

## Dependencies
glm, SDL2

## Credits
GLAD (OpenGL loader) under MIT license  
https://github.com/Dav1dde/glad  
stb_image (public domain image loader)  
https://github.com/nothings/stb  
Various 3D models from  
http://graphics.stanford.edu/data/3Dscanrep/  
Planet textures from  
https://www.solarsystemscope.com/textures/  

## Building
### On Windows
Install MSYS2  
Open MSYS2 Clang64 (!) Terminal and enter:  
`pacman -Syu`  
`pacman -S mingw-w64-clang-x86_64-toolchain`  
`pacman -S mingw-w64-clang-x86_64-cmake`  
`pacman -S mingw-w64-clang-x86_64-SDL2 mingw-w64-clang-x86_64-glm`  
Navigate to repository  

### On Linux
Install SDL2, glm  
Navigate to repository  

### On Linux & Windows
Enter:  
`cmake --preset debug` or `cmake --preset release`  
`cd build/debug` or `cd build/release`  
`ninja`  
`./sdl_app`  


