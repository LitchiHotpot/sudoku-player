cmake_minimum_required(VERSION 3.23)
project(suduku_player)

set(CMAKE_CXX_STANDARD 14)

add_executable(suduku_player main.cpp DLXNode.cpp DLXNode.h DLXSolver.cpp DLXSolver.h SudokuSolver.cpp SudokuSolver.h SudokuGenerator.cpp SudokuGenerator.h DLXGenerator.cpp DLXGenerator.h)
