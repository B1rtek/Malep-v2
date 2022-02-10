cmake_minimum_required(VERSION 3.20)
project(Malep_v2)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_PREFIX_PATH "C:\\Users\\skrze\\Documents\\SFML-2.5.1;D:\\Kody\\ExtLibs\\SFML\\SFML-2.5.1")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/Modules)

find_package(SFML 2 COMPONENTS system window graphics audio REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})