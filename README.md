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

## Building
### On Windows
Install MSYS2
Open MSYS2 Clang64 (!) Terminal and enter:
`pacman -Syu`
`pacman -S mingw-w64-clang-x86_64-toolchain` 
`pacman -S mingw-w64-clang-x86_64-cmake`
`pacman -S mingw-w64-clang-x86_64-SDL2 mingw-w64-clang-x86_64-glm`
navigate to repository

### On Linux
Install SDL2, glm

### On Linux & Windows
Navigate to repository
`mkdir build`
`cd build`
`cmake ..`
`ninja`


