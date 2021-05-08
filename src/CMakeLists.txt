cmake_minimum_required(VERSION 3.17) 
 
project(screen)  

set(CMAKE_CXX_STANDARD 14) 

include_directories(../include)


add_library(screen STATIC screen.cpp) # 生成静态库

