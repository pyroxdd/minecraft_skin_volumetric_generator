cmake_minimum_required(VERSION 3.14)
project(project)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE sources
    "${CMAKE_CURRENT_SOURCE_DIR}/src/include/*.cpp"
)

add_executable(main ${sources})

target_include_directories(main
    PRIVATE ${CMAKE_SOURCE_DIR}/src/include/
)