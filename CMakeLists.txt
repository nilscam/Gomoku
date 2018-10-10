cmake_minimum_required(VERSION 3.1)
project(IA)

set(CMAKE_CXX_STANDARD 17)

add_executable(pbrain-gradeAgo main.cpp algo/Board.cpp algo/Board.hpp PiskvorkInterface.cpp PiskvorkInterface.hpp algo/TreeNode.cpp algo/TreeNode.hpp)
