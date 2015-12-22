cmake_minimum_required(VERSION 2.8.12)
project(kde-start)
# define source files
set(tutorial_SRCS
    my_lib.cpp
    main.cpp
)
# make them as executable
add_executable(tutorial ${tutorial_SRCS})
include_directories(headers)
