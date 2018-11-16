cmake_minimum_required(VERSION 3.12)
project(DSPtask)

set(CMAKE_CXX_STANDARD 17)

add_executable(DSPtask main.cpp Complex.h cmake-build-debug/ComplexDeclare.h)