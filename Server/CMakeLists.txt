# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

project ("Chess")

set(CMAKE_CXX_STANDARD 11)

# 包含库路径
set(LIBRARY_PATH ${PROJECT_BINARY_DIR}/bin)
set(EXECUTUBLE_PATH ${PROJECT_BINARY_DIR}/bin)

SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

# 包含子项目。
add_subdirectory ("src")
add_subdirectory ("lib")
