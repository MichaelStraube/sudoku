cmake_minimum_required(VERSION 3.11)

project(sudoku LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
add_compile_options(-Wall -Wextra)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(sudoku
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/mainwindow.ui
    src/sudoku.cpp
    src/sudoku.h
)

target_link_libraries(sudoku PRIVATE Qt6::Widgets)

install(TARGETS sudoku DESTINATION bin)
install(FILES share/sudoku.desktop DESTINATION share/applications)
install(FILES share/sudoku.png DESTINATION share/icons)
