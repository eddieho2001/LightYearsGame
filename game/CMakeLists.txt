message(STATUS "game --> CMAKE_CURRENT_SOURCE_DIR : ${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(${LIGHTYEARS_GAME_EXE_NAME} 
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/game.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/game.cpp
	
)

target_include_directories(${LIGHTYEARS_GAME_EXE_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

#2. After fetch lib we also  need to setup the linking
target_link_libraries(${LIGHTYEARS_GAME_EXE_NAME} PUBLIC sfml-graphics)
target_link_libraries(${LIGHTYEARS_GAME_EXE_NAME} PUBLIC sfml-audio)
target_link_libraries(${LIGHTYEARS_GAME_EXE_NAME} PUBLIC sfml-main)
target_link_libraries(${LIGHTYEARS_GAME_EXE_NAME} PUBLIC sfml-network)
target_link_libraries(${LIGHTYEARS_GAME_EXE_NAME} PUBLIC sfml-system)
target_link_libraries(${LIGHTYEARS_GAME_EXE_NAME} PUBLIC sfml-window)

function(CopyLibToTarget LIB_NAME TARGET_NAME)
	add_custom_command(TARGET ${TARGET_NAME} 
	POST_BUILD
	COMMAND
	${CMAKE_COMMAND} -E copy_if_different
	$<TARGET_FILE:${LIB_NAME}>
	$<TARGET_FILE_DIR:${TARGET_NAME}>)
endfunction()

CopyLibToTarget(sfml-graphics ${LIGHTYEARS_GAME_EXE_NAME})
CopyLibToTarget(sfml-audio ${LIGHTYEARS_GAME_EXE_NAME})
CopyLibToTarget(sfml-main ${LIGHTYEARS_GAME_EXE_NAME})
CopyLibToTarget(sfml-network ${LIGHTYEARS_GAME_EXE_NAME})
CopyLibToTarget(sfml-system ${LIGHTYEARS_GAME_EXE_NAME})
CopyLibToTarget(sfml-window ${LIGHTYEARS_GAME_EXE_NAME})


