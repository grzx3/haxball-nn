cmake_minimum_required(VERSION 3.26)
project(haxball_nn)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BOX2D_DIR "${CMAKE_SOURCE_DIR}/lib/box2d-2.4.1")
set(SFML_DIR "${CMAKE_SOURCE_DIR}/lib/SFML-2.6.2")

include_directories(${BOX2D_DIR}/include)
link_directories(${BOX2D_DIR}/build/bin/Debug)

include_directories(${SFML_DIR}/include)
link_directories(${SFML_DIR}/lib)

add_executable(haxball_nn
    src/main.cpp
    src/Ball.cpp
    src/Ball.h
    src/constants.h
    src/GameObject.cpp
    src/GameObject.h
    src/GoalPost.cpp
    src/GoalPost.h
    src/Player.cpp
    src/Player.h
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(haxball_nn sfml-graphics-d sfml-window-d sfml-system-d box2d)
else()
    target_link_libraries(haxball_nn sfml-graphics sfml-window sfml-system box2d)
endif()
