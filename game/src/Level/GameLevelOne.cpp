#include "Level/GameLevelOne.h"
#include "Enemy/Vanguard.h"
#include "framework/Actor.h"
#include "framework/World.h"
#include "player/PlayerSpaceship.h"

ly::GameLevelOne::GameLevelOne(Application* owner)
	:World{ owner }
{
	mTestPlayeSpaceship = SpawnActors<PlayerSpaceship>();
	mTestPlayeSpaceship.lock()->SetLocation(sf::Vector2f(600 / 2, 980 / 2));
	
	weak<Vanguard> testSpacesship = SpawnActors<Vanguard>();
	testSpacesship.lock()->SetLocation(sf::Vector2f{ 100.f, 50.f });
}
