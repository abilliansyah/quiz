cmake_minimum_required(VERSION 3.10)
project(QuizGame)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tambahkan source files
add_executable(QuizGame 
    src/main.cpp
    src/quiz_game.cpp
)

# Copy resources ke direktori build
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})
