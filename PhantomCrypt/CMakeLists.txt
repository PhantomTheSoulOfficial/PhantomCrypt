# CMakeList.txt: проект CMake для PhantomCrypt.

cmake_minimum_required(VERSION 3.20)

project(PhantomCrypt)

set(CMAKE_PREFIX_PATH "C:/Qt/6.11.2/msvc2022_64")

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

add_executable(PhantomCrypt
    PhantomCrypt.cpp
    PhantomCrypt.h
    MainWindow.cpp
    MainWindow.h
    ImageView.cpp
    ImageView.h
)

target_compile_features(PhantomCrypt PRIVATE cxx_std_20)

target_link_libraries(PhantomCrypt PRIVATE
    Qt6::Widgets
)