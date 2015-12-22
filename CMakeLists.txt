cmake_minimum_required(VERSION 2.8.12)
project(kde-start)
# define source files
set(tutorial_SRCS
    main.cpp
)
# make them as executable
add_executable(tutorial ${tutorial_SRCS})
