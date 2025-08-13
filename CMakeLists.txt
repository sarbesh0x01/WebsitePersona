cmake_minimum_required(VERSION 3.16)
project(MyProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add your include folder
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(myweb src/main.cpp)
