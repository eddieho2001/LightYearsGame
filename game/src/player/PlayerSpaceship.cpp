#include "player/PlayerSpaceship.h"
#include "SFML/Graphics.hpp"

ly::PlayerSpaceship::PlayerSpaceship(World* ptrOwner, const std::string& texturePath)
	:Spaceship{ ptrOwner , texturePath }, mMoveInput{}, mfSpeed{200.f}
{
}

//The Tick function is same as the update functionality
void ly::PlayerSpaceship::Tick(float deltaTime)
{
	Spaceship::Tick(deltaTime);
	HandlingInput();
	ConsumeInput(deltaTime);
}

void ly::PlayerSpaceship::HandlingInput()
{
	//If we not use if else for the oppose key detected, it allow diagonal move 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		mMoveInput.y += -1.f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		mMoveInput.y += 1.f;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		mMoveInput.x += -1.f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		mMoveInput.x += 1.f;
	}
}

void ly::PlayerSpaceship::ConsumeInput(float deltaTime)
{
	SetVelocity(mMoveInput * mfSpeed);
	//After the consume, reset the mMoveInput to zero
	mMoveInput.x = 0.f;
	mMoveInput.y = 0.f;

}


