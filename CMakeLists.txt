cmake_minimum_required(VERSION 2.8.12)
project(testproject)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
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
    visualeventoverlay.cpp
    splitter.cpp
    session.cpp
    sessionstack.cpp
)

# Use the Widgets module from Qt 5.
target_link_libraries(
    helloworld
    Qt5::Widgets
    KF5::CoreAddons
    KF5::XmlGui
    KF5::Service
    KF5::Parts
)
