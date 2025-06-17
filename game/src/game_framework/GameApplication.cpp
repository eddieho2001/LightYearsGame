#include "game_framework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"

ly::Application* GetApplication(){
	return new ly::GameApplication();
}

ly::GameApplication::GameApplication()
	:Application{600, 980, "Light Years", sf::Style::Close|sf::Style::Titlebar}
{
	weak<World> newWorld = LoadWorld<World>();
	newWorld.lock()->SpawnActors<Actor>();
	mDeleteActor = newWorld.lock()->SpawnActors<Actor>();
	mDeleteActor.lock()->SetTexture("assets\\SpaceShooterRedux\\PNG\\playerShip1_blue.png");
	counter = 0;
}

void ly::GameApplication::Tick(float deltaTime)
{
	counter += deltaTime;
	if (counter > 2.f) {//After 2s, the actor to be deleted
		if (!mDeleteActor.expired()) {
			mDeleteActor.lock()->Destory();
		}
	}
}
	