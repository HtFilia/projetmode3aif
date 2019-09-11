cmake_minimum_required(VERSION 3.14)
project(projetmodpro)

set(CMAKE_CXX_STANDARD 14)

add_library(projetmodpro STATIC ../src/MonteCarlo.cpp ../src/MonteCarlo.h ../src/Option.cpp ../src/Option.h ../src/BlackScholesModel.cpp ../src/BlackScholesModel.h)