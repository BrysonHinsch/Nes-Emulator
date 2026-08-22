cmake_minimum_required(VERSION 3.10)

# set the project name
project(NesEmulator VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/vendored/SDL/include/SDL3)

add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

add_executable(NesEmulator
    src/bus.cpp
    src/cartridge.cpp
    src/cpu.cpp
    src/debug.cpp
    src/emulator.cpp
    src/main.cpp
    src/opcodes.cpp
    src/ppu.cpp
    src/renderer.cpp
)

target_link_libraries(NesEmulator PRIVATE SDL3::SDL3)