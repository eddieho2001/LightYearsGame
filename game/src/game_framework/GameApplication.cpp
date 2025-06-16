#include "game_framework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"

ly::Application* GetApplication(){
	return new ly::GameApplication();
}

ly::GameApplication::GameApplication() {
	weak<World> newWorld = RoadWorld<World>();
	newWorld.lock()->SpawnActors<Actor>();
	newWorld.lock()->SpawnActors<Actor>();
	newWorld.lock()->SpawnActors<Actor>();
}