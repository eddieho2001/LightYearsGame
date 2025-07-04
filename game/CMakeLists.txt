message(STATUS "Sub Project/Target Name : ${LIGHTYEARS_GAME_TARGET_NAME} --> CMAKE_CURRENT_SOURCE_DIR : ${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(${LIGHTYEARS_GAME_TARGET_NAME} 
	${CMAKE_CURRENT_SOURCE_DIR}/include/game_framework/GameApplication.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/game_framework/GameApplication.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/spaceship/Spaceship.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/spaceship/Spaceship.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/player/PlayerSpaceship.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/player/PlayerSpaceship.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/weapon/Shooter.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/weapon/Shooter.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/weapon/BulletShooter.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/weapon/BulletShooter.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/weapon/Bullet.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/weapon/Bullet.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/gameplay/HealthComponent.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/gameplay/HealthComponent.cpp
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


#Handle relative path for game assets 
set(ASSET_FOLDER_NAME "assets")
set(ASSET_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${ASSET_FOLDER_NAME}")

add_custom_command(
	TARGET ${LIGHTYEARS_GAME_TARGET_NAME}
	POST_BUILD
	COMMAND
	${CMAKE_COMMAND} -E copy_directory
	${ASSET_SRC_DIR}
	$<TARGET_FILE_DIR:${LIGHTYEARS_GAME_TARGET_NAME}>/${ASSET_FOLDER_NAME}
)

message(STATUS "${LIGHTYEARS_GAME_TARGET_NAME} -  Copied assets from ${ASSET_SRC_DIR} to ${LIGHTYEARS_GAME_TARGET_NAME}/${ASSET_FOLDER_NAME}")
message(STATUS "${LIGHTYEARS_GAME_TARGET_NAME} -  Modified config.h.in --> config.h for assets resources...")

configure_file(
	"config.h.in"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/config.h" ESCAPE_QUOTES
)
