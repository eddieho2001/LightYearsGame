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

#1. In order to use external library, we using cmake fetch content feature
include(FetchContent)
set(SFML_LIB_NAME SFML)
FetchContent_Declare(
	${SFML_LIB_NAME} 
	GIT_REPOSITORY https://github.com/SFML/SFML.git
	GIT_TAG 2.5.1
	GIT_SHALLOW FALSE)
FetchContent_MakeAvailable(${SFML_LIB_NAME})

#2. After fetch lib we also  need to setup the linking
target_link_libraries(${LIGHTYEARS_GAME_EXE_NAME} PUBLIC sfml-graphics)
target_link_libraries(${LIGHTYEARS_GAME_EXE_NAME} PUBLIC sfml-audio)
target_link_libraries(${LIGHTYEARS_GAME_EXE_NAME} PUBLIC sfml-main)
target_link_libraries(${LIGHTYEARS_GAME_EXE_NAME} PUBLIC sfml-network)
target_link_libraries(${LIGHTYEARS_GAME_EXE_NAME} PUBLIC sfml-system)
target_link_libraries(${LIGHTYEARS_GAME_EXE_NAME} PUBLIC sfml-window)




