#include "player/PlayerSpaceship.h"
#include "weapon/BulletShooter.h"
#include "SFML/Graphics.hpp"
#include <framework/MathUtility.h>


ly::PlayerSpaceship::PlayerSpaceship(World* ptrOwner, const std::string& texturePath)
	:Spaceship{ ptrOwner , texturePath }, 
	 mDisplacementInput{}, 
	mfSpeed{200.f}, 
	mShooter{ new BulletShooter{this, 0.1f} }
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
		mDisplacementInput.y = -1.f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		mDisplacementInput.y = 1.f;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		mDisplacementInput.x = -1.f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		mDisplacementInput.x = 1.f;
	}

	
	/*
	 * Control the  
	 */
	ClampInputOnEdge();
	/*
		Becuase the move velocity depend on the x, y component of the move vector, we want the two component scale same rate
		after normalized the player will move same speed with all direction.
	*/
	NormalizeInput();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		Shoot();
	}

}

void ly::PlayerSpaceship::ConsumeInput(float deltaTime)
{
	SetVelocity(mDisplacementInput * mfSpeed);
	//After the consume, reset the mMoveInput to zero
	mDisplacementInput.x = 0.f;
	mDisplacementInput.y = 0.f;

}

void ly::PlayerSpaceship::NormalizeInput()
{
	Normalize(mDisplacementInput);
}

void ly::PlayerSpaceship::ClampInputOnEdge()
{
	sf::Vector2f curLoc = GetLocation();
	//Check if the postion x is on 0, and player still want to move left, set mMoveInput.x = 0
	if (curLoc.x < epsilon && mDisplacementInput.x == -1) {
		mDisplacementInput.x = 0.f;
	}

	if (curLoc.x > GetWindowSize().x && mDisplacementInput.x == 1.f) {
		mDisplacementInput.x = 0.f;
	}

	if (curLoc.y < epsilon && mDisplacementInput.y == -1) {
		mDisplacementInput.y = 0.f;
	}

	if (curLoc.y > GetWindowSize().y && mDisplacementInput.y == 1.f) {
		mDisplacementInput.y = 0.f;
	}
}

void ly::PlayerSpaceship::Shoot()
{
	if (mShooter) {
		mShooter->Shoot();
	}
}



