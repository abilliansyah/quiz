cmake_minimum_required(VERSION 3.1.0)

project(quiz-game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(quiz-game
    src/main.cpp
    src/mainwindow.cpp
    src/quiz_game.cpp
)

target_link_libraries(quiz-game Qt5::Widgets)