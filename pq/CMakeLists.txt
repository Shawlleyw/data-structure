cmake_minimum_required(VERSION 3.2)
project(Demo)
aux_source_directory(. DIR_SRCS)
add_executable(Demo ${DIR_SRCS})