cmake_minimum_required(VERSION 2.8.12)
project(testproject)




# https://www.guyrutenberg.com/2014/01/05/enabling-c11-c0x-in-cmake/
# because of: error: ‘std::function’ has not been declared
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()





# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(KF5CoreAddons)
find_package(KF5XmlGui)
find_package(KF5Service)
find_package(KF5Parts)

# Tell CMake to create the helloworld executable
add_executable(helloworld
    main.cpp
    mainwindow.cpp
    terminal.cpp
    #visualeventoverlay.cpp
    splitter.cpp
    session.cpp
    sessionstack.cpp
)

# Use the Widgets module from Qt 5.
target_link_libraries(
    helloworld
    Qt5::Core
    Qt5::Widgets
    KF5::CoreAddons
    KF5::XmlGui
    KF5::Service
    KF5::Parts
)
