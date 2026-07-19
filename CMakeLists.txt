cmake_minimum_required(VERSION 3.10)

# set the project name
project(NesEmulator VERSION 1.0)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(NesEmulator
    src/bus.cpp
    src/cartridge.cpp
    src/cpu.cpp
    src/emulator.cpp
    src/main.cpp
    src/opcodes.cpp
)