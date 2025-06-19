#include <framework/World.h>
#include <framework/AssetManager.h>
#include <framework/Actor.h>

#include "game_framework/GameApplication.h"
#include "player/PlayerSpaceship.h"
#include "config.h"


ly::Application* GetApplication() {
	return new ly::GameApplication();
}

ly::GameApplication::GameApplication()
	:Application{ 600, 980, "Light Years", sf::Style::Close | sf::Style::Titlebar }
{
	AssetManager::GetInstance().SetAssetRootDir(GetResourceDir());
	weak<World> newWorld = LoadWorld<World>();
	newWorld.lock()->SpawnActors<Actor>();
	mTestPlayeSpaceship = newWorld.lock()->SpawnActors<PlayerSpaceship>();
	//mTestPlayeSpaceship.lock()->SetTexture("SpaceShooterRedux/PNG/playerShip1_blue.png");
	mTestPlayeSpaceship.lock()->SetLocation(sf::Vector2f(600 / 2, 980 / 2));
	//mTestPlayeSpaceship.lock()->SetRotation(180.f);
	mTestPlayeSpaceship.lock()->SetVelocity(sf::Vector2f{ 0.f, -200.f });
	counter = 0;
}

void ly::GameApplication::Tick(float deltaTime)
{
	/*
	counter += deltaTime;
	if (counter > 2.f) {//After 2s, the actor to be deleted
		if (!mTestPlayeSpaceship.expired()) {
			mDeleteActor.lock()->Destory();
		}
	}*/
}
