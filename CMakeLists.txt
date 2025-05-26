cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 17)

# define the project with name as LightYears
project(LightYears VERSION 1.0.0)
message(STATUS "project level --> PROJECT_NAME: ${PROJECT_NAME}")
message(STATUS "project level --> CMAKE_PROJECT_NAME : ${CMAKE_PROJECT_NAME}")
message(STATUS "project level --> PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
message(STATUS "project level --> PROJECT_BINARY_DIR : ${PROJECT_BINARY_DIR}")

# set all built output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#create variable for executable target name
set(LIGHTYEARS_GAME_EXE_NAME LightYears)


# add sub projects
# add_subdirectory(engine)
add_subdirectory(game) 

