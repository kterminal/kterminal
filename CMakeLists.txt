cmake_minimum_required(VERSION 2.8.12)
project(UsingFrameworksTutorial)

find_package(KF5Archive 5.15 REQUIRED)

set(tutorial_SRCS
    main.cpp
)
add_executable(tutorial ${tutorial_SRCS})

target_link_libraries(
    tutorial
    PRIVATE
        KF5::Archive
)

