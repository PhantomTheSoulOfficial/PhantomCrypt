# CMakeList.txt: проект CMake для PhantomCrypt.

cmake_minimum_required(VERSION 3.20)

project(PhantomCrypt)

add_executable(PhantomCrypt
    PhantomCrypt.cpp
    PhantomCrypt.h
)

target_compile_features(PhantomCrypt PRIVATE cxx_std_20)