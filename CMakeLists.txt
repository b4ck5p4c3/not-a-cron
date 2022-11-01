cmake_minimum_required(VERSION 3.14)

project(not-a-cron LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(not-a-cron
    3rdparty/qcron/src/qcron.cpp
    3rdparty/qcron/src/qcronfield.cpp
    3rdparty/qcron/src/qcronnode.cpp
    3rdparty/qcron/src/holiday.cpp
    main.cpp
)

target_include_directories(not-a-cron PRIVATE "3rdparty/qcron/src")
target_link_libraries(not-a-cron Qt${QT_VERSION_MAJOR}::Core)

install(TARGETS not-a-cron
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
