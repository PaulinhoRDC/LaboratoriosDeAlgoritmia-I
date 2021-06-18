cmake_minimum_required(VERSION 3.13)
project(Projeto C)

set(CMAKE_C_STANDARD 99)

add_executable(Projeto main.c estado.c estado.h intepretador.c intepretador.h)