cmake_minimum_required(VERSION 3.16)
project(practica06_motor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -Wpedantic)

option(ENABLE_ASAN "Habilitar AddressSanitizer" OFF)
if(ENABLE_ASAN)
    add_compile_options(-fsanitize=address -g -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address)
endif()

find_package(SDL3 QUIET)
if(NOT SDL3_FOUND)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL3 REQUIRED IMPORTED_TARGET sdl3)
    set(SDL3_TARGET PkgConfig::SDL3)
else()
    set(SDL3_TARGET SDL3::SDL3)
endif()

find_package(SDL3_image QUIET)
if(NOT SDL3_image_FOUND)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL3_IMAGE REQUIRED IMPORTED_TARGET sdl3-image)
    set(SDL3_IMAGE_TARGET PkgConfig::SDL3_IMAGE)
else()
    set(SDL3_IMAGE_TARGET SDL3_image::SDL3_image)
endif()

add_library(motor_core STATIC
    src/math/Vector2.cpp
    src/engine/GameObject.cpp
    src/engine/components/TransformComponent.cpp
    src/engine/components/RectRenderComponent.cpp
    src/engine/components/ColliderComponent.cpp
    src/engine/components/SpriteComponent.cpp
    src/engine/ResourceManager.cpp
    src/physics/CollisionManager.cpp
    src/engine/Scene.cpp
    src/engine/SceneManager.cpp
)
target_include_directories(motor_core PUBLIC include)
target_link_libraries(motor_core PUBLIC ${SDL3_TARGET} ${SDL3_IMAGE_TARGET})

add_executable(practica06_motor
    src/practicas/main_demo.cpp
    src/practicas/ResourceDemoScene.cpp
)
target_include_directories(practica06_motor PRIVATE include src)
target_link_libraries(practica06_motor PRIVATE motor_core ${SDL3_IMAGE_TARGET})

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/proyecto01/main_proyecto01.cpp")
    file(GLOB_RECURSE PROYECTO01_SOURCES "src/proyecto01/*.cpp")
    add_executable(proyecto01 ${PROYECTO01_SOURCES})
    target_include_directories(proyecto01 PRIVATE include src)
    target_link_libraries(proyecto01 PRIVATE motor_core ${SDL3_IMAGE_TARGET})
endif()
