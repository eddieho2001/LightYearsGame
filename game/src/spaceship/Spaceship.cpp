#include "spaceship/Spaceship.h"

ly::Spaceship::Spaceship(World* ptrOwner, std::string& p_strTexturePath)
	:Actor{ ptrOwner , p_strTexturePath },
	mVelocity{}
{

}

void ly::Spaceship::Tick(float deltaTime)
{
	Actor::Tick(deltaTime);
	AddLocationOffset(GetVelocity() * deltaTime);
}

void ly::Spaceship::SetVelocity(sf::Vector2f& newVelocity)
{
	mVelocity = newVelocity;
}


