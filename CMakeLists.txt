cmake_minimum_required(VERSION 3.13)
project(angkringan_amikom)
set(CMAKE_CXX_STANDARD 14)

FILE(GLOB SOURCE_FILES "./src/main.cpp" "./src/**/*.h")

add_executable(angkringan_amikom ${SOURCE_FILES})
