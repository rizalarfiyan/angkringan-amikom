cmake_minimum_required(VERSION 3.13)
project(angkringan_amikom)

FILE(GLOB SOURCE_FILES "./src/**/*.h" "./src/**/*.cpp" "./src/main.cpp")

add_executable(angkringan_amikom ${SOURCE_FILES})
