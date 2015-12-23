cmake_minimum_required(VERSION 2.8.12)
#project(UsingFrameworksTutorial)
#
#find_package(
#    KF5Parts NO_MODULE
#    Qt5Widgets
#)
#
#set(tutorial_SRCS
#    main.cpp
#)
#add_executable(tutorial ${tutorial_SRCS})
#
#target_link_libraries(
#    tutorial
#    PRIVATE
#        KF5::Archive
#)
#
#target_link_libraries(
#    helloworld Qt5::Widgets
#)

project(testproject)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

# Tell CMake to create the helloworld executable
add_executable(helloworld main.cpp)

# Use the Widgets module from Qt 5.
target_link_libraries(helloworld Qt5::Widgets)

