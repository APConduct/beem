cmake_minimum_required(VERSION 3.28)
project(beem)

set(CMAKE_CXX_STANDARD 20)


add_library(beem STATIC src/beem.cpp include/beem.hpp)
