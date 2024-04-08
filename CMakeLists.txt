cmake_minimum_required (VERSION 3.5)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
project (sdl_app)

# Main Executable
file(GLOB SOURCES
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        ${CMAKE_SOURCE_DIR}/src/core/*.cpp
        ${CMAKE_SOURCE_DIR}/src/glad/glad.c
    )

add_executable(sdl_app ${SOURCES})

target_include_directories(sdl_app PUBLIC
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/src/glad
        ${CMAKE_SOURCE_DIR}/src/stb
    )

# Add Resource folder
add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/resources
    ${PROJECT_BINARY_DIR}/resources
    COMMENT "Copying resources into binary directory")

add_dependencies(sdl_app copy_resources)

# SDL2
find_package(SDL2 REQUIRED)
target_link_libraries(sdl_app ${SDL2_LIBRARY})
target_include_directories(sdl_app PUBLIC ${SDL2_INCLUDE_DIR})

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(sdl_app ${OPENGL_gl_LIBRARY})
target_include_directories(sdl_app PUBLIC ${OPENGL_INCLUDE_DIR})

find_package(GLM REQUIRED)
target_include_directories(sdl_app PUBLIC ${GLM_INCLUDE_DIRS})

#target_compile_options(sdl_app PUBLIC -Wall -Wextra -O3 -g -g3 -gdwarf-2 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero)
#target_link_options(sdl_app PUBLIC -fsanitize=address)
#target_compile_options (sdl_app PUBLIC -O3)
#target_compile_definitions(sdl_app PUBLIC -DNDEBUG)
target_compile_options(sdl_app PUBLIC -Wall -Wextra -O3 -g -g3 -gdwarf-2)
target_link_options(sdl_app PUBLIC)