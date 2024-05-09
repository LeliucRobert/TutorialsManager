cmake_minimum_required(VERSION 3.27)
project(oop_a4_5_LeliucRobert)
set(CMAKE_PREFIX_PATH "C://Qt//6.7.1//mingw_64")
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include_directories(.)

include_directories("C://Program Files//MySQL//MySQL Server 8.0//include")
link_directories("C://Program Files//MySQL//MySQL Server 8.0//lib")

find_package(Qt6 COMPONENTS Widgets REQUIRED)
add_executable(oop_a4_5_LeliucRobert
        main.cpp
        UI.cpp
        UI.h
        Repository.cpp
        DynamicArray.cpp
        Domain.cpp
        Domain.h
        Controller.h
        Controller.cpp
        Tests.cpp
        Tests.h
        Exceptions.cpp
        Exceptions.h
        Validator.h
        Validator.cpp
        CSV_Repository.h
        CSV_Repository.cpp
        HTML_Repository.h
        HTML_Repository.cpp
        SQL_Repository.h
        SQL_Repository.cpp
        GUI.cpp
        GUI.h
        GUI.h)

target_link_libraries(oop_a4_5_LeliucRobert
        Qt6::Widgets
        libmysql
        )

