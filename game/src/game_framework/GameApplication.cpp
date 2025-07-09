#include <framework/AssetManager.h>
#include "config.h"
#include "Level/GameLevelOne.h"
#include "game_framework/GameApplication.h"



ly::Application* GetApplication() {
	return new ly::GameApplication();
}


ly::GameApplication::GameApplication()
	:Application{ 600, 980, "Light Years", sf::Style::Close | sf::Style::Titlebar }
{
	AssetManager::GetInstance().SetAssetRootDir(GetResourceDir());
	weak<GameLevelOne> newWorld = LoadWorld<GameLevelOne>();
	
}

