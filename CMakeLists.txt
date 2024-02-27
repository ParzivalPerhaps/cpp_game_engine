cmake_minimum_required(VERSION 3.28)
project(cpp_game_engine)

set(CMAKE_CXX_STANDARD 17)

# Notes from hayden :>
# If you receive process finished with exit code -1073741515 you need to take the SDL2.dll in x64 or x86 (depending on your machine's stuff) and copy it to your System32 folder

set(SDL2_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/SDL/include)
set(SDL2_LIB_DIR ${CMAKE_SOURCE_DIR}/SDL/lib/x64) # If something messes up try switching this to x86 on your machine

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(cpp_game_engine main.cpp
        EngineRenderService.cpp
        EngineRenderService.h
        UserInterfaceElements)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2)

