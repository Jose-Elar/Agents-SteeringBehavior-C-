cmake_minimum_required(VERSION 3.10.0)

project(BehaviorAgents VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
)
FetchContent_MakeAvailable(raylib)

add_executable(BehaviorAgents
    main.cpp
    classes/Agent.cpp
    )

target_link_libraries(BehaviorAgents PRIVATE raylib)
target_include_directories(BehaviorAgents PRIVATE classes)