cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lraylib -lGL -lm -lpthread -ldl -lrt -lX11")

project(gamefight C)

include_directories(headers)
file(GLOB MAIN "sources/*.c" "headers/*.h")

find_package(raylib REQUIRED)

add_executable(gamefight ${MAIN})

