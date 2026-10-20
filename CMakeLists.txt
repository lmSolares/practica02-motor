cmake_minimum_required(VERSION 3.16)
project(practica05_motor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -Wpedantic)

find_package(SDL3 QUIET)
if(NOT SDL3_FOUND)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL3 REQUIRED IMPORTED_TARGET sdl3)
    set(SDL3_TARGET PkgConfig::SDL3)
else()
    set(SDL3_TARGET SDL3::SDL3)
endif()

add_library(motor_core STATIC
    src/motor/Vector2.cpp
    src/motor/GameObject.cpp
    src/motor/TransformComponent.cpp
    src/motor/RectRenderComponent.cpp
    src/motor/ColliderComponent.cpp
    src/motor/CollisionManager.cpp
    src/motor/Scene.cpp
    src/motor/SceneManager.cpp
)
target_include_directories(motor_core PUBLIC include)
target_link_libraries(motor_core PUBLIC ${SDL3_TARGET})

add_executable(practica05_motor
    src/practicas/main_pelota.cpp
    src/practicas/BallComponent.cpp
    src/practicas/PatrolComponent.cpp
    src/practicas/PlayerControllerComponent.cpp
    src/practicas/TitleScene.cpp
    src/practicas/GameScene.cpp
    src/practicas/PauseScene.cpp
    src/practicas/GameOverScene.cpp
)
target_include_directories(practica05_motor PRIVATE include src)
target_link_libraries(practica05_motor PRIVATE motor_core)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/proyecto01/main_proyecto01.cpp")
    file(GLOB_RECURSE PROYECTO01_SOURCES "src/proyecto01/*.cpp")
    add_executable(proyecto01 ${PROYECTO01_SOURCES})
    target_include_directories(proyecto01 PRIVATE include src)
    target_link_libraries(proyecto01 PRIVATE motor_core)
endif()
