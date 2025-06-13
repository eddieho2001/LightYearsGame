message(STATUS "Sub Project/Target Name : ${LIGHTYEARS_GAME_TARGET_NAME} --> CMAKE_CURRENT_SOURCE_DIR : ${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(${LIGHTYEARS_GAME_TARGET_NAME} 
	${CMAKE_CURRENT_SOURCE_DIR}/include/game_framework/GameApplication.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/game_framework/GameApplication.cpp
 )

target_include_directories(${LIGHTYEARS_GAME_TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

#2. For the application, it not need to link the sfml libraries file again, it only linking the engine.lib is ok
target_link_libraries(${LIGHTYEARS_GAME_TARGET_NAME} PUBLIC ${LIGHTYEARS_ENGINE_TARGET_NAME})

function(CopyLibDirToTarget LIB_NAME TARGET_NAME)
	add_custom_command(TARGET ${TARGET_NAME} 
	POST_BUILD
	COMMAND
	${CMAKE_COMMAND} -E copy_directory
	$<TARGET_FILE_DIR:${LIB_NAME}>
	$<TARGET_FILE_DIR:${TARGET_NAME}>)
endfunction()

CopyLibDirToTarget(${LIGHTYEARS_ENGINE_TARGET_NAME} ${LIGHTYEARS_GAME_TARGET_NAME})



