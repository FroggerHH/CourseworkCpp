cmake_minimum_required(VERSION 3.30)
project(CourseworkCpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(CourseworkCpp main.cpp)

if(MSVC)
    # Указываем компилятору MSVC, что исходные файлы в кодировке UTF-8
    target_compile_options(CourseworkCpp PRIVATE /utf-8)
endif()