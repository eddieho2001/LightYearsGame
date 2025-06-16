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
 )

target_include_directories(${LIGHTYEARS_ENGINE_TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${LIGHTYEARS_ENGINE_TARGET_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/${QUILL_LIB_NAME}/include)

#2. After fetch lib we also  need to setup the linking
target_link_libraries(${LIGHTYEARS_ENGINE_TARGET_NAME} PUBLIC sfml-graphics)
target_link_libraries(${LIGHTYEARS_ENGINE_TARGET_NAME} PUBLIC sfml-audio)
target_link_libraries(${LIGHTYEARS_ENGINE_TARGET_NAME} PUBLIC sfml-main)
target_link_libraries(${LIGHTYEARS_ENGINE_TARGET_NAME} PUBLIC sfml-network)
target_link_libraries(${LIGHTYEARS_ENGINE_TARGET_NAME} PUBLIC sfml-system)
target_link_libraries(${LIGHTYEARS_ENGINE_TARGET_NAME} PUBLIC sfml-window)
target_link_libraries(${LIGHTYEARS_ENGINE_TARGET_NAME} PUBLIC quill::quill)

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


