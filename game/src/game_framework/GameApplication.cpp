#include "game_framework/GameApplication.h"
#include "framework/World.h"

ly::Application* GetApplication(){
	return new ly::GameApplication();
}

ly::GameApplication::GameApplication() {
	RoadWorld<World>();
}