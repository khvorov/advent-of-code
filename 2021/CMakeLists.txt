cmake_minimum_required(VERSION 3.14.0)
project(aoc_2021 VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -pedantic -Werror)

add_subdirectory(cpp)
