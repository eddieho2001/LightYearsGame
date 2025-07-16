cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 17)

#define variables
set(CURRENT_VERSION 0.1.0)
set(QUILL_LIB_NAME quill)

# define the project with name as LightYears
project(LightYears VERSION ${CURRENT_VERSION})

message(STATUS "project level --> Project Name           : ${PROJECT_NAME}")
message(STATUS "project level --> Project Current Version: ${CURRENT_VERSION}")
message(STATUS "project level --> external Libraries     : ${SFML_LIB_NAME}, ${QUILL_LIB_NAME}")
message(STATUS "project level --> CMAKE_PROJECT_NAME     : ${CMAKE_PROJECT_NAME}")
message(STATUS "project level --> PROJECT_SOURCE_DIR     : ${PROJECT_SOURCE_DIR}")
message(STATUS "project level --> PROJECT_BINARY_DIR     : ${PROJECT_BINARY_DIR}")

message(STATUS "task hository --> 0.0.1 v ---> setup game project structure 1) fetching sfml library 2) separate game loop to Application class that call by main.")
message(STATUS "task hository --> 0.0.4 v ---> split project as 1. engine library target 2. game executable target")
message(STATUS "task hository --> 0.0.5 v ---> using quill as logging library")
message(STATUS "task hository --> 0.0.6 v ---> add Box2D library handle collision detected and refactor outer CMakeLists.txt by move SFML to engine's CMakeList.txt")
message(STATUS "task hository --> 0.0.7 v ---> implement Delegate Class, using enable_shared_from_this in stdlib as the top parent")
message(STATUS "task hository --> 0.0.8 v ---> add and implement VFX effect when enemy have been hit by bullet that empty health")	
message(STATUS "task hository --> 0.0.9 v ---> add level concept in game")	
message(STATUS "task hository --> 0.1.0 v ---> add timer factility to engine which is very similar to scheduler so that we can use it for any time-based actions")	
message(STATUS "task hository --> 0.1.1 v ---> further refined TimerManager internally with TimerHandler for more safe.")
message(STATUS "task hository --> 0.1.2 v ---> Use timer class to control enemy attach pattern named concept is Stage")
message(STATUS "task hository --> 0.1.3 v ---> Add Vanguard, Vanguard Stage and Twin Blade emeny classes")
message(STATUS "task hository --> 0.1.4 v ---> Add Wait Stage as empty stage.")
# set all built output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#create variable for executable target name

set(LIGHTYEARS_GAME_EXE_NAME LightYears_${CURRENT_VERSION})
set(LIGHTYEARS_ENGINE_TARGET_NAME engine)
set(LIGHTYEARS_GAME_TARGET_NAME game)
# add sub projects
add_subdirectory(engine)
add_subdirectory(game)
add_subdirectory(quill)
 






