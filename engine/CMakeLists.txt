message(STATUS "Sub Project/Target Name : ${LIGHTYEARS_ENGINE_TARGET_NAME} --> CMAKE_CURRENT_SOURCE_DIR : ${CMAKE_CURRENT_SOURCE_DIR}")
add_library(${LIGHTYEARS_ENGINE_TARGET_NAME} STATIC 
	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/application.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/application.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/EntryPoint.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/EntryPoint.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Core.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Core.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/World.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/World.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Actor.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Actor.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Object.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Object.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/AssetManager.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/AssetManager.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/MathUtility.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/MathUtility.cpp

  "src/framework/MathUtility.cpp")

target_include_directories(${LIGHTYEARS_ENGINE_TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${LIGHTYEARS_ENGINE_TARGET_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/${QUILL_LIB_NAME}/include)

#1. In order to use external library, we using cmake fetch content feature
#   Refactor during include Box2D library 
set(SFML_LIB_NAME SFML)
include(FetchContent)
FetchContent_Declare(
	${SFML_LIB_NAME} 
	GIT_REPOSITORY https://github.com/SFML/SFML.git
	GIT_TAG 2.6.1
	GIT_SHALLOW FALSE)
FetchContent_MakeAvailable(${SFML_LIB_NAME})

#2. After fetch lib we also  need to setup the linking
target_link_libraries(${LIGHTYEARS_ENGINE_TARGET_NAME} PUBLIC sfml-graphics)
target_link_libraries(${LIGHTYEARS_ENGINE_TARGET_NAME} PUBLIC sfml-audio)
target_link_libraries(${LIGHTYEARS_ENGINE_TARGET_NAME} PUBLIC sfml-main)
target_link_libraries(${LIGHTYEARS_ENGINE_TARGET_NAME} PUBLIC sfml-network)
target_link_libraries(${LIGHTYEARS_ENGINE_TARGET_NAME} PUBLIC sfml-system)
target_link_libraries(${LIGHTYEARS_ENGINE_TARGET_NAME} PUBLIC sfml-window)
target_link_libraries(${LIGHTYEARS_ENGINE_TARGET_NAME} PUBLIC quill::quill)

#include the Box2D library by CMake's Fetch Content command
set(BOX2D_LIB_NAME Box2D)
FetchContent_Declare(
	${BOX2D_LIB_NAME} 
	GIT_REPOSITORY https://github.com/erincatto/box2d.git
	GIT_TAG v2.4.1
	GIT_SHALLOW FALSE)
FetchContent_MakeAvailable(${BOX2D_LIB_NAME})

target_link_libraries(${LIGHTYEARS_ENGINE_TARGET_NAME} PUBLIC box2d)

function(CopyLibToTarget LIB_NAME TARGET_NAME)
	add_custom_command(TARGET ${TARGET_NAME} 
	POST_BUILD
	COMMAND
	${CMAKE_COMMAND} -E copy_if_different
	$<TARGET_FILE:${LIB_NAME}>
	$<TARGET_FILE_DIR:${TARGET_NAME}>)
endfunction()

CopyLibToTarget(sfml-graphics ${LIGHTYEARS_ENGINE_TARGET_NAME})
CopyLibToTarget(sfml-audio ${LIGHTYEARS_ENGINE_TARGET_NAME})
CopyLibToTarget(sfml-main ${LIGHTYEARS_ENGINE_TARGET_NAME})
CopyLibToTarget(sfml-network ${LIGHTYEARS_ENGINE_TARGET_NAME})
CopyLibToTarget(sfml-system ${LIGHTYEARS_ENGINE_TARGET_NAME})
CopyLibToTarget(sfml-window ${LIGHTYEARS_ENGINE_TARGET_NAME})
CopyLibToTarget(box2d ${LIGHTYEARS_ENGINE_TARGET_NAME})



