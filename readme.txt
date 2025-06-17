Source Repos: https://github.com/TutLeeUdemy/LightYears
Version 0.0.3:
 - Previous version 0.0.3 is completed: There most simple starting game project template

Version 0.0.4:
 - From 0.0.4 version I will split the game application as two part one is game itself and 
   the other part is the engine as static library.
 - root
    |
    |-game/
	    |-include/
		     |
			 |framework/
			     | - application.h
	    |-src
		   |
		   |- framework/
		         |- application.cpp
           | - main.cpp
        |- -CMakeLists.txt		   
	|-CMakeLists.txt
	 
	Will bcome as below:
 - root
    |
    |-game/
	    |-include/
		     |
			 |framework/
			     | - application.h
	    |-src
		   |
		   |- framework/
		         |- application.cpp
           | - main.cpp		  
	|-CMakeLists.txt	
	
	Step 1 : remove main.cpp in game/src/ & remove the main.cpp declaration in root/CMakeLists.txt
	Step 2 : add new file EntryPoint.h to game/include/
             add new file EntryPoint.cpp to game/src/ 
             The two file aim for as a template pattern for orginal main function 			 
	Step 3 : add two file to cmake command add_executable
             - we declare GetApplication() function as extern in EntryPoint.h which return Application object for user.
             - user should implements this function.
			 add main function in EntryPoint.cpp
	Step 4 : rename orginal game directory to engine
             create new folder name game under the root directory and copy the engine/CMakeLists.txt to game/CMakeLists.txt
			 change the engine/CMakeLists.txt add_executable to add_library
			 specified the target library as STATIC linking
			 then go to game folder:
			   a ) create include folder and inside this folder create game_framework folder
			   b ) create src folder and then create game_framework folder inside it.
			   c ) open and edit CMakeLists.txt file for the game sub project.
			       - change the target_link_libraries to linking to the engine library
				   - change the copy function CopyLibToTarget to CopyLibDirToTarget
				   - change the [-E copy_if_different] to [-E copy_directory]
	               - change the [$<TARGET_FILE:${LIB_NAME}>] to [$<TARGET_FILE_DIR:${LIB_NAME}>]
				   - change CopyLibToTarget(sfml-graphics ${LIGHTYEARS_ENGINE_TARGET_NAME}) to CopyLibDirToTarget(${LIGHTYEARS_ENGINE_TARGET_NAME} ${LIGHTYEARS_GAME_TARGET_NAME})
				     and remove the other
	
Version 0.0.5: add quill as logging library
               1 ) get quill library : git clone https://github.com/odygrd/quill.git
			   2 ) add set(QUILL_LIB_NAME quill) command to root CMakeLists.txt
			   3 ) add add_subdirectory(quill) command to root CMakeLists.txt
			   4 ) add target_include_directories(${LIGHTYEARS_ENGINE_TARGET_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/${QUILL_LIB_NAME}/include) command to engine/CMakeLists.txt 
			       for engine library target can reference quill include files
			   5 ) add target_link_libraries(${LIGHTYEARS_ENGINE_TARGET_NAME} PUBLIC quill::quill) command to engine/CMakeLists.txt 
			       for engine library target can linking quill
			   6 ) Add the follow code to EntryPoint.cpp main() function to initial the configuration & quill log backend server
						
						#include<quill/Backend.h>
						#include<quill/Frontend.h>
						#include<quill/LogMacros.h>
						#include<quill/Logger.h>
						#include<quill/sinks/ConsoleSink.h>
						#include <quill/std/Array.h>
						
						...
						
						quill::BackendOptions options;
						options.enable_yield_when_idle = true;
						options.transit_event_buffer_initial_capacity = 64;  // Reduce initial buffer size
						options.transit_events_soft_limit = 2048;  // Lower soft limit
						options.transit_events_hard_limit = 8192;  // Reduce max buffer size
	
						quill::Backend::start(options);
						auto console_sink = quill::Frontend::create_or_get_sink<quill::ConsoleSink>("sink_id_1");
						quill::Logger* logger = quill::Frontend::create_or_get_logger("root", std::move(console_sink));
						logger->set_log_level(quill::LogLevel::TraceL3);

						LOG_INFO(logger, "Start Logging in Entry");
			
				
	
	