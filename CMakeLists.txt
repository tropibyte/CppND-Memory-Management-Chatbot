cmake_minimum_required(VERSION 3.11.3)

set(CMAKE_CXX_STANDARD 17)

project(Membot)

find_package(wxWidgets CONFIG REQUIRED)

file(GLOB project_SRCS src/*.cpp)

add_executable(membot WIN32 ${project_SRCS})
target_link_libraries(membot PRIVATE wx::core wx::base)
