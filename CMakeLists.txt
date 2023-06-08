cmake_minimum_required(VERSION 3.25)
project(tagwalk1 C)

set(CMAKE_C_STANDARD 99)

add_executable(tagwalk1 main.c headerfile.h convolution.c sobel.c)
