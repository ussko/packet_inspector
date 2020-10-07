cmake_minimum_required(VERSION 3.13)
project(packet_inspector)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

set(GCC_WARNINGS
        "-Wall"
        "-Wextra"
        "-Wpedantic"
        "-Wdouble-promotion"
        "-Wduplicated-cond"
        "-Wduplicated-branches"
        "-Wformat=2"
        "-Wimplicit-fallthrough=2"
        "-Wlogical-op"
        "-Wno-misleading-indentation"
        "-Wnull-dereference"
        "-Wredundant-decls"
        "-Wrestrict"
        "-Wshadow"
        "-Wswitch-default")
add_definitions(${GCC_WARNINGS})

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)
