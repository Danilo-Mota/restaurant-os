cmake_minimum_required(VERSION 3.22)
project(restaurante_app)
set(CMAKE_CXX_STANDARD 11)
add_executable(restaurante_app main.cpp
        restaurante.cpp
        restaurante.h
        chef.cpp
        chef.h)
