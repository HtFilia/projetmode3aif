cmake_minimum_required(VERSION 3.14)
project(projetmodpro)

set(CMAKE_CXX_STANDARD 14)

add_library(projetmodpro SHARED src/MonteCarlo.cpp include/MonteCarlo.h src/Option.cpp include/Option.h src/BlackScholesModel.cpp include/BlackScholesModel.h)