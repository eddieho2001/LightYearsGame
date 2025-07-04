#include "spaceship/Spaceship.h"
#include "framework/World.h"

ly::Spaceship::Spaceship(World* ptrOwner, const std::string& texturePath)
	:Actor{ ptrOwner , texturePath },
	mVelocity{}, 
	mHealthComp{100.f, 100.f}
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

void ly::Spaceship::Shoot()
{

}

void ly::Spaceship::BeginPlay()
{
	Actor::BeginPlay();
	SetEnablePhysics(true);
}


