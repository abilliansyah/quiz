cmake_minimum_required(VERSION 3.10)
project(QuizGame)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tambahkan semua source files
add_executable(QuizGame 
    quiz_game.cpp
    # tambahkan file cpp lainnya jika ada
)

# Jika menggunakan library eksternal
# find_package(...)
# target_link_libraries(...)