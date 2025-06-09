cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 17)

# define the project with name as LightYears
project(LightYears VERSION 0.0.2)
message(STATUS "project level --> PROJECT_NAME: ${PROJECT_NAME}")
message(STATUS "project level --> CMAKE_PROJECT_NAME : ${CMAKE_PROJECT_NAME}")
message(STATUS "project level --> PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
message(STATUS "project level --> PROJECT_BINARY_DIR : ${PROJECT_BINARY_DIR}")

# set all built output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#create variable for executable target name

#1. In order to use external library, we using cmake fetch content feature
include(FetchContent)
set(SFML_LIB_NAME SFML)
FetchContent_Declare(
	${SFML_LIB_NAME} 
	GIT_REPOSITORY https://github.com/SFML/SFML.git
	GIT_TAG 2.6.1
	GIT_SHALLOW FALSE)
FetchContent_MakeAvailable(${SFML_LIB_NAME})

set(LIGHTYEARS_GAME_EXE_NAME LightYears)
#set(LIGHTYEARS_ENGINE_TARGET_NAME engine)
#set(LIGHTYEARS_GAME_TARGET_NAME game)
# add sub projects
# add_subdirectory(engine)
add_subdirectory(game) 






