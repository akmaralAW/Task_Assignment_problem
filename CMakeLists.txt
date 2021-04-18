cmake_minimum_required(VERSION 3.16)
project(ordonnancement)

set(CMAKE_CXX_STANDARD 14)
include_directories(include)
add_executable(ordonnancement
        src/ordonnancement.cpp
		src/tache.cpp
		src/tests_ordonnancement.cpp
        include/ordonnancement.hpp
        include/tache.hpp)

