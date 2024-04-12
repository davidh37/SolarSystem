# OpenGL Solar System
A 3D OpenGL demo with simple euler orbits.
WASD space and shift to move + number keys for camera modes  

https://github.com/davidh37/SolarSystem/assets/51903513/2aeb4ae7-1495-4274-a580-a053fef9e1a1

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


